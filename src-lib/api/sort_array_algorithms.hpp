#include <cstddef>
#include <iostream>
#include <limits>
#include <cassert>
#include <cmath>
#include "binary_search_tree.hpp"
#include "avl_tree.hpp"
#include "my_span.hpp"

namespace ankur {

template<typename T>
void insertion_sort(my_span<T> span);

template<typename T>
void selection_sort(my_span<T> span);

template<typename T>
void merge_sort(my_span<T> span);

template<typename T>
void heap_sort(my_span<T> span);

template<typename T>
void bst_sort(my_span<T> span);

template<typename T>
void counting_sort_v1(my_span<T> span);

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
void merge_sorted_spans(my_span<T>& span, std::size_t start, std::size_t mid, std::size_t end) {
    assert(start < end);
    assert(start <= mid);
    assert(mid <= end);
    assert(span.size() > end - start);
    assert(mid-start <= end-start);

    // populate copy of arrays
    std::size_t const left_size = mid - start + 1;
    std::size_t const right_size = end - mid;
    T* left = new T[left_size];
    T* right = new T[right_size];
    std::size_t left_index = 0;
    std::size_t right_index = 0;
    std::size_t span_index = start;
    for (; span_index <= mid; span_index++, left_index++) {
        assert(left_index < left_size);
        left[left_index] = span[span_index];
    }
    for (; span_index <= end; span_index++, right_index++) {
        assert(right_index < right_size);
        right[right_index] = span[span_index];
    }
    assert(left_index == left_size);
    assert(right_index == right_size);
    assert(span_index == end + 1);
    span_index = start;
    left_index = 0;
    right_index = 0;
    while(span_index <= end) {
        if (right_index >= right_size || left[left_index] <= right[right_index]) {
            span[span_index] = left[left_index];
            left_index++;
        } else {
            span[span_index] = right[right_index];
            right_index++;
        }
        span_index++;
    }
    delete[] left;
    delete[] right;
}

template<typename T>
void do_merge_sort(my_span<T>& span, std::size_t start, std::size_t end) {
    assert(span.size() > end - start);
    if (end - start < 1) {
        return;
    }
    std::size_t midpoint = start + (end - start) / 2;
    do_merge_sort(span, start, midpoint);
    do_merge_sort(span, midpoint + 1, end);
    merge_sorted_spans(span, start, midpoint, end);
}

template<typename T>
void merge_sort(my_span<T> span) {
    return do_merge_sort(span, std::size_t(0), span.size()-1);
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

template<typename T>
void avl_sort(my_span<T> span) {
    avl_tree tree {};
    for (std::size_t i=0; i<span.size(); i++) {
        tree.insert(span[i]);
    }
    for (std::size_t i=0; i<span.size(); i++) {
        span[i] = tree.find_min();
        tree.remove(span[i]);
    }
}

template<typename T>
void counting_sort_v1(my_span<T> span) {
    std::size_t counts_size = (std::size_t) pow(2, sizeof(T)*8);
    std::size_t* counts = new std::size_t[counts_size]{ 0 };
    // we assume that T starts on 0
    // if not, we need a separate mapping function from a value T t
    // to index in counts. Probably something that just offsets.
    // for something like floats, would need to come up with a more
    // complex mapping function
    for (auto it = span.begin(); it != span.end(); it++) {
        counts[*it]++;
    }
    std::size_t n_inserted = 0;
    for (std::size_t i=0; i < counts_size; i++) {
        if (counts[i] == 0) {
            continue;
        }
        for (std::size_t j=0; j<counts[i]; j++) {
            span[n_inserted] = i;
            n_inserted ++;
        }
    }
    delete[] counts;
}

}
