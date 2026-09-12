#pragma once
#include <set>
#include <string>
#include <vector>

class Shell;

class Interceptor {
public:
  Interceptor(Shell &aShell);
  bool intercept(const std::vector<std::string> &);
  bool checkIfSupported(const std::string &);

private:
  const std::set<std::string> supportedOps_{"cd", "exit"};
  Shell &shell_;
};
