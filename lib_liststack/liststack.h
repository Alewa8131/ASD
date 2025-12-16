// Copyright 2025 Alewa8131

#ifndef LIB_LISTSTACK_LISTSTACK_H_
#define LIB_LISTSTACK_LISTSTACK_H_
#pragma once
#include <stdexcept>

#include "../lib_list/list.h"

template <class T>
class ListStack {
    List<T>* _data;
    int _size;
    int _top = -1;
public:
    ListStack();
    ListStack(int size);
    ListStack(const ListStack& other);
    ~ListStack();
    void push(T val);
    void pop();
    inline T top() const;
    inline bool is_empty() const noexcept;
    inline bool is_full() const noexcept;
    void clear() noexcept;
};

template<class T>
ListStack<T>::ListStack() : _size(0), _top(-1) {
    _data = new List<T>();
}

template<class T>
ListStack<T>::ListStack(int size) : _size(size), _top(-1) {
    if (size < 0) throw std::invalid_argument("Stack size cannot be negative.");
    _data = new List<T>();
}

template <class T>
ListStack<T>::ListStack(const ListStack& other)
    : _size(other._size), _top(other._top) {
    _data = new List<T>();

    for (List<int>::Iterator it = other._data->begin(); it != other._data->end(); ++it) {
        _data->push_back(*it);
    }
}

template<class T>
ListStack<T>::~ListStack() {
    delete _data;
}

template<class T>
void ListStack<T>::push(T val) {
    if (is_full()) {
        throw std::out_of_range("Stack is full, cannot push.");
    }
    _data->push_front(val);
    ++_top;
}

template<class T>
void ListStack<T>::pop() {
    if (is_empty()) {
        throw std::out_of_range("Stack is empty, cannot pop.");
    }
    _data->pop_front();
    --_top;
}

template<class T>
T ListStack<T>::top() const {
    if (is_empty()) {
        throw std::out_of_range("Stack is empty, no top element.");
    }
    return *(_data->begin());
}

template<class T>
inline bool ListStack<T>::is_empty() const noexcept {
    return (_top == -1);
}

template<class T>
inline bool ListStack<T>::is_full() const noexcept {
    return (_top == _size - 1);
}

template<class T>
void ListStack<T>::clear() noexcept {
    for (int i = 0; i <= _top; i++) {
        _data->pop_front();
    }
    _top = -1;
}

#endif  // LIB_LISTSTACK_LISTSTACK_H_
