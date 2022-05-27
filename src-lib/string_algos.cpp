#include "string_algos.hpp"
#include <cstddef>
#include <cassert>
#include <cmath>
#include <vector>

namespace {

class rolling_hash {
public:
    rolling_hash()
    : m_current_size(0)
    , m_current_hash(0)
    {}

    std::size_t operator()() const {
        assert(m_current_size == m_current_string.size());
        return m_current_hash;
    }

    void append(char x) {
        assert(m_current_size == m_current_string.size());
        m_current_hash = (m_current_hash * PRIME_BASE + x) % PRIME_MOD;
        m_current_size ++;
        m_current_string.push_back(x);
    }

    void skip() {
        assert(m_current_size > 0);
        assert(m_current_size == m_current_string.size());
        std::size_t subtractand = (m_current_string.front() * pow_without_overflow(PRIME_BASE, m_current_size-1, PRIME_MOD)) % PRIME_MOD;
        if (subtractand > m_current_hash) {
            m_current_hash = PRIME_MOD - (subtractand - m_current_hash);
        } else {
            m_current_hash -= subtractand;
        }
        m_current_size--;
        m_current_string.erase(m_current_string.begin());
    }

private:
    std::size_t pow_without_overflow(std::size_t base, std::size_t exp, std::size_t mod) const {
        std::size_t power = 1;
        for (std::size_t i = 0; i < exp; i++) {
            power = (power * base) % mod;
        }
        return power;
    }
    const std::size_t PRIME_BASE = 100;
    const std::size_t PRIME_MOD = 1000000007;
    std::size_t m_current_size = 0;
    std::size_t m_current_hash = 0;
    std::vector<char> m_current_string;
};

}

namespace ankur {

// naive algorithm
bool substr_contains_v1(
    char const * big_string,
    std::size_t big_size,
    char const * small_string,
    std::size_t small_size
) {
    assert(big_size >= small_size);
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

// smarter karp rabin algo
bool substr_contains_v2(
    char const * big_string,
    std::size_t big_size,
    char const * small_string,
    std::size_t small_size
) {
    assert(big_size >= small_size);
    rolling_hash rh_small, rh_rolling;
    /*
    std::cout << "--------------------------------------" << std::endl;
    std::cout << "Trying to find if substr_contains_v2 where big_string = " << big_string << " and small string = " << small_string << std::endl;
    std::cout << "--------------------------------------" << std::endl;
    std::cout << "STARTING LOOP OVER SMALL STRING" << std::endl;
    */
    bool _found_in_first_try = true;
    for (std::size_t i=0; i<small_size; i++) {
        //std::cout << "char in small_string at i=" << i << " is " << small_string[i] << "(" << (unsigned int) small_string[i] << ")" << std::endl;
        //std::cout << "char in big_string at i=" << i << " is " << big_string[i] << "(" << (unsigned int) big_string[i] << ")" << std::endl;
        rh_small.append(small_string[i]);
        rh_rolling.append(big_string[i]);
        //std::cout << "rh_small = " << rh_small() << std::endl;
        //std::cout << "rh_rolling = " << rh_rolling() << std::endl;
        if (small_string[i] != big_string[i]) {
            _found_in_first_try = false;
        }
    }
    if (_found_in_first_try) {
        assert(rh_small() == rh_rolling());
        return true;
    }
    //std::cout << "STARTING LOOP OVER BIG STRING" << std::endl;
    for (std::size_t i=small_size; i<big_size; i++) {
        rh_rolling.skip();
        rh_rolling.append(big_string[i]);
        //std::cout << "char in big_string at i=" << i << " is " << big_string[i] << "(" << (int) big_string[i] << ")" << std::endl;
        //std::cout << "rh_small = " << rh_small() << std::endl;
        //std::cout << "rh_rolling = " << rh_rolling() << std::endl;
        if (rh_small() == rh_rolling()) {
            //std::cout << "substr_contains_v2:: hashes MATCHED at i=" << i << std::endl;
            bool matched = true;
            for (std::size_t j=0; j<small_size; j++) {
                std::size_t big_char_index = i-small_size+1+j;
                char big_char = big_string[big_char_index];
                char small_char = small_string[j];
                //std::cout << "substr_contains_v2:: comparing at i=" << i << ", j=" << j << ", big_char_index=" << big_char_index << std::endl;
                //std::cout << "substr_contains_v2:: comparing big_char=" << big_char << ", small_char=" << small_char << std::endl;
                if (big_char != small_char) {
                    matched = false;
                    break;
                }
            }
            if (matched) {
                return true;
            }
        }
    }
    return false;
}

}
