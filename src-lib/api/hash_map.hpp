#ifndef ANKUR_HASH_MAP_HPP
#define ANKUR_HASH_MAP_HPP

#include <cstddef>
#include <iterator>
#include <memory>
#include <sstream>
#include <type_traits>
#include <cassert>
#include <iostream>
#include <utility>

namespace ankur {

template<typename K, typename V>
class chained_hash_map {

public:
    chained_hash_map() {};

    void insert(K const& key, V const& val) {
        (void) key;
        (void) val;
    }

    bool contains(K const& key) const {
        (void) key;
        return false;
    }
};

}

#endif
