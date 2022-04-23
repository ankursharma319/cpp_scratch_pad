
#include <gtest/gtest.h>
#include "sort_array_algorithms.hpp"
#include <algorithm>
#include <numeric>

TEST(SortArrayAlgosTest, test_selection_sort) {
    int arr[5] = {5, 4, 3, 2, 1};
    ankur::selection_sort(arr);

    for (int x = 0; x < 5; x++) {
        EXPECT_EQ(x+1, arr[x]);
    }
}

TEST(SortArrayAlgosTest, test_insertion_sort) {
    int arr[5] = {5, 4, 3, 2, 1};
    ankur::insertion_sort(arr);

    for (int x = 0; x < 5; x++) {
        EXPECT_EQ(x+1, arr[x]);
    }
}
