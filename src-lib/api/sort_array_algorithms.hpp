#include <cstddef>
#include <iostream>
#include <limits>
#include <cassert>

namespace ankur {

template<typename T, std::size_t N>
void insertion_sort(T (&arr)[N]);

template<typename T, std::size_t N>
void selection_sort(T (&arr)[N]);

template<typename T, std::size_t N>
void heap_sort(T (&arr)[N]);

template<typename T, std::size_t N>
void insertion_sort(T (&arr)[N]) {
    for (std::size_t i=1; i<N; i++) {
        for (
            std::size_t j = i;
            j > 0 && arr[j] < arr[j-1];
            j--
        ) {
            std::swap(arr[j], arr[j-1]);
        }
    }
}

template<typename T, std::size_t N>
void selection_sort(T (&arr)[N]) {
    for (std::size_t i=0; i<N; i++) {
        std::size_t smallest_index = i;
        for (std::size_t j=i; j<N; j++) {
            if (arr[j] < arr[smallest_index]) {
                smallest_index = j;
            }
        }
        if (smallest_index != i) {
            std::swap(arr[i], arr[smallest_index]);
        }
    }
}

template<typename T, std::size_t N>
void print_array(T (&arr)[N]) {
    for (std::size_t i=0; i<N;i++) {
        std::cout << arr[i] << ", ";
    }
    std::cout << std::endl;
}

template<typename T>
void max_heapify_down_arr(T* arr, std::size_t N, std::size_t index) {
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

template<typename T, std::size_t N>
void heap_sort(T (&arr)[N]) {
    for (
        std::size_t i = (N/2)-1;
        i < std::numeric_limits<std::size_t>::max();
        i--
    ) {
        max_heapify_down_arr(arr, N, i);
    }

    for (std::size_t i=N-1; i!=0; i--) {
        std::swap(arr[0], arr[i]);
        max_heapify_down_arr(arr, i, 0);
    }
}

}
