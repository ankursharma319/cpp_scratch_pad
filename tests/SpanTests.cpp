
#include <cstddef>
#include <gtest/gtest.h>
#include "my_span.hpp"
#include <algorithm>
#include <iostream>
#include <numeric>
#include <vector>

TEST(SpanTest, test_construct_from_array) {
    int arr[3] = {23, 4, 6};
    my_span<int> a(arr);

    EXPECT_EQ(3, a.size());
    EXPECT_EQ(23, a[0]);
    EXPECT_EQ(4, a[1]);
    EXPECT_EQ(6, a[2]);
    EXPECT_EQ(23, *(a.data()));
}

TEST(SpanTest, test_for_loop_iter) {
    int arr[3] = {23, 4, 6};
    my_span<int> a(arr);
    std::size_t count = 0;
    for (const auto& val: a) {
        EXPECT_TRUE(val <= 23);
        EXPECT_TRUE(val >= 4);
        count++;
    }
    EXPECT_EQ(3, count);
}

TEST(SpanTest, test_construct_from_std_array) {
    std::array<int, 2> stdarr {{3, 4}};
    my_span<int> c(stdarr);
    EXPECT_EQ(2, c.size());
    EXPECT_EQ(3, c[0]);
    EXPECT_EQ(4, c[1]);
    c[1] = 9;
    EXPECT_EQ(9, c[1]);
}

TEST(SpanTest, test_construct_from_ptr) {
    int * ptr = new int[3];
    ptr[0] = 90;
    ptr[1] = 2;
    ptr[2] = 5;
    my_span<int> b(ptr, 3);
    EXPECT_EQ(b[1], 2);
    EXPECT_EQ(3, b.size());
    delete[] ptr;
}

TEST(SpanTest, test_span_from_vector) {
    std::vector<int> vec(5);
    std::iota(std::begin(vec), std::end(vec), 0);
    my_span<int> s (vec.begin(), vec.end());
    EXPECT_EQ(5, s.size());
    EXPECT_EQ(0, s[0]);
    EXPECT_EQ(2, s[2]);
    EXPECT_EQ(4, s[4]);
    s[3] = 10;
    EXPECT_EQ(10, s[3]);
    EXPECT_EQ(10, vec.at(3));
}
