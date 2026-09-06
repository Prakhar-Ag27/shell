#include "./Interceptor.hpp"
#include "./Tokenize.hpp"
#include <sys/types.h>

class Shell {
public:
  Shell();
  Shell(char);
  void run();

private:
  void execute(char *const *);
  void freeTokens(char *const *);
  bool checkIfBackgorundProcess(std::string);
  void waitOnAllProcesses();

  char shellPrompt_;
  pid_t foregroundProcess_{-1};
  std::set<pid_t> backgroundProcess_;
  Interceptor interceptor_;
};
