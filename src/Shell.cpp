#include "Shell.hpp"
#include "Tokenize.hpp"
#include <cerrno>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <unistd.h>

Shell::Shell() {};

void Shell::execute(std::string &input) {
  char *const *inputTokens = tokenize_on_spaces(input);
  if (inputTokens == nullptr) {
    exit(1);
  }
  execvp(inputTokens[0], inputTokens);
  for (size_t i = 0; inputTokens[i] != nullptr; ++i) {
    delete[] inputTokens[i];
  }
  delete[] inputTokens;
  std::cerr << strerror(errno) << '\n';
  exit(1);
}
