#include <cstddef>
#include <iostream>
#include <limits>
#include <cassert>
#include "binary_search_tree.hpp"
#include "my_span.hpp"

namespace ankur {

template<typename T>
void insertion_sort(my_span<T> span);

template<typename T>
void selection_sort(my_span<T> span);

template<typename T>
void heap_sort(my_span<T> span);

template<typename T>
void bst_sort(my_span<T> span);

template<typename T>
void insertion_sort(my_span<T> span) {
    for (std::size_t i=1; i<span.size(); i++) {
        for (
            std::size_t j = i;
            j > 0 && span[j] < span[j-1];
            j--
        ) {
            std::swap(span[j], span[j-1]);
        }
    }
}

template<typename T>
void selection_sort(my_span<T> span) {
    for (std::size_t i=0; i<span.size(); i++) {
        std::size_t smallest_index = i;
        for (std::size_t j=i; j<span.size(); j++) {
            if (span[j] < span[smallest_index]) {
                smallest_index = j;
            }
        }
        if (smallest_index != i) {
            std::swap(span[i], span[smallest_index]);
        }
    }
}

template<typename T>
void print_span(my_span<T> span) {
    for (std::size_t i=0; i<span.size();i++) {
        std::cout << span[i] << ", ";
    }
    std::cout << std::endl;
}

template<typename T>
void max_heapify_down_arr(my_span<T> arr, std::size_t N, std::size_t index) {
    assert(index < N);
    // assume trees on the left and right are max heaps
    std::size_t left_child_index = index * 2 + 1;
    bool has_left_subtree = left_child_index < N;
    if (!has_left_subtree) {
        return;
    }
    T& left_child_value = arr[left_child_index];
    std::size_t right_child_index = left_child_index + 1;
    bool has_right_subtree = right_child_index < N;
    if (
        arr[index] < left_child_value ||
        (has_right_subtree && arr[right_child_index] > arr[index])
    ) {
        if (has_right_subtree && left_child_value < arr[right_child_index]) {
            std::swap(arr[index], arr[right_child_index]);
            max_heapify_down_arr(arr, N, right_child_index);
        } else {
            std::swap(arr[index], arr[left_child_index]);
            max_heapify_down_arr(arr, N, left_child_index);
        }
    }
}

template<typename T>
void heap_sort(my_span<T> span) {
    for (
        std::size_t i = (span.size()/2)-1;
        i < std::numeric_limits<std::size_t>::max();
        i--
    ) {
        max_heapify_down_arr(span, span.size(), i);
    }

    for (std::size_t i=span.size()-1; i!=0; i--) {
        std::swap(span[0], span[i]);
        max_heapify_down_arr(span, i, 0);
    }
}

template<typename T>
void bst_sort(my_span<T> span) {
    binary_search_tree my_bst {};
    for (std::size_t i=0; i<span.size(); i++) {
        my_bst.insert(span[i]);
    }
    for (std::size_t i=0; i<span.size(); i++) {
        span[i] = my_bst.find_min();
        my_bst.remove(span[i]);
    }
}

}
