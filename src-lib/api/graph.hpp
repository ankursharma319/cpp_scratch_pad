#ifndef GRAPH_ALGOS_HPP
#define GRAPH_ALGOS_HPP

#include <unordered_map>
#include <vector>
#include <optional>

namespace ankur {

struct GraphBFSResults {
    std::vector<int> visited;
    std::unordered_map<int, std::optional<int>> parents;
    std::unordered_map<int, std::size_t> levels;
};

GraphBFSResults bfs_visit(std::unordered_map<int, std::vector<int>> const& adj_list, int starting_vertex);

std::vector<int> topological_sort(std::unordered_map<int, std::vector<int>> const& adj_list);

}

#endif
