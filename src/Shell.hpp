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
  void installSigKillHandler();

private:
  void execute(const std::vector<std::string> &);
  bool checkIfBackgorundProcess(std::string);
  void waitOnAllProcesses();
  bool checkInput(const std::vector<std::vector<std::string>> &);
  void executeSingleMode(std::string);
  void executeMultiMode(const std::vector<std::vector<std::string>> &);

  char shellPrompt_;
  pid_t foregroundProcess_{-1};
  std::set<pid_t> backgroundProcess_;
  std::set<pid_t> foregroundProcessesInMultiMode_;
  Interceptor interceptor_;
  pid_t bgProcessGroup{-1};
};
