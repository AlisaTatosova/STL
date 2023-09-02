#include "hash_set.h"
#include <iostream>

int main() {
    HashSet hash_set;
    hash_set.insert(1);
    hash_set.insert(2);
    std::cout << "Contains 1: " << hash_set.search(1) << std::endl; 
    std::cout << "Contains 3: " << hash_set.search(3) << std::endl;
    hash_set.erase(2);
    std::cout << "Contains 2: " << hash_set.search(2) << std::endl; 

    return 0;
}