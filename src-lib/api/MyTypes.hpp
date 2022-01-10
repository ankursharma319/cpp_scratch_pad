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
    operator std::string() const; // conversion to string
    Complex operator! () const; // in our case, conjugate
    Complex operator-(const Complex& a) const;
    Complex operator++(int);

private:
    int real_ {0};
    int imaginary_ {0};
};

std::ostream& operator<<(std::ostream& stream, const Complex& complex);
Complex operator+(const Complex& a, const Complex& b);

Complex operator "" _im(unsigned long long im);


template <size_t N>
constexpr auto my_size(char (&)[N]) {
    return N;
}

#endif
