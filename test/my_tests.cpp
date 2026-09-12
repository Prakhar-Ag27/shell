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
