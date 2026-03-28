// Copyright 2026 Alewa8131

#ifndef LIB_HEAP_HEAP_H_
#define LIB_HEAP_HEAP_H_
#pragma once

#include <iostream>
#include "../lib_tvector/tvector.h"

template<class T>
class Heap {
    TVector<T> _data;
public:
    Heap() = default;
    ~Heap() = default;

    void siftup(size_t pos);
    void siftdown(size_t pos);
    void insert(const T& val);
    T pop();
    void print();

    size_t get_left(size_t pos) const;
    size_t get_right(size_t pos) const;
    size_t get_parent(size_t pos) const;
};

template<class T>
void Heap<T>::print() {
    for (int i = 0; i < _data.size(); i++)
        std::cout << _data[i] << " ";
    std::cout << "\n";
}

template<class T>
void Heap<T>::insert(const T& val) {
    _data.push_back(val);
    if (_data.size() > 1) {
        siftup(_data.size() - 1);
    }
}

template<class T>
T Heap<T>::pop() {
    if (_data.size() == 0)
        throw std::out_of_range("Heap underflow: cannot pop from an empty heap");

    T root_val = _data[0];
    _data[0] = _data[_data.size() - 1];
    _data.pop_back();

    if (_data.size() > 0)
        siftdown(0);

    return root_val;
}

template<class T>
void Heap<T>::siftup(size_t pos) {
    while (pos > 0) {
        size_t parent = get_parent(pos);
        if (_data[pos] < _data[parent]) {
            T temp = _data[parent];
            _data[parent] = _data[pos];
            _data[pos] = temp;
            pos = parent;
        } else {
            break;
        }
    }
}

template<class T>
void Heap<T>::siftdown(size_t pos) {
    while (1) {
        size_t left = get_left(pos);
        size_t right = get_right(pos);
        size_t smallest = pos;

        if (left < _data.size() && _data[left] < _data[smallest]) {
            smallest = left;
        }
        if (right < _data.size() && _data[right] < _data[smallest]) {
            smallest = right;
        }

        if (smallest != pos) {
            T temp = _data[pos];
            _data[pos] = _data[smallest];
            _data[smallest] = temp;
            pos = smallest;
        } else {
            break;
        }
    }
}

template<class T>
size_t Heap<T>::get_left(size_t pos) const {
    return (pos + 1) * 2 - 1;
}

template<class T>
size_t Heap<T>::get_right(size_t pos) const {
    return (pos + 1) * 2;
}

template<class T>
size_t Heap<T>::get_parent(size_t pos) const {
    return (pos - 1) / 2;
}

#endif  // LIB_HEAP_HEAP_H_
