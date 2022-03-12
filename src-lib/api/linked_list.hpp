#ifndef ANKUR_LINKED_LIST_HPP
#define ANKUR_LINKED_LIST_HPP

#include <cstddef>
#include <iterator>
#include <memory>
#include <type_traits>
#include <cassert>
#include <iostream>

namespace ankur {

struct node_base {
    node_base(): next(nullptr) {}
    node_base(std::unique_ptr<node_base>&& n): next(std::move(n)) {}
    std::unique_ptr<node_base> next;
};

template<typename T>
struct node : node_base {
    node(std::unique_ptr<node_base>&& n, T d): node_base(std::move(n)), data(std::move(d)) {}
    T data;
};

template<typename T, typename node_ptr = node_base*>
class linked_list_forward_iterator {
public:
    // https://www.internalpointers.com/post/writing-custom-iterators-modern-cpp
    using iterator_category = std::forward_iterator_tag;
    using difference_type = std::ptrdiff_t;
    using value_type = T;
    using reference = T&;
    using pointer = T*;

    linked_list_forward_iterator(node_ptr ptr): m_ptr(ptr) {};
    // copy constructor, copy assignment operator, destructor= default

    reference operator*() const {
        return data_node()->data;
    }

    pointer operator->() {
        return &data_node()->data;
    }

    bool operator==(linked_list_forward_iterator<T, node_ptr> const& other) const {
        return this->m_ptr == other.m_ptr;
    }

    bool operator!=(linked_list_forward_iterator<T, node_ptr> const& other) const {
        return !(*this == other);
    }

    // prefix increment
    node_ptr operator++() {
        assert(m_ptr);
        m_ptr = m_ptr->next.get();
        return m_ptr;
    }

    // postfix increment
    node_ptr operator++(int) {
        linked_list_forward_iterator<T, node_ptr> tmp = *this;
        ++(*this);
        return tmp.m_ptr;
    }

    node<T>* data_node() const {
        return static_cast<node<T>*>(m_ptr);
    }

    node_ptr m_ptr;
};

template<typename T>
using linked_list_forward_iterator_volatile = linked_list_forward_iterator<T>;

template<typename T>
using linked_list_forward_iterator_constant = linked_list_forward_iterator<const T>;

template<typename T>
class linked_list {

static_assert(std::is_object_v<T>, "T must be object");

public:
    using value_type = T;
    using size_type = std::size_t;
    using difference_type = std::ptrdiff_t;
    using reference = T&;
    using const_reference = T const&;
    using pointer = T*;
    using const_pointner = T const*;
    using iterator = linked_list_forward_iterator_volatile<T>;
    using const_iterator = linked_list_forward_iterator_constant<T>;

    // constructors
    linked_list(): m_head(std::make_unique<node_base>(nullptr)) {}

    explicit linked_list(size_type count): linked_list(count, T{}) {}

    explicit linked_list(size_type count, const_reference value)
    : linked_list()
    {
        node_base* last_node = m_head.get();
        for (size_type i = 0; i < count; i++) {
            last_node->next = std::make_unique<node<T>>(nullptr, value);
            last_node = last_node->next.get();
        }
    }

    explicit linked_list(std::initializer_list<T> init): linked_list(init.begin(), init.end()) {}

    template<class InputIt>
    linked_list(InputIt first, InputIt last)
    : linked_list()
    {
        node_base* last_node = m_head.get();
        for (auto it = first; it != last; ++it) {
            last_node->next = std::make_unique<node<T>>(nullptr, *it);
            last_node = last_node->next.get();
        }
    }

    linked_list(const linked_list& other): linked_list(other.cbegin(), other.cend()) {}
    linked_list(linked_list&& other) = default;
    ~linked_list() = default;

    linked_list& operator=(linked_list&& other) = default;
    linked_list& operator=(const linked_list& other) {
        linked_list<T> copy {other};
        swap(copy);
        return *this;
    }

    linked_list& operator=(std::initializer_list<T> ilist) {
        *this = linked_list<T>(ilist);
        return *this;
    }

    void assign(size_type count, const T& value) {
        *this = linked_list<T>(count, value);
    }

    template<class InputIt>
    void assign(InputIt first, InputIt last) {
        *this = linked_list<T>(first, last);
    }

    void assign(std::initializer_list<T> ilist) {
        *this = linked_list<T>(ilist);
    }

