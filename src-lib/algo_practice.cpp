#include "algo_practice.hpp"
#include <unordered_map>
#include <utility>
#include <cassert>
#include <cmath>

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

// Queue via Stacks: Implement a MyQueue class which implements a queue using two stacks.
void queue_via_stacks::enqueue(int val) {
    stack1.push(val);
}

int queue_via_stacks::dequeue() {
    stack stack2 = {};
    while (!stack1.empty()) {
        stack2.push(stack1.pop());
    }
    int to_return = stack2.pop();
    while (!stack2.empty()) {
        stack1.push(stack2.pop());
    }
    return to_return;
}

bool queue_via_stacks::empty() const {
    return stack1.empty();
}

int queue_via_stacks::peek() const {
    return stack1.peek();
}

// stack impl

class stack::impl {
public:
    void push(int val) {
        vec_.push_back(val);
    }
    int pop() {
        int to_return = vec_.back();
        vec_.pop_back();
        return to_return;
    }
    bool empty() const {
        return vec_.empty();
    }
    int peek() const {
        return vec_.back();
    }
private:
    std::vector<int> vec_{};
};

stack::stack()
: impl_{std::make_unique<stack::impl>()}
{}

stack::~stack() {}

void stack::push(int val) {
    impl_->push(val);
}

int stack::pop() {
    return impl_->pop();
}

bool stack::empty() const {
    return impl_->empty();
}

int stack::peek() const {
    return impl_->peek();
}

void sort_stack_using_another_stack(stack& s) {
    stack tmp_stack;
    while (!s.empty()) {
        int tmp_element = s.pop();
        while (true) {
            if (tmp_stack.empty()) {
                tmp_stack.push(tmp_element);
                break;
            }
            if (tmp_stack.peek() > tmp_element) {
                s.push(tmp_stack.pop());
            } else {
                tmp_stack.push(tmp_element);
                break;
            }
        }
    }
    while (!tmp_stack.empty()) {
        s.push(tmp_stack.pop());
    }
}

BinaryTreeNode::~BinaryTreeNode() {
    if (left_child) {
        delete left_child;
    }
    if (right_child) {
        delete right_child;
    }
    if (parent && (parent->left_child == this)) {
        parent->left_child = nullptr;
    }
    if (parent && (parent->right_child == this)) {
        parent->right_child = nullptr;
    }
}

BinaryTreeNode * _bst_from_sorted_array_recursive(std::vector<int> const& vec, std::size_t begin_index, std::size_t end_index, BinaryTreeNode * parent) {
    assert(begin_index <= end_index);
    std::size_t mid_index = begin_index + std::ceil((end_index - begin_index)/2.0);
    BinaryTreeNode * centre_node = new BinaryTreeNode{};
    centre_node->parent = parent;
    centre_node->value = vec.at(mid_index);
    if (begin_index == end_index) {
        return centre_node;
    }
    centre_node->left_child = _bst_from_sorted_array_recursive(vec, begin_index, mid_index-1, centre_node);
    if (end_index > begin_index + 1) {
        centre_node->right_child = _bst_from_sorted_array_recursive(vec, mid_index+1, end_index, centre_node);
    }
    return centre_node;
}

BinaryTreeNode* bst_from_sorted_array(std::vector<int> const& vec) {
    if (vec.size() == 0) {
        return nullptr;
    }
    return _bst_from_sorted_array_recursive(vec, 0, vec.size()-1, nullptr);
}

struct tmp_is_bst_result {
    bool is_bst;
    int min_val;
    int max_val;
};

tmp_is_bst_result _check_if_bst_recursive(BinaryTreeNode * root) {
    assert(root != nullptr);
    bool is_bst = true;
    int min_val = root->value;
    int max_val = root->value;
    if (root->left_child) { 
        tmp_is_bst_result left_result = _check_if_bst_recursive(root->left_child);
        is_bst = is_bst && left_result.is_bst && left_result.min_val <= root->value;
        min_val = left_result.min_val;
    }
    if (root->right_child) {
        tmp_is_bst_result right_result = _check_if_bst_recursive(root->right_child);
        is_bst = is_bst && right_result.is_bst && right_result.max_val > root->value;
        max_val = right_result.max_val;
    }
    return {is_bst, min_val, max_val};
}

bool is_bst(BinaryTreeNode* root) {
    if (!root) {
        return true;
    }
    return _check_if_bst_recursive(root).is_bst;
}

