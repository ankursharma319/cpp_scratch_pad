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
        m_current_hash = m_current_hash - m_current_string.front() * pow_without_overflow(PRIME_BASE, m_current_size-1, PRIME_MOD);
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
    const std::size_t PRIME_BASE = 97;
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
    for (std::size_t i=0; i<small_size; i++) {
        rh_small.append(small_string[i]);
        rh_rolling.append(big_string[i]);
    }
    for (std::size_t i=small_size-1; i<big_size-small_size; i++) {
        if (rh_small() == rh_rolling()) {
            bool matched = true;
            for (std::size_t j=0; j<small_size; j++) {
                if (big_string[j+i] != small_string[j]) {
                    matched = false;
                }
            }
            if (matched) {
                return true;
            }
        }
        rh_rolling.skip();
        rh_rolling.append(big_string[i]);
    }
    return false;
}

}
