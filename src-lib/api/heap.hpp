#include "linked_list.hpp"
#include <cassert>
#include <cstddef>
#include <vector>
#include <limits>
#include <string>
#include <iostream>

namespace ankur {

class max_heap {
public:
    std::vector<int> vec {};

    max_heap() {}

    void insert(int x) {
        vec.push_back(x);
        max_heapify_up(vec.size()-1);
    }

    int max() const {
        return vec.at(0);
    }

    int extract_max() {
        int ret = vec.at(0);
        std::swap(vec.at(0), vec.at(vec.size()-1));
        vec.pop_back();
        max_heapify_down(0);
        return ret;
    }

    void change_key(std::size_t index, int new_value) {
        assert(index < vec.size());
        int old_value = vec.at(index);
        vec.at(index) = new_value;
        if (new_value > old_value) {
            max_heapify_up(index);
        } else {
            max_heapify_down(index);
        }
    }

    void max_heapify_down(std::size_t index) {
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
                max_heapify_down(right_child_index);
            } else {
                std::swap(vec.at(index), vec.at(left_child_index));
                max_heapify_down(left_child_index);
            }
        }
    }

    void max_heapify_up(std::size_t index) {
        // assume everything above is heap
        std::size_t parent_index = index < 1 ? 0 : (index - 1) / 2;
        while(index != 0) {
            assert(index < vec.size());
            if (vec.at(index) > vec.at(parent_index)) {
                std::swap(vec.at(parent_index), vec.at(index));
            } else {
                break;
            }
            index = parent_index;
            parent_index = parent_index < 1 ? 0 : (parent_index - 1) / 2;
        }
    }

    void build_max_heap() {
        for (
            std::size_t i = (vec.size()/2) - 1;
            i < std::numeric_limits<std::size_t>::max();
            i--
        ) {
            max_heapify_down(i);
        }
    }

};

}
