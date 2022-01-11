#ifndef MY_TYPES_HPP
#define MY_TYPES_HPP

#include <iostream>
#include <string>

class Complex {
public:
    Complex() = default;
    Complex(int re, int im);
    int real() const;
    int imaginary() const;
    double magnitude() const;
    operator std::string() const; // conversion to string
    Complex operator! () const; // in our case, conjugate
    Complex operator-(const Complex& a) const;
    Complex operator++(int);
    bool operator<(const Complex& a) const;

private:
    int real_ {0};
    int imaginary_ {0};
};

bool operator> (const Complex& lhs, const Complex& rhs);
bool operator<=(const Complex& lhs, const Complex& rhs);
bool operator>=(const Complex& lhs, const Complex& rhs);

std::ostream& operator<<(std::ostream& stream, const Complex& complex);
Complex operator+(const Complex& a, const Complex& b);

Complex operator "" _im(unsigned long long im);

template<typename T, std::size_t SIZE>
class MyArray {
public:
    T& operator[](std::size_t idx);
    const T& operator[](std::size_t idx) const;
    constexpr size_t size() const;
    T* data();
    T* begin();
    T* end();

    template<typename U>
    void addToEachElement(const U& u);

    T arr_[SIZE];
};

void demonstrate_templates();

#endif
