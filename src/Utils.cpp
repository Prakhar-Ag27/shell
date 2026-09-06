#include "Utils.hpp"
#include <cerrno>
#include <unistd.h>

std::string getCurrentWorkingDirectory() {
  size_t size = 1024;
  char *dir = nullptr;
  std::string cwd = "";
  while (dir == nullptr) {
    char *buf = new char[size];
    dir = getcwd(buf, size);
    if (dir == nullptr && errno == ERANGE) {
      size *= 2;
    } else if (dir != nullptr) {
      cwd = dir;
    }
    delete[] buf;
  }
  return cwd;
}
