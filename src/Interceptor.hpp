#pragma once
#include <set>
#include <string>

class Shell;

class Interceptor {
public:
  Interceptor(Shell& aShell);
  bool intercept(char *const *);
  bool checkIfSupported(char *const);

private:
  const std::set<std::string> supportedOps_{"cd", "exit"};
  Shell &shell_;
};
