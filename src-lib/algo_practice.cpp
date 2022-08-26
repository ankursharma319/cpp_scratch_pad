#include "algo_practice.hpp"
#include <unordered_map>
#include <utility>
#include <cassert>

namespace {

[[maybe_unused]] bool _is_palindrome_permutation_v1(std::string const& s) {
    // standardize case, remove all non a-z chars
    // std::unordered_map populated character counts
    // if all but one of counts is even, then its a palindrome
    // otherwise its not a palindrome permutation

    std::unordered_map<char, bool> is_even_count_map {};
    for (char c: s) {
        char standardized_char;
        if (c >= 'a' && c <= 'z') {
            standardized_char = c;
        } else if(c >= 'A' && c <= 'Z') {
            standardized_char = (c - 'A' + 'a');
        } else {
            continue;
        }
        if (is_even_count_map.count(standardized_char) == 0) {
            is_even_count_map.insert({standardized_char, false});
        } else {
            is_even_count_map[standardized_char] = !is_even_count_map.at(standardized_char);
        }
    }
    bool one_odd_found = false;
    for(std::pair<const char, bool> const& pair : is_even_count_map) {
        if (!pair.second) {
            if (one_odd_found) {
                return false;
            }
            one_odd_found = true;
        }
    }
    return true;
}

bool check_exactly_one_bit_set(std::uint32_t bit_vector) {
    bool anded = (bit_vector - 1) & bit_vector;
    return anded == 0;
}

[[maybe_unused]] bool _is_palindrome_permutation_v2(std::string const& s) {
    std::uint32_t is_odd_bit_vector = 0U;
    for (char c: s) {
        unsigned short char_index;
        if (c >= 'a' && c <= 'z') {
            char_index = c - 'a';
        } else if(c >= 'A' && c <= 'Z') {
            char_index = c - 'A';
        } else {
            continue;
        }
        std::uint32_t mask = 1U << char_index;
        is_odd_bit_vector = is_odd_bit_vector ^ mask;
    }
    if(is_odd_bit_vector == 0) {
        return true;
    }
    return (is_odd_bit_vector == 0) ||  check_exactly_one_bit_set(is_odd_bit_vector);
}

}

namespace ankur {

bool is_palindrome_permutation(std::string const& s) {
    return _is_palindrome_permutation_v2(s);
}

bool is_rotated_string(std::string const& s1, std::string const& s2) {
    if (s1.size() != s2.size()) {
        return false;
    }
    std::string concatenated = s1+s1;
    return concatenated.find(s2) != std::string::npos;
}

ForwardListNode* create_forward_list_from_vector(std::vector<signed int> const& values) {
    assert(values.size() > 0);
    auto it = values.cbegin();
    ForwardListNode* head = new ForwardListNode{nullptr, *it};
    it++;
    ForwardListNode* current = nullptr;
    ForwardListNode* previous = head;
    for(; it != values.cend(); it++) {
        current = new ForwardListNode{nullptr, *it};
        previous->next = current;
        previous = current;
    }
    return head;
}

bool operator==(ForwardListNode const& lhs, ForwardListNode const& rhs) {
    ForwardListNode const * left = &lhs;
    ForwardListNode const * right = &rhs;
    for(; left != nullptr && right != nullptr; left = left->next, right = right->next) {
        if(left->value != right->value) {
            return false;
        }
    }
    return (left == nullptr) && (right == nullptr);
}

ForwardListNode* partition_forward_list_node(ForwardListNode * head, signed int partition) {
    // linked list operations needed
    // create (bulk insert)
    // deletion in destructor
    // iteration (trivial)
    // operator==

    if (head == nullptr) {
        return head;
    }
    ForwardListNode* current_node = head;
    ForwardListNode* left_sub_list = new ForwardListNode{nullptr, std::nullopt};
    ForwardListNode* right_sub_list = new ForwardListNode{nullptr, std::nullopt};
    ForwardListNode* left_current_node = left_sub_list;
    ForwardListNode* righ_current_node = right_sub_list;
    while(current_node != nullptr) {
        ForwardListNode* next = current_node->next;
        if (current_node->value < partition) {
            // move to the left sublist
            left_current_node->next = current_node;
            current_node->next = nullptr;
            left_current_node = current_node;
        } else {
            // move to the right sublist
            righ_current_node->next = current_node;
            current_node->next = nullptr;
            righ_current_node = current_node;
        }
        current_node = next;
    }
    ForwardListNode* new_head = left_sub_list->next ? left_sub_list->next : right_sub_list->next;
    assert(new_head != nullptr);
    left_current_node->next = right_sub_list->next;
    right_sub_list->next = nullptr;
    left_sub_list->next = nullptr;
    delete right_sub_list;
    delete left_sub_list;
    return new_head;
}

// Examples for _is_palindrome_recursive
// (7,9,4,9,7), 5
// (9,4,9,7), 3
// (4,9,7), 1
// and then return true, 9
// compare 9 == 9, return true, 7
// compare 7 == 7, return true, nullptr

// (7,9,4,4,9,7), 6
// (9,4,4,9,7), 4
// (4,4,9,7), 2
// (4,9,7), 0
// and then return true, 4
// compare 4 == 4, return true, 9
// compare 9 == 9, return true, 7
// compare 7 == 7, return true, nullptr

// (7,9,4,9,6), 5
// (9,4,9,6), 3
// (4,9,6), 1
// and then return true, 9
// compare 9 == 9, return true, 6
// compare 7 == 6, return false, nullptr

// (7,9,4,9), 4
// (9,4,9), 2
// (4,9), 0
// and then return true, 4
// compare 9 == 4, return false, nullptr
// return false, nullptr

std::pair<bool, ForwardListNode const*> _is_palindrome_recursive(ForwardListNode const * head, std::size_t remaining_size) {
    assert(head != nullptr);
    ForwardListNode const* next = head->next;
    if (remaining_size == 0) {
        return std::make_pair(true, head);
    }
    if (remaining_size == 1) {
        return std::make_pair(true, next);
    }
    std::pair<bool, ForwardListNode const*> res = _is_palindrome_recursive(next, remaining_size-2);
    if (!res.first || (res.second == nullptr)) {
        return res;
    }
    if (res.second->value == head->value) {
        return std::make_pair(true, res.second->next);
    }
    return std::make_pair(false, nullptr);
}

std::size_t _linked_list_length(ForwardListNode const * head) {
    std::size_t count = 0;
    for(ForwardListNode const * node = head; node != nullptr; node = node->next) {
        count++;
    }
    return count;
}

bool is_linked_list_palindrome(ForwardListNode const * head) {
    // iterative approach #1: reverse & compare
    // iterative approach #2: push values to a stack while going to mid point (fast runner)
    // and then iterate through the rest popping from the stack. At the end should have 0 elements
    // here i am implementing the recursive approach
    if (head == nullptr) {
        return true;
    }
    return _is_palindrome_recursive(head, _linked_list_length(head)).first;
}

}
