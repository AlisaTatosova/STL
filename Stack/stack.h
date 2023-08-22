#ifndef STACK_H
#define STACK_H
#include "vector.h"

template <typename T>
class Stack : private Vector<T> {
public:
    void push(T val);
    void pop();
    T& top();
    std::size_t size() const;
    bool empty() const;
};

template <typename T>
void Stack<T>::push(T val) {
    Vector<T>::push_back(val);
}

template <typename T>
void Stack<T>::pop() {
    if (!Vector<T>::empty()) {
        Vector<T>::pop_back();
    }
}

template <typename T>
T& Stack<T>::top() {
    if (!Vector<T>::empty()) {
        return (*this)[Vector<T>::get_size() - 1];
    }
}

template <typename T>
std::size_t Stack<T>::size() const {
    return Vector<T>::get_size();
}

template <typename T>
bool Stack<T>::empty() const {
    return Vector<T>::empty();
}

#endif