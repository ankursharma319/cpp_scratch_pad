#ifndef MY_ALGO_PRACTICE_HPP
#define MY_ALGO_PRACTICE_HPP

#include <string>
#include <optional>
#include <vector>

namespace ankur {

bool is_palindrome_permutation(std::string const& s);
bool is_rotated_string(std::string const& s1, std::string const& s2);

struct ForwardListNode {
    ForwardListNode* next = nullptr;
    std::optional<signed int> value = std::nullopt;

    ~ForwardListNode() {
        if (next != nullptr) {
            delete next;
        }
    }
};

bool operator==(ForwardListNode const& lhs, ForwardListNode const& rhs);
ForwardListNode* create_forward_list_from_vector(std::vector<signed int> const& val);

ForwardListNode * partition_forward_list_node(ForwardListNode * head, signed int partition);
bool is_linked_list_palindrome(ForwardListNode const * head);

}

#endif
