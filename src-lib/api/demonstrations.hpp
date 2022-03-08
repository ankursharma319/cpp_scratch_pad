#ifndef DEMONSTRATIONS_HPP
#define DEMONSTRATIONS_HPP

#include <cstddef>
#include <type_traits>

template<typename T, std::size_t SIZE>
class MyArray {
    static_assert(not std::is_pointer <T>::value);
public:
    T& operator[](std::size_t idx);
    const T& operator[](std::size_t idx) const;
    constexpr std::size_t size() const;
    T* data();
    T* begin();
    T* end();

    template<typename U>
    void addToEachElement(const U& u);

    T arr_[SIZE];
};

void demonstrate_operators();
void demonstrate_templates();
void demonstrate_misc();

void demonstrate_linked_list();

#endif
