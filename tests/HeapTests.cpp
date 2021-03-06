#include <gtest/gtest.h>
#include "heap.hpp"
#include <algorithm>
#include <numeric>
#include <vector>

TEST(MaxHeapTest, test_max_heapify_down) {
    ankur::max_heap my_heap {};
    my_heap.vec = std::vector<int>({3, 4, 1, 2});
    my_heap.max_heapify_down(0);
    EXPECT_EQ(std::vector<int>({4, 3, 1, 2}), my_heap.vec);
}

TEST(MaxHeapTest, test_max_heapify_down_deep) {
    // still correct single violation
    //i.e. trees rooted at 3, and 4 , are max-heaps
    ankur::max_heap my_heap {};
    my_heap.vec = std::vector<int>({12, 1, 10, 7, 6, 4, 9, 3, 2, 5});
    my_heap.max_heapify_down(1);
    EXPECT_EQ(std::vector<int>({12, 7, 10, 3, 6, 4, 9, 1, 2, 5}), my_heap.vec);
}

TEST(MaxHeapTest, test_build_max_heap) {
    // correct single violation
    ankur::max_heap my_heap {};
    my_heap.vec = std::vector<int>({1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12});
    my_heap.build_max_heap();
    EXPECT_EQ(std::vector<int>({12, 11, 7, 9, 10, 6, 1, 8, 4, 2, 5, 3}), my_heap.vec);
}

TEST(MaxHeapTest, test_insert) {
    ankur::max_heap my_heap {};
    my_heap.insert(4);
    my_heap.insert(2);
    my_heap.insert(3);
    my_heap.insert(1);
    my_heap.insert(5);
    EXPECT_EQ(std::vector<int>({5, 4, 3, 1, 2}), my_heap.vec);
}

TEST(MaxHeapTest, test_change_key) {
    ankur::max_heap my_heap {};
    my_heap.vec = std::vector<int>({12, 11, 7, 9, 10, 6, 1, 8, 4, 2, 5, 3});
    my_heap.change_key(4, 14);
    EXPECT_EQ(std::vector<int>({14, 12, 7, 9, 11, 6, 1, 8, 4, 2, 5, 3}), my_heap.vec);
    my_heap.change_key(4, 3);
    EXPECT_EQ(std::vector<int>({14, 12, 7, 9, 5, 6, 1, 8, 4, 2, 3, 3}), my_heap.vec);
}

TEST(MaxHeapTest, test_extract_max) {
    ankur::max_heap my_heap {};
    my_heap.vec = std::vector<int>({12, 11, 7, 9, 10, 6, 1, 8, 4, 2, 5, 3});
    EXPECT_EQ(12, my_heap.extract_max());
    EXPECT_EQ(std::vector<int>({11, 10, 7, 9, 5, 6, 1, 8, 4, 2, 3}), my_heap.vec);
}