void _populate_nodes_in_tree_to_vec(BinaryTreeNode const * root, std::vector<BinaryTreeNode const *>& nodes) {
    if (root == nullptr) {
        return;
    }
    nodes.push_back(root);
    _populate_nodes_in_tree_to_vec(root->left_child, nodes);
    _populate_nodes_in_tree_to_vec(root->right_child, nodes);
}

std::vector<BinaryTreeNode const*> _all_nodes_in_tree(BinaryTreeNode const * root) {
    std::vector<BinaryTreeNode const*> nodes = {};
    _populate_nodes_in_tree_to_vec(root, nodes);
    return nodes;
}

void _number_of_paths_with_sum_dfs(BinaryTreeNode const * root, std::size_t desired_sum, std::size_t current_sum, std::size_t& desired_sum_count) {
    if (!root) {
        return;
    }
    current_sum = root->value + current_sum;
    if (current_sum == desired_sum) {
        desired_sum_count ++;
    }
    _number_of_paths_with_sum_dfs(root->left_child, desired_sum, current_sum, desired_sum_count);
    _number_of_paths_with_sum_dfs(root->right_child, desired_sum, current_sum, desired_sum_count);
}

[[maybe_unused]] std::size_t _number_of_paths_with_sum_iterative(BinaryTreeNode const * root, std::size_t desired_sum) {
    std::vector<BinaryTreeNode const*> nodes = _all_nodes_in_tree(root);
    std::size_t paths_with_desired_sum = 0;
    for (BinaryTreeNode const * source : nodes) {
        _number_of_paths_with_sum_dfs(source, desired_sum, 0, paths_with_desired_sum);
    }
    return paths_with_desired_sum;
}

void increment_running_sum_count(
    std::unordered_map<int, std::size_t> & running_sum_counts,
    int current_sum, int delta
) {
    if (running_sum_counts.count(current_sum) == 0) {
        assert(delta == 1);
        running_sum_counts.insert({current_sum, delta});
    } else {
        running_sum_counts[current_sum] += delta;
    }
}

std::size_t _number_of_paths_with_sum_optimized(
    BinaryTreeNode const * root,
    int desired_sum,
    std::unordered_map<int, std::size_t>& running_sum_counts,
    std::size_t running_sum
) {
    if (!root) {
        return 0;
    }
    std::size_t number_of_paths = 0;
    int current_sum = running_sum + root->value;
    if (current_sum == desired_sum) {
        number_of_paths += 1;
    }
    if (running_sum_counts.count(current_sum-desired_sum) == 1) {
        number_of_paths += running_sum_counts.at(current_sum-desired_sum);
    }

    increment_running_sum_count(running_sum_counts, current_sum, 1);
    number_of_paths += _number_of_paths_with_sum_optimized(root->left_child, desired_sum, running_sum_counts, current_sum);
    number_of_paths += _number_of_paths_with_sum_optimized(root->right_child, desired_sum, running_sum_counts, current_sum);
    increment_running_sum_count(running_sum_counts, current_sum, -1);

    return number_of_paths;
}

std::size_t number_of_paths_with_sum(BinaryTreeNode const * root, int desired_sum) {
    if (!root) {
        return 0;
    }
    //return _number_of_paths_with_sum_iterative(root, desired_sum);
    std::unordered_map<int, std::size_t> running_sum_counts {};
    return _number_of_paths_with_sum_optimized(root, desired_sum, running_sum_counts, 0);
}

std::uint32_t _clear_bits(std::uint32_t N, unsigned short i, unsigned short j) {
    // produce mask like 0011000 where 1s are i through j
    std::uint32_t left_side_ones = (-1 << i);
    std::uint32_t right_side_ones = (1 << (j+1)) - 1;
    std::uint32_t mask = left_side_ones & right_side_ones;
    return N & (~mask);
}

std::uint32_t insert_bit_sequence_into_int(
    std::uint32_t N,
    std::uint32_t M,
    unsigned short i,
    unsigned short j
) {
    // clear bits i through j in N
    N = _clear_bits(N, i, j);
    // M with the relevant bits in correct position
    M = M << i;
    // insert
    N = N | M;
    return N;
}

std::string binary_to_string(double n) {
    assert(n > 0);
    assert(n < 1);
    std::string result = "0.";
    while (n>0) {
        if (result.size() > 32) {
            return "ERROR";
        }
        if (n*2 >= 1) {
            result.append("1");
            n = (n*2) - 1;
        } else {
            result.append("0");
            n = n*2;
        } 
    }
    return result;
}