    //  Element access
    T& front() {
        assert(m_head);
        return *begin();
    }

    T const& front() const {
        assert(m_head);
        return *cbegin();
    }

    // capacity

    size_type size() const {
        size_type size = 0;
        for (auto it = cbegin(); it != cend(); it++) {
            size++;
        }
        return size;
    }

    bool empty() const {
        return !m_head->next;
    }

    // iterators

    iterator before_begin() {
        return iterator(m_head.get());
    }

    const_iterator before_begin() const {
        return cbefore_begin();
    }

    const_iterator cbefore_begin() const {
        return const_iterator(m_head.get());
    }

    iterator begin() {
        return iterator(m_head->next.get());
    }

    const_iterator begin() const {
        return cbegin();
    }

    const_iterator cbegin() const {
        return const_iterator(m_head->next.get());
    }

    iterator end() {
        return nullptr;
    }

    const_iterator end() const {
        return cend();
    }

    const_iterator cend() const {
        return nullptr;
    }

    // modifiers

    iterator insert_after(const_iterator pos, T value) {
        assert(pos.m_ptr);
        node_base* my_node = pos.m_ptr;
        std::unique_ptr<node_base> old_next = std::move(my_node->next);
        std::unique_ptr<node<T>> new_node = std::make_unique<node<T>>(std::move(old_next), std::move(value));
        my_node->next = std::move(new_node);
        return my_node->next.get();
    }

    iterator insert_after(const_iterator pos, size_type count, const T& value) {
        assert(pos.m_ptr);
        iterator insert_pos = pos.m_ptr;
        for (size_type i=0; i<count; i++) {
            insert_pos = insert_after(insert_pos.m_ptr, value);
        }
        return insert_pos;
    }

    template<class InputIt>
    iterator insert_after(const_iterator pos, InputIt first, InputIt last) {
        assert(pos.m_ptr);
        iterator insert_pos = pos.m_ptr;
        for (auto it = first; it != last; it++) {
            insert_pos = insert_after(insert_pos.m_ptr, *it);
        }
        return insert_pos;
    }

    iterator insert_after(const_iterator pos, std::initializer_list<T> ilist) {
        return insert_after(pos, ilist.begin(), ilist.end());
    }

    template<class... Args>
    iterator emplace_after(const_iterator pos, Args&&... args) {
        assert(pos.m_ptr);
        node_base* my_node = pos.m_ptr;
        std::unique_ptr<node_base> old_next = std::move(my_node->next);
        std::unique_ptr<node<T>> new_node = std::make_unique<node<T>>(std::move(old_next), T(std::forward<Args...>(args...)));
        my_node->next = std::move(new_node);
        return my_node->next.get();
    }

    void push_front(const T& value) {
        insert_after(cbefore_begin(), value);
    }

    void push_front(T&& value) {
        insert_after(cbefore_begin(), std::move(value));
    }

    template<class... Args>
    reference emplace_front(Args&&... args) {
        return *emplace_after(cbefore_begin(), std::forward<Args...>(args...));
    }

    void pop_front() {
        erase_after(cbefore_begin());
    }

    iterator erase_after(const_iterator pos) {
        assert(pos.m_ptr);
        node_base* my_node = pos.m_ptr;
        std::unique_ptr<node_base> old_next = std::move(my_node->next);
        std::unique_ptr<node_base> new_next = std::move(old_next->next);        
        my_node->next = std::move(new_next);
        return my_node->next.get();
    }

    iterator erase_after(const_iterator first, const_iterator last) {
        // get prev to last node
        assert(first.m_ptr);
        if (first == last) {
            return last.m_ptr;
        }
        node_base* first_node = first.m_ptr;
        node_base* prev_to_last_node = get_prev_to_last_node(first, last).m_ptr;
        std::unique_ptr<node_base> new_next = std::move(prev_to_last_node->next);        
        first_node->next = std::move(new_next);
        return first_node->next.get();
    }

    void clear() {
        erase_after(cbefore_begin(), cend());
    }

    void swap(linked_list& other) {
        using std::swap;
        swap(m_head, other.m_head);
    }

    // operations

