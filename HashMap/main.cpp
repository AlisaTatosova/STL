#include "hash_map.h"

int main() {
    HashMap hashSet;
    hashSet.insert("Alisa", 2);
    hashSet.insert("Ann", 3);
    std::cout << "Contains 1: " << hashSet.search("Alisa") << std::endl; 
    std::cout << "Contains 3: " << hashSet.search("a") << std::endl; 
    hashSet.erase("Ann");
    std::cout << "Contains 2: " << hashSet.search("Ann") << std::endl; 

    return 0;
}

