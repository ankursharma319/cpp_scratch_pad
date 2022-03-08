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