std::size_t flip_a_bit_for_longest_ones_bit_sequence(std::uint32_t n) {
    std::size_t longest_seq = 1;
    std::size_t current_ones_seq = 0;
    std::size_t previous_ones_seq = 0;
    for (;; n=n/2) {
        bool current_bit = n%2;
        bool next_bit = (n/2)%2;
        if (current_bit == 1) {
            current_ones_seq ++;
            continue;
        }
        // else current_bit == 0
        longest_seq = std::max(longest_seq, current_ones_seq + previous_ones_seq + 1);
        if (next_bit == 0) {
            previous_ones_seq = 0;
        } else {
            previous_ones_seq = current_ones_seq;
        }
        current_ones_seq = 0;
        if (n == 0) {
            break;
        }
    }
    // assume there is a zero at the beginning
    return longest_seq;
}

std::uint32_t _update_bit(std::uint32_t n, std::size_t index, bool val) {
    //clear bit using 111101111 looking mask
    std::uint32_t mask = ~(1<<index);
    std::uint32_t cleared = mask & n;
    //set bit to val
    return cleared | (val<<index);
}

std::size_t _count_ones_in_bit_sub_sequence(std::uint32_t n, std::size_t i, std::size_t j) {
    assert(j >= i);
    std::size_t count = 0;
    for (std::size_t x=i; x<=j; x++) {
        bool current_bit = 1 & (n >> x);
        count += current_bit;
    }
    return count;
}

std::uint32_t _fill_bit_sub_sequence(std::uint32_t n, std::size_t i, std::size_t j, bool val) {
    if (j < i) {
        return n;
    }
    // produce mask like 00000xxx0000 where x is val
    std::uint32_t left_ones_mask = (-1) << i;
    std::uint32_t right_ones_mask = (1 << (j+1))-1;
    std::uint32_t mask = val ? (left_ones_mask & right_ones_mask) : 0;
    // clear middle part
    std::uint32_t mask_for_clearing = ~(left_ones_mask & right_ones_mask);
    std::size_t cleared = n & mask_for_clearing;
    std::uint32_t result = cleared | mask;
    return result;
}

std::uint32_t next_smallest_int_with_same_number_of_ones(std::uint32_t n) {
    // find the first transition from 0 to 1 (going from LSB to MSB)
    // and swap the 2 bits
    for (std::size_t i=0; i < sizeof(std::uint32_t)*8; i++) {
        std::uint32_t current_bit = (n >> i) & 1;
        std::uint32_t next_bit = (n >> (i + 1)) & 1;
        if ((next_bit == 1) && (current_bit == 0)) {
            n = _update_bit(n, i, 1);
            n = _update_bit(n, i+1, 0);
            if (i == 0) {
                return n;
            }
            // move all 1s (which are currently to the right of i) so that they are left aligned towards i
            std::size_t ones_count = _count_ones_in_bit_sub_sequence(n, 0, i-1);
            std::size_t zeros_count = i-ones_count;
            n = _fill_bit_sub_sequence(n, 0, zeros_count-1, 0);
            n = _fill_bit_sub_sequence(n, zeros_count, zeros_count+ones_count-1, 1);
            return n;
        }
    }
    return n;
}

std::size_t _count_remaining_steps_possibilities(std::size_t n, std::unordered_map<std::size_t, std::size_t> counts_memo) {
    if (counts_memo.count(n) == 1) {
        return counts_memo.at(n);
    }
    if (n == 0) {
        return 0;
    }
    if (n == 1) {
        return 1;
    }
    if (n == 2) {
        return 2;
    }
    if (n == 3) {
        return 4;
    }
    std::size_t count =
        _count_remaining_steps_possibilities(n-1, counts_memo) +
        _count_remaining_steps_possibilities(n-2, counts_memo) +
        _count_remaining_steps_possibilities(n-3, counts_memo);
    counts_memo[n] = count;
    return counts_memo.at(n);
}

std::size_t count_number_of_step_hop_sequences_to_cover_n_steps(std::size_t n) {
    std::unordered_map<std::size_t, std::size_t> memo {};
    return _count_remaining_steps_possibilities(n, memo);
}

std::unordered_set<std::string> _permutation_without_dups_suffix(std::string s) {
    if (0 == s.size()) {
        return {};
    }
    if (s.size() == 1) {
        return {s};
    }
    std::unordered_set<std::string> result;
    for (std::size_t i = 0; i<s.size(); i++) {
        std::string remaining_string = s.substr(0,i) + s.substr(i+1, s.size()-i-1);
        char current_char = s.at(i);
        std::unordered_set<std::string> suffix_permutations = _permutation_without_dups_suffix(remaining_string);
        for (auto it = suffix_permutations.begin(); it != suffix_permutations.end(); it++) {
            result.insert(std::string{current_char} + (*it));
        }
    }
    return result;
}
struct pair_hash
{
    template <class T1, class T2>
    std::size_t operator() (const std::pair<T1, T2> &pair) const {
        return std::hash<T1>()(pair.first) ^ std::hash<T2>()(pair.second);
    }
};

std::unordered_set<std::string> permutation_without_dups(std::string const& s) {
    return _permutation_without_dups_suffix(s);
}

std::size_t _count_ways_for_remaining(
    std::size_t n,
    std::vector<std::size_t> const& denoms,
    std::size_t denom_index,
    std::unordered_map<std::pair<std::size_t, std::size_t>, std::size_t, pair_hash>& memo
) {
    //count ways for representing n using denoms[:denom_index]
    if (memo.count({n, denom_index}) == 1) {
        return memo.at({n, denom_index});
    }
    if (n == 0) {
        return 1;
    }
    if (denoms.size() == 0) {
        return 0;
    }
    assert(denom_index < denoms.size());
    if (denom_index == 0) {
        if ((n % denoms.at(denom_index)) == 0) {
            return 1;
        } else {
            return 0;
        }
    }
    std::size_t result = 0;
    std::size_t current_denom = denoms.at(denom_index);
    for (std::size_t current_denom_count=0; current_denom_count * current_denom <= n; current_denom_count++) {
        std::size_t count_for_remaining = _count_ways_for_remaining(n-current_denom_count*current_denom, denoms, denom_index-1, memo);
        result += count_for_remaining;
    }
    memo[{n, denom_index}] = result;
    return memo.at({n, denom_index});
}

std::size_t count_ways_to_represent_n_cents(std::size_t n, std::vector<std::size_t> const& denoms) {
    std::unordered_map<std::pair<std::size_t, std::size_t>, std::size_t, pair_hash> memo {};
    return _count_ways_for_remaining(n, denoms, denoms.size()-1, memo);
}

bool _is_base_big_enough(std::size_t base_h, std::size_t base_w, std::size_t base_d, my_box const& box) {
    return (base_h >= box.height) && (base_d >= box.depth) && (base_w >= box.width);
}

// optimization: memmoize
std::size_t _compute_tallest_height_with_base_and_remaining_stack(std::vector<my_box> boxes, std::size_t base_h, std::size_t base_w, std::size_t base_d) {
    std::size_t tallest_height = 0;
    for (std::size_t i=0; i<boxes.size(); i++) {
        if (_is_base_big_enough(base_h, base_w, base_d, boxes.at(i))) {
            std::vector<my_box> remaining_boxes = boxes;
            remaining_boxes.erase(remaining_boxes.begin() + i);
            std::size_t remaining_height = _compute_tallest_height_with_base_and_remaining_stack(remaining_boxes, boxes.at(i).height, boxes.at(i).width, boxes.at(i).depth);
            if (tallest_height < remaining_height + boxes.at(i).height) {
                tallest_height = remaining_height + boxes.at(i).height;
            }
        }
    }
    return tallest_height;
}

std::size_t compute_tallest_height_of_stack(std::vector<my_box> const& boxes) {
    return _compute_tallest_height_with_base_and_remaining_stack(boxes, -1, -1, -1);
}

std::vector<std::string> string_list_decode(std::string const& str) {
    std::vector<std::string> res {};
    std::size_t i=0;
    std::string current_str = "";
    bool escape = false;
    while (i < str.size()) {
        char c = str.at(i);
        i++;
        if (escape) {
            current_str += c;
            escape = false;
            continue;
        }
        if (c == ':') {
            escape = true;
            continue;
        }
        if (c != ';') {
            current_str += c;
            continue;
        }
        res.push_back(current_str);
        current_str = "";
    }
    assert(!escape);
    assert(current_str.empty());
    return res;
}

std::string escape(std::string const& s) {
    std::string res {};
    for (char c: s) {
        if (c == ';' || c == ':') {
            res += ':';
        }
        res += c;
    }
    return res;
}

std::string string_list_encode(std::vector<std::string> const& strs) {
    std::string res = "";
    for (auto it=strs.cbegin(); it != strs.cend(); it++) {
        res += escape(*it);
        res += ";";
    }
    return res;
}

}
