#include "algo_practice.hpp"
#include <string>
#include <gtest/gtest.h>

TEST(AlgoPracticeTest, test_1_4_palindrome_permutation) {
    EXPECT_EQ(true, ankur::is_palindrome_permutation("Tact Coa"));
    EXPECT_EQ(true, ankur::is_palindrome_permutation("tactcoa"));
    EXPECT_EQ(true, ankur::is_palindrome_permutation(" Tact 12312Ca"));
    EXPECT_EQ(true, ankur::is_palindrome_permutation("_,.-xyzxzy-  ++"));
    EXPECT_EQ(true, ankur::is_palindrome_permutation(""));
    EXPECT_EQ(true, ankur::is_palindrome_permutation("    "));
    EXPECT_EQ(false, ankur::is_palindrome_permutation("Tact Coal"));
    EXPECT_EQ(false, ankur::is_palindrome_permutation("_-xyxjzxzy-  ++"));
    EXPECT_EQ(false, ankur::is_palindrome_permutation("hello world"));
}

TEST(AlgoPracticeTest, test_1_9_string_rotation) {
    EXPECT_EQ(true, ankur::is_rotated_string("waterbottle", "erbottlewat"));
    EXPECT_EQ(false, ankur::is_rotated_string("waterbottles", "erbottlewat"));
    EXPECT_EQ(true, ankur::is_rotated_string("Waterbottles are good", "erbottles are goodWat"));
    EXPECT_EQ(false, ankur::is_rotated_string("waterbottles are good.", "erbottles are good wat"));
    EXPECT_EQ(true, ankur::is_rotated_string("", ""));
    EXPECT_EQ(false, ankur::is_rotated_string("", " "));
    EXPECT_EQ(true, ankur::is_rotated_string("exempelary", "elaryexemp"));
    EXPECT_EQ(true, ankur::is_rotated_string("exempelary", "exempelary"));
    EXPECT_EQ(false, ankur::is_rotated_string("exempelary", "Exempelary"));
    EXPECT_EQ(true, ankur::is_rotated_string("youryour", "ouryoury"));
    EXPECT_EQ(false, ankur::is_rotated_string("your", "ouryoury"));
}

TEST(AlgoPracticeTest, test_2_4_linked_list_partition) { 
    ankur::ForwardListNode * head = ankur::create_forward_list_from_vector({3, 5, 8, 5, 10, 2, 1});
    signed int partition_value = 5;
    ankur::ForwardListNode * new_head = ankur::partition_forward_list_node(head, partition_value);
    ankur::ForwardListNode * expected_head = ankur::create_forward_list_from_vector({3, 2, 1, 5, 8, 5, 10});
    EXPECT_TRUE(*expected_head == *new_head);
    delete new_head;
    delete expected_head;
}

TEST(AlgoPracticeTest, test_2_6_is_linked_list_palindrome) {
    ankur::ForwardListNode * head = ankur::create_forward_list_from_vector({3, 5, 8, 5, 10, 2, 1});
    EXPECT_EQ(false, ankur::is_linked_list_palindrome(head));
    delete head;

    head = ankur::create_forward_list_from_vector({3, 4, 5, 3});
    EXPECT_EQ(false, ankur::is_linked_list_palindrome(head));
    delete head;

    head = ankur::create_forward_list_from_vector({3, 4, 5, 4});
    EXPECT_EQ(false, ankur::is_linked_list_palindrome(head));
    delete head;

    head = ankur::create_forward_list_from_vector({1, 3, 5, 6, 6, 5, 3, 1});
    EXPECT_EQ(true, ankur::is_linked_list_palindrome(head));
    delete head;

    head = ankur::create_forward_list_from_vector({1, 3, 5, 6, 7, 6, 5, 3, 1});
    EXPECT_EQ(true, ankur::is_linked_list_palindrome(head));
    delete head;

    head = ankur::create_forward_list_from_vector({4});
    EXPECT_EQ(true, ankur::is_linked_list_palindrome(head));
    delete head;
}

