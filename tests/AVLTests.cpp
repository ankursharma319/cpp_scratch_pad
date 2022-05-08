
#include <gtest/gtest.h>
#include "avl_tree.hpp"
#include <algorithm>
#include <iostream>
#include <numeric>
#include <vector>

TEST(AVLTest, test_simple_insert_and_print) {
    ankur::avl_tree my_tree {};
    EXPECT_EQ(my_tree.size(), 0);
    my_tree.insert(9);
    my_tree.insert(5);
    my_tree.insert(10);
    my_tree.insert(12);
    my_tree.insert(7);
    my_tree.insert(3);
    my_tree.insert(8);
    my_tree.insert(2);
    my_tree.insert(4);
    EXPECT_EQ(9, my_tree.size());
    // h is height of node
    // s is height sidedness where left is negative and right is positive
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

TEST(AVLTest, test_avl_property_is_preserved_during_insert_right_rotate) {
    ankur::avl_tree my_tree {};
    my_tree.insert(9);
    my_tree.insert(5);
    my_tree.insert(4);
    my_tree.insert(3);
    EXPECT_EQ(4, my_tree.size());
    std::string expected_string_repr =
        "5(s=-1,h=2)\n"
        "|--4(s=-1,h=1)\n"
        "|  |--3(s=0,h=0)\n"
        "|--9(s=0,h=0)\n";
    EXPECT_EQ(expected_string_repr, my_tree.to_string());
}

TEST(AVLTest, test_avl_property_is_preserved_during_insert_left_rotate) {
    ankur::avl_tree my_tree {};
    my_tree.insert(3);
    my_tree.insert(4);
    my_tree.insert(5);
    my_tree.insert(9);
    EXPECT_EQ(4, my_tree.size());
    std::string expected_string_repr =
        "4(s=1,h=2)\n"
        "|--3(s=0,h=0)\n"
        "|--5(s=1,h=1)\n"
        "   |--9(s=0,h=0)\n";
    EXPECT_EQ(expected_string_repr, my_tree.to_string());
}

TEST(AVLTest, test_avl_property_is_preserved_during_zigzag_rotate) {
    ankur::avl_tree my_tree {};
    my_tree.insert(20);
    my_tree.insert(14);
    my_tree.insert(29);
    my_tree.insert(10);
    my_tree.insert(17);
    my_tree.insert(16);
    EXPECT_EQ(6, my_tree.size());
    std::string expected_string_repr =
        "17(s=0,h=2)\n"
        "|--14(s=0,h=1)\n"
        "|  |--10(s=0,h=0)\n"
        "|  |--16(s=0,h=0)\n"
        "|--20(s=1,h=1)\n"
        "   |--29(s=0,h=0)\n";
    EXPECT_EQ(expected_string_repr, my_tree.to_string());
}
