#include "graph.hpp"

#include <unordered_set>
#include <algorithm>

namespace {

template<typename K, typename V>
std::unordered_set<K> key_set(std::unordered_map<K, V> const& map) {
    std::unordered_set<K> keys {};
    for (auto it = map.cbegin(); it != map.cend(); it++) {
        keys.insert(it->first); 
    }
    return keys;
}

void dfs_visit_for_top_sort(
    std::unordered_map<int, std::vector<int>> const& adj_list,
    int starting_vertex,
    std::vector<int>& top_sort_result,
    std::unordered_set<int>& unvisited_vertices
) {
    unvisited_vertices.erase(starting_vertex);
    for (int dest: adj_list.at(starting_vertex)) {
        if (unvisited_vertices.count(dest) == 0) {
            continue;
        }
        dfs_visit_for_top_sort(adj_list, dest, top_sort_result, unvisited_vertices);
    }
    top_sort_result.push_back(starting_vertex);
}

}

namespace ankur {

GraphBFSResults bfs_visit(std::unordered_map<int, std::vector<int>> const& adj_list, int starting_vertex) {
    struct GraphBFSResults results {};
    results.parents.insert({starting_vertex, std::nullopt});
    std::vector<int> frontier {starting_vertex};
    std::size_t level = 0;
    while (!frontier.empty()) {    
        std::vector<int> new_frontier{};
        for (int node: frontier) {
            results.visited.push_back(node);
            results.levels.insert({node, level});
            for (int dest: adj_list.at(node)) {
                if (results.parents.count(dest) == 1) {
                    continue;
                }
                results.parents.insert({dest, node});
                new_frontier.push_back(dest);
            }
        }
        frontier = std::move(new_frontier);
        level++;
    }
    return results;
}

std::vector<int> topological_sort(std::unordered_map<int, std::vector<int>> const& adj_list) {
    std::vector<int> res {};
    std::unordered_set<int> unvisited_vertices = key_set(adj_list);
    while (!unvisited_vertices.empty()) {
        int vertex = *unvisited_vertices.begin();
        dfs_visit_for_top_sort(adj_list, vertex, res, unvisited_vertices);
    }
    std::reverse(res.begin(), res.end());
    return res;
}

}
