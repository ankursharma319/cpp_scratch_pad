#include "graph.hpp"

#include <unordered_set>

namespace {

template<typename K, typename V>
std::unordered_set<K> key_set(std::unordered_map<K, V> const&) {
    return {};
}

void dfs_visit_for_top_sort(
    std::unordered_map<int, std::vector<int>> const& adj_list,
    int starting_vertex,
    std::vector<int>& top_sort_result,
    std::unordered_set<int>& unvisited_vertices
) {
    (void) adj_list;
    (void) starting_vertex;
    (void) top_sort_result;
    (void) unvisited_vertices;
}

}

namespace ankur {

GraphBFSResults bfs_visit(std::unordered_map<int, std::vector<int>> const& adj_list) {
    struct GraphBFSResults results {};
    (void) adj_list;
    return results;
}

std::vector<int> topological_sort(std::unordered_map<int, std::vector<int>> const& adj_list) {
    std::vector<int> res {};
    std::unordered_set<int> unvisited_vertices = key_set(adj_list);
    while (!unvisited_vertices.empty()) {
        int vertex = *unvisited_vertices.begin();
        dfs_visit_for_top_sort(adj_list, vertex, res, unvisited_vertices);
    }
    return res;
}

}
