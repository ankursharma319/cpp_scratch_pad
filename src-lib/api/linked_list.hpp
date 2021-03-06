#ifndef ANKUR_LINKED_LIST_HPP
#define ANKUR_LINKED_LIST_HPP

#include <cstddef>
#include <iterator>
#include <memory>
#include <sstream>
#include <type_traits>
#include <cassert>
#include <iostream>
#include <utility>

namespace ankur {

template<typename T>
class linked_list;

namespace detail {

struct node_base {
    node_base(): next(nullptr) {}
    node_base(std::unique_ptr<node_base>&& n): next(std::move(n)) {}
    ~node_base() {
        // this is an optimization to remove recursiveness of destructors
        while(next) {
            next = std::move(next->next);
        }
    }
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

    template<typename U = T>
    explicit linked_list_forward_iterator(
        linked_list_forward_iterator<std::add_const_t<U>> it,
        typename std::enable_if_t<!std::is_const_v<U>, T>* = nullptr
    ): m_node_base_ptr(it.m_node_base_ptr) {}

    template<typename U = T>
    explicit linked_list_forward_iterator(
        linked_list_forward_iterator<std::remove_const_t<U>> it,
        typename std::enable_if_t<std::is_const_v<U>, T>* = nullptr
    ): m_node_base_ptr(it.m_node_base_ptr) {}

    explicit linked_list_forward_iterator(node_ptr ptr): m_node_base_ptr(ptr) {}
    // copy constructor, copy assignment operator, destructor= default

    reference operator*() const {
        return data_node()->data;
    }

    pointer operator->() {
        return &data_node()->data;
    }

    bool operator==(linked_list_forward_iterator<T, node_ptr> const& other) const {
        return this->m_node_base_ptr == other.m_node_base_ptr;
    }

    bool operator!=(linked_list_forward_iterator<T, node_ptr> const& other) const {
        return !(*this == other);
    }

    // prefix increment
    linked_list_forward_iterator operator++() {
        assert(m_node_base_ptr);
        m_node_base_ptr = m_node_base_ptr->next.get();
        return *this;
    }

    // postfix increment
    linked_list_forward_iterator operator++(int) {
        linked_list_forward_iterator<T, node_ptr> tmp = *this;
        ++(*this);
        return tmp;
    }

    node<T>* data_node() const {
        return static_cast<node<T>*>(m_node_base_ptr);
    }

private:
    template<typename>
    friend class ankur::linked_list;

    template <typename, typename>
    friend class linked_list_forward_iterator;

    node_ptr m_node_base_ptr;
};

} // end namespace detail

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
    using iterator = detail::linked_list_forward_iterator<T>;
    using const_iterator = detail::linked_list_forward_iterator<const T>;

    // constructors && assignments
    linked_list(): m_head(std::make_unique<detail::node_base>(nullptr)) {}

    explicit linked_list(size_type count): linked_list(count, T{}) {}

    explicit linked_list(size_type count, const_reference value)
    : linked_list()
    {
        detail::node_base* last_node = m_head.get();
        for (size_type i = 0; i < count; i++) {
            last_node->next = std::make_unique<detail::node<T>>(nullptr, value);
            last_node = last_node->next.get();
        }
    }

    explicit linked_list(std::initializer_list<T> init): linked_list(init.begin(), init.end()) {}

    template<class InputIt>
    linked_list(InputIt first, InputIt last)
    : linked_list()
    {
        detail::node_base* last_node = m_head.get();
        for (auto it = first; it != last; ++it) {
            last_node->next = std::make_unique<detail::node<T>>(nullptr, *it);
            last_node = last_node->next.get();
        }
    }

    linked_list(const linked_list& other): linked_list(other.cbegin(), other.cend()) {}
    linked_list(linked_list&& other) = default;
    ~linked_list() = default;

    linked_list& operator=(linked_list&& other) = default;
    linked_list& operator=(const linked_list& other) {
        linked_list copy {other};
        swap(copy);
        return *this;
    }

    linked_list& operator=(std::initializer_list<T> ilist) {
        *this = linked_list(ilist);
        return *this;
    }

    void assign(size_type count, const T& value) {
        *this = linked_list(count, value);
    }

    template<class InputIt>
    void assign(InputIt first, InputIt last) {
        *this = linked_list(first, last);
    }

