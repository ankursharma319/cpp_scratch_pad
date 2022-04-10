#include <gtest/gtest.h>
#include <forward_list>
#include <list>
#include <algorithm>
#include <numeric>

TEST(StdContainerTest, test_sort_large_forward_linked_list) {
    std::size_t my_size = 1000000;
    std::forward_list<int> my_list(my_size);
    std::iota (std::begin(my_list), std::end(my_list), 1);
    EXPECT_EQ(1, *my_list.cbegin());

    my_list.reverse();
    EXPECT_EQ(my_size, *my_list.cbegin());

    my_list.sort();
    EXPECT_EQ(1, *my_list.cbegin());
}

TEST(StdContainerTest, test_sort_large_doubly_linked_list) {
    std::size_t my_size = 1000000;
    std::list<int> my_list(my_size);
    std::iota (std::begin(my_list), std::end(my_list), 1);
    EXPECT_EQ(1, *my_list.cbegin());

    my_list.reverse();
    EXPECT_EQ(my_size, *my_list.cbegin());

    my_list.sort();
    EXPECT_EQ(1, *my_list.cbegin());
}
