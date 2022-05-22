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

template<typename K, typename V, typename Hash = std::hash<K>>
class chained_hash_map {

public:

    using _linked_list_type = ankur::linked_list<chained_hash_map_detail::item<K, V>>;
    using _arr_type = std::unique_ptr<_linked_list_type>;
    chained_hash_map()
    : m_array_capacity(8)
    , m_array_occupied_size(0)
    , m_array(new _arr_type[m_array_capacity]{0})
    , m_pre_hash_fn()
    {};

    ~chained_hash_map() {
        delete[] m_array;
    }

    bool insert(K const& key, V const& value) {
        std::size_t index = hash(key);
        assert(index < m_array_capacity);
        if (m_array[index].get() == nullptr) {
            m_array[index] = std::make_unique<_linked_list_type>();
        }
        auto it = m_array[index]->cbegin();
        auto before_end_it = m_array[index]->cbefore_begin();
        while(it != m_array[index]->cend()) {
            if (it->key == key) {
                return false;
            }
            before_end_it = it++;
        }
        chained_hash_map_detail::item<K, V> _item = {key, value};
        m_array[index]->insert_after(before_end_it, std::move(_item));
        m_array_occupied_size++;
        return true;
    }

    bool remove(K const& key) {
        std::size_t index = hash(key);
        assert(index < m_array_capacity);
        if (m_array[index].get() == nullptr) {
            return false;
        }
        auto it = m_array[index]->cbegin();
        auto prev_it = m_array[index]->cbefore_begin();
        while(it != m_array[index]->cend()) {
            if (it->key == key) {
                break;
            }
            prev_it = it++;
        }
        if (it == m_array[index]->cend()) {
            return false;
        }
        m_array[index]->erase_after(prev_it);
        m_array_occupied_size--;
        if (m_array[index]->empty()) {
            m_array[index] = nullptr;
        }
        return true;
    }

    V& operator[](K const& key) {
        std::size_t index = hash(key);
        assert(index < m_array_capacity);
        if (m_array[index].get() == nullptr) {
            m_array[index] = std::make_unique<_linked_list_type>();
        }
        auto it = m_array[index]->cbegin();
        auto prev_it = m_array[index]->cbefore_begin();
        bool found = false;
        while(it != m_array[index]->cend()) {
            if (it->key == key) {
                found = true;
                break;
            }
            prev_it = it++;
        }
        if (found) {
            auto non_const_it = typename _linked_list_type::iterator(it);
            return non_const_it->value;
        }
        chained_hash_map_detail::item<K, V> _item = {key, V()};
        auto inserted_it = m_array[index]->insert_after(prev_it, std::move(_item));
        m_array_occupied_size++;
        return inserted_it->value;
    }

    bool contains(K const& key) const {
        std::size_t index = hash(key);
        assert(index < m_array_capacity);
        if (m_array[index].get() == nullptr) {
            return false;
        }
        for(auto it = m_array[index]->cbegin(); it != m_array[index]->cend(); it++) {
            if (it->key == key) {
                return true;
            }
        }
        return false;
    }

    std::size_t size() const {
        return m_array_occupied_size;
    }

private:
    std::size_t hash(K const& key) const {
        return m_pre_hash_fn(key) % m_array_capacity;
    }

    std::size_t m_array_capacity;
    std::size_t m_array_occupied_size;
    _arr_type* m_array {nullptr};
    Hash m_pre_hash_fn;
};

}

#endif