TEST(AlgoPracticeTest, test_3_4_queue_via_stacks) {
    ankur::stack s {};
    EXPECT_EQ(true, s.empty());
    s.push(4);
    s.push(3);
    EXPECT_EQ(3, s.peek());
    EXPECT_EQ(3, s.peek());
    EXPECT_EQ(3, s.pop());
    EXPECT_FALSE(s.empty());
    EXPECT_EQ(4, s.pop());
    EXPECT_TRUE(s.empty());

    ankur::queue_via_stacks q {};
    q.enqueue(3);
    q.enqueue(5);
    EXPECT_EQ(3, q.dequeue());
    EXPECT_FALSE(q.empty());
    EXPECT_EQ(5, q.dequeue());
    EXPECT_TRUE(q.empty());
    q.enqueue(7);
    q.enqueue(7);
    q.enqueue(8);
    EXPECT_FALSE(q.empty());
    EXPECT_EQ(8, q.peek());
    EXPECT_EQ(7, q.dequeue());
    EXPECT_FALSE(q.empty());
    EXPECT_EQ(7, q.dequeue());
    EXPECT_EQ(8, q.dequeue());
    EXPECT_TRUE(q.empty());
}

TEST(AlgoPracticeTest, test_3_5_sort_stack) {
    ankur::stack s {};
    for (int val: {9,5,3,7,2,9,1,2,8,4}) {
        s.push(val);
    }
    ankur::sort_stack_using_another_stack(s);
    for (int val: {1,2,2,3,4,5,7,8,9,9}) {
        EXPECT_EQ(val, s.pop());
    }
}

TEST(AlgoPracticeTest, test_4_2_bst_from_sorted_array) {
    ankur::BinaryTreeNode * root = ankur::bst_from_sorted_array({1,2,3,4,5,6,7,8});
    ASSERT_NE(nullptr, root);
    EXPECT_EQ(nullptr, root->parent);
    ankur::BinaryTreeNode * node_1_1 = root->left_child;
    ankur::BinaryTreeNode * node_1_2 = root->right_child;
    ankur::BinaryTreeNode * node_2_1 = node_1_1->left_child;
    ankur::BinaryTreeNode * node_2_2 = node_1_1->right_child;
    ankur::BinaryTreeNode * node_2_3 = node_1_2->left_child;
    ankur::BinaryTreeNode * node_2_4 = node_1_2->right_child;
    ankur::BinaryTreeNode * node_3_1 = node_2_1->left_child;
    EXPECT_EQ(nullptr, node_2_1->right_child);
    EXPECT_EQ(nullptr, node_2_2->left_child);
    EXPECT_EQ(nullptr, node_2_2->right_child);
    EXPECT_EQ(nullptr, node_2_3->left_child);
    EXPECT_EQ(nullptr, node_2_3->right_child);
    EXPECT_EQ(nullptr, node_2_4->left_child);
    EXPECT_EQ(nullptr, node_2_4->right_child);
    EXPECT_EQ(5, root->value);
    EXPECT_EQ(3, node_1_1->value);
    EXPECT_EQ(7, node_1_2->value);
    EXPECT_EQ(2, node_2_1->value);
    EXPECT_EQ(4, node_2_2->value);
    EXPECT_EQ(6, node_2_3->value);
    EXPECT_EQ(8, node_2_4->value);
    EXPECT_EQ(1, node_3_1->value);
    delete root;
}

TEST(AlgoPracticeTest, test_4_5_confirm_if_binary_tree_is_bst) {
    ankur::BinaryTreeNode * root = ankur::bst_from_sorted_array({1,2,3,4,5,6,7,8,9});
    EXPECT_TRUE(ankur::is_bst(root));
    delete root;

    root = new ankur::BinaryTreeNode{};
    root->value = 2;
    root->left_child = new ankur::BinaryTreeNode{};
    root->left_child->value = 4;
    EXPECT_FALSE(ankur::is_bst(root));
    delete root;

    root = new ankur::BinaryTreeNode{};
    root->value = 2;
    root->left_child = new ankur::BinaryTreeNode{};
    root->left_child->value = 2;
    root->right_child = new ankur::BinaryTreeNode{};
    root->right_child->value = 3;
    EXPECT_TRUE(ankur::is_bst(root));
    delete root;

    root = ankur::bst_from_sorted_array({1,2,3,4,5,6,7,8,9});
    root->value = 10;
    EXPECT_FALSE(ankur::is_bst(root));
    delete root;

}

