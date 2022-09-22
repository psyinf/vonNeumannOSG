#include <gtest/gtest.h>

#include "StringTools.h"


TEST(StringTools_matches, MatchIdentity)
{
    EXPECT_TRUE(Strings::matches("abcd1234", "abcd1234"));
    
}

TEST(StringTools_matches, SimpleExpression)
{
    EXPECT_TRUE(Strings::matches("Simple testString", "String(.*)"));
    EXPECT_TRUE(Strings::matches("Simple testString", "Simple(.*)"));
    EXPECT_TRUE(Strings::matches("Simple testString", "(.*)String"));

    EXPECT_FALSE(Strings::matches("Simple testString", "(.*)string"));
}

TEST(StringTools_matchWildcard, match)
{
    EXPECT_TRUE(Strings::matchesWildCard("SomeString.x", "*.x"));
    EXPECT_TRUE(Strings::matchesWildCard("*..Flat", "*"));
    EXPECT_TRUE(Strings::matchesWildCard("abcSOMEdefSOMEghi", "abc*def*gh*"));
    EXPECT_FALSE(Strings::matchesWildCard("abcSOMEdefSOMEghi", "abc*def*ghj*"));
    EXPECT_FALSE(Strings::matchesWildCard("*..Flat", "*.y"));
}

TEST(StringTools, wildCardToRegex)
{
    EXPECT_EQ(Strings::wildcardToRegex("abc*.*"), "abc.*\\..*");
    EXPECT_EQ(Strings::wildcardToRegex("*.x"), ".*\\.x");
}