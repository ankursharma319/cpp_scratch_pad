#include "string_algos.hpp"
#include <gtest/gtest.h>

TEST(StringAlgosTest, test_substr_contains_v1) {
    char x[] = "Hello World";
    char y[] = "Lol";
    char z[] = "Wor";
    EXPECT_FALSE(ankur::substr_contains_v1(x, sizeof(x)-1, y, sizeof(y)-1));
    EXPECT_TRUE(ankur::substr_contains_v1(x, sizeof(x)-1, z, sizeof(z)-1));
}
