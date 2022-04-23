#include <cstddef>
#include <iostream>

namespace ankur {

template<typename T, std::size_t N>
void insertion_sort(T (&arr)[N]);

template<typename T, std::size_t N>
void selection_sort(T (&arr)[N]);

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

}
