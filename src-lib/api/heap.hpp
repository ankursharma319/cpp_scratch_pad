#include <cassert>
#include <cstddef>
#include <vector>
#include <limits>

namespace ankur {

class max_heap {
public:
    std::vector<int> vec {};

    max_heap() {}
    void insert(int x);
    int max() const;
    int extract_max();
    void change_key(std::size_t index, int new_value);

    void max_heapify(std::size_t index) {
        assert(index < vec.size());
        // assume trees on the left and right are max heaps
        std::size_t left_child_index = index * 2 + 1;
        bool has_left_subtree = left_child_index < vec.size();
        if (!has_left_subtree) {
            return;
        }
        int& left_child_value = vec.at(left_child_index);
        std::size_t right_child_index = left_child_index + 1;
        bool has_right_subtree = right_child_index < vec.size();
        if (
            vec.at(index) < left_child_value ||
            (has_right_subtree && vec.at(right_child_index) > vec.at(index))
        ) {
            if (has_right_subtree && left_child_value < vec.at(right_child_index)) {
                std::swap(vec.at(index), vec.at(right_child_index));
                max_heapify(right_child_index);
            } else {
                std::swap(vec.at(index), vec.at(left_child_index));
                max_heapify(left_child_index);
            }
        }
    }

    void build_max_heap() {
        for (
            std::size_t i = (vec.size()/2) - 1;
            i < std::numeric_limits<std::size_t>::max();
            i--
        ) {
            max_heapify(i);
        }
    }

};

}