    void assign(std::initializer_list<T> ilist) {
        *this = linked_list(ilist);
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
        return iterator(nullptr);
    }

    const_iterator end() const {
        return cend();
    }

    const_iterator cend() const {
        return const_iterator(nullptr);
    }

    // modifiers

    iterator insert_after(const_iterator pos, T value) {
        assert(pos.m_node_base_ptr);
        detail::node_base* my_node = pos.m_node_base_ptr;
        std::unique_ptr<detail::node_base> old_next = std::move(my_node->next);
        std::unique_ptr<detail::node<T>> new_node = std::make_unique<detail::node<T>>(std::move(old_next), std::move(value));
        my_node->next = std::move(new_node);
        return iterator(my_node->next.get());
    }

    iterator insert_after(const_iterator pos, size_type count, const T& value) {
        assert(pos.m_node_base_ptr);
        iterator insert_pos = iterator(pos);
        for (size_type i=0; i<count; i++) {
            insert_pos = insert_after(const_iterator(insert_pos), value);
        }
        return insert_pos;
    }

    template<class InputIt>
    iterator insert_after(const_iterator pos, InputIt first, InputIt last) {
        assert(pos.m_node_base_ptr);
        iterator insert_pos = iterator(pos);
        for (auto it = first; it != last; it++) {
            insert_pos = insert_after(const_iterator(insert_pos), *it);
        }
        return insert_pos;
    }

    iterator insert_after(const_iterator pos, std::initializer_list<T> ilist) {
        return insert_after(pos, ilist.begin(), ilist.end());
    }

    template<class... Args>
    iterator emplace_after(const_iterator pos, Args&&... args) {
        assert(pos.m_node_base_ptr);
        detail::node_base* my_node = pos.m_node_base_ptr;
        std::unique_ptr<detail::node_base> old_next = std::move(my_node->next);
        std::unique_ptr<detail::node<T>> new_node = std::make_unique<detail::node<T>>(std::move(old_next), T(std::forward<Args...>(args...)));
        my_node->next = std::move(new_node);
        return iterator(my_node->next.get());
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
        assert(pos.m_node_base_ptr);
        detail::node_base* my_node = pos.m_node_base_ptr;
        std::unique_ptr<detail::node_base> old_next = std::move(my_node->next);
        std::unique_ptr<detail::node_base> new_next = std::move(old_next->next);        
        my_node->next = std::move(new_next);
        return iterator(++pos);
    }

    iterator erase_after(const_iterator first, const_iterator last) {
        // get prev to last node
        assert(first.m_node_base_ptr);
        if (first == last) {
            return iterator(last);
        }
        detail::node_base* first_node = first.m_node_base_ptr;
        detail::node_base* prev_to_last_node = get_prev_to_last_node(first, last).m_node_base_ptr;
        std::unique_ptr<detail::node_base> new_next = std::move(prev_to_last_node->next);        
        first_node->next = std::move(new_next);
        return iterator(++first);
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
        auto it_1 = this->before_begin();
        auto it_2 = other.before_begin();
        while (!other.empty()) {
            if (end() == ++iterator(it_1)) {
                std::unique_ptr<detail::node_base> node_to_move = std::move(it_2.m_node_base_ptr->next);
                it_1.m_node_base_ptr->next = std::move(node_to_move);
                continue;
            }
            T const& val1 = static_cast<detail::node<T>*>(it_1.m_node_base_ptr->next.get())->data;
            T const& val2 = static_cast<detail::node<T>*>(it_2.m_node_base_ptr->next.get())->data;
            if (val1 > val2) {
                std::unique_ptr<detail::node_base> node_to_move = std::move(it_2.m_node_base_ptr->next);
                std::unique_ptr<detail::node_base> old_next_of_node_to_move = std::move(node_to_move->next);
                std::unique_ptr<detail::node_base> new_next_of_node_to_move = std::move(it_1.m_node_base_ptr->next);
                it_2.m_node_base_ptr->next = std::move(old_next_of_node_to_move);
                node_to_move->next = std::move(new_next_of_node_to_move);
                it_1.m_node_base_ptr->next = std::move(node_to_move);
            }
            it_1 ++;
        }
    }

