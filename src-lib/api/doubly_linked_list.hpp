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
        prev = this;
        next = this;
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
        //std::cout << "~doubly_linked_list :: size = " << size() << std::endl;
        clear();
        delete m_sentinel;
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
        /*std::cout << "doubly_linked_list::clear :: clearing list of size "
        << size() << " with m_sentinel " << m_sentinel << std::endl;
        _debug_print();*/
        for (auto it = begin(); it != end();) {
            /*std::cout <<  "Erasing " << it.m_node_ptr
            << ", is_head = " << (_head_node() == it.m_node_ptr)
            << ", is_tail = " << (_tail_node() == it.m_node_ptr)
            << std::endl;*/
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
        while (it_a != end() && it_b != other.end()) {
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
            assert(it_b.m_node_ptr == other._head_node());
            auto* other_head = other._head_node();
            auto* other_tail = other._tail_node();
            other.m_sentinel->unlink();
            other_tail->next = m_sentinel;
            other_head->prev = m_sentinel->prev;
            m_sentinel->prev->next = other_head;
            m_sentinel->prev = other_tail;
        }
    }

    void remove(int value) {
        for (auto it = begin(); it != end();) {
            if (value == *it) {
                it = erase(it);
            } else {
                ++it;
            }
        }
    }

    void reverse() {
        auto * current_node = _head_node();

        while(current_node != m_sentinel) {
            auto * old_prev = current_node->prev;
            current_node->prev = current_node->next;
            current_node->next = old_prev;
            current_node = current_node->prev;
        }

        auto * old_prev = m_sentinel->prev;
        m_sentinel->prev = m_sentinel->next;
        m_sentinel->next = old_prev;
    }

    void sort() {
        merge_sort(*this);
    }

    void _debug_print() const {
        //std::cout << "debug printing doubly linked list of size = " << size() << std::endl;
        std::cout << "--------------------" << std::endl;
        std::cout << "|                  |" << std::endl;
        std::cout << "|  val = sentinel  |" << std::endl;
        std::cout << "| addr = " << m_sentinel << " |" << std::endl;
        std::cout << "| prev = " << m_sentinel->prev << " |" << std::endl;
        std::cout << "| next = " << m_sentinel->next << " |" << std::endl;
        std::cout << "|                  |" << std::endl;
        std::cout << "--------------------" << std::endl;
        std::cout << "         ^          " << std::endl;
        std::cout << "         |          " << std::endl;
        std::cout << "         |          " << std::endl;
        std::cout << "         v          " << std::endl;
        for (auto it = begin(); it != end(); ++it) {
            std::cout << "--------------------" << std::endl;
            std::cout << "|                  |" << std::endl;
            std::cout << "|     val = " << *it << "      |" << std::endl;
            std::cout << "| addr = " << it.m_node_ptr << " |" << std::endl;
            std::cout << "| prev = " << it.m_node_ptr->prev << " |" << std::endl;
            std::cout << "| next = " << it.m_node_ptr->next << " |" << std::endl;
            std::cout << "|                  |" << std::endl;
            std::cout << "--------------------" << std::endl;
            std::cout << "         ^          " << std::endl;
            std::cout << "         |          " << std::endl;
            std::cout << "         |          " << std::endl;
            std::cout << "         v          " << std::endl;
        }
        std::cout << "--------------------" << std::endl;
        std::cout << "|                  |" << std::endl;
        std::cout << "|  val = sentinel  |" << std::endl;
        std::cout << "| addr = " << m_sentinel << " |" << std::endl;
        std::cout << "| prev = " << m_sentinel->prev << " |" << std::endl;
        std::cout << "| next = " << m_sentinel->next << " |" << std::endl;
        std::cout << "|                  |" << std::endl;
        std::cout << "--------------------" << std::endl;
        std::cout << "" << std::endl;
        std::cout << "DONE debug printing" << std::endl;
    }

    bool operator==(const doubly_linked_list& rhs) const {
        return std::equal(begin(), end(), rhs.begin(), rhs.end());
    }

private:
    void merge_sort(doubly_linked_list& d) {
        if (d.size() == 0 || d.size() == 1) {
            return;
        }
        doubly_linked_list right;
        divide(d, right);
        assert(d.size() - right.size() <= 1);
        merge_sort(d);
        merge_sort(right);
        d.merge(right);
    }

    void divide(doubly_linked_list& d, doubly_linked_list& right) {
        auto it1 = d.begin();
        auto it2 = d.end();

        while (it1 != it2) {
            ++it1;
            if (it1 == it2) {
                break;
            }
            --it2;
        }
        auto * end_left = it1.m_node_ptr->prev;
        auto * start_right = it1.m_node_ptr;
        auto * end_right = d._tail_node();

        d.m_sentinel->prev = end_left;
        d.m_sentinel->link();

        right.m_sentinel->prev = end_right;
        right.m_sentinel->next = start_right;
        right.m_sentinel->link();
       }

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

}

#endif
