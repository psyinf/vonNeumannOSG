#include <gtest/gtest.h>

#include "StringTools.h"


TEST(StringTools, MatchIdentity)
{
    EXPECT_TRUE(Strings::matches("abcd1234", "abcd1234"));
    
}

