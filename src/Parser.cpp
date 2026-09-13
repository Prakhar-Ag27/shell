#include "Parser.hpp"
#include <cstddef>
#include <vector>

std::vector<std::vector<std::string>> parseInput(const std::string &input) {
  if (input.length() == 0) {
    return {};
  }
  std::vector<std::string> tokens;
  std::string delimeter = " && ";
  std::size_t st = 0;
  std::size_t curr = input.find(delimeter, st);
  while (curr != std::string::npos) {
    tokens.push_back(input.substr(st, curr - st));
    st = curr + delimeter.length();
    curr = input.find(delimeter, st);
  }
  tokens.push_back(input.substr(st, input.length() - st));
  std::vector<std::vector<std::string>> tokenVec;
  for (auto &in : tokens) {
    std::vector<std::string> list;
    std::string delim = " &&& ";
    std::size_t s = 0;
    std::size_t cur = in.find(delim, s);
    while (cur != std::string::npos) {
      list.push_back(in.substr(s, cur - s));
      s = cur + delim.length();
      cur = in.find(delim, s);
    }
    list.push_back(in.substr(s, in.length() - s));
    tokenVec.push_back(list);
  }
  return tokenVec;
}
