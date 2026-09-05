#include "Tokenize.hpp"
#include <cstddef>

char **tokenize_on_spaces(std::string &input) {
  std::size_t i = 0;
  std::size_t j = 0;
  std::size_t numTokens = numberOfTokens(input);
  if (numTokens == 0) {
    return nullptr;
  }
  char **arr = new char *[numTokens + 1];
  arr[numTokens] = nullptr;
  while (i < numTokens) {
    while (j < input.size() && input[j] == ' ') {
      j++;
    }
    int len = 0;
    while (j < input.size() && input[j] != ' ') {
      len++;
      j++;
    }
    char *token = new char[len + 1];
    for (std::size_t k = 0; k < len; k++) {
      token[k] = input[j - len + k];
    }
    token[len] = '\0';
    arr[i] = token;
    i++;
  }
  return arr;
}

std::size_t numberOfTokens(std::string &input) {
  std::size_t i = 0;
  int count = 0;
  while (i < input.size()) {
    while (i < input.size() && input[i] == ' ') {
      i++;
    }
    if (i < input.size()) {
      count++;
    }
    while (i < input.size() && input[i] != ' ') {
      i++;
    }
  }
  return count;
}
