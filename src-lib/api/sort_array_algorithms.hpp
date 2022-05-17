#include <algorithm>
#include <array>
#include <cstddef>
#include <cstdint>
#include <iostream>
#include <limits>
#include <cassert>
#include <cmath>
#include <type_traits>
#include <vector>
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
void counting_sort_v2(my_span<T> span, std::size_t digit_number, std::size_t base);

template<typename T>
void radix_sort(my_span<T> span, std::size_t base=10);

template<typename T>
void quick_sort(my_span<T> span);

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
    assert(std::is_integral_v<T>);
    // we assume that T starts on 0
    // if not, we need a separate mapping function from a value T t
    // to index in counts. Probably something that just offsets.
    // for something like floats, would need to come up with a more
    // complex mapping function
    for (auto it = span.begin(); it != span.end(); it++) {
        assert(*it >= 0); // didnt implement, too lazy
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

template<typename T>
T get_digit_at_nth_position(T number, std::size_t digit_number, std::size_t base) {
    assert(std::is_integral_v<T>);
    if constexpr (!std::is_unsigned_v<T>) {
        number = abs(number);
    }
    return (number/(T)pow(base, digit_number)) % base;
}

template<typename T>
void counting_sort_v2(my_span<T> span, std::size_t digit_number, std::size_t base) {
    assert(std::is_integral_v<T>);
    // doesnt sort signed integers correctly
    // (sorts them as if they were positive also)
    // users of counting sort (i.e. radix sort)
    // should do something about negative integers
    assert(base > 0);

    // populate counts of each digit
    std::size_t* counts = new std::size_t[base]{ 0 };
    for (auto it = span.begin(); it != span.end(); it++) {
        counts[get_digit_at_nth_position(*it, digit_number, base)]++;
    }

    // transform counts into cumulative
    for (std::size_t i=1; i < base; i++) {
        counts[i] = counts[i-1] + counts[i];
    }

    //duplicate the output to be sorted
    std::vector<T> dup (span.begin(), span.end());
    // go from back to front to maintain property of stability
    for (auto it = dup.rbegin(); it != dup.rend(); it++) {
        std::size_t index_in_counts = get_digit_at_nth_position(*it, digit_number, base);
        std::size_t num_elems_less_or_equal = counts[index_in_counts];
        std::size_t new_pos = num_elems_less_or_equal - 1;
        span[new_pos] = *it;
        counts[index_in_counts]--;
    }
    delete[] counts;
}

template<typename T>
void radix_sort(my_span<T> span, std::size_t base) {
    auto [min_it, max_it] = std::minmax_element(span.begin(), span.end());
    assert(min_it != span.end());
    assert(max_it != span.end());
    T abs_max_element = *max_it;
    if constexpr (!std::is_unsigned_v<T>) {
        if (abs(*min_it) > abs_max_element) {
            abs_max_element = abs(*min_it);
        }
    }
    std::size_t n_digits = (log(abs_max_element)/log(base)) + 1;
    for (std::size_t digit_number=0; digit_number<n_digits; digit_number++) {
        counting_sort_v2(span, digit_number, base);
    } 
    if constexpr (!std::is_unsigned_v<T>) {
        // handle the negative values properly
        std::vector<T> negative_values {};
        std::vector<T> positive_values {};
        for (auto it = span.begin(); it != span.end(); it++) {
            if(*it < 0) {
                negative_values.push_back(*it);
            } else {
                positive_values.push_back(*it);
            }
        }
        std::size_t i = 0;
        for (auto it = negative_values.rbegin(); it != negative_values.rend(); it++, i++) {
            span[i] = *it;
        }
        for (auto it = positive_values.begin(); it != positive_values.end(); it++, i++) {
            span[i] = *it;
        }
        assert(i == span.size());
    }
}

template<typename T>
void move_pivot_to_right(my_span<T>& span, std::size_t start, std::size_t end) {
    T& left = span[start];
    T& right = span[end];
    std::size_t mid_index = start + (end-start)/2;
    T& mid = span[mid_index];
    if (((left > right) && (left < mid)) || ((left < right) && (left > mid))) {
        std::swap(left, right);
        return;
    }
    if (((mid > left) && (mid < right)) || ((mid < left) && (mid > right))) {
        std::swap(mid, right);
    }
}

template<typename T>
std::size_t quicksort_partition_lomuto(my_span<T>& span, std::size_t start, std::size_t end) {
    assert(span.size() > end);
    assert(end > start);
    move_pivot_to_right(span, start, end);
    T const& pivot = span[end];
    my_span<T> interesting_span (&span[start], end-start+1);
    std::size_t temporary_pivot_index = start;
    for (std::size_t i=start; i<end; i++) {
        if (span[i] < pivot) {
            std::swap(span[i], span[temporary_pivot_index]);
            temporary_pivot_index++;
        }
    }
    std::swap(span[end], span[temporary_pivot_index]);
    return temporary_pivot_index;
}

template<typename T>
void do_quick_sort_lomuto(my_span<T>& span, std::size_t start, std::size_t end) {
    assert(span.size() > end);
    assert(end > start);
    std::size_t partition_index = quicksort_partition_lomuto(span, start, end);
    assert(partition_index >= start);
    assert(partition_index <= end);
    if (partition_index > start + 1) {
        do_quick_sort_lomuto(span, start, partition_index - 1);
    }
    if (partition_index + 1 < end) {
        do_quick_sort_lomuto(span, partition_index + 1, end);
    }
}

template<typename T>
void quick_sort_v1(my_span<T> span) {
    do_quick_sort_lomuto(span, 0, span.size()-1);
}

}
