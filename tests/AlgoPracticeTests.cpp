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
