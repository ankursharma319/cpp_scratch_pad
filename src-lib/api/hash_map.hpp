#ifndef ANKUR_HASH_MAP_HPP
#define ANKUR_HASH_MAP_HPP

#include <functional>
#include <list>

namespace ankur {

template<typename K, typename V, typename Hash = std::hash<K>>
class chained_hash_map {

public:

    chained_hash_map()
    : m_array_capacity(8)
    , m_array_occupied_size(0)
    , m_array(new array_type[m_array_capacity]{})
    , m_pre_hash_fn()
    {};

    ~chained_hash_map() {
        delete[] m_array;
    }

    bool insert(K const& key, V const& value) {
        std::size_t index = hash(key);
        auto it = m_array[index].cbegin();
        while(it != m_array[index].cend()) {
            if (it->key == key) {
                return false;
            }
            it++;
        }
        item _item = {key, value};
        m_array[index].push_back(std::move(_item));
        m_array_occupied_size++;
        rehash_if_required();
        return true;
    }

    bool remove(K const& key) {
        std::size_t index = hash(key);
        auto it = m_array[index].cbegin();
        while(it != m_array[index].cend()) {
            if (it->key == key) {
                break;
            }
            it++;
        }
        if (it == m_array[index].cend()) {
            return false;
        }
        m_array[index].erase(it);
        m_array_occupied_size--;
        rehash_if_required();
        return true;
    }

    V& operator[](K const& key) {
        std::size_t index = hash(key);
        auto it = m_array[index].begin();
        while(it != m_array[index].end()) {
            if (it->key == key) {
                return it->value;
            }
            it++;
        }
        item _item = {key, V()};
        m_array[index].push_back(std::move(_item));
        m_array_occupied_size++;
        rehash_if_required();
        return (--(m_array[index].end()))->value;
    }

    bool contains(K const& key) const {
        std::size_t index = hash(key);
        for(auto it = m_array[index].cbegin(); it != m_array[index].cend(); it++) {
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

    struct item {
        K key;
        V value;
    };

    using linked_list_type = std::list<item>;
    using array_type = linked_list_type;

    void rehash_if_required() {
        float current_factor = current_load_factor();
        bool array_too_big = current_factor < m_min_load_factor && m_array_occupied_size > 4;
        bool array_too_small = current_factor > m_max_load_factor;

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
        array_type* new_array = new array_type[target_capacity] {};
        // loop through all items in old array and move them to new array
        for (std::size_t i = 0; i < m_array_capacity; i++) {
            for (auto it = m_array[i].cbegin(); it != m_array[i].cend(); it++) {
                std::size_t new_index = hash(it->key, target_capacity);
                new_array[new_index].push_back(*it);
            }
        }
        delete[] m_array;
        m_array_capacity = target_capacity;
        m_array = new_array;
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
    array_type* m_array {nullptr};
    Hash m_pre_hash_fn;
    const float m_min_load_factor = 0.4;
    const float m_max_load_factor = 1.0;
};

}

#endif
