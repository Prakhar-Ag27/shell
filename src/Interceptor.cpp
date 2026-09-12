#include "Interceptor.hpp"
#include "Shell.hpp"
#include <cstring>
#include <iostream>
#include <unistd.h>

Interceptor::Interceptor(Shell &aShell) : shell_{aShell} {};

bool Interceptor::intercept(char *const *inputTokens) {
  if (strcmp(inputTokens[0], "cd") == 0) {
    if (chdir(inputTokens[1]) != 0) {
      std::string err = strerror(errno);
      std::cout << "Cannot change the directory with error: " << err << "\n";
    }
  } else if (strcmp(inputTokens[0], "exit") == 0) {
    shell_.killAllBackgroundProcesses();
    exit(0);
  } else {
    return false;
  }
  return true;
}

bool Interceptor::checkIfSupported(char *const operation) {
  if (supportedOps_.find(std::string{operation}) == supportedOps_.end()) {
    return false;
  }
  return true;
}
