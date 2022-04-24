
#include <gtest/gtest.h>
#include "binary_search_tree.hpp"
#include <algorithm>
#include <iostream>
#include <numeric>
#include <vector>

TEST(BSTTest, test_insert_and_print) {
    ankur::binary_search_tree my_tree {};
    my_tree.insert(9);
    my_tree.insert(5);
    my_tree.insert(10);
    my_tree.insert(12);
    my_tree.insert(7);
    my_tree.insert(8);
    my_tree.insert(3);
    my_tree.insert(2);
    my_tree.insert(4);
    EXPECT_EQ(9, my_tree.size());
    std::string expected_string_repr =
        "9\n"
        "|--5\n"
        "|  |--3\n"
        "|  |  |--2\n"
        "|  |  |--4\n"
        "|  |--7\n"
        "|     |--8\n"
        "|--10\n"
        "   |--12\n";
    EXPECT_EQ(expected_string_repr, my_tree.to_string());
}
