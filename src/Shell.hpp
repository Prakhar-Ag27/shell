#pragma once
#include "./Interceptor.hpp"
#include "./Tokenize.hpp"
#include <sys/types.h>
#include <vector>

class Shell {
public:
  Shell();
  Shell(char);
  void run();
  void killAllBackgroundProcesses();

private:
  void execute(const std::vector<std::string> &);
  bool checkIfBackgorundProcess(std::string);
  void waitOnAllProcesses();

  char shellPrompt_;
  pid_t foregroundProcess_{-1};
  std::set<pid_t> backgroundProcess_;
  Interceptor interceptor_;
};
