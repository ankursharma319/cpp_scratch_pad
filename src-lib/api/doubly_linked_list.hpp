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
        link();
    }

    ~node() {
        unlink();
    }

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

    bool isTail() {
        return next == nullptr;
    }
    
    bool isHead() {
        return prev == nullptr;
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
        m_head = new detail::node();
        detail::node * previous = m_head;
        for (std::size_t i=1; i<count; i++) {
            detail::node * current = new detail::node(0, previous);
            previous = current;
        }
        m_tail = previous;
    }

    template<class InputIt>
    explicit doubly_linked_list(InputIt first, InputIt last)
    : doubly_linked_list()
    {
        m_head = new detail::node(*(first++));
        detail::node * previous = m_head;
        for (auto it = first; it != last; it++) {
            detail::node * current = new detail::node(*it, previous);
            previous = current;
        }
        m_tail = previous;
    }

    explicit doubly_linked_list(std::initializer_list<int> init)
    : doubly_linked_list(init.begin(), init.end())
    {}

    ~doubly_linked_list() {
        clear();
    }

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
        return !m_head;
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
        assert(pos.m_node_ptr);
        if (pos.m_node_ptr->isHead()) {
            m_head = pos.m_node_ptr->next;
        }
        if (pos.m_node_ptr->isTail()) {
            m_tail = pos.m_node_ptr->prev;
        }
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
        detail::node * current = nullptr;
        if (!pos.m_node_ptr) {
            //assume need to push something to the end
            current = new detail::node(value, m_tail);
            m_tail = current;
        } else {
            current = new detail::node(value, pos.m_node_ptr->prev, pos.m_node_ptr);
        }
        if (current->isHead()) {
            m_head = current;
        }
        return iterator(current);
    }

    void push_front(int value) {
        insert(begin(), value);
    }

    void push_back(int value) {
        insert(end(), value);
    }

    int pop_front() {
        assert(m_head);
        int to_return = *begin();
        erase(begin());
        return to_return;
    }

    int pop_back() {
        assert(m_tail);
        int to_return = m_tail->data;
        erase(iterator(m_tail));
        return to_return;
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
