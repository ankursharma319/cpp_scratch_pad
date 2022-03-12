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
