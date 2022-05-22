#include <gtest/gtest.h>
#include "hash_map.hpp"
#include <algorithm>
#include <numeric>
#include <vector>

TEST(ChainedHashMapTest, test_insert_and_contains) {
    ankur::chained_hash_map<int, int> map {};
    EXPECT_EQ(false, map.contains(3));
    bool inserted = map.insert(9, 99);
    EXPECT_TRUE(inserted);
    inserted = map.insert(9, 88);
    EXPECT_FALSE(inserted);
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

TEST(ChainedHashMapTest, test_square_bracket_operator) {
    ankur::chained_hash_map<int, int> map {};
    map.insert(9, 99);
    map.insert(9, 98);
    map.insert(8, 88);
    EXPECT_EQ(99, map[9]);
    EXPECT_EQ(88, map[8]);
    map[8] = 77;
    EXPECT_EQ(77, map[8]);
    map[7] = 66;
    EXPECT_EQ(66, map[7]);
}

TEST(ChainedHashMapTest, test_larger_input) {
    ankur::chained_hash_map<int, int> map {};
    std::size_t map_size = 50;
    for (std::size_t i=0; i < map_size; i++) {
        map.insert(i, i*5);
        EXPECT_TRUE(map.contains(i));
        EXPECT_EQ(i+1, map.size());
        EXPECT_EQ(i*5, map[i]);
    }
    for (std::size_t i=0; i < map_size; i++) {
        map.remove(i);
        EXPECT_FALSE(map.contains(i));
        EXPECT_EQ(map_size-i-1, map.size());
    }
}
