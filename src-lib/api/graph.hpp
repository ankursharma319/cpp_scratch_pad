#ifndef GRAPH_ALGOS_HPP
#define GRAPH_ALGOS_HPP

#include <unordered_map>
#include <vector>

namespace ankur {

std::vector<int> topological_sort(std::unordered_map<int, std::vector<int>> const& adj_list);

}

#endif
