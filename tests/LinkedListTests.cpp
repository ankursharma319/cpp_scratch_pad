#include <gtest/gtest.h>
#include "linked_list.hpp"
#include <algorithm>
#include <numeric>

TEST(LinkedListTest, test_comparison_operators) {
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

TEST(LinkedListTest, test_iterator_constructors) {
    ankur::linked_list<int> my_list {2, 4, 9};
    EXPECT_EQ(3, my_list.size());

    auto it1 = my_list.begin();
    auto it2 = ankur::linked_list<int>::iterator(it1);
    EXPECT_EQ(it1, it2);

    auto it3 = my_list.cbegin();
    auto it4 = ankur::linked_list<int>::const_iterator(it3);
    EXPECT_EQ(it3, it4);

    auto it5 = my_list.begin();
    auto it6 = ankur::linked_list<int>::const_iterator(it5);
    EXPECT_EQ(my_list.cbegin(), it6);

    auto it7 = my_list.cbegin();
    auto it8 = ankur::linked_list<int>::iterator(it7);
    EXPECT_EQ(my_list.begin(), it8);
}

TEST(LinkedListTest, test_constructors_assignments_and_iterator) {
    ankur::linked_list<int> my_list_0 {};
    EXPECT_EQ(0, my_list_0.size());

    ankur::linked_list<int> my_list_1 {2, 4, 9};
    EXPECT_EQ(3, my_list_1.size());
    EXPECT_EQ(ankur::linked_list({2, 4, 9}), my_list_1);

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
}

TEST(LinkedListTest, test_modifier_funcs) {
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

    ankur::linked_list<double> expectation {};
    expectation = { 42, 44, 45, -3, 309, 319, 10, 20, -3, -2, 1, 2, 3 };
    EXPECT_EQ(expectation, my_list);
    EXPECT_EQ(false, my_list.empty());
    my_list.clear();
    EXPECT_EQ(true, my_list.empty());
}

TEST(LinkedListTest, test_erase_after) {
    ankur::linked_list<double> my_list {1, 2, 3, 4, 5, 6};
    auto start_it = my_list.cbegin();
    auto stop_it = start_it;
    ++stop_it;
    ++stop_it;
    ++stop_it;
    my_list.erase_after(start_it, stop_it);

    EXPECT_EQ(ankur::linked_list<double>({1, 4, 5, 6}), my_list);
}

TEST(LinkedListTest, test_merge) {
    ankur::linked_list<int> my_list {2, 4, 6, 7};
    my_list.merge(my_list);
    EXPECT_EQ(4, my_list.size());
    ankur::linked_list<int> tmp_list {1, 5, 6};
    my_list.merge(tmp_list);
    ankur::linked_list<int> tmp_list_2 {9, 9};
    my_list.merge(tmp_list_2);
    EXPECT_EQ(0, tmp_list.size());

    EXPECT_EQ(ankur::linked_list<int>({1, 2, 4, 5, 6, 6, 7, 9, 9}), my_list);
}

TEST(LinkedListTest, test_splice) {
    ankur::linked_list<int> my_list {1, 2, 3};
    ankur::linked_list<int> tmp_list {10, 12};

    my_list.splice_after(my_list.cbegin(), tmp_list);
    EXPECT_EQ(0, tmp_list.size());

    tmp_list = {21, 22, 23};
    my_list.splice_after(my_list.cbegin(), tmp_list, tmp_list.cbegin());
    EXPECT_EQ(2, tmp_list.size());

    EXPECT_EQ(ankur::linked_list<int>({1, 22, 10, 12, 2, 3}), my_list);
}

TEST(LinkedListTest, test_remove) {
    ankur::linked_list<int> my_list {1, 2, 3, 5, 7, 5, 3, 2, 1};
    my_list.remove(2);
    my_list.remove_if([](auto const& val) { return (val == 5) || (val == 7); });
    EXPECT_EQ(ankur::linked_list<int>({1, 3, 3, 1}), my_list);
}

TEST(LinkedListTest, test_reverse) {
    ankur::linked_list<int> my_list {1, 2, 3};
    my_list.reverse();
    EXPECT_EQ(ankur::linked_list<int>({3, 2, 1}), my_list);
}

TEST(LinkedListTest, test_unique) {
    ankur::linked_list<int> my_list {1, 2, 2, 2, 3, 2, 2, 3,  2};
    my_list.unique();
    EXPECT_EQ(ankur::linked_list<int>({1, 2, 3, 2, 3, 2}), my_list);
}

TEST(LinkedListTest, test_sort) {
    ankur::linked_list<int> my_list {1, 3, 2, 5, 4, 1};
    my_list.sort();
    EXPECT_EQ(ankur::linked_list<int>({1, 1, 2, 3, 4, 5}), my_list);

    my_list = {1, 3, 2};
    my_list.sort();
    EXPECT_EQ(ankur::linked_list<int>({1, 2, 3}), my_list);
}

TEST(LinkedListTest, test_swap) {
    ankur::linked_list<int> my_list_1 {1, 2};
    ankur::linked_list<int> my_list_2 {7, 8, 9};
    ankur::linked_list<int> my_list_3 {7, 8, 9};
    ankur::linked_list<int> my_list_4 {1, 2};

    std::swap(my_list_1, my_list_2);
    EXPECT_TRUE(my_list_1 == my_list_3);
    EXPECT_TRUE(my_list_2 == my_list_4);
}

TEST(LinkedListTest, test_std_algorithm_fill_and_iota) {
    ankur::linked_list<int> my_list(5);
    EXPECT_EQ(5, my_list.size());

    std::fill(my_list.begin(), my_list.end(), 99);
    EXPECT_EQ(ankur::linked_list<int>({99, 99, 99, 99, 99}), my_list);

    std::iota (std::begin(my_list), std::end(my_list), 2);
    EXPECT_EQ(ankur::linked_list<int>({2, 3, 4, 5, 6}), my_list);
}

TEST(LinkedListTest, test_sort_large) {
    std::size_t my_size = 1E5;
    ankur::linked_list<int> my_list(my_size);
    std::iota (std::begin(my_list), std::end(my_list), 1);
    EXPECT_EQ(1, *my_list.cbegin());

    my_list.reverse();
    EXPECT_EQ(my_size, *my_list.cbegin());

    my_list.sort();
    EXPECT_EQ(1, *my_list.cbegin());
}

TEST(LinkedListTest, test_non_default_constructible_T) {
    class MyType {
    public:
        MyType(int x):m_x(x+3) {}
    private:
        MyType();
        int m_x;
    };

    //MyType should_give_compiler_error {};

    ankur::linked_list<MyType> my_list_1 {1, 2};
    EXPECT_EQ(2, my_list_1.size());

    ankur::linked_list<MyType> my_list_2(std::size_t(4), 2);
    EXPECT_EQ(4, my_list_2.size());

    ankur::linked_list<MyType> my_list_3(std::size_t(4), MyType(5));
    EXPECT_EQ(4, my_list_3.size());

    // should be compiler error
    //ankur::linked_list<MyType> my_list_4(std::size_t(5));
    //EXPECT_EQ(5, my_list_4.size());
}

TEST(LinkedListTest, test_const_T) {
    ankur::linked_list<const int> my_list{1, 3, 4};
    EXPECT_EQ(3, my_list.size());

    auto it = my_list.begin();
    EXPECT_EQ(1, *it);

    // should be compiler error
    // *it = 2;
    //EXPECT_EQ(2, *it);
}

TEST(LinkedListTest, test_volatile_T) {
    ankur::linked_list<volatile int> my_list{1, 3, 4};
    EXPECT_EQ(3, my_list.size());

    auto it = my_list.begin();
    EXPECT_EQ(1, *it);
    *it = 2;
    EXPECT_EQ(2, *it);

    auto cit = my_list.cbegin();
    EXPECT_EQ(2, *cit);
    // should be compiler error
    //*cit = 0;
    //EXPECT_EQ(0, *cit);
}


TEST(LinkedListTest, test_reference_T) {
    // should fail to compile

    /*int a = 2;
    int b = 5;
    ankur::linked_list<int&> my_list{a, b};
    EXPECT_EQ(2, *cit);*/
}
