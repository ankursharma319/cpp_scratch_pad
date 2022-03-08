#ifndef ANKUR_LINKED_LIST_HPP
#define ANKUR_LINKED_LIST_HPP

#include <cstddef>
#include <iterator>
#include <memory>
#include <type_traits>

namespace ankur {

template<typename T>
struct node {
    T data;
    std::unique_ptr<node<T>> next;
};

template<typename T, typename node_ptr>
class linked_list_forward_iterator {
public:
    // https://www.internalpointers.com/post/writing-custom-iterators-modern-cpp
    using iterator_category = std::forward_iterator_tag;
    using difference_type = std::ptrdiff_t;
    using value_type = T;
    using reference = T&;
    using pointer = T*;

    linked_list_forward_iterator(node_ptr ptr);
    // copy constructor, copy assignment operator, destructor= default

    reference operator*() const;
    pointer operator->();
    bool operator==(linked_list_forward_iterator<T, node_ptr> const& other) const;
    bool operator!=(linked_list_forward_iterator<T, node_ptr> const& other) const;

    // prefix increment
    node_ptr operator++();
    // postfix increment
    node_ptr operator++(int);

    node_ptr m_ptr;
};

template<typename T>
using linked_list_forward_iterator_volatile = linked_list_forward_iterator<T, node<T>*>;

template<typename T>
using linked_list_forward_iterator_constant = linked_list_forward_iterator<const T, node<T>*>;

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

    linked_list();
    explicit linked_list(size_type count);
    explicit linked_list(size_type count, const_reference value);
    explicit linked_list(std::initializer_list<T> init);
    template<class InputIt>
    linked_list(InputIt first, InputIt last);

    linked_list(const linked_list& other);
    linked_list(linked_list&& other) = default;
    ~linked_list() = default;

    linked_list& operator=(const linked_list& other);
    linked_list& operator=(linked_list&& other) = default;
    linked_list& operator=(std::initializer_list<T> ilist);

    void assign(size_type count, const T& value);
    template<class InputIt>
    void assign(InputIt first, InputIt last);
    void assign(std::initializer_list<T> ilist);

    //  Element access 
    T& front();
    T const& front() const;

    // capacity
    size_type size() const;
    bool empty() const;

    // iterators
    iterator before_begin();
    const_iterator before_begin() const;
    const_iterator cbefore_begin() const;
    iterator begin();
    const_iterator begin() const;
    const_iterator cbegin() const;
    iterator end();
    const_iterator end() const;
    const_iterator cend() const;

    // modifiers
    iterator insert_after(const_iterator pos, const T& value);
    iterator insert_after(const_iterator pos, T&& value);
    iterator insert_after(const_iterator pos, size_type count, const T& value);
    template<class InputIt>
    iterator insert_after(const_iterator pos, InputIt first, InputIt last);
    iterator insert_after(const_iterator pos, std::initializer_list<T> ilist);

    template<class... Args>
    iterator emplace_after(const_iterator pos, Args&&... args);
    void push_front(const T& value);
    void push_front(T&& value);
    template<class... Args>
    reference emplace_front(Args&&... args);

    void pop_front();
    void erase_after(const_iterator it);
    void erase_after(const_iterator first, const_iterator last);
    void clear();
    void resize(size_type count);
    void resize(size_type count, const T& value);
    void swap(linked_list& other);

    // operations
    void merge(linked_list& other);
    void merge(linked_list&& other);
    template<typename Compare>
    void merge(linked_list& other, Compare comp);
    template<typename Compare>
    void merge(linked_list&& other, Compare comp);

    void splice_after(const_iterator pos, linked_list& other);
    void splice_after(const_iterator pos, linked_list&& other);
    void splice_after(const_iterator pos, linked_list& other, const_iterator it);
    void splice_after(const_iterator pos, linked_list&& other, const_iterator it);
    void splice_after(const_iterator pos, linked_list& other, const_iterator first, const_iterator last);
    void splice_after(const_iterator pos, linked_list&& other, const_iterator first, const_iterator last);

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
    std::unique_ptr<node<T>> m_head;
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
