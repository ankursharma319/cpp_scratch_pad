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

    node(int _data = 0, node * _prev = nullptr, node * _next = nullptr)
    : data(_data), prev(_prev), next(_next)
    {
        if (!prev) {
            prev = this;
        }
        if (!next) {
            next = this;
        }
        link();
    }

    ~node() {
        unlink();
    }

    void link() {
        if (prev != this) {
            prev->next = this;
        }
        if (next != this) {
            next->prev = this;
        }
    }

    void unlink() {
        if (prev != this) {
            prev->next = next;
        }
        if (next != this) {
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
    doubly_linked_list_iterator& operator--() {
        assert(m_node_ptr);
        m_node_ptr = m_node_ptr->prev;
        return *this;
    }

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
    doubly_linked_list(): m_sentinel(new detail::node()) {}

    explicit doubly_linked_list(std::size_t count)
    : doubly_linked_list()
    {
        detail::node * previous = m_sentinel;
        for (std::size_t i=0; i<count; i++) {
            detail::node * current = new detail::node(0, previous, m_sentinel);
            previous = current;
        }
        m_sentinel->prev = previous;
    }

    template<class InputIt>
    explicit doubly_linked_list(InputIt first, InputIt last)
    : doubly_linked_list()
    {
        detail::node * previous = m_sentinel;
        for (auto it = first; it != last; it++) {
            detail::node * current = new detail::node(*it, previous, m_sentinel);
            previous = current;
        }
        m_sentinel->prev = previous;
    }

    explicit doubly_linked_list(std::initializer_list<int> init)
    : doubly_linked_list(init.begin(), init.end())
    {}

    ~doubly_linked_list() {
        clear();
    }

    //  Element access

    int& front() {
        return _head_node()->data;
    }

    int& back() {
        return _tail_node()->data;
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
        return _head_node() == m_sentinel;
    }

    // iterators

    iterator begin() const {
        return iterator(_head_node());
    }

    iterator end() const {
        return iterator(m_sentinel);
    }


    // modifiers

    iterator erase(iterator pos) {
        assert(pos != end());
        detail::node * to_delete = pos.m_node_ptr;
        iterator to_return = ++pos;
        delete to_delete;
        return to_return;
    }

    void clear() {
        for (auto it = begin(); it != end();) {
            it = erase(it);
        }
    }

    iterator insert(iterator pos, int value) {
        detail::node * current = new detail::node(value, pos.m_node_ptr->prev, pos.m_node_ptr);
        return iterator(current);
    }

    void push_front(int value) {
        insert(begin(), value);
    }

    void push_back(int value) {
        insert(end(), value);
    }

    int pop_front() {
        int to_return = *begin();
        erase(begin());
        return to_return;
    }

    int pop_back() {
        int to_return = _tail_node()->data;
        erase(iterator(_tail_node()));
        return to_return;
    }

    // operations

    void merge(doubly_linked_list& other) {
        // assumes sorted lists
        iterator it_a = begin();
        iterator it_b = other.begin();
        while (it_a != end() && it_b != end()) {
            assert(it_a.m_node_ptr != m_sentinel);
            assert(it_b.m_node_ptr != other.m_sentinel);

            if (*it_a > *it_b) {
                assert(it_b.m_node_ptr == other._head_node());
                it_b.m_node_ptr->unlink();
                _insert_node(it_a, it_b.m_node_ptr);
                it_b = other.begin();
            } else {
                ++it_a;
            }
        }

        if (!other.empty()) {
            // move rest of other into this
            assert(it_a.m_node_ptr == _tail_node());
            assert(it_b.m_node_ptr == _head_node());
            _tail_node()->next = it_b.m_node_ptr;
            _tail_node()->link();
            m_sentinel->prev = (--(other.end())).m_node_ptr;
        }
    }

    void remove(int value) {
        (void) value;
    }

    void reverse() {
    }

    void sort() { 
    }
private:
    iterator _insert_node(iterator pos, detail::node* node) {
        node->next = pos.m_node_ptr;
        node->prev = pos.m_node_ptr->prev;
        node->link();
        return iterator(node);
    }

    detail::node * _head_node() const {
        return m_sentinel->next;
    }
    detail::node * _tail_node() const {
        return m_sentinel->prev;
    }

    detail::node * m_sentinel;
};

bool operator==(const doubly_linked_list& lhs, const doubly_linked_list& rhs) {
    return std::equal(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
}

}

#endif