    void merge(linked_list& other) {
        // assumes sorted list
        if (this == &other) {
            return;
        }
        std::cout << "merge: this->size() = " << this->size() << std::endl;
        std::cout << "merge: other.size() = " << other.size() << std::endl;
        auto it_1 = this->before_begin();
        auto it_2 = other.before_begin();
        while (!other.empty()) {
            std::cout << "merge: new_loop" << std::endl;
            std::cout << "merge: Looping it_1.m_ptr->next = " << it_1.m_ptr->next.get() << std::endl;
            std::cout << "merge: Looping it_2.m_ptr->next = " << it_2.m_ptr->next.get() << std::endl;
            if (end() == it_1.m_ptr->next.get()) {
                std::cout << "Finished with list1 elements, appending rest of list2 to list1" << std::endl;
                std::unique_ptr<node_base> node_to_move = std::move(it_2.m_ptr->next);
                it_1.m_ptr->next = std::move(node_to_move);
                continue;
            }
            T const& val1 = static_cast<node<T>*>(it_1.m_ptr->next.get())->data;
            T const& val2 = static_cast<node<T>*>(it_2.m_ptr->next.get())->data;
            std::cout << "merge: Looping val1 = " << val1 << std::endl;
            std::cout << "merge: Looping val2 = " << val2 << std::endl;
            if (val1 > val2) {
                std::unique_ptr<node_base> node_to_move = std::move(it_2.m_ptr->next);
                std::cout << "merge: val1 > val2" << std::endl;
                std::unique_ptr<node_base> old_next_of_node_to_move = std::move(node_to_move->next);
                std::unique_ptr<node_base> new_next_of_node_to_move = std::move(it_1.m_ptr->next);
                it_2.m_ptr->next = std::move(old_next_of_node_to_move);
                node_to_move->next = std::move(new_next_of_node_to_move);
                it_1.m_ptr->next = std::move(node_to_move);
            }
            it_1 ++;
        }
    }

    void splice_after(const_iterator pos, linked_list& other) {
        std::unique_ptr<node_base> old_next = std::move(pos.m_ptr->next);
        auto before_end_it = get_prev_to_last_node(other.cbegin(), other.cend());
        before_end_it.m_ptr->next = std::move(old_next);
        std::unique_ptr<node_base> node_to_move = std::move(other.m_head->next);
        pos.m_ptr->next = std::move(node_to_move);
    }

    void splice_after(const_iterator pos, linked_list& other, const_iterator it) {
        (void) other;
        std::unique_ptr<node_base> old_next = std::move(pos.m_ptr->next);
        std::unique_ptr<node_base> node_to_move = std::move(it.m_ptr->next);
        std::unique_ptr<node_base> others_remaining_next = std::move(node_to_move->next);
        it.m_ptr->next = std::move(others_remaining_next);
        node_to_move->next = std::move(old_next);
        pos.m_ptr->next = std::move(node_to_move);
    }

    void remove(const T& value);
    template<class UnaryPredicate>
    void remove_if(UnaryPredicate p);

    void reverse();

    void unique();
    template<class BinaryPredicate>
    void unique(BinaryPredicate p);

    void sort();
    template<class Compare>
    void sort(Compare comp);

private:
    const_iterator get_prev_to_last_node(const_iterator first, const_iterator last) {
        assert(first.m_ptr);
        assert(first != last);
        auto it = first;
        auto prev_to_last_it = first;
        while (it != last) {
            prev_to_last_it = it++;
        }
        assert(prev_to_last_it.m_ptr);
        assert(prev_to_last_it.m_ptr->next.get() == last.m_ptr);
        return prev_to_last_it;
    }

    std::unique_ptr<node_base> m_head;
};

template<class T>
bool operator==(const linked_list<T>& lhs, const linked_list<T>& rhs);

template<class T>
bool operator!=(const linked_list<T>& lhs, const linked_list<T>& rhs);

template<class T>
bool operator<(const linked_list<T>& lhs, const linked_list<T>& rhs);

template<class T>
bool operator<=(const linked_list<T>& lhs, const linked_list<T>& rhs);

template<class T>
bool operator>(const linked_list<T>& lhs, const linked_list<T>& rhs);

template<class T>
bool operator>=(const linked_list<T>& lhs, const linked_list<T>& rhs);

}

namespace std {

template<class T>
void swap(ankur::linked_list<T>& lhs, ankur::linked_list<T>& rhs);

template<class T, class U>
typename ankur::linked_list<T>::size_type erase(ankur::linked_list<T>& c, const U& value);

template<class T, class Pred>
typename ankur::linked_list<T>::size_type erase_if(ankur::linked_list<T>& c, Pred pred);

}

#endif
