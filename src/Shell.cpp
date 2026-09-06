#include "Shell.hpp"
#include "Tokenize.hpp"
#include <iostream>
#include <unistd.h>

Shell::Shell() {};

void Shell::execute(char* const* inputTokens) {
  if (inputTokens == nullptr) {
    std::cout << "Please provide a program to run.\n";
    return;
  }
  execvp(inputTokens[0], inputTokens);
  for (size_t i = 0; inputTokens[i] != nullptr; ++i) {
    delete[] inputTokens[i];
  }
  delete[] inputTokens;
}
