#include "Interceptor.hpp"
#include <cstring>
#include <iostream>
#include <unistd.h>

Interceptor::Interceptor() : supportedOps_{"cd", "exit"}{};

bool Interceptor::intercept(char *const *inputTokens) {
  if (strcmp(inputTokens[0], "cd") == 0) {
    if (chdir(inputTokens[1]) != 0) {
      std::string err = strerror(errno);
      std::cout << "Cannot change the directory with error: " << err << "\n";
    }
    return true;
  } else if (strcmp(inputTokens[0], "exit") == 0) {
    exit(0);
    //need not worry about freeing memory here since OS will automatically reclaim the memory
  }
  return true;
}

bool Interceptor::checkIfSupported(char *const operation) {
  if (supportedOps_.find(std::string{operation}) == supportedOps_.end()) {
    return false;
  }
  return true;
}
