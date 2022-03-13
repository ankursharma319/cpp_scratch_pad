#include <gtest/gtest.h>
#include "linked_list.hpp"

class LinkedListTestFixture : public testing::Test {
protected:
    LinkedListTestFixture() {
    }

    ~LinkedListTestFixture() = default;
};


TEST_F(LinkedListTestFixture, test_constructors_assignments_and_iterator) {
    ankur::linked_list<int> my_list_1 {2, 4, 9};
    EXPECT_EQ(3, my_list_1.size());
    std::vector<int> tmp_vector {1, 5, 6};
    ankur::linked_list<int> my_list_2 (tmp_vector.begin(), tmp_vector.end());
    EXPECT_EQ(3, my_list_2.size());
    my_list_2 = ankur::linked_list<int>(std::size_t(5), 9);
    EXPECT_EQ(5, my_list_2.size());
    ankur::linked_list<int> my_list_3 = my_list_2;
    my_list_3 = my_list_1;
    my_list_3 = my_list_2;
    EXPECT_EQ(5, my_list_3.size());

    ankur::linked_list<int> my_list_4 = std::move(my_list_3);
    EXPECT_EQ(5, my_list_4.size());

    auto i = 0;
    std::vector expected_values = {2, 4, 9};
    for (int const& x : my_list_1) {
        int const& y = expected_values.at(i);
        EXPECT_EQ(y, x);
        i++;
    }
}

TEST_F(LinkedListTestFixture, test_modifier_funcs) {
    ankur::linked_list<double> my_list {1, 2, 3};
    my_list.insert_after(my_list.cbefore_begin(), -2);
    my_list.insert_after(my_list.cbefore_begin(), std::size_t(2), -3);
    ankur::linked_list<double> tmp_list {10, 20};
    my_list.insert_after(my_list.cbegin(), tmp_list.cbegin(), tmp_list.cend());
    my_list.insert_after(my_list.cbegin(), {309, 319});
    my_list.emplace_after(my_list.cbefore_begin(), 45);
    my_list.push_front(44);
    my_list.emplace_front(42);
    my_list.emplace_front(42);
    my_list.pop_front();

    auto i = 0;
    std::vector<double> expectation = {
        42, 44, 45, -3, 309, 319, 10, 20, -3, -2, 1, 2, 3
    };
    for (double const& x : my_list) {
        double const& y = expectation.at(i);
        EXPECT_EQ(y, x);
        i++;
    }
    EXPECT_EQ(expectation.size(), my_list.size());
    EXPECT_EQ(false, my_list.empty());
    my_list.clear();
    EXPECT_EQ(true, my_list.empty());
}

TEST_F(LinkedListTestFixture, test_erase_after) {
    ankur::linked_list<double> my_list {1, 2, 3, 4, 5, 6};
    auto start_it = my_list.cbegin();
    auto stop_it = start_it;
    ++stop_it;
    ++stop_it;
    ++stop_it;
    my_list.erase_after(start_it, stop_it);

    auto i = 0;
    std::vector<double> expectation = {1, 4, 5, 6};
    EXPECT_EQ(expectation.size(), my_list.size());
    for (double const& x : my_list) {
        double const& y = expectation.at(i);
        EXPECT_EQ(y, x);
        i++;
    }
}

TEST_F(LinkedListTestFixture, test_merge) {
    ankur::linked_list<int> my_list {2, 4, 6, 7};
    my_list.merge(my_list);
    EXPECT_EQ(4, my_list.size());
    ankur::linked_list<int> tmp_list {1, 5, 6};
    my_list.merge(tmp_list);
    ankur::linked_list<int> tmp_list_2 {9, 9};
    my_list.merge(tmp_list_2);
    EXPECT_EQ(0, tmp_list.size());

    auto i = 0;
    std::vector<int> expectation = {1, 2, 4, 5, 6, 6, 7, 9, 9};
    EXPECT_EQ(expectation.size(), my_list.size());
    for (auto const& x : my_list) {
        auto const& y = expectation.at(i);
        EXPECT_EQ(y, x);
        i++;
    }
}

