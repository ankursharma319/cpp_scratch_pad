#include "MyTypes.hpp"
#include <iostream>
#include <cmath>

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

double Complex::magnitude() const {
    return sqrt(pow(imaginary(), 2) + pow(real(), 2));
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

bool Complex::operator<(const Complex& a) const {
    return this->magnitude() < a.magnitude();
}

bool operator> (const Complex& lhs, const Complex& rhs) {
    return rhs < lhs;
}

bool operator<=(const Complex& lhs, const Complex& rhs) {
    return !(lhs > rhs);
}

bool operator>=(const Complex& lhs, const Complex& rhs) {
    return !(lhs < rhs);
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

namespace {

template <size_t N>
constexpr auto my_size(char (&)[N]) {
    return N;
}

template<typename T>
T my_min(const T& x, const T& y) {
    std::cout << "Normal Template function min" << std::endl;
    if (x > y) {
        return y;
    }
    return x;
}

template<>
double my_min(const double& x, const double& y) {
    std::cout << "Template specialization function for double min" << std::endl;
    if (x > y) {
        return y;
    }
    return x;
}

template<>
std::string my_min(const std::string& x, const std::string& y) {
    std::cout << "Template specialization function for std::string min" << std::endl;
    if (x.size() > y.size()) {
        return y;
    }
    return x;
} 

Complex my_min(Complex& x, Complex& y) {
    std::cout << "my_min overload for complex numbers called" << std::endl;
    if (x > y) {
        return y;
    }
    return x;
}

}

template<typename T, std::size_t SIZE>
T& MyArray<T, SIZE>::operator[](std::size_t idx) {
    return arr_[idx];
}

template<typename T, std::size_t SIZE>
const T& MyArray<T, SIZE>::operator[](std::size_t idx) const {
    return arr_[idx];
}

template<typename T, std::size_t SIZE>
constexpr size_t MyArray<T, SIZE>::size() const {
    return SIZE;
}

template<typename T, std::size_t SIZE>
T* MyArray<T, SIZE>::data() {
    return std::addressof(arr_[0]);
}

template<typename T, std::size_t SIZE>
T* MyArray<T, SIZE>::begin() {
    return data();
}

template<typename T, std::size_t SIZE>
T* MyArray<T, SIZE>::end() {
    return data() + size();
}

template<typename T, std::size_t SIZE>
template<typename U>
void MyArray<T, SIZE>::addToEachElement(const U& u) {
    for (auto it = begin(); it != end(); it++) {
        *it += u;
    }
}

namespace {

void demonstrate_func_templates() {
    char buffer[16]{};
    std::cout << "Size of buffer is = " << my_size(buffer) << std::endl;

    // rvalues do bind to const ref
    //This one goes to the normal template func
    int minInt = my_min(4, -10);
    std::cout << "Min between two ints 4, -10 is " <<  minInt << std::endl;

    std::string x("hi");
    std::string y("hey");
    std::string minString { my_min(x, y) };
    //This one goes to the template specialization func
    std::cout << "Min between two strings " << x << ", " << y << " is " <<  minString << std::endl;

    double dx{0.567}, dy{10.56};
    double minDouble {my_min(dx, dy)};
    //This one goes to the template specialization func
    std::cout << "Min between two doubles " << dx << ", " << dy << " is " <<  minDouble << std::endl;

    Complex c1{4, 2};
    Complex c2{-1, 5};
    Complex minC {my_min(c1, c2)};
    //This one goes to the overloaded func
    std::cout << "Min between two complexes " << c1 << ", " << c2 << " is " <<  minC << std::endl;

    //This one goes to the normal template
    // because rvalue dont bind to non const ref
    Complex minC2 {my_min(Complex{0, 0}, Complex{1, 2})};
    std::cout << "Min between two rvalue complexes (0, 0) and (1, 2) is " <<  minC2 << std::endl;
}

template <size_t N>
using MyCharArray = MyArray<char, N>;

void demonstrate_class_templates() {
    MyArray<int, 5> primes {2, 3, 5, 7, 11};
    std::cout << "Created array with " << primes.size() << " primes" << std::endl;
    std::cout << "Element at begin = " << *primes.begin() << std::endl;
    std::cout << "Address at begin = " << primes.begin() << std::endl;
    std::cout << "Address at end = " << primes.end() << std::endl;
    std::cout << "Element at 2th index = " << primes[2] << std::endl;

    //Create array of 0 ints - gives error because cannot declar int arr_[0] 
    //MyArray<int, 0> zeroLenArray {};
    //std::cout << "Created array with " << zeroLenArray.size() << " ints" << std::endl;

    MyArray<float, 3> floats {1.5, 4.0f, 5.5f};
    std::cout << "Created array with " << floats.size() << " floats" << std::endl;
    std::cout << "Element at 2th index = " << floats[2] << std::endl;
    floats.addToEachElement(5);
    std::cout << "Element at 2th index after addToEachElement(5) = " << floats[2] << std::endl;

    MyCharArray<4> my_chars {"hey"};
    std::cout << "Created array with " << my_chars.size() << " chars" << std::endl;
}

}

void demonstrate_templates() {
    //demonstrate_func_templates();
    (void) demonstrate_func_templates;
    demonstrate_class_templates();
}
