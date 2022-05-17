
#include <gtest/gtest.h>
#include "sort_array_algorithms.hpp"
#include "my_span.hpp"
#include <algorithm>
#include <numeric>

class SortLargeArrayAlgosTestFixture : public testing::Test
{
public:
    SortLargeArrayAlgosTestFixture()
    : vec(LARGE_N)
    , span(vec.begin(), vec.end())
    {
        std::iota(std::begin(vec), std::end(vec), 1);
        EXPECT_EQ(1, *span.begin());
        std::reverse(vec.begin(), vec.end());
        EXPECT_EQ(1, *(span.end()-1));
        EXPECT_EQ(LARGE_N, *span.begin());
    }

    std::vector<int> vec {};
    my_span<int> span {};
};

TEST(SortArrayAlgosTest, test_selection_sort) {
    int arr[5] = {5, 4, 3, 2, 1};
    ankur::selection_sort(my_span<int>(arr));

    for (int x = 0; x < 5; x++) {
        EXPECT_EQ(x+1, arr[x]);
    }
}

TEST(SortArrayAlgosTest, test_insertion_sort) {
    int arr[5] = {5, 4, 3, 2, 1};
    ankur::insertion_sort(my_span<int>(arr));

    for (int x = 0; x < 5; x++) {
        EXPECT_EQ(x+1, arr[x]);
    }
}

TEST(SortArrayAlgosTest, test_merge_sort) {
    int arr[5] = {5, 4, 3, 2, 1};
    ankur::merge_sort(my_span<int>(arr));

    for (int x = 0; x < 5; x++) {
        EXPECT_EQ(x+1, arr[x]);
    }
}

TEST(SortArrayAlgosTest, test_heap_sort) {
    int arr[5] = {5, 4, 3, 2, 1};
    ankur::heap_sort(my_span<int>(arr));

    for (int x = 0; x < 5; x++) {
        EXPECT_EQ(x+1, arr[x]);
    }
}

TEST(SortArrayAlgosTest, test_bst_sort) {
    int arr[5] = {5, 4, 3, 2, 1};
    ankur::bst_sort(my_span<int>(arr));

    for (int x = 0; x < 5; x++) {
        EXPECT_EQ(x+1, arr[x]);
    }
}

TEST(SortArrayAlgosTest, test_avl_sort) {
    int arr[5] = {5, 4, 3, 2, 1};
    ankur::avl_sort(my_span<int>(arr));

    for (int x = 0; x < 5; x++) {
        EXPECT_EQ(x+1, arr[x]);
    }
}

TEST(SortArrayAlgosTest, test_counting_sort_v1) {
    short arr[5] = {5, 4, 3, 2, 1};
    ankur::counting_sort_v1(my_span<short>(arr));

    for (int x = 0; x < 5; x++) {
        EXPECT_EQ(x+1, arr[x]);
    }
}

TEST(SortArrayAlgosTest, test_counting_sort_v2) {
    short arr[8] = {-9, 3, 2, -2, 2, -1, -6, 4};
    ankur::counting_sort_v2(my_span<short>(arr), 0, 10);

    EXPECT_EQ(-9, arr[7]);
    EXPECT_EQ(-6, arr[6]);
    EXPECT_EQ(4, arr[5]);
    EXPECT_EQ(3, arr[4]);
    EXPECT_EQ(2, arr[3]);
    EXPECT_EQ(-2, arr[2]);
    EXPECT_EQ(2, arr[1]);
    EXPECT_EQ(-1, arr[0]);
}

TEST(SortArrayAlgosTest, test_radix_sort) {
    int arr[10] = {-3, 90, 500, 419, 391, 250, 148, -987, -101, 0};
    ankur::radix_sort(my_span<int>(arr), 10);

    for (std::size_t x = 1; x < std::size(arr); x++) {
        EXPECT_LE(arr[x-1], arr[x]);
    }
}

TEST(SortArrayAlgosTest, test_quick_sort) {
    int arr[5] = {5, 4, 3, 2, 1};
    ankur::quick_sort_v1(my_span<int>(arr));

    for (int x = 0; x < 5; x++) {
        EXPECT_EQ(x+1, arr[x]);
    }
}

TEST_F(SortLargeArrayAlgosTestFixture, test_selection_sort_large_input) {
    ankur::selection_sort(span);
    EXPECT_EQ(LARGE_N, *(span.end()-1));
    EXPECT_EQ(1, *span.begin());
}

TEST_F(SortLargeArrayAlgosTestFixture, test_insertion_sort_large_input) {
    ankur::insertion_sort(span);
    EXPECT_EQ(LARGE_N, *(span.end()-1));
    EXPECT_EQ(1, *span.begin());
}

TEST_F(SortLargeArrayAlgosTestFixture, test_heap_sort_large_input) {
    ankur::heap_sort(span);
    EXPECT_EQ(LARGE_N, *(span.end()-1));
    EXPECT_EQ(1, *span.begin());
}

TEST_F(SortLargeArrayAlgosTestFixture, test_bst_sort_large_input) {
    ankur::bst_sort(span);
    EXPECT_EQ(LARGE_N, *(span.end()-1));
    EXPECT_EQ(1, *span.begin());
}

TEST_F(SortLargeArrayAlgosTestFixture, test_std_sort_large_input) {
    std::sort(span.begin(), span.end());
    EXPECT_EQ(LARGE_N, *(span.end()-1));
    EXPECT_EQ(1, *span.begin());
}

TEST_F(SortLargeArrayAlgosTestFixture, test_merge_sort_large_input) {
    ankur::merge_sort(span);
    EXPECT_EQ(LARGE_N, *(span.end()-1));
    EXPECT_EQ(1, *span.begin());
}

TEST_F(SortLargeArrayAlgosTestFixture, test_avl_sort_large_input) {
    ankur::avl_sort(span);
    EXPECT_EQ(LARGE_N, *(span.end()-1));
    EXPECT_EQ(1, *span.begin());
}

// skip because takes up a huge amount of memory (like 32 GB)
/*TEST_F(SortLargeArrayAlgosTestFixture, test_counting_sort_v1_large_input) {
    return;
    ankur::counting_sort_v1(span);
    EXPECT_EQ(LARGE_N, *(span.end()-1));
    EXPECT_EQ(1, *span.begin());
}
*/


TEST_F(SortLargeArrayAlgosTestFixture, test_radix_sort_large_input) {
    ankur::radix_sort(span);
    EXPECT_EQ(LARGE_N, *(span.end()-1));
    EXPECT_EQ(1, *span.begin());
}

TEST_F(SortLargeArrayAlgosTestFixture, test_quick_sort_v1_large_input) {
    ankur::quick_sort_v1(span);
    EXPECT_EQ(LARGE_N, *(span.end()-1));
    EXPECT_EQ(1, *span.begin());
}
