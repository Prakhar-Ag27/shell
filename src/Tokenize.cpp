#include "Tokenize.hpp"
#include <cstddef>

std::vector<std::string> tokenize_on_spaces(std::string &input) {
  std::size_t i = 0;
  std::vector<std::string> tokens;
  while (i < input.size()) {
    std::string token = "";
    while (i < input.size() && input[i] == ' ') {
      i++;
    }
    while (i < input.size() && input[i] != ' ') {
      token += input[i++];
    }
    if (token.size() > 0) {
      tokens.push_back(token);
    }
  }
  return tokens;
}
