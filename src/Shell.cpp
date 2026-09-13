#include "Shell.hpp"
#include "Parser.hpp"
#include "Tokenize.hpp"
#include "Utils.hpp"
#include <algorithm>
#include <csignal>
#include <cstdlib>
#include <iostream>
#include <string>
#include <sys/wait.h>
#include <unistd.h>
#include <vector>
#include <cerrno>

Shell::Shell(char prompt) : shellPrompt_(prompt), interceptor_{*this} {};

void Shell::run() {
  while (true) {
    std::cout << getCurrentWorkingDirectory() << " " << shellPrompt_ << " ";
    std::string input;
    std::getline(std::cin, input, '\n');

    std::vector<std::vector<std::string>> commands = parseInput(input);

    bool isMultiMode =
        input.length() > 0 && (commands.size() > 1 || commands[0].size() > 1);

    if (isMultiMode && !checkInput(commands)) {
      std::cout << "Cannot use bg process while having multiple processes.\n";
      continue;
    };

    if (isMultiMode) {
      executeMultiMode(commands);
    } else {
      executeSingleMode(input);
    }
  }
}

void Shell::execute(const std::vector<std::string> &inputTokens) {
  if (inputTokens.empty()) {
    std::cout << "Please provide a program to run.\n";
    return;
  }
  execvp(inputTokens[0].c_str(), getCStringVector(inputTokens));
}

bool Shell::checkIfBackgorundProcess(std::string input) {
  if (input.length() > 1 && input[input.length() - 1] == '$' &&
      input[input.length() - 2] == ' ') {
    return true;
  }
  return false;
}

void Shell::waitOnAllProcesses() {
  while (true) {
    for (auto it = backgroundProcess_.begin();
         it != backgroundProcess_.end();) {
      pid_t x = *it;
      int status;

      pid_t result = waitpid(x, &status, WNOHANG);

      if (result == x) {
        if (WIFEXITED(status)) {
          int exitStatus = WEXITSTATUS(status);

          if (exitStatus != 0) {
            std::cout << "Background Process with p_id:" << x
                      << " failed with code " << exitStatus << '\n';
          } else {
            std::cout << "Successfully executed background process with p_id: "
                      << x << '\n';
          }
        } else if (WIFSIGNALED(status)) {
          std::cout << "Background Process with p_id:" << x
                    << " terminated by signal " << WTERMSIG(status) << '\n';
        }

        it = backgroundProcess_.erase(it);
      } else {
        ++it;
      }
    }

    if (foregroundProcess_ == -1) {
      break;
    }

    int status;
    pid_t result = waitpid(foregroundProcess_, &status, WNOHANG);

    if (result == foregroundProcess_) {
      if (WIFEXITED(status)) {
        int exitStatus = WEXITSTATUS(status);

        if (exitStatus != 0) {
          std::cout << "Process failed with code " << exitStatus << '\n';
        }
      } else if (WIFSIGNALED(status)) {
        std::cout << "Process terminated by signal " << WTERMSIG(status)
                  << '\n';
      }
      foregroundProcess_ = -1;
      break;
    }
  }
}

void Shell::killAllBackgroundProcesses() {
  if (bgProcessGroup > 1) {
    kill(-bgProcessGroup, SIGKILL);
  }
  for (pid_t pid : backgroundProcess_) {
    waitpid(pid, nullptr, 0);
  }
  backgroundProcess_.clear();
  bgProcessGroup = -1;
}

void Shell::installSigKillHandler() {
  struct sigaction sa{};
  sa.sa_handler = [](int signal) {};
  sigemptyset(&sa.sa_mask);
  sa.sa_flags = SA_RESTART;

  sigaction(SIGINT, &sa, nullptr);
}

bool Shell::checkInput(const std::vector<std::vector<std::string>> &input) {
  bool isValid = true;
  int count = 0;
  std::for_each(input.begin(), input.end(),
                [&](const std::vector<std::string> &commands) {
                  for (auto &command : commands) {
                    isValid = isValid && !checkIfBackgorundProcess(command);
                    count++;
                  }
                });
  return isValid && count > 0;
}

void Shell::executeSingleMode(std::string input) {
  bool isBgProcess = checkIfBackgorundProcess(input);

  if (isBgProcess) {
    input = input.substr(0, input.size() - 2);
  }

  std::vector<std::string> tokens = tokenize_on_spaces(input);
  if (tokens.size() > 0 && interceptor_.checkIfSupported(tokens[0])) {
    interceptor_.intercept(tokens);
    return;
  }

  pid_t p_id = fork();
  if (p_id == -1) {
    std::cout << "Shell Error. Please Retry \n";
    return;
  }
  if (!isBgProcess) {
    foregroundProcess_ = p_id;
  } else {
    bool groupIsStale =
        bgProcessGroup > 1 && kill(-bgProcessGroup, 0) == -1 && errno == ESRCH;
    if (bgProcessGroup == -1 || groupIsStale) {
      bgProcessGroup = p_id;
    }
    setpgid(p_id, bgProcessGroup);
    backgroundProcess_.insert(p_id);
  }
  if (p_id == 0) {
    execute(tokens);
    _exit(1);
  } else {
    waitOnAllProcesses();
  }
}

void Shell::executeMultiMode(
    const std::vector<std::vector<std::string>> &inputs) {
  for (auto &commands : inputs) {
    bool doBreak = false;
    for (std::string command : commands) {
      std::vector<std::string> tokens = tokenize_on_spaces(command);
      if (tokens.size() > 0 && interceptor_.checkIfSupported(tokens[0])) {
        interceptor_.intercept(tokens);
        continue;
      }
      pid_t p_id = fork();
      if (p_id == -1) {
        std::cout << "Shell Error. Please Retry \n";
        doBreak = true;
        break;
      }
      if (p_id == 0) {
        execute(tokens);
        _exit(1);
      } else {
        foregroundProcessesInMultiMode_.insert(p_id);
      }
    }
    for (auto &fp_id : foregroundProcessesInMultiMode_) {
      int status;
      pid_t result = waitpid(fp_id, &status, 0);
      if (result == fp_id) {
        if (WIFEXITED(status)) {
          int exitStatus = WEXITSTATUS(status);

          if (exitStatus != 0) {
            std::cout << "Process failed with code " << exitStatus << '\n';
          }
        } else if (WIFSIGNALED(status)) {
          std::cout << "Process terminated by signal " << WTERMSIG(status)
                    << '\n';
        }
      }
    }
    foregroundProcessesInMultiMode_.clear();
    if (doBreak) {
      break;
    }
  }
}
