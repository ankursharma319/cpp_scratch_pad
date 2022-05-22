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
        rehash_if_required();
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
        rehash_if_required();
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
    using _linked_list_type = ankur::linked_list<chained_hash_map_detail::item<K, V>>;
    using _arr_type = std::unique_ptr<_linked_list_type>;

    void rehash_if_required() {
        float current_factor = current_load_factor();
        bool array_too_big = current_factor < m_min_load_factor && m_array_occupied_size > 4;
        bool array_too_small = current_factor > m_max_load_factor;

        /*std::cout << "hash_map: rehash_if_required: m_array_capacity = " << m_array_capacity << std::endl;
        std::cout << "hash_map: rehash_if_required: m_array_occupied_size = " << m_array_occupied_size << std::endl;
        std::cout << "hash_map: rehash_if_required: current_load_factor = " << current_factor << std::endl;
        std::cout << "hash_map: rehash_if_required: array_too_big = " << array_too_big << std::endl;
        std::cout << "hash_map: rehash_if_required: array_too_small = " << array_too_small << std::endl;*/

        if (!array_too_big && !array_too_small) {
            return;
        }
        std::size_t target_capacity = m_array_occupied_size / m_min_load_factor;
        if (array_too_big) {
            target_capacity = m_array_occupied_size / m_max_load_factor;
        }
        do_rehash(target_capacity);
    }

    void do_rehash(std::size_t target_capacity) {
        //std::cout << "hash_map: do_rehash: target_capacity = " << target_capacity << std::endl;
        _arr_type* new_array = new _arr_type[target_capacity] {0};
        // loop through all items in old array and move them to new array
        for (std::size_t i = 0; i < m_array_capacity; i++) {
            if (m_array[i].get() == nullptr) {
                continue;
            }
            for (auto it = m_array[i]->cbegin(); it != m_array[i]->cend(); it++) {
                std::size_t new_index = hash(it->key, target_capacity);
                if (new_array[new_index].get() == nullptr) {
                    new_array[new_index] = std::make_unique<_linked_list_type>();
                }
                auto new_it = new_array[new_index]->cbegin();
                auto before_end_it = new_array[new_index]->cbefore_begin();
                while(new_it != new_array[new_index]->cend()) {
                    assert(it->key != new_it->key);
                    before_end_it = new_it++;
                }
                new_array[new_index]->insert_after(before_end_it, *it);
            }
        }
        delete[] m_array;
        m_array_capacity = target_capacity;
        m_array = new_array;
    }

    bool resize_required() const {
        float current_factor = current_load_factor();
        bool array_too_big = current_factor < m_min_load_factor && m_array_occupied_size > 4;
        bool array_too_small = current_factor > m_max_load_factor;
        return array_too_big || array_too_small;
    }

    inline float current_load_factor() const {
        return m_array_occupied_size / (float)m_array_capacity;
    }

    std::size_t hash(K const& key) const {
        return hash(key, m_array_capacity);
    }
    std::size_t hash(K const& key, std::size_t capacity) const {
        return m_pre_hash_fn(key) % capacity;
    }

    std::size_t m_array_capacity;
    std::size_t m_array_occupied_size;
    _arr_type* m_array {nullptr};
    Hash m_pre_hash_fn;
    const float m_min_load_factor = 0.4;
    const float m_max_load_factor = 1.0;
};

}

#endif
