#include "Interceptor.hpp"
#include "Shell.hpp"
#include <cstring>
#include <iostream>
#include <unistd.h>

Interceptor::Interceptor(Shell &aShell) : shell_{aShell} {}

bool Interceptor::intercept(const std::vector<std::string> &inputTokens) {
  if (inputTokens[0] == "cd") {
    if (inputTokens.size() < 2) {
      std::cout << "Provide the directory to cd into\n";
    } else if (chdir(inputTokens[1].c_str()) != 0) {
      std::string err = strerror(errno);
      std::cout << "Cannot change the directory with error: " << err << "\n";
    }
  } else if (inputTokens[0] == "exit") {
    shell_.killAllBackgroundProcesses();
    exit(0);
  } else {
    return false;
  }
  return true;
}

bool Interceptor::checkIfSupported(const std::string &operation) {
  if (supportedOps_.find(std::string{operation}) == supportedOps_.end()) {
    return false;
  }
  return true;
}
