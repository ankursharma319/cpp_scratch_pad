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
#include <functional>
#include "linked_list.hpp"

namespace ankur {

namespace chained_hash_map_detail {

template<typename K, typename V>
struct item {
    K key;
    V value;
};

}

template<typename K, typename V>
class chained_hash_map {

public:

    using _arr_type = ankur::linked_list<chained_hash_map_detail::item<K, V>>;
    chained_hash_map()
    : m_array_capacity(8)
    , m_array_occupied_size(0)
    , m_array(new _arr_type[m_array_capacity])
    {};

    ~chained_hash_map() {
        delete[] m_array;
    }

    void insert(K const& key, V const& val) {
        (void) key;
        (void) val;
    }

    void remove(K const& key) {
        (void) key;
    }

    bool contains(K const& key) const {
        (void) key;
        return false;
    }

    std::size_t size() const {
        return 0;
    }

private:
    std::size_t m_array_capacity;
    std::size_t m_array_occupied_size;
    ankur::linked_list<chained_hash_map_detail::item<K, V>>* m_array {nullptr};
};

}

#endif
