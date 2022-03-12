#include "demonstrations.hpp"
#include "linked_list.hpp"
#include <iostream>
#include <ostream>
#include <vector>

void demonstrate_linked_list() {
    std::cout << "Demonstrating linked list" << std::endl;
    ankur::linked_list<int> my_list_1 {2, 4, 9};
    std::cout << "my_list_1.size() = " << my_list_1.size() << std::endl;
    std::vector<int> tmp_vector {1, 5, 6};
    ankur::linked_list<int> my_list_2 (tmp_vector.begin(), tmp_vector.end());
    std::cout << "my_list_2.size() = " << my_list_2.size() << std::endl;
    my_list_2 = ankur::linked_list<int>(std::size_t(5), 9);
    std::cout << "my_list_2.size() = " << my_list_2.size() << std::endl;
    ankur::linked_list<int> my_list_3 = my_list_2;
    my_list_3 = my_list_1;
    my_list_3 = my_list_2;
    std::cout << "my_list_3.size() = " << my_list_3.size() << std::endl;
    ankur::linked_list<int> my_list_4 = std::move(my_list_3);
    std::cout << "my_list_4.size() = " << my_list_4.size() << std::endl;
    my_list_4.insert_after(my_list_4.cbefore_begin(), -2);
    my_list_4.insert_after(my_list_4.cbefore_begin(), std::size_t(2), -3);
    my_list_4.insert_after(my_list_4.cbegin(), my_list_1.cbegin(), my_list_1.cend());
    std::cout << "my_list_4.size() = " << my_list_4.size() << std::endl;
    my_list_4.insert_after(my_list_4.cbegin(), {309, 319});
    my_list_4.emplace_after(my_list_4.cbefore_begin(), 45);
    my_list_4.push_front(44);
    my_list_4.emplace_front(42);
    my_list_4.emplace_front(42);
    my_list_4.pop_front();

    for (int const& x : my_list_4) {
        std::cout << "Looping my_list_4, x = " << x << std::endl;
    }
    std::cout << "my_list_4.empty() = " << my_list_4.empty() << std::endl;

    std::cout << "Erasing after cbegin to cbegin+4" << std::endl;
    auto start_it = my_list_4.cbegin();
    auto stop_it = start_it;
    ++stop_it;
    ++stop_it;
    ++stop_it;
    ++stop_it;
    my_list_4.erase_after(start_it, stop_it);

    for (int const& x : my_list_4) {
        std::cout << "Looping my_list_4, x = " << x << std::endl;
    }

    my_list_4.merge(my_list_4);
    ankur::linked_list<int> my_list_5 {1, 5, 6};
    my_list_1.merge(my_list_5);
    std::cout << "Merged my_list_1 with my_list_5" << std::endl;
    for (int const& x : my_list_1) {
        std::cout << "Looping my_list_1, x = " << x << std::endl;
    }

    ankur::linked_list<int> my_list_6 {10, 20};
    my_list_1.splice_after(my_list_1.cbegin(), my_list_6);
    std::cout << "splice_after my_list_1 with my_list_6" << std::endl;
    for (int const& x : my_list_1) {
        std::cout << "Looping my_list_1, x = " << x << std::endl;
    }

    ankur::linked_list<int> my_list_7 {11, 21, 31};
    my_list_1.splice_after(my_list_1.cbegin(), my_list_7, my_list_7.cbegin());
    std::cout << "splice_after my_list_1 with my_list_7" << std::endl;
    for (int const& x : my_list_1) {
        std::cout << "Looping my_list_1, x = " << x << std::endl;
    }
    for (int const& x : my_list_7) {
        std::cout << "Looping my_list_7, x = " << x << std::endl;
    }

    my_list_4.clear();
    std::cout << "my_list_4.size() after clearing = " << my_list_4.size() << std::endl;
    std::cout << "my_list_4.empty() = " << my_list_4.empty() << std::endl;
}
