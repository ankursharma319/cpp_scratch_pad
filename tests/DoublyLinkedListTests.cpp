#include <gtest/gtest.h>
#include <algorithm>
#include <numeric>
#include "doubly_linked_list.hpp"

TEST(DoublyLinkedListTest, test_comparison_operators) {
    ankur::doubly_linked_list my_list_1 {1, 2};
    ankur::doubly_linked_list my_list_2 {7, 8, 9};

    EXPECT_FALSE(my_list_1 == my_list_2);
    EXPECT_TRUE(my_list_1 == my_list_1);
    EXPECT_TRUE(my_list_2 == my_list_2);
}

TEST(DoublyLinkedListTest, test_constructor) {
    ankur::doubly_linked_list my_list_0 {};
    EXPECT_EQ(0, my_list_0.size());

    ankur::doubly_linked_list my_list_1 {2, 4, 9};
    EXPECT_EQ(3, my_list_1.size());
    EXPECT_EQ(ankur::doubly_linked_list({2, 4, 9}), my_list_1);

    ankur::doubly_linked_list my_list_2 = ankur::doubly_linked_list(std::size_t(5));
    EXPECT_EQ(5, my_list_2.size());
}

TEST(DoublyLinkedListTest, test_iterator_constructor) {
    ankur::doubly_linked_list my_list {2, 4, 9};
    EXPECT_EQ(3, my_list.size());

    auto it1 = my_list.begin();
    auto it2 = ankur::doubly_linked_list::iterator(it1);
    EXPECT_EQ(it1, it2);
}

TEST(DoublyLinkedListTest, test_iterator_increment_decrement) {
    ankur::doubly_linked_list my_list {2, 4, 9};
    EXPECT_EQ(3, my_list.size());

    auto it = my_list.begin();
    EXPECT_EQ(2, *it);
    ++it;
    EXPECT_EQ(4, *it);
    ++it;
    EXPECT_EQ(9, *it);
    ++it;
    --it;
    EXPECT_EQ(9, *it);
    --it;
    EXPECT_EQ(4, *it);
    --it;
    EXPECT_EQ(2, *it);
    --it;
    ++it;
    EXPECT_EQ(2, *it);
}

TEST(DoublyLinkedListTest, test_insert) {
    ankur::doubly_linked_list my_list {1, 2, 3};
    my_list.insert(my_list.begin(), 0);
    EXPECT_EQ(4, my_list.size());
    my_list.insert(my_list.end(), 4);
    EXPECT_EQ(5, my_list.size());
    EXPECT_EQ(ankur::doubly_linked_list({0, 1, 2, 3, 4}), my_list);
}

TEST(DoublyLinkedListTest, test_push_and_pop) {
    ankur::doubly_linked_list my_list {1, 2, 3};
    my_list.push_back(4);
    my_list.push_front(0);
    EXPECT_EQ(ankur::doubly_linked_list({0, 1, 2, 3, 4}), my_list);

    my_list.pop_back();
    my_list.pop_front();
    EXPECT_EQ(ankur::doubly_linked_list({1, 2, 3}), my_list);
}

TEST(DoublyLinkedListTest, test_clear_and_empty) {
    ankur::doubly_linked_list my_list {1, 2, 3};
    EXPECT_EQ(false, my_list.empty());
    my_list.clear();
    EXPECT_EQ(true, my_list.empty());
}

TEST(DoublyLinkedListTest, test_erase) {
    ankur::doubly_linked_list my_list {1, 2, 3, 4, 5, 6};
    auto start_it = my_list.begin();
    auto it = start_it;
    ++it;
    ++it;
    auto new_it = my_list.erase(it);

    EXPECT_EQ(ankur::doubly_linked_list({1, 2, 4, 5, 6}), my_list);
    EXPECT_EQ(4, *new_it);
}

TEST(DoublyLinkedListTest, test_merge) {
    ankur::doubly_linked_list my_list {2, 4, 6, 7};
    ASSERT_EQ(4, my_list.size());
    ankur::doubly_linked_list tmp_list_1 {1, 5, 6};
    my_list.merge(tmp_list_1);
    ASSERT_EQ(0, tmp_list_1.size());
    ASSERT_EQ(7, my_list.size());
    ankur::doubly_linked_list tmp_list_2 {9, 9};
    my_list.merge(tmp_list_2);
    ASSERT_EQ(0, tmp_list_2.size());
    ASSERT_EQ(9, my_list.size());

    ASSERT_EQ(ankur::doubly_linked_list({1, 2, 4, 5, 6, 6, 7, 9, 9}), my_list);
}

TEST(DoublyLinkedListTest, test_remove) {
    ankur::doubly_linked_list my_list {1, 2, 3, 2, 1};
    my_list.remove(2);
    EXPECT_EQ(ankur::doubly_linked_list({1, 3, 1}), my_list);
}

TEST(DoublyLinkedListTest, test_reverse) {
    ankur::doubly_linked_list my_list {1, 2, 3};
    my_list.reverse();
    EXPECT_EQ(ankur::doubly_linked_list({3, 2, 1}), my_list);
}

TEST(DoublyLinkedListTest, test_std_algorithm_fill_and_iota) {
    ankur::doubly_linked_list my_list(5);
    EXPECT_EQ(5, my_list.size());

    std::fill(my_list.begin(), my_list.end(), 99);
    EXPECT_EQ(ankur::doubly_linked_list({99, 99, 99, 99, 99}), my_list);

    std::iota (std::begin(my_list), std::end(my_list), 2);
    EXPECT_EQ(ankur::doubly_linked_list({2, 3, 4, 5, 6}), my_list);
}

TEST(DoublyLinkedListTest, test_sort) {
    ankur::doubly_linked_list my_list {1, 3, 2, 5, 4, 1};
    my_list.sort();
    EXPECT_EQ(ankur::doubly_linked_list({1, 1, 2, 3, 4, 5}), my_list);

    ankur::doubly_linked_list my_list_2 {1, 3, 2};
    my_list_2.sort();
    EXPECT_EQ(ankur::doubly_linked_list({1, 2, 3}), my_list_2);
}

TEST(DoublyLinkedListTest, test_sort_large) {
    std::size_t my_size = 1000000;
    ankur::doubly_linked_list my_list(my_size);
    std::iota (std::begin(my_list), std::end(my_list), 1);
    EXPECT_EQ(1, *my_list.begin());

    my_list.reverse();
    EXPECT_EQ(my_size, *my_list.begin());

    my_list.sort();
    EXPECT_EQ(1, *my_list.begin());
}
