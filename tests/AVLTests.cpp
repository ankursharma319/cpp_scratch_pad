
#include <gtest/gtest.h>
#include "avl_tree.hpp"
#include <algorithm>
#include <iostream>
#include <numeric>
#include <vector>

TEST(AVLTest, test_size_insert_and_print) {
    ankur::avl_tree my_tree {};
    EXPECT_EQ(my_tree.size(), 0);
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
        "9(s=-1,h=3)\n"
        "|--5(s=0,h=2)\n"
        "|  |--3(s=0,h=1)\n"
        "|  |  |--2(s=0,h=0)\n"
        "|  |  |--4(s=0,h=0)\n"
        "|  |--7(s=1,h=1)\n"
        "|     |--8(s=0,h=0)\n"
        "|--10(s=1,h=1)\n"
        "   |--12(s=0,h=0)\n";
    EXPECT_EQ(expected_string_repr, my_tree.to_string());
}
