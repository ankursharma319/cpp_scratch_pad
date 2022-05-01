#ifndef MY_SPAN_HPP
#define MY_SPAN_HPP

#include <cstddef>
#include <array>
#include <memory>

// TODO - https://codereview.stackexchange.com/questions/217814/c17-span-implementation

template<typename T>
class my_span {
public:

    using element_type = T;
    using value_type = std::remove_cv<T>;
    using size_type = std::size_t;
    using difference_type = std::ptrdiff_t;
    using pointer = T*;
    using const_pointer = const T*;
    using reference = T&;
    using const_reference = const T&;
    using iterator = T*;
    using const_iterator = const T*;
 
    constexpr my_span() : data_(nullptr), size_(0) {}

    constexpr my_span(T* ptr, size_t sz): data_(ptr), size_(sz) {}

    template<size_t N>
    constexpr my_span(std::array<T, N>& arr): data_(arr.data()), size_(N) {}

    template<size_t N>
    constexpr my_span(T (&arr)[N]): data_(&arr[0]), size_(N) {}

    template<typename It>
    constexpr my_span(It first, It last): data_(&*first), size_(last-first) {}

    constexpr size_t size() { return size_; }
    constexpr bool empty() { return size_ > 0 && data_ != nullptr; }
    T* data() {
        return data_;
    }
    T* begin() { return data_; }
    T* end() { return data_ + size_; }
    T const * cbegin();
    T const * cend();

    T& operator[](std::size_t i) const {
        return data_[i];   
    }
private:
    T* data_;
    const size_t size_;
};

#endif
