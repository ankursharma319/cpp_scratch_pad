#include "algo_practice.hpp"
#include <string>
#include <gtest/gtest.h>

TEST(AlgoPracticeTest, test_1_4_palindrome_permutation) {
    EXPECT_EQ(true, ankur::is_palindrome_permutation("Tact Coa"));
    EXPECT_EQ(true, ankur::is_palindrome_permutation("tactcoa"));
    EXPECT_EQ(true, ankur::is_palindrome_permutation(" Tact 12312Ca"));
    EXPECT_EQ(true, ankur::is_palindrome_permutation("_,.-xyzxzy-  ++"));
    EXPECT_EQ(true, ankur::is_palindrome_permutation(""));
    EXPECT_EQ(true, ankur::is_palindrome_permutation("    "));
    EXPECT_EQ(false, ankur::is_palindrome_permutation("Tact Coal"));
    EXPECT_EQ(false, ankur::is_palindrome_permutation("_-xyxjzxzy-  ++"));
    EXPECT_EQ(false, ankur::is_palindrome_permutation("hello world"));
}

TEST(AlgoPracticeTest, test_1_9_string_rotation) {
    EXPECT_EQ(true, ankur::is_rotated_string("waterbottle", "erbottlewat"));
    EXPECT_EQ(false, ankur::is_rotated_string("waterbottles", "erbottlewat"));
    EXPECT_EQ(true, ankur::is_rotated_string("Waterbottles are good", "erbottles are goodWat"));
    EXPECT_EQ(false, ankur::is_rotated_string("waterbottles are good.", "erbottles are good wat"));
    EXPECT_EQ(true, ankur::is_rotated_string("", ""));
    EXPECT_EQ(false, ankur::is_rotated_string("", " "));
    EXPECT_EQ(true, ankur::is_rotated_string("exempelary", "elaryexemp"));
    EXPECT_EQ(true, ankur::is_rotated_string("exempelary", "exempelary"));
    EXPECT_EQ(false, ankur::is_rotated_string("exempelary", "Exempelary"));
    EXPECT_EQ(true, ankur::is_rotated_string("youryour", "ouryoury"));
    EXPECT_EQ(false, ankur::is_rotated_string("your", "ouryoury"));
}
