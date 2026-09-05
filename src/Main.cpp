<<<<<<< HEAD
#include "tokenize.hpp"
#include <iostream>
#include <string>
#include <vector>

int main() {
  std::string input;
  std::getline(std::cin, input, '\n');
  std::vector<std::string> v;
  tokenize_on_spaces(input, v);

}
