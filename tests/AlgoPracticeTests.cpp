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
