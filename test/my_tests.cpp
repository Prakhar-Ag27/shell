#include "../src/Parser.hpp"
#include "../src/Tokenize.hpp"
#include <gtest/gtest.h>

TEST(TokeizerTest, TokenizeStrings) {
  std::string s{"token1 token2"};
  std::vector<std::string> v = tokenize_on_spaces(s);
  EXPECT_EQ(v, (std::vector<std::string>{"token1", "token2"}));
}

TEST(TokeizerTest, TokenizeNoStringsWhenInputEmpty) {
  std::string s{""};
  std::vector<std::string> v = tokenize_on_spaces(s);
  EXPECT_EQ(v, (std::vector<std::string>{}));
}

TEST(TokeizerTest, TokenizeStringWithOneToken) {
  std::string s{"token1"};
  std::vector<std::string> v = tokenize_on_spaces(s);
  EXPECT_EQ(v, (std::vector<std::string>{"token1"}));
  std::string t{"token1 "};
  v.clear();
  v = tokenize_on_spaces(t);
  EXPECT_EQ(v, (std::vector<std::string>{"token1"}));
}

TEST(TokeizerTest, TokenizeStringWithExtraSpaces) {
  std::string s{"token1  token2  "};
  std::vector<std::string> v = tokenize_on_spaces(s);
  EXPECT_EQ(v, (std::vector<std::string>{"token1", "token2"}));
}

TEST(ParserTest, ParseMultipleInputs) {
  std::string input{"tokena1 tokena2 && tokenb1 tokenb2"};
  std::vector<std::vector<std::string>> vec = parseInput(input);
  std::vector<std::vector<std::string>> check{{"tokena1 tokena2"},
                                              {"tokenb1 tokenb2"}};
  EXPECT_EQ(vec, check);
}

TEST(ParserTest, ParseMultipleInputsWithMultipleStrings) {
  std::string input{"tokena1 tokena2 &&& tokena11 tokena12 && tokenb1 tokenb2"};
  std::vector<std::vector<std::string>> vec = parseInput(input);
  std::vector<std::vector<std::string>> check{
      {"tokena1 tokena2", "tokena11 tokena12"}, {"tokenb1 tokenb2"}};
  EXPECT_EQ(vec, check);
}

TEST(ParserTest, ParseMultipleInputsWithMultipleStringsExtended) {
  std::string input{"tokena1 tokena2 &&& tokena11 tokena12 &&& tokena21 "
                    "tokena22 && tokenb1 tokenb2 &&& tokenb11 tokenb12"};
  std::vector<std::vector<std::string>> vec = parseInput(input);
  std::vector<std::vector<std::string>> check{
      {"tokena1 tokena2", "tokena11 tokena12", "tokena21 tokena22"},
      {"tokenb1 tokenb2", "tokenb11 tokenb12"}};
  EXPECT_EQ(vec, check);
}

TEST(ParserTest, ParseMultipleInputsWithMultipleStringsShort) {
  std::string input{"tokena1 tokena2 &&& tokena11 tokena12"};
  std::vector<std::vector<std::string>> vec = parseInput(input);
  std::vector<std::vector<std::string>> check{
      {"tokena1 tokena2", "tokena11 tokena12"}};
  EXPECT_EQ(vec, check);
}
