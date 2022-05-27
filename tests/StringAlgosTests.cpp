#include "string_algos.hpp"
#include <cstddef>
#include <gtest/gtest.h>

TEST(StringAlgosTest, test_substr_contains_v1) {
    char x[] = "Hello World";
    char y[] = "Lol";
    char z[] = "Wor";
    EXPECT_FALSE(ankur::substr_contains_v1(x, sizeof(x)-1, y, sizeof(y)-1));
    EXPECT_TRUE(ankur::substr_contains_v1(x, sizeof(x)-1, z, sizeof(z)-1));
}

TEST(StringAlgosTest, test_substr_contains_v2) {
    char x[] = "Hello Worldabcdef";
    char y[] = "Lol";
    char z[] = "Wor";
    char yy[] = "";
    char zz[] = "abcdef";
    EXPECT_FALSE(ankur::substr_contains_v2(x, sizeof(x)-1, y, sizeof(y)-1));
    EXPECT_TRUE(ankur::substr_contains_v2(x, sizeof(x)-1, z, sizeof(z)-1));
    EXPECT_TRUE(ankur::substr_contains_v2(x, sizeof(x)-1, yy, sizeof(yy)-1));
    EXPECT_TRUE(ankur::substr_contains_v2(x, sizeof(x)-1, zz, sizeof(zz)-1));
}

TEST(StringAlgosPerformanceTest, test_std_strfind) {
    char* big_string = new char[LARGE_N];
    char small_string_1[] = "abcdefghijklmnopqrstuvwxyz";
    char small_string_2[] = "nonexistentlolasdghdajdgahdgajdgasjdahdasgdkajdgasjdgasask";
    for (std::size_t i=0; i<LARGE_N; i++) {
        big_string[i] = i;
    }
    std::string std_big_string(big_string, LARGE_N);
    std::string std_small_string_1(small_string_1, sizeof(small_string_1)-1);
    std::string std_small_string_2(small_string_2, sizeof(small_string_2)-1);
    EXPECT_TRUE(std_big_string.find(std_small_string_1) != std::string::npos);
    EXPECT_FALSE(std_big_string.find(std_small_string_2) != std::string::npos);
    delete[] big_string;
}

TEST(StringAlgosPerformanceTest, test_substr_contains_v1) {
    char* big_string = new char[LARGE_N];
    char small_string_1[] = "abcdefghijklmnopqrstuvwxyz";
    char small_string_2[] = "nonexistentlolasdghdajdgahdgajdgasjdahdasgdkajdgasjdgasask";
    for (std::size_t i=0; i<LARGE_N; i++) {
        big_string[i] = i;
    }
    EXPECT_TRUE(ankur::substr_contains_v1(big_string, LARGE_N, small_string_1, sizeof(small_string_1)-1));
    EXPECT_FALSE(ankur::substr_contains_v1(big_string, LARGE_N, small_string_2, sizeof(small_string_2)-1));
    delete[] big_string;
}

TEST(StringAlgosPerformanceTest, test_substr_contains_v2) {
    char* big_string = new char[LARGE_N];
    char small_string_1[] = "abcdefghijklmnopqrstuvwxyz";
    char small_string_2[] = "nonexistentlolasdghdajdgahdgajdgasjdahdasgdkajdgasjdgasask";
    for (std::size_t i=0; i<LARGE_N; i++) {
        big_string[i] = i;
    }
    EXPECT_TRUE(ankur::substr_contains_v2(big_string, LARGE_N, small_string_1, sizeof(small_string_1)-1));
    EXPECT_FALSE(ankur::substr_contains_v2(big_string, LARGE_N, small_string_2, sizeof(small_string_2)-1));
    delete[] big_string;
}