TEST_F(LinkedListTestFixture, test_splice) {
    ankur::linked_list<int> my_list {1, 2, 3};
    ankur::linked_list<int> tmp_list {10, 12};

    my_list.splice_after(my_list.cbegin(), tmp_list);
    EXPECT_EQ(0, tmp_list.size());

    tmp_list = {21, 22, 23};
    my_list.splice_after(my_list.cbegin(), tmp_list, tmp_list.cbegin());
    EXPECT_EQ(2, tmp_list.size());

    auto i = 0;
    std::vector<int> expectation = {1, 22, 10, 12, 2, 3};
    EXPECT_EQ(expectation.size(), my_list.size());
    for (auto const& x : my_list) {
        auto const& y = expectation.at(i);
        EXPECT_EQ(y, x);
        i++;
    }
}

TEST_F(LinkedListTestFixture, test_remove) {
    ankur::linked_list<int> my_list {1, 2, 3, 5, 7, 5, 3, 2, 1};
    my_list.remove(2);
    my_list.remove_if([](auto const& val) { return (val == 5) || (val == 7); });

    auto i = 0;
    std::vector<int> expectation = {1, 3, 3, 1};
    EXPECT_EQ(expectation.size(), my_list.size());
    for (auto const& x : my_list) {
        auto const& y = expectation.at(i);
        EXPECT_EQ(y, x);
        i++;
    }
}

TEST_F(LinkedListTestFixture, test_reverse) {
    ankur::linked_list<int> my_list {1, 2, 3};
    my_list.reverse();

    auto i = 0;
    std::vector<int> expectation = {3, 2, 1};
    EXPECT_EQ(expectation.size(), my_list.size());
    for (auto const& x : my_list) {
        auto const& y = expectation.at(i);
        EXPECT_EQ(y, x);
        i++;
    }
}

TEST_F(LinkedListTestFixture, test_unique) {
    ankur::linked_list<int> my_list {1, 2, 2, 2, 3, 2, 2, 3,  2};
    my_list.unique();

    auto i = 0;
    std::vector<int> expectation = {1, 2, 3, 2, 3, 2};
    EXPECT_EQ(expectation.size(), my_list.size());
    for (auto const& x : my_list) {
        auto const& y = expectation.at(i);
        EXPECT_EQ(y, x);
        i++;
    }
}

TEST_F(LinkedListTestFixture, test_sort) {
    ankur::linked_list<int> my_list {1, 3, 2, 5, 4, 1};
    my_list.sort();

    auto i = 0;
    std::vector<int> expectation = {1, 1, 2, 3, 4, 5};
    EXPECT_EQ(expectation.size(), my_list.size());
    for (auto const& x : my_list) {
        auto const& y = expectation.at(i);
        EXPECT_EQ(y, x);
        i++;
    }

    my_list = {1, 3, 2};
    my_list.sort();

    i = 0;
    expectation = {1, 2, 3};
    EXPECT_EQ(expectation.size(), my_list.size());
    for (auto const& x : my_list) {
        auto const& y = expectation.at(i);
        EXPECT_EQ(y, x);
        i++;
    }
}

TEST_F(LinkedListTestFixture, test_comparison_operators) {
    ankur::linked_list<int> my_list_1 {1, 2};
    ankur::linked_list<int> my_list_2 {7, 8, 9};
    ankur::linked_list<int> my_list_3 {7, 8, 9};

    EXPECT_FALSE(my_list_1 == my_list_2);
    EXPECT_TRUE(my_list_1 != my_list_2);
    EXPECT_FALSE(my_list_1 >= my_list_2);
    EXPECT_TRUE(my_list_1 <= my_list_2);
    EXPECT_TRUE(my_list_1 < my_list_2);
    EXPECT_FALSE(my_list_1 > my_list_2);

    EXPECT_TRUE(my_list_2 == my_list_3);
    EXPECT_FALSE(my_list_2 != my_list_3);
    EXPECT_TRUE(my_list_2 >= my_list_3);
    EXPECT_TRUE(my_list_2 <= my_list_3);
    EXPECT_FALSE(my_list_2 < my_list_3);
    EXPECT_FALSE(my_list_2 > my_list_3);
}

TEST_F(LinkedListTestFixture, test_swap) {
    ankur::linked_list<int> my_list_1 {1, 2};
    ankur::linked_list<int> my_list_2 {7, 8, 9};
    ankur::linked_list<int> my_list_3 {7, 8, 9};
    ankur::linked_list<int> my_list_4 {1, 2};

    std::swap(my_list_1, my_list_2);
    EXPECT_TRUE(my_list_1 == my_list_3);
    EXPECT_TRUE(my_list_2 == my_list_4);
}
