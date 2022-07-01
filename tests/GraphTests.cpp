#include "graph.hpp"
#include <cstddef>
#include <gtest/gtest.h>

TEST(GraphTest, test_topological_sort) {
    std::unordered_map<int, std::vector<int>> adj_list = {
        {1, {}},
        {2, {}}
    };
    std::vector<int> result = ankur::topological_sort(adj_list);
    EXPECT_EQ(2, result.size());
}
