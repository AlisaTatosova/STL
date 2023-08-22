#ifndef VECTOR_H
#define VECTOR_H

#include <initializer_list>
#include <iostream>

template <typename T>
class Vector {
public:
    Vector();
    Vector(std::size_t size);
    Vector(const Vector& other);
    Vector(Vector&& other) noexcept;
    ~Vector();

    std::size_t get_size() const;
    std::size_t get_capacity() const;

    void resize();
    void push_back(T val);
    void pop_back();
    void insert(std::size_t index, const T& value);
    void insert(std::size_t index, const T& value, std::size_t count);
    void insert(std::size_t index, const T arr[], std::size_t count);
    void insert(std::size_t index, std::initializer_list<T> list);
    void erase(std::size_t index);
    void erase(std::size_t index, std::size_t count);
    void shrink_to_fit();
    Vector& operator=(const Vector& rhs);
    T& operator[](std::size_t i);
    bool empty() const;
    void clear();

private:
    T* vec;
    std::size_t size;
    std::size_t capacity;
};


template <typename T>
Vector<T>::Vector() : size(0), capacity(2), vec(new T[capacity]) {}

template <typename T>
Vector<T>::Vector(std::size_t size) : size{size}, capacity{2 * size} {
    vec = new T[capacity];
}

template <typename T>
Vector<T>::Vector(const Vector& other) : size{other.size}, capacity{other.capacity} {
    vec = new T[capacity];
    for (std::size_t i = 0; i < other.size; ++i) {
        vec[i] = other.vec[i];
    }
}

template <typename T>
Vector<T>::Vector(Vector&& other) noexcept : size{other.size}, capacity{other.capacity}, vec{other.vec} {
    other.vec = nullptr;
    other.size = 0;
    other.capacity = 0;
}

template <typename T>
Vector<T>::~Vector() {
    delete[] vec;
}

template <typename T>
std::size_t Vector<T>::get_size() const {
    return size;
}

template <typename T>
std::size_t Vector<T>::get_capacity() const {
    return capacity;
}

template <typename T>
void Vector<T>::resize() {
    std::size_t new_capacity = 2 * size;
    T* new_vec = new T[new_capacity];
    for (std::size_t i = 0; i < size; ++i) {
        new_vec[i] = vec[i];
    }
    delete[] vec;
    vec = new_vec;
    capacity = new_capacity;
}

template <typename T>
void Vector<T>::push_back(T val) {
    if (size == capacity) {
        resize();
    }
    vec[size] = val;
    ++size;
}

template <typename T>
void Vector<T>::pop_back() {
    if (size > 0) {
        --size;
    }
}

template <typename T>
void Vector<T>::insert(std::size_t index, const T& value) {
    if (index > size) {
        return;
    }

    if (size + 1 > capacity) {
        resize();
    }

    for (std::size_t i = size; i > index; --i) {
        vec[i] = vec[i - 1];
    }

    vec[index] = value;
    ++size;
}

template <typename T>
void Vector<T>::insert(std::size_t index, const T& value, std::size_t count) {
    if (index > size) {
        return;
    }

    if (size + count > capacity) {
        while (size + count > capacity) {
            resize();
        }
    }

    for (std::size_t i = size + count - 1; i >= index + count; --i) {
        vec[i] = vec[i - count];
    }

    for (std::size_t i = index; i < index + count; ++i) {
        vec[i] = value;
    }

    size += count;
}

template <typename T>
void Vector<T>::insert(std::size_t index, const T arr[], std::size_t count) {
    if (index > size) {
        return;
    }

    if (size + count > capacity) {
        while (size + count > capacity) {
            resize();
        }
    }

    for (std::size_t i = size + count - 1; i >= index + count; --i) {
        vec[i] = vec[i - count];
    }

    for (std::size_t i = index; i < index + count; ++i) {
        vec[i] = arr[i - index];
    }

    size += count;
}

template <typename T>
void Vector<T>::insert(std::size_t index, std::initializer_list<T> list) {
    if (index > size) {
        return;
    }

    std::size_t count = list.size();
    if (size + count > capacity) {
        while (size + count > capacity) {
            resize();
        }
    }

    for (std::size_t i = size + count - 1; i >= index + count; --i) {
        vec[i] = vec[i - count];
    }

    std::size_t i = 0;
    for (const T& value : list) {
        vec[index + i] = value;
        ++i;
    }

    size += count;
}

template <typename T>
void Vector<T>::erase(std::size_t index) {
    if (index >= size) {
        return;
    }
    for (std::size_t i = index; i < size - 1; ++i) {
        vec[i] = vec[i + 1];
    }
    --size;
}

template <typename T>
void Vector<T>::erase(std::size_t index, std::size_t count) {
    if (index + count >= size) {
        return;
    }

    for (std::size_t i = index; i < size - count; ++i) {
        vec[i] = vec[i + count];
    }
    size -= count;
}

template <typename T>
void Vector<T>::shrink_to_fit() {
    if (size < capacity) {
        capacity = size;
        T* new_vec = new T[capacity];
        for (std::size_t i = 0; i < size; ++i) {
            new_vec[i] = vec[i];
        }
        delete[] vec;
        vec = new_vec;
    }
}

template <typename T>
Vector<T>& Vector<T>::operator=(const Vector& rhs) {
    if (this == &rhs) {
        return *this;
    }
    delete[] vec;
    size = rhs.size;
    capacity = rhs.capacity;
    vec = new T[capacity];
    for (std::size_t i = 0; i < size; ++i) {
        vec[i] = rhs.vec[i];
    }
    return *this;
}

template <typename T>
T& Vector<T>::operator[](std::size_t i) {
    return vec[i];
}

template <typename T>
bool Vector<T>::empty() const {
    return size == 0;
}

template <typename T>
void Vector<T>::clear() {
    delete[] vec;
    size = 0;
    capacity = 2;
    vec = new T[capacity];
}

#endif