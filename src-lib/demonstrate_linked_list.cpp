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

    my_list_4.clear();
    std::cout << "my_list_4.size() = " << my_list_4.size() << std::endl;
    //std::cout << "my_list.empty() = " << my_list.empty() << std::endl;
    /*std::cout << "my_list.head() = " << my_list.head() << std::endl;
    std::cout << "my_list.tail() = " << my_list.tail() << std::endl;

    auto ret_it_1 = my_list.insert(my_list.end(), 5);
    auto ret_it_2 = my_list.insert(my_list.cbegin(), 1);
    std::cout << "*ret_it_1  = " << *ret_it_1 << std::endl;
    std::cout << "*ret_it_2 = " << *ret_it_2 << std::endl;
    auto it_insert = my_list.begin();
    it_insert++;
    it_insert++;
    auto ret_it_3 = my_list.insert(it_insert, {20, 30});
    std::cout << "*ret_it_3 = " << *ret_it_3 << std::endl;

    for (auto const& x : my_list) {
        std::cout << "Looping, x = " << x << std::endl;
    }*/
}