    void splice_after(const_iterator pos, linked_list& other) {
        std::unique_ptr<detail::node_base> old_next = std::move(pos.m_node_base_ptr->next);
        auto before_end_it = get_prev_to_last_node(other.cbegin(), other.cend());
        before_end_it.m_node_base_ptr->next = std::move(old_next);
        std::unique_ptr<detail::node_base> node_to_move = std::move(other.m_head->next);
        pos.m_node_base_ptr->next = std::move(node_to_move);
    }

    void splice_after(const_iterator pos, linked_list& other, const_iterator it) {
        (void) other;
        std::unique_ptr<detail::node_base> old_next = std::move(pos.m_node_base_ptr->next);
        std::unique_ptr<detail::node_base> node_to_move = std::move(it.m_node_base_ptr->next);
        std::unique_ptr<detail::node_base> others_remaining_next = std::move(node_to_move->next);
        it.m_node_base_ptr->next = std::move(others_remaining_next);
        node_to_move->next = std::move(old_next);
        pos.m_node_base_ptr->next = std::move(node_to_move);
    }

    void remove(const T& value) {
        return remove_if([&value](const T& val){ return val == value; });
    }

    template<class UnaryPredicate>
    void remove_if(UnaryPredicate p) {
        auto it = before_begin();
        while (it.m_node_base_ptr->next.get() != nullptr) {
            T const& val = static_cast<detail::node<T>*>(it.m_node_base_ptr->next.get())->data;
            if (!p(val)) {
                it++;
                continue;
            }
            std::unique_ptr<detail::node_base> remaining = std::move(it.m_node_base_ptr->next->next);
            it.m_node_base_ptr->next = std::move(remaining);
        }
    }

    void reverse() {
        std::unique_ptr<detail::node_base> following = nullptr;
        std::unique_ptr<detail::node_base> current = std::move(m_head->next);
        std::unique_ptr<detail::node_base> previous = nullptr;
        while (current) {
            following = std::move(current->next);

            current->next = std::move(previous);
            previous = std::move(current);
            current = std::move(following);
        }
        m_head->next = std::move(previous);
    }

    void unique() {
        auto it = begin();
        while (it.m_node_base_ptr->next.get() != nullptr) {
            T const& previous_val = static_cast<detail::node<T>*>(it.m_node_base_ptr)->data;
            T const& val = static_cast<detail::node<T>*>(it.m_node_base_ptr->next.get())->data;
            if (previous_val == val) {
                std::unique_ptr<detail::node_base> node_to_remove = std::move(it.m_node_base_ptr->next);
                std::unique_ptr<detail::node_base> new_next = std::move(node_to_remove->next);
                it.m_node_base_ptr->next = std::move(new_next);
            } else {
                it ++;
            }
        }
    }

    void sort() { 
        return sort([](const T& a, const T& b){ return a < b; });
    }

    template<class Compare>
    void sort(Compare comp) {
        merge_sort(m_head->next, comp);
    }

private:
    const_iterator get_prev_to_last_node(const_iterator first, const_iterator last) {
        assert(first.m_node_base_ptr);
        assert(first != last);
        auto it = first;
        auto prev_to_last_it = first;
        while (it != last) {
            prev_to_last_it = it++;
        }
        assert(prev_to_last_it.m_node_base_ptr);
        assert(prev_to_last_it.m_node_base_ptr->next.get() == last.m_node_base_ptr);
        return prev_to_last_it;
    }

    template<class Compare>
    void merge_sort(std::unique_ptr<detail::node_base>& node_to_sort, Compare const& comp) {
        if (!node_to_sort || !node_to_sort->next) {
            return;
        }
        std::unique_ptr<detail::node_base> other {nullptr};
        split_list(node_to_sort, other);
        assert(node_to_sort);
        assert(other);
        assert(debug_size(node_to_sort)-debug_size(other) <= 1);
        merge_sort(node_to_sort, comp);
        merge_sort(other, comp);
        assert(node_to_sort);
        assert(other);
        merge_sorted_nodes(node_to_sort, other, comp);
        assert(node_to_sort);
        assert(!other);
    }

