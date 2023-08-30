#include "self-organizing-list.h"
#include <iostream>

int main() {
    SelfOrganizingList<int> list;
    list.push_back(5);
    list.push_back(89);
    list.push_back(3);
    list.push_back(4);
    list.pop_back();
    list.push_back(111);
    list.insert(3, 77);

    std::cout << "List before geting some position: ";
    list.print();

    const int a = list.get_at(2);

    std::cout << "List after geting position: ";
    list.print();
    
    std::cout << "Sorted list in ascending: ";
    list.print_ascending_order();

    std::cout << "Sorted list in descending: ";
    list.print_descending_order();
}