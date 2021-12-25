#include "MyTypes.hpp"
#include <iostream>

Complex::Complex(int re, int im)
: real_{re}
, imaginary_{im}
{
    std::cout << "Conversion Ctor called with real=" << re << " and imaginary="<< im << std::endl;
    (void) re;
    (void) im;
}

int Complex::real() const {
    return real_;
}

int Complex::imaginary() const {
    return imaginary_;
}

Complex::operator std::string() const {
    //std::cout << "string Conversion Operator" << std::endl;
    return "Real=" + std::to_string(real_) + ", Imaginary=" + std::to_string(imaginary_);
}

Complex Complex::operator! () const {
    return Complex(real_, -imaginary_);
}

Complex Complex::operator-(const Complex& b) const {
    return Complex(real_ - b.real(), imaginary_ - b.imaginary());
}

Complex Complex::operator++(int) {
    real_++;
    imaginary_++;
    return *this;
}

Complex operator+(const Complex& a, const Complex& b) {
    return Complex(a.real() + b.real(), a.imaginary() + b.imaginary());
}

std::ostream& operator <<(std::ostream& stream, const Complex& complex) {
    stream << "Real part = " << complex.real() << ", Imaginary part = " << complex.imaginary() << ".";
    return stream;
}

Complex operator "" _im(unsigned long long im) {
    return Complex(0, im);
}
