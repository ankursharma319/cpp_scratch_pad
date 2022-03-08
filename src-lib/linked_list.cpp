#include "linked_list.hpp"
#include <memory>
#include <cassert>
#include <vector>

namespace ankur {

template<typename T, typename node_ptr>
linked_list_forward_iterator<T, node_ptr>::linked_list_forward_iterator(node_ptr ptr)
: m_ptr(ptr)
{}

template<typename T, typename node_ptr>
T& linked_list_forward_iterator<T, node_ptr>::operator*() const {
    return data_node()->data;
}

template<typename T, typename node_ptr>
T* linked_list_forward_iterator<T, node_ptr>::operator->() {
    return &data_node()->data;
}

template<typename T, typename node_ptr>
bool linked_list_forward_iterator<T, node_ptr>::operator==(linked_list_forward_iterator<T, node_ptr> const& other) const {
    return this->m_ptr == other.m_ptr;
}

template<typename T, typename node_ptr>
bool linked_list_forward_iterator<T, node_ptr>::operator!=(linked_list_forward_iterator<T, node_ptr> const& other) const {
    return !(*this == other);
}

// prefix increment
template<typename T, typename node_ptr>
node_ptr linked_list_forward_iterator<T, node_ptr>::operator++() {
    m_ptr = m_ptr->next.get();
    return m_ptr;
}

// postfix increment
template<typename T, typename node_ptr>
node_ptr linked_list_forward_iterator<T, node_ptr>::operator++(int) {
    linked_list_forward_iterator<T, node_ptr> tmp = *this;
    ++(*this);
    return tmp.m_ptr;
}

template<typename T, typename node_ptr>
node<T>* linked_list_forward_iterator<T, node_ptr>::data_node() const {
    return static_cast<node<T>*>(m_ptr);
}

template<typename T>
linked_list<T>::linked_list()
: m_head(std::make_unique<node_base>(nullptr))
{}

template<typename T>
linked_list<T>::linked_list(size_type count)
: linked_list(count, T{})
{}

template<typename T>
linked_list<T>::linked_list(size_type count, value_type const& value)
: linked_list()
{
    node_base* last_node = m_head.get();
    for (size_type i = 0; i < count; i++) {
        last_node->next = std::make_unique<node<T>>(nullptr, value);
        last_node = last_node->next.get();
    }
}

template<typename T>
linked_list<T>::linked_list(std::initializer_list<T> init)
: linked_list(init.begin(), init.end())
{}

template<typename T>
template<class InputIt>
linked_list<T>::linked_list(InputIt first, InputIt last)
: linked_list()
{
    node_base* last_node = m_head.get();
    for (auto it = first; it != last; ++it) {
        last_node->next = std::make_unique<node<T>>(nullptr, *it);
        last_node = last_node->next.get();
    }
}

template<typename T>
linked_list<T>::linked_list(const linked_list<T>& other)
: linked_list(other.cbegin(), other.cend())
{
}

template<typename T>
linked_list<T>& linked_list<T>::operator=(const linked_list<T>& other) {
    linked_list<T> copy {other};
    swap(copy);
    return *this;
}

template<typename T>
linked_list<T>& linked_list<T>::operator=(std::initializer_list<T> ilist) {
    *this = linked_list<T>(ilist);
    return *this;
}

template<typename T>
void linked_list<T>::assign(size_type count, const T& value) {
    *this = linked_list<T>(count, value);
}

template<typename T>
template<class InputIt>
void linked_list<T>::assign(InputIt first, InputIt last) {
    *this = linked_list<T>(first, last);
}

template<typename T>
void linked_list<T>::assign(std::initializer_list<T> ilist) {
    *this = linked_list<T>(ilist);
}

template<typename T>
void linked_list<T>::swap(linked_list<T>& other) {
    using std::swap;
    swap(m_head, other.m_head);
}

template<typename T>
T& linked_list<T>::front() {
    assert(m_head);
    return *begin();
}

template<typename T>
T const& linked_list<T>::front() const {
    assert(m_head);
    return *cbegin();
}

template<typename T>
typename linked_list<T>::size_type linked_list<T>::size() const {
    size_type size = 0;
    for (auto it = cbegin(); it != cend(); it++) {
        size++;
    }
    return size;
}

template<typename T>
bool linked_list<T>::empty() const {
    return !m_head;
}

template<typename T>
typename linked_list<T>::iterator linked_list<T>::before_begin() {
    return linked_list<T>::iterator(m_head.get());
}

template<typename T>
typename linked_list<T>::const_iterator linked_list<T>::before_begin() const {
    return linked_list<T>::const_iterator(m_head.get());
}

template<typename T>
typename linked_list<T>::const_iterator linked_list<T>::cbefore_begin() const {
    return linked_list<T>::const_iterator(m_head.get());
}

template<typename T>
typename linked_list<T>::iterator linked_list<T>::begin() {
    return linked_list<T>::iterator(m_head->next.get());
}

template<typename T>
typename linked_list<T>::const_iterator linked_list<T>::begin() const {
    return linked_list<T>::const_iterator(m_head->next.get());
}

template<typename T>
typename linked_list<T>::const_iterator linked_list<T>::cbegin() const {
    return linked_list<T>::const_iterator(m_head->next.get());
}

template<typename T>
typename linked_list<T>::iterator linked_list<T>::end() {
    return nullptr;
}

template<typename T>
typename linked_list<T>::const_iterator linked_list<T>::end() const {
    return nullptr;
}

template<typename T>
typename linked_list<T>::const_iterator linked_list<T>::cend() const {
    return nullptr;
}

template<typename T>
typename linked_list<T>::iterator linked_list<T>::insert_after(const_iterator pos, const T& value) {
    node_base* my_node = pos.m_ptr;
    std::unique_ptr<node_base> old_next = std::move(my_node->next);
    std::unique_ptr<node<T>> new_node = std::make_unique<node<T>>(std::move(old_next), value);
    my_node->next = std::move(new_node);
    return my_node->next.get();
}


template<typename T>
typename linked_list<T>::iterator linked_list<T>::insert_after(const_iterator pos, T&& value) {
    node_base* my_node = pos.m_ptr;
    std::unique_ptr<node_base> old_next = std::move(my_node->next);
    std::unique_ptr<node<T>> new_node = std::make_unique<node<T>>(std::move(old_next), std::move(value));
    my_node->next = std::move(new_node);
    return my_node->next.get();
}

template<typename T>
typename linked_list<T>::iterator linked_list<T>::insert_after(const_iterator pos, size_type count, const T& value) {
    iterator insert_pos = pos.m_ptr;
    for (size_type i=0; i<count; i++) {
        insert_pos = insert_after(insert_pos.m_ptr, value);
    }
    return insert_pos;
}

template<typename T>
template<class InputIt>
typename linked_list<T>::iterator linked_list<T>::insert_after(const_iterator pos, InputIt first, InputIt last) {
    iterator insert_pos = pos.m_ptr;
    for (auto it = first; it != last; it++) {
        insert_pos = insert_after(insert_pos.m_ptr, *it);
    }
    return insert_pos;
}

template<typename T>
typename linked_list<T>::iterator linked_list<T>::insert_after(const_iterator pos, std::initializer_list<T> ilist) {
    return insert_after(pos, ilist.begin(), ilist.end());
}

// Explicit template instantiation
template class linked_list<int>;
template linked_list<int>::linked_list(std::vector<int>::iterator, std::vector<int>::iterator);
template linked_list<int>::linked_list(std::vector<int>::const_iterator, std::vector<int>::const_iterator);
template class linked_list_forward_iterator<int, node_base*>;
template class linked_list_forward_iterator<const int, node_base*>;

/*template struct node<int>;
template linked_list_forward_iterator_volatile<int>;

template class linked_list<const int>;
template struct node<const int>;
template class linked_list_forward_iterator_volatile<const int>;*/

//template class linked_list<const int>;
//template class linked_list<int*>;

}