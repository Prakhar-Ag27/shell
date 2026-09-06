#include "Interceptor.hpp"
#include <cstring>
#include <iostream>
#include <unistd.h>

Interceptor::Interceptor() : supportedOps_{"cd"}{};

bool Interceptor::intercept(char *const *inputTokens) {
  if (strcmp(inputTokens[0], "cd") == 0) {
    if (chdir(inputTokens[1]) != 0) {
      std::string err = strerror(errno);
      std::cout << "Cannot change the directory with error: " << err << "\n";
      return false;
    }
    return true;
  }
  return false;
}

bool Interceptor::checkIfSupported(char *const operation) {
  if (supportedOps_.find(std::string{operation}) == supportedOps_.end()) {
    return false;
  }
  return true;
}
