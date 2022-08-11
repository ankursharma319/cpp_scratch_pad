#ifndef GRAPH_ALGOS_HPP
#define GRAPH_ALGOS_HPP

#include <unordered_map>
#include <vector>

namespace ankur {

struct GraphBFSResults {
    std::vector<int> visited;
    std::unordered_map<int, std::optional<int>> parents;
    std::unordered_map<int, int> levels;
};

GraphBFSResults bfs_visit(std::unordered_map<int, std::vector<int>> const& adj_list);

std::vector<int> topological_sort(std::unordered_map<int, std::vector<int>> const& adj_list);

}

#endif
