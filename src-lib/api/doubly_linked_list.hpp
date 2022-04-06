#ifndef ANKUR_DOUBLY_LINKED_LIST_HPP
#define ANKUR_DOUBLY_LINKED_LIST_HPP

#include <cstddef>
#include <iterator>
#include <memory>
#include <sstream>
#include <type_traits>
#include <cassert>
#include <iostream>
#include <utility>

namespace ankur {

namespace detail {

struct node
{
    int data {0};
    node * prev {nullptr};
    node * next {nullptr};

    node(int _data, node * _prev, node * _next)
    : data(_data), prev(_prev), next(_next)
    {}

    void link() {
        if (prev) {
            prev->next = this;
        }
        if (next) {
            next->prev = this;
        }
    }

    void unlink() {
        if (prev) {
            prev->next = next;
        }
        if (next) {
            next->prev = prev;
        }
    }
};

struct doubly_linked_list_iterator
: public std::iterator<std::bidirectional_iterator_tag, int,std::ptrdiff_t, int*, int&>
{
    doubly_linked_list_iterator(node * node_ptr): m_node_ptr(node_ptr) {}

    int& operator*() const {
        assert(m_node_ptr);
        return m_node_ptr->data;
    }
    int* operator->() const {
        assert(m_node_ptr);
        return &(m_node_ptr->data);
    }

    doubly_linked_list_iterator& operator++() {
        assert(m_node_ptr);
        m_node_ptr = m_node_ptr->next;
        return *this;
    }

    doubly_linked_list_iterator operator++(int);
    doubly_linked_list_iterator& operator--();
    doubly_linked_list_iterator operator--(int);
    bool operator==(doubly_linked_list_iterator const& other) const {
        return this->m_node_ptr == other.m_node_ptr;
    }
    bool operator!=(doubly_linked_list_iterator const& other) const {
        return !(*this == other);
    }
    node * m_node_ptr;
};

}

class doubly_linked_list {

public:
    using iterator = detail::doubly_linked_list_iterator;

    // constructors && assignments
    doubly_linked_list(): m_head(nullptr), m_tail(nullptr) {}

    explicit doubly_linked_list(std::size_t count)
    : doubly_linked_list()
    {
        if (count < 1) {
            return;
        }
        m_head = new detail::node(0, nullptr, nullptr);
        detail::node * previous = m_head;
        for (std::size_t i=1; i<count; i++) {
            detail::node * current = new detail::node(0, previous, nullptr);
            current->link();
            previous = current;
        }
        m_tail = previous;
    }

    template<class InputIt>
    explicit doubly_linked_list(InputIt first, InputIt last)
    : doubly_linked_list()
    {
        m_head = new detail::node(*(first++), nullptr, nullptr);
        detail::node * previous = m_head;
        for (auto it = first; it != last; it++) {
            detail::node * current = new detail::node(*it, previous, nullptr);
            current->link();
            previous = current;
        }
        m_tail = previous;
    }

    explicit doubly_linked_list(std::initializer_list<int> init)
    : doubly_linked_list(init.begin(), init.end())
    {}

    ~doubly_linked_list() = default;

    //  Element access

    int& front() {
        assert(m_head);
        return m_head->data;
    }

    int& back() {
        assert(m_tail);
        return m_tail->data;
    }

    // capacity

    std::size_t size() const {
        std::size_t size = 0;
        for (auto it = begin(); it != end(); ++it) {
            size++;
        }
        return size;
    }

    bool empty() const {
        return !m_head->next;
    }

    // iterators

    iterator begin() const {
        return iterator(m_head);
    }

    iterator end() const {
        return iterator(nullptr);
    }


    // modifiers

    iterator erase(iterator pos) {
        return pos;
    }

    void clear() {
    }

    iterator insert(iterator pos, int value) {
        assert(pos.m_node_ptr);
        detail::node * current = new detail::node(value, pos.m_node_ptr->prev, pos.m_node_ptr);
        current->link();
        return iterator(current);
    }

    void push_front(int value) {
        (void) value;
    }

    void push_back(int value) {
        (void) value;
    }

    int pop_front() {
        return 0;
    }

    int pop_back() {
        return 0;
    }

    // operations

    void merge(doubly_linked_list& other) {
        (void) other;
        // assumes sorted list
    }

    void remove(int value) {
        (void) value;
    }

    void reverse() {
    }

    void sort() { 
    }
private:
    detail::node * m_head;
    detail::node * m_tail;
};

bool operator==(const doubly_linked_list& lhs, const doubly_linked_list& rhs) {
    return std::equal(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
}

}

#endif