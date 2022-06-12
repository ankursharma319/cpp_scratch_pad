#include "big_math.hpp"
#include <cstddef>
#include <gtest/gtest.h>

TEST(BigMathTest, test_small_addition_hex) {
    EXPECT_EQ("9", big_math::add_hex_integers("2", "7"));
    EXPECT_EQ("-4", big_math::add_hex_integers("3", "-7"));
    EXPECT_EQ("2", big_math::add_hex_integers("7", "-5"));
    EXPECT_EQ("-32", big_math::add_hex_integers("-10", "-22"));
    EXPECT_EQ("0", big_math::add_hex_integers("256", "-256"));
    EXPECT_EQ("132", big_math::add_hex_integers("99", "99"));
    EXPECT_EQ("14B", big_math::add_hex_integers("AC", "9F"));
}

TEST(BigMathTest, test_big_addition_hex) {
    EXPECT_EQ("222224", big_math::add_hex_integers("2", "222222"));
    EXPECT_EQ("0", big_math::add_hex_integers("-FFFFFFFFFFFBB", "FFFFFFFFFFFBB"));
    EXPECT_EQ("77778", big_math::add_hex_integers("-ABCDE", "123456"));
    EXPECT_EQ("1234567890BE024579B3BE024579B3BE024579B3BE024579B3BE024579B3BE024579B3",
        big_math::add_hex_integers(
        "1234567890123456789012345678901234567890123456789012345678901234567890",
        "ABCDEF0123ABCDEF0123ABCDEF0123ABCDEF0123ABCDEF0123ABCDEF0123"
        )
    );
    EXPECT_EQ("-1234567890BE024579B3BE024579B3BE024579B3BE024579B3BE024579B3BE024579B3",
        big_math::add_hex_integers(
        "-1234567890123456789012345678901234567890123456789012345678901234567890",
        "-ABCDEF0123ABCDEF0123ABCDEF0123ABCDEF0123ABCDEF0123ABCDEF0123"
        )
    );
    EXPECT_EQ("-123456788F666667776C666667776C666667776C666667776C666667776C666667776D",
        big_math::add_hex_integers(
            "-1234567890123456789012345678901234567890123456789012345678901234567890",
            "ABCDEF0123ABCDEF0123ABCDEF0123ABCDEF0123ABCDEF0123ABCDEF0123"
        )
    );
    EXPECT_EQ("-7778", big_math::add_hex_integers("-12345","ABCD"));
}

TEST(BigMathTest, test_small_multiplication_hex) {
    EXPECT_EQ("E", big_math::multiply_hex_integers("2", "7"));
    EXPECT_EQ("-15", big_math::multiply_hex_integers("3", "-7"));
    EXPECT_EQ("-23", big_math::multiply_hex_integers("7", "-5"));
    EXPECT_EQ("220", big_math::multiply_hex_integers("-10", "-22"));
    EXPECT_EQ("-574E4", big_math::multiply_hex_integers("256", "-256"));
    EXPECT_EQ("5B71", big_math::multiply_hex_integers("99", "99"));
    EXPECT_EQ("6AD4", big_math::multiply_hex_integers("AC", "9F"));
}