TEST(AlgoPracticeTest, test_4_12_path_of_sums) {
    ankur::BinaryTreeNode* root = new ankur::BinaryTreeNode{};
    root->left_child = new ankur::BinaryTreeNode{};
    root->right_child = new ankur::BinaryTreeNode{};
    root->left_child->left_child = new ankur::BinaryTreeNode{};
    root->left_child->right_child = new ankur::BinaryTreeNode{};
    root->value = 1;
    root->left_child->value = 2;
    root->left_child->left_child->value = 3;
    root->left_child->right_child->value = -4;
    root->right_child->value = 2;

    EXPECT_EQ(1, ankur::number_of_paths_with_sum(root, -4));
    EXPECT_EQ(0, ankur::number_of_paths_with_sum(root, -3));
    EXPECT_EQ(1, ankur::number_of_paths_with_sum(root, -2));
    EXPECT_EQ(1, ankur::number_of_paths_with_sum(root, -1));
    EXPECT_EQ(0, ankur::number_of_paths_with_sum(root, 0));
    EXPECT_EQ(1, ankur::number_of_paths_with_sum(root, 1));
    EXPECT_EQ(2, ankur::number_of_paths_with_sum(root, 2));
    EXPECT_EQ(3, ankur::number_of_paths_with_sum(root, 3));
    EXPECT_EQ(0, ankur::number_of_paths_with_sum(root, 4));
    EXPECT_EQ(1, ankur::number_of_paths_with_sum(root, 5));
    EXPECT_EQ(1, ankur::number_of_paths_with_sum(root, 6));
    EXPECT_EQ(0, ankur::number_of_paths_with_sum(root, 7));
    delete root;
}

TEST(AlgoPracticeTest, test_5_1_insert_bit_seq_into_int) {
    EXPECT_EQ(0b10001001100, ankur::insert_bit_sequence_into_int(0b10000000000, 0b10011, 2, 6));
    EXPECT_EQ(0b10000, ankur::insert_bit_sequence_into_int(0b0, 0b10000, 0, 4));
    EXPECT_EQ(0b111, ankur::insert_bit_sequence_into_int(0b1111111111, 0b0, 3, 9));
}

TEST(AlgoPracticeTest, test_5_2_binary_as_string) {
    EXPECT_EQ("0.1", ankur::binary_to_string(0.5));
    EXPECT_EQ("0.01", ankur::binary_to_string(0.25));
    EXPECT_EQ("0.11", ankur::binary_to_string(0.75));
    EXPECT_EQ("0.111", ankur::binary_to_string(0.875));
    EXPECT_EQ("ERROR", ankur::binary_to_string(0.333));
    EXPECT_EQ("ERROR", ankur::binary_to_string(0.33333333333));
}

TEST(AlgoPracticeTest, test_5_3_flip_a_bit) {
    EXPECT_EQ(1, ankur::flip_a_bit_for_longest_ones_bit_sequence(0b0));
    EXPECT_EQ(4, ankur::flip_a_bit_for_longest_ones_bit_sequence(0b1110));
    EXPECT_EQ(3, ankur::flip_a_bit_for_longest_ones_bit_sequence(0b101010));
    EXPECT_EQ(6, ankur::flip_a_bit_for_longest_ones_bit_sequence(0b11111));
    EXPECT_EQ(6, ankur::flip_a_bit_for_longest_ones_bit_sequence(0b1101110101));
    EXPECT_EQ(8, ankur::flip_a_bit_for_longest_ones_bit_sequence(0b11011101111));
    EXPECT_EQ(7, ankur::flip_a_bit_for_longest_ones_bit_sequence(0b111101101));
}

