#ifndef QUEUE_H
#define QUEUE_H
#include "vector.h"
#include <initializer_list>

template <typename T>
class Queue : private Vector<T> {
public:
    std::size_t size() const;
    bool empty() const;
    void push(T val);
    void pop();
    T& back();
    T& top();
};

template <typename T>
std::size_t Queue<T>::size() const {
    return Vector<T>::get_size();
}

template <typename T>
bool Queue<T>::empty() const {
    return Vector<T>::empty();
}

template <typename T>
void Queue<T>::push(T val) {
    Vector<T>::push_back(val);
}

template <typename T>
void Queue<T>::pop() {
    if (!Vector<T>::empty()) {
        Vector<T>::erase(0);
    }
}

template <typename T>
T& Queue<T>::back() {
    return Vector<T>::operator[](this -> get_size() - 1);
}

template <typename T>
T& Queue<T>::top() {
    if (!Vector<T>::empty()) {
        return Vector<T>::operator[](0);
    }
    throw std::runtime_error("Queue is empty.");
}

#endif
