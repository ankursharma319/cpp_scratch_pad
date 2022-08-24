#include "algo_practice.hpp"
#include <unordered_map>

namespace {

bool _is_palindrome_permutation_v1(std::string const& s) {
    // standardize case, remove all non a-z chars
    // std::unordered_map populated character counts
    // if all but one of counts is even, then its a palindrome
    // otherwise its not a palindrome permutation

    std::unordered_map<char, bool> is_even_count_map {};
    for (char c: s) {
        char standardized_char;
        if (c >= 'a' && c <= 'z') {
            standardized_char = c;
        } else if(c >= 'A' && c <= 'Z') {
            standardized_char = (c - 'A' + 'a');
        } else {
            continue;
        }
        if (is_even_count_map.count(standardized_char) == 0) {
            is_even_count_map.insert({standardized_char, false});
        } else {
            is_even_count_map[standardized_char] = !is_even_count_map.at(standardized_char);
        }
    }
    bool one_odd_found = false;
    for(std::pair<const char, bool> const& pair : is_even_count_map) {
        if (!pair.second) {
            if (one_odd_found) {
                return false;
            }
            one_odd_found = true;
        }
    }
    return true;
}

}

namespace ankur {

bool is_palindrome_permutation(std::string const& s) {
    return _is_palindrome_permutation_v1(s);
}

}
