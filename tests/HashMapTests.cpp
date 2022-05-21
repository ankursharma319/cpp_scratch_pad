#include <gtest/gtest.h>
#include "hash_map.hpp"
#include <algorithm>
#include <numeric>
#include <vector>

TEST(ChainedHashMapTest, test_insert_and_contains) {
    ankur::chained_hash_map<int, int> map {};
    EXPECT_EQ(false, map.contains(3));
    map.insert(9, 99);
    EXPECT_EQ(true, map.contains(9));
    EXPECT_EQ(false, map.contains(99));
}

TEST(ChainedHashMapTest, test_size_and_remove) {
    ankur::chained_hash_map<int, int> map {};
    EXPECT_EQ(0, map.size());
    map.insert(9, 99);
    EXPECT_EQ(1, map.size());
    map.remove(9);
    EXPECT_EQ(0, map.size());
}
