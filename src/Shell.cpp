#include "Shell.hpp"
#include "Tokenize.hpp"
#include "Utils.hpp"
#include <cstdlib>
#include <iostream>
#include <sys/wait.h>
#include <unistd.h>
#include <vector>

Shell::Shell(char prompt) : shellPrompt_(prompt), interceptor_{*this} {};

void Shell::run() {
  while (true) {
    std::cout << getCurrentWorkingDirectory() << " " << shellPrompt_ << " ";
    std::string input;
    std::getline(std::cin, input, '\n');

    bool isBgProcess = checkIfBackgorundProcess(input);

    if (isBgProcess) {
      input = input.substr(0, input.size() - 2);
    }

    std::vector<std::string> tokens = tokenize_on_spaces(input);
    if (tokens.size() > 0 && interceptor_.checkIfSupported(tokens[0])) {
      interceptor_.intercept(tokens);
      continue;
    }

    pid_t p_id = fork();
    if (p_id == -1) {
      std::cout << "Shell Error. Please Retry \n";
      continue;
    }
    if (!isBgProcess) {
      foregroundProcess_ = p_id;
    } else {
      backgroundProcess_.insert(p_id);
    }
    if (p_id == 0) {
      execute(tokens);
      _exit(1);
    } else {
      waitOnAllProcesses();
    }
    foregroundProcess_ = -1;
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
      break;
    }
  }
}

void Shell::killAllBackgroundProcesses() {
  for (pid_t pid : backgroundProcess_) {
    kill(pid, SIGKILL);
  }
  for (pid_t pid : backgroundProcess_) {
    waitpid(pid, nullptr, 0);
  }
  backgroundProcess_.clear();
}
