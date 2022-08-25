#include "algo_practice.hpp"
#include <unordered_map>
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

}
