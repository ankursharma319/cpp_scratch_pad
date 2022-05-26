#include "string_algos.hpp"
#include <cstddef>
#include <iostream>

namespace ankur {

// naive algorithm
bool substr_contains_v1(
    char const * big_string,
    std::size_t big_size,
    char const * small_string,
    std::size_t small_size
) {
    bool found = false;
    for (std::size_t i=0; i<big_size-small_size; i++) {
        char const * sub_string = big_string + i;
        found = true;
        for (std::size_t j=0; j<small_size; j++) {
            if(sub_string[j] != small_string[j]) {
                found = false;
                break;
            }
        }
        if (found) {
            return true;
        }
    }
    return false;
}

}
