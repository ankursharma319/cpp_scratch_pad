#ifndef MY_ALGO_PRACTICE_HPP
#define MY_ALGO_PRACTICE_HPP

#include <string>
#include <optional>
#include <vector>
#include <memory>

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

class stack {
public:
    stack();

    void push(int val);
    int pop();
    bool empty() const;
    int peek() const;

    ~stack();

private:
    class impl;
    std::unique_ptr<impl> impl_;
};

class queue_via_stacks {
public:
    void enqueue(int val);
    int dequeue();
    bool empty() const;
    int peek() const;
private:
    stack stack1;
};

void sort_stack_using_another_stack(stack& s);

struct BinaryTreeNode {
    int value;
    BinaryTreeNode* left_child = nullptr;
    BinaryTreeNode* right_child = nullptr;
    BinaryTreeNode* parent = nullptr;

    ~BinaryTreeNode();
};

BinaryTreeNode* bst_from_sorted_array(std::vector<int> const& vec);

bool is_bst(BinaryTreeNode* root);

std::size_t number_of_paths_with_sum(BinaryTreeNode const * root, int desired_sum);

}

#endif