    void split_list(
        std::unique_ptr<detail::node_base>& begin_a,
        std::unique_ptr<detail::node_base>& begin_b
    ) {
        assert(begin_a);
        assert(!begin_b);
        std::unique_ptr<detail::node_base>* ptr_1 {&begin_a->next};
        std::unique_ptr<detail::node_base>* ptr_2 {&begin_a};

        while (*ptr_1) {
            ptr_1 = &(*ptr_1)->next;
            if (*ptr_1) {
                ptr_1 = &(*ptr_1)->next;
                ptr_2 = &(*ptr_2)->next;
            }
        }

        begin_b = std::move((*ptr_2)->next);
        (*ptr_2)->next = nullptr;
        assert(begin_b);
    }

    template<class Compare>
    void merge_sorted_nodes(
        std::unique_ptr<detail::node_base>& a,
        std::unique_ptr<detail::node_base>& b,
        Compare const& comp
    ) {
        // assumes sorted list
        std::unique_ptr<detail::node_base> tmp_base = std::make_unique<detail::node_base>(std::move(a));
        std::unique_ptr<detail::node_base>* current_node = &tmp_base;
        while (b) {
            if (!(*current_node)->next) {
                (*current_node)->next = std::move(b);
                b = nullptr;
                continue;
            }
            T const& val1 = static_cast<detail::node<T>*>((*current_node)->next.get())->data;
            T const& val2 = static_cast<detail::node<T>*>(b.get())->data;
            if (comp(val2, val1)) { // val2 < val1
                std::unique_ptr<detail::node_base> node_to_move = std::move(b);
                std::unique_ptr<detail::node_base> old_next_of_node_to_move = std::move(node_to_move->next);
                std::unique_ptr<detail::node_base> new_next_of_node_to_move = std::move((*current_node)->next);
                b = std::move(old_next_of_node_to_move);
                node_to_move->next = std::move(new_next_of_node_to_move);
                (*current_node)->next = std::move(node_to_move);
            }
            current_node = &(*current_node)->next;
        }
        a = std::move(tmp_base->next);
    }

    std::size_t debug_size(std::unique_ptr<detail::node_base> const& n) {
        std::unique_ptr<detail::node_base> const * ptr = &n;
        std::size_t i = 0;
        while(*ptr) {
            ptr = &(*ptr)->next;
            i++;
        }
        return i;
    }

    std::string debug_string(detail::node_base const* n) {
        std::stringstream ss {};
        while (n) {
            ss << n << ", ";
            n = n->next.get();
        }
        return ss.str();
    }

    std::unique_ptr<detail::node_base> m_head;
};

template<class T>
bool operator==(const linked_list<T>& lhs, const linked_list<T>& rhs) {
    auto it_1 = lhs.begin();
    auto it_2 = rhs.begin();
    while(it_1 != lhs.end() && it_2 != rhs.end()) {
        T const& val1 = it_1.data_node()->data;
        T const& val2 = it_2.data_node()->data;;
        if (!(val1 == val2)) {
            return false;
        }
        it_1 ++;
        it_2 ++;
    }
    return it_1 == lhs.end() && it_2 == rhs.end();
}

template<class T>
bool operator!=(const linked_list<T>& lhs, const linked_list<T>& rhs) {
    return !(lhs == rhs);
}

template<class T>
bool operator<(const linked_list<T>& lhs, const linked_list<T>& rhs) {
    auto it_1 = lhs.begin();
    auto it_2 = rhs.begin();
    while(it_1 != lhs.end() && it_2 != rhs.end()) {
        T const& val1 = it_1.data_node()->data;
        T const& val2 = it_2.data_node()->data;;
        if (!(val1 < val2)) {
            return false;
        }
        it_1 ++;
        it_2 ++;
    }
    return true;
}

template<class T>
bool operator<=(const linked_list<T>& lhs, const linked_list<T>& rhs) {
    return (lhs == rhs) || (lhs < rhs);
}

template<class T>
bool operator>(const linked_list<T>& lhs, const linked_list<T>& rhs) {
    return !(lhs <= rhs);
}

template<class T>
bool operator>=(const linked_list<T>& lhs, const linked_list<T>& rhs) {
    return (lhs == rhs) || (lhs > rhs);
}

}

namespace std {

template<class T>
void swap(ankur::linked_list<T>& lhs, ankur::linked_list<T>& rhs) {
    lhs.swap(rhs);
}

}

#endif
