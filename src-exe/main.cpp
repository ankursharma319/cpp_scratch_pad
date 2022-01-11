#include <iostream>
#include "MyTypes.hpp"

void demonstrate_operators();

int main() {
    std::cout << "Hello World!" << std::endl;
    //demonstrate_operators();
    demonstrate_templates();
    return 0;
}

void demonstrate_operators() {
    Complex c1 {1, 2};
    c1 = {3, 4};
    Complex c2 = {7, 8};
    Complex c3 (10, 20);
    //Complex c4 = (30, 40); //error
    std::cout << "c1 = " << c1 << std::endl << "c2 = " << c2 << std::endl;
    std::string c3_as_string = c3;
    std::cout << "c3_as_string = " << c3_as_string << std::endl;
    std::cout << "static_cast<std::string>(c3) = " << static_cast<std::string>(c3) << std::endl;
    // Complex c5 = static_cast<Complex>(3); //error
    Complex c6 = !c3;
    std::cout << "Conjugate !c3 = " << c6 << std::endl;
    Complex c7 = c3 + c2;
    std::cout << "c3 + c2 = " << c7 << std::endl;
    Complex c8 = c3 - c2;
    std::cout << "c3 - c2 = " << c8 << std::endl;
    Complex c9 = c3++;
    std::cout << "c3++ = " << c9 << std::endl;
    Complex c10 = 77_im;
    std::cout << "77_im = " << c10 << std::endl;
}
