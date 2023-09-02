#ifndef HASH_SET_H
#define HASH_SET_H
#include <vector>
#include <iostream>

class HashSet {
public:
    HashSet(int capacity = 7);
    double get_load_factor() const;
    void insert(int key);
    void erase(int key);
    bool search(int key);
        
private:
    int capacity;
    int size;
    double load_factor;
    std::vector<std::vector<int>> hash_table;

private:
    int hash(int key, int cap);
    void rehash();
    bool is_prime(int num);
    int get_next_prime_number(int num) ;
};

#endif