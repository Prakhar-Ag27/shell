#include "Utils.hpp"
#include <cerrno>
#include <cstddef>
#include <cstring>
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
    } else {
      delete[] buf;
      break;
    }
    delete[] buf;
  }
  return cwd;
}

char **getCStringVector(const std::vector<std::string> &vec) {
  char **cVec = new char *[vec.size() + 1];

  for (std::size_t i = 0; i < vec.size(); i++) {
    cVec[i] = new char[vec[i].size() + 1];
    std::strcpy(cVec[i], vec[i].c_str());
  }

  cVec[vec.size()] = nullptr;
  return cVec;
}
