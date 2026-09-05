#include "Shell.hpp"
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <string>
#include <sys/wait.h>
#include <unistd.h>

int main() {
  constexpr char shellPrompt = '$';
  Shell shell_;
  while (true) {
    std::cout << shellPrompt << " ";
    std::string input;
    std::getline(std::cin, input, '\n');
    pid_t p_id = fork();
    if (p_id == -1) {
      std::cout << "Shell Error. Please Retry \n";
    } else if (p_id == 0) {
      shell_.execute(input);
      _exit(1);
    } else {
      int status;
      waitpid(p_id, &status, 0);
      int exitStatus = WEXITSTATUS(status);
      if (WIFEXITED(status)) {
        std::cout << "Failed to execute\n";
      }
    }
  }
}
