#include <gtest/gtest.h>
#include "../src/tokenize.hpp"

TEST(TokeizerTest, TokenizeStrings) {
    std::vector<std::string> v;
    std::string s {"token1 token2"};
    tokenize_on_spaces(s, v);
    EXPECT_EQ(v.size(), 2);
}

TEST(TokeizerTest, TokenizeNoStringsWhenInputEmpty) {
    std::vector<std::string> v;
    std::string s {""};
    tokenize_on_spaces(s, v);
    EXPECT_EQ(v.size(), 0);
}

TEST(TokeizerTest, TokenizeStringWithOneToken) {
    std::vector<std::string> v;
    std::string s {"token1"};
    tokenize_on_spaces(s, v);
    EXPECT_EQ(v.size(), 1);
    std::string t {"token1 "};
    v.clear();
    tokenize_on_spaces(t, v);
    EXPECT_EQ(v.size(), 1);
}