#ifndef MY_SPAN_HPP
#define MY_SPAN_HPP

#include <cstddef>
#include <array>

template<typename T>
class my_span {
public:

    constexpr my_span() : data_(nullptr), size_(0) {}

    constexpr my_span(T* ptr, size_t sz): data_(ptr), size_(sz) {}

    template<size_t N>
    constexpr my_span(std::array<T, N> arr): data_(arr.data()), size_(N) {}

    template<size_t N>
    constexpr my_span(T (&arr)[N]): data_(&arr[0]), size_(N) {}

    constexpr size_t size() { return size_; }
    constexpr bool empty() { return size_ > 0 && data_ != nullptr; }
    T* data();
    T* begin() { return data_; }
    T* end() { return data_ + size_; }
    T const * cbegin();
    T const * cend();
private:
    T* data_;
    const size_t size_;
};

#endif
