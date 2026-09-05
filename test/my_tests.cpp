#include "../src/Tokenize.hpp"
#include <gtest/gtest.h>

TEST(TokeizerTest, TokenizeStrings) {
  std::string s{"token1 token2"};
  char *const *v = tokenize_on_spaces(s);
  EXPECT_STREQ(v[0], "token1");
  EXPECT_STREQ(v[1], "token2");
  delete[] v[0];
  delete[] v[1];
  delete[] v;
}

TEST(TokeizerTest, TokenizeNoStringsWhenInputEmpty) {
  std::string s{""};
  char *const *v = tokenize_on_spaces(s);
  EXPECT_EQ(v, nullptr);
}

TEST(TokeizerTest, TokenizeStringWithOneToken) {
  std::string s{"token1"};
  char *const *v = tokenize_on_spaces(s);
  EXPECT_STREQ(v[0], "token1");
  std::string t{"token1 "};
  delete[] v[0];
  delete[] v;
  v = tokenize_on_spaces(t);
  EXPECT_STREQ(v[0], "token1");
}

TEST(TokeizerTest, TokenizeStringWithExtraSpaces) {
  std::string s{"token1  token2  "};
  char *const *v = tokenize_on_spaces(s);
  EXPECT_STREQ(v[0], "token1");
  EXPECT_STREQ(v[1], "token2");
  delete[] v[0];
  delete[] v[1];
  delete[] v;
}
