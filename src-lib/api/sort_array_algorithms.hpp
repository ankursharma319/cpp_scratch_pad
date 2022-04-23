#include <cstddef>
#include <iostream>

namespace ankur {

template<typename T, std::size_t N>
void insertion_sort(T (&arr)[N]);

template<typename T, std::size_t N>
void selection_sort(T (&arr)[N]);

template<typename T, std::size_t N>
void insertion_sort(T (&arr)[N]) {
    (void) arr;
}

template<typename T, std::size_t N>
void selection_sort(T (&arr)[N]) {
    (void) arr;
}

}
