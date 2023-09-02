#include "hash_set.h"

HashSet::HashSet(int capacity) 
    : capacity{capacity}
    , size{0}
    , load_factor{0.67}
    , hash_table(capacity, std::vector<int>()) {}

double HashSet::get_load_factor() const {
    return load_factor;
}

void HashSet::insert(int key) {
    if (static_cast<double> (size) / capacity > load_factor) {
        rehash();
    } else {
        if (search(key)) {
            return;
        }
        int index = key % capacity;
        hash_table[index].push_back(key);
        ++size;
    }
}

void HashSet::erase(int key) {
    int index = hash(key, capacity);
    std::vector<int>& bucket = hash_table[index];
    
    for (int i = 0; i < bucket.size(); ++i) {
        if (bucket[i] == key) {
            bucket.erase(bucket.begin() + i);
            --size;
            return;
        }
    }
    throw std::out_of_range("Key not found in hash table.");  
}

bool HashSet::search(int key) {
    int index = hash(key, capacity);
    for (int i = 0; i < hash_table[index].size(); ++i) {
        if (hash_table[index][i] == key) {
            return true;
        }
    }
    return false;
}
        
int HashSet::hash(int key, int cap) {
    return key % cap;
}

void HashSet::rehash() {
    int new_capacity = get_next_prime_number(2 * capacity); // to preserve uniformity we get the next prime number of 2 * cap
    std::vector<std::vector<int>> new_table(new_capacity, std::vector<int>());
    for (int i = 0; i < hash_table.size(); ++i) {
        for (int j = 0; j < hash_table[i].size(); ++i) {
            int index = hash(hash_table[i][j], new_capacity);
            new_table[index].push_back(hash_table[i][j]);
        }
    }
    hash_table = new_table;
}

bool HashSet::is_prime(int num) {
    if (num == 1) {
        return false;
    } 
    for (int i = 2; i <= num / 2; ++i) {
        if (num % i == 0) {
            return false;
        }
    }
    return true;
}

int HashSet::get_next_prime_number(int num) {
    while (!is_prime(num)) {
        ++num;
    }
    return num;
}