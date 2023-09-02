#ifndef HASH_MAP_H
#define HASH_MAP_H
#include <vector>
#include <list>
#include <iostream>

class HashMap {
public:
    HashMap(int capacity = 7) 
        : capacity{capacity}
        , size{0}
        , load_factor{0.67}
        , hash_table(capacity, std::list<std::pair<std::string, int>>()) {}

    double get_load_factor() const {
        return load_factor;
    }

    void insert(const std::string& key, int value) {
        if (static_cast<double> (size) / capacity > load_factor) {
            rehash();
        }

        int index = hash(key, capacity);
        std::list<std::pair<std::string, int>>& bucket = hash_table[index];

        for (auto& el : bucket) {
            if (el.first == key) {
                el.second = value;
                return;
            }
        }

        bucket.push_back({key, value});
        size++;
    }


    void erase(const std::string& key) {
        int index = hash(key, capacity);
        std::list<std::pair<std::string, int>>& bucket = hash_table[index];
    
        for (auto it = bucket.begin(); it != bucket.end(); ++it) {
            if (it -> first == key) {
                bucket.erase(it);
                --size;
                return;
            }
        }
        throw std::out_of_range("Key not found in hash table."); 
    }

    bool search(const std::string& key) {
        int index = hash(key, capacity);
        std::list<std::pair<std::string, int>>& bucket = hash_table[index];
        for (auto it = bucket.begin(); it != bucket.end(); ++it) {
            if (it -> first == key) {
                return true;
            }
        }
        return false;
    }
        
private:
    int capacity;
    int size;
    double load_factor;
    std::vector<std::list<std::pair<std::string, int>>> hash_table;

    int hash(const std::string& key, int cap) {
        int hashValue = 0;
        for (char ch : key) {
            hashValue += (ch - 32);
        }
        return hashValue % cap;
    }

    void rehash() {
        int new_capacity = get_next_prime_number(2 * capacity); // to preserve uniformity we get the next prime number of 2 * cap
        std::vector<std::list<std::pair<std::string, int>>> new_table(new_capacity, std::list<std::pair<std::string, int>>());
        for (int i = 0; i < new_table.size(); ++i) {
            std::list<std::pair<std::string, int>>& bucket = hash_table[i];
            for (auto it = bucket.begin(); it != bucket.end(); ++it) {
                int index = hash(it -> first, new_capacity);
                new_table[index].push_back({it -> first, it -> second});
            }
        }
        hash_table = new_table;
    }

    bool is_prime(int num) {
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

    int get_next_prime_number(int num) {
        while (!is_prime(num)) {
            ++num;
        }
        return num;
    }
};

#endif