TEST(AlgoPracticeTest, test_5_4_next_smallest_int_with_same_number_of_ones) {
    EXPECT_EQ(0b1001, ankur::next_smallest_int_with_same_number_of_ones(0b1010));
    EXPECT_EQ(0b1010, ankur::next_smallest_int_with_same_number_of_ones(0b1100));
    EXPECT_EQ(0b101, ankur::next_smallest_int_with_same_number_of_ones(0b110));
    EXPECT_EQ(0b1011, ankur::next_smallest_int_with_same_number_of_ones(0b1101));
    EXPECT_EQ(0b1010011, ankur::next_smallest_int_with_same_number_of_ones(0b1010101));
    EXPECT_EQ(0b10101001, ankur::next_smallest_int_with_same_number_of_ones(0b10101010));
    EXPECT_EQ(0b111010, ankur::next_smallest_int_with_same_number_of_ones(0b111100));
    EXPECT_EQ(0b1111, ankur::next_smallest_int_with_same_number_of_ones(0b10111));
    EXPECT_EQ(0b101111, ankur::next_smallest_int_with_same_number_of_ones(0b110111));
    EXPECT_EQ(0b10101110, ankur::next_smallest_int_with_same_number_of_ones(0b10110011));
    EXPECT_EQ(0b11011011111100, ankur::next_smallest_int_with_same_number_of_ones(0b11011100011111));
}

TEST(AlgoPracticeTest, test_8_1_triple_step) {
    EXPECT_EQ(1, ankur::count_number_of_step_hop_sequences_to_cover_n_steps(1));
    EXPECT_EQ(2, ankur::count_number_of_step_hop_sequences_to_cover_n_steps(2));
    EXPECT_EQ(4, ankur::count_number_of_step_hop_sequences_to_cover_n_steps(3));
    // [[1,1,1,1], [1,1,2],[1,2,1],[2,1,1],[2,2],[1,3],[3,1]]
    EXPECT_EQ(7, ankur::count_number_of_step_hop_sequences_to_cover_n_steps(4));
}

TEST(AlgoPracticeTest, test_8_7_permutation_without_dups) {
    EXPECT_EQ(
        std::unordered_set<std::string>({"a"}),
        ankur::permutation_without_dups("a")
    );
    EXPECT_EQ(
        std::unordered_set<std::string>({"aA", "Aa"}),
        ankur::permutation_without_dups("aA")
    );
    EXPECT_EQ(
        std::unordered_set<std::string>({"abc", "acb", "bac", "bca", "cab", "cba"}),
        ankur::permutation_without_dups("abc")
    );
    EXPECT_EQ(24, ankur::permutation_without_dups("abcd").size());
}

TEST(AlgoPracticeTest, test_8_11_coins_representating_n_cents) {
    EXPECT_EQ(1, ankur::count_ways_to_represent_n_cents(1, {1,5,10,25}));
    EXPECT_EQ(1, ankur::count_ways_to_represent_n_cents(4, {1,5,10,25}));
    EXPECT_EQ(4, ankur::count_ways_to_represent_n_cents(10, {1,5,10,25}));
}

TEST(AlgoPracticeTest, test_8_13_stack_of_boxes) {
    EXPECT_EQ(0, ankur::compute_tallest_height_of_stack({}));
    EXPECT_EQ(20, ankur::compute_tallest_height_of_stack({{20,15,10}}));
    EXPECT_EQ(30, ankur::compute_tallest_height_of_stack({{20,5,5}, {10,5,3}}));
    EXPECT_EQ(35, ankur::compute_tallest_height_of_stack({{20,5,5}, {10,5,3}, {5,4,3}}));
    EXPECT_EQ(25, ankur::compute_tallest_height_of_stack({{20,5,5}, {10,6,3}, {5,4,3}}));
}

TEST(AlgoPracticeTest, neetcode_encode_decode_strings) {
    std::vector<std::vector<std::string>> inputs {
        {""},
        {"", ""},
        {},
        {"hello", "world"},
        {"lint","code","love","you"},
        {"//","",";",":","",";;",},
        {"a","","",":","::",";;",":;"},
    };
    for (auto const& input: inputs) {
        EXPECT_EQ(input, ankur::string_list_decode(ankur::string_list_encode(input)));
    }
}

