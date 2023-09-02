#ifndef HASH_MAP_H
#define HASH_MAP_H
#include <vector>
#include <list>
#include <iostream>

class HashMap {
public:
    HashMap(int capacity = 7);
    double get_load_factor() const;
    void insert(const std::string& key, int value);
    void erase(const std::string& key);
    bool search(const std::string& key);
        
private:
    int capacity;
    int size;
    double load_factor;
    std::vector<std::list<std::pair<std::string, int>>> hash_table;

private:
    int hash(const std::string& key, int cap);
    void rehash();
    bool is_prime(int num);
    int get_next_prime_number(int num);
};

#endif