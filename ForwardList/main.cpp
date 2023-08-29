#include "forward_list.h"
#include <iostream>

int main() {
    List<int> list1;
    List<int> list2;
    list1.push_back(890);
    list1.push_back(16);
    list1.push_back(89);
    list2.push_back(3);
    list2.push_back(7);
    list2.push_back(50);
    list2.push_back(90);

    list1.sort();

    std::cout << "List after sorting: ";
    for (List<int>::Iterator it = list1.begin(); it != list1.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;

    list1.pop_back();

    std::cout << "List after pop_back: ";
    for (List<int>::Iterator it = list1.begin(); it != list1.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;

    List<int>::Iterator it = list2.begin();
    ++it;
    list2.erase(it);

    std::cout << "List2 after erase: ";
    for (int val : list2) {
        std::cout << val << " ";
    }
    std::cout << std::endl;

    return 0;
}
