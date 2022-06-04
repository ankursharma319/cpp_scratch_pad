#include "big_math.hpp"
#include <cstddef>
#include <gtest/gtest.h>

TEST(BigMathTest, test_small_addition) {
    EXPECT_EQ("9", big_math::add_integers("2", "7"));
    EXPECT_EQ("-4", big_math::add_integers("3", "-7"));
    EXPECT_EQ("0", big_math::add_integers("256", "-256"));
    EXPECT_EQ("198", big_math::add_integers("99", "99"));
}
