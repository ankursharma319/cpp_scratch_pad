#ifndef MY_COMPLEX_HPP
#define MY_COMPLEX_HPP

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

#endif
