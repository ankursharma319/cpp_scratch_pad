#include "graph.hpp"
#include <cstddef>
#include <gtest/gtest.h>
#include <unordered_set>

TEST(GraphTest, test_bfs_visit) {
    std::unordered_map<int, std::vector<int>> adj_list = {
        {1, {2, 3}},
        {2, {8}},
        {3, {1,4}},
        {4, {9}},
        {5, {6}},
        {6, {5}},
        {8, {9}},
        {9, {}}
    };
    std::vector<int> expected_visited_order = {1,2,3,8,4,9};
    std::unordered_map<int, std::optional<int>> expected_parents = {
        {1, std::nullopt},
        {2, 1},
        {3, 1},
        {8, 2},
        {4, 3},
        {9, 8}
    };
    std::unordered_map<int, std::size_t> expected_levels = {
        {1, 0}, {2, 1}, {3, 1}, {8, 2}, {4, 2}, {9, 3}
    };
    ankur::GraphBFSResults results = ankur::bfs_visit(adj_list, 1);
    EXPECT_EQ(expected_visited_order, results.visited);
    EXPECT_EQ(expected_parents, results.parents);
    EXPECT_EQ(expected_levels, results.levels);
}

TEST(GraphTest, test_topological_sort) {
    std::unordered_map<int, std::vector<int>> adj_list = {
        {1, {2, 6}},
        {2, {3}},
        {3, {5, 4}},
        {4, {5}},
        {5, {}},
        {6, {7}},
        {7, {12, 8, 13}},
        {8, {9, 11}},
        {9, {4, 10}},
        {10, {}},
        {11, {12, 13}},
        {12, {}},
        {13, {9}}
    };
    std::unordered_set<int> checked = {};
    std::vector<int> result = ankur::topological_sort(adj_list);
    EXPECT_EQ(13, result.size());
    for(int node: result) {
        for (auto const& [possible_source, dests] : adj_list) {
            bool contains_node_in_dests = std::find(dests.cbegin(), dests.cend(), node) != dests.cend();
            if (contains_node_in_dests){
                assert(checked.count(possible_source) == 1);
            }
        }
        checked.insert(node);
    }
}
