#ifndef MY_ALGO_PRACTICE_HPP
#define MY_ALGO_PRACTICE_HPP

#include <string>
#include <optional>
#include <vector>
#include <memory>
#include <unordered_set>
#include <cstdint>

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

std::uint32_t insert_bit_sequence_into_int(std::uint32_t N, std::uint32_t M, unsigned short i, unsigned short j);

std::string binary_to_string(double n);

std::size_t flip_a_bit_for_longest_ones_bit_sequence(std::uint32_t n);

std::uint32_t next_smallest_int_with_same_number_of_ones(std::uint32_t n);

std::size_t count_number_of_step_hop_sequences_to_cover_n_steps(std::size_t n);

std::unordered_set<std::string> permutation_without_dups(std::string const& s);

std::size_t count_ways_to_represent_n_cents(std::size_t n, std::vector<std::size_t> const& denoms);

struct my_box {
    double height;
    double width;
    double depth;
};

std::size_t compute_tallest_height_of_stack(std::vector<my_box> const& boxes);

std::vector<std::string> string_list_decode(std::string const& str);
std::string string_list_encode(std::vector<std::string> const& strs);

}

#endif
