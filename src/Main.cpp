#include "Shell.hpp"
#include "Utils.hpp"
#include <cstdio>
#include <iostream>
#include <string>
#include <sys/wait.h>
#include <unistd.h>

int main() {
  char shellPrompt = '$';
  Shell shell_;
  while (true) {
    std::cout << getCurrentWorkingDirectory() << " " << shellPrompt << " ";
    std::string input;
    std::getline(std::cin, input, '\n');
    char * const * tokens = tokenize_on_spaces(input);
    Interceptor interceptor_;
    if(interceptor_.checkIfSupported(tokens[0])) {
        interceptor_.intercept(tokens);
        continue;
    }
    pid_t p_id = fork();
    if (p_id == -1) {
      std::cout << "Shell Error. Please Retry \n";
    } else if (p_id == 0) {
      shell_.execute(tokenize_on_spaces(input));
      _exit(1);
    } else {
      int status;
      waitpid(p_id, &status, 0);
      if (WIFEXITED(status)) {
        int exitStatus = WEXITSTATUS(status);

        if (exitStatus != 0) {
          std::cout << "Process failed with code " << exitStatus << '\n';
        }
      }
    }
  }
}
