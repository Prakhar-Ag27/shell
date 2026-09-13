#include "Shell.hpp"
#include <sys/wait.h>
#include <unistd.h>

int main() {
  Shell shell_{'$'};
  shell_.installSigKillHandler();
  shell_.run();
}
