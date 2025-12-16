// Copyright 2025 Alewa8131

#ifndef LIB_STACK_STACK_H_
#define LIB_STACK_STACK_H_
#pragma once
#include <stdexcept>

template <class T>
class Stack {
    T* _data;
    int _size;
    int _top = -1;
public:
    Stack();
    Stack(int size);
    Stack(const Stack& other);
    ~Stack();
    void push(T val);
    void pop();
    inline T top() const;
    inline bool is_empty() const noexcept;
    inline bool is_full() const noexcept;
    void clear() noexcept;
};

template<class T>
Stack<T>::Stack() : _data(nullptr), _size(0), _top(-1) {}

template<class T>
Stack<T>::Stack(int size) : _size(size), _top(-1) {
    if (size < 0) throw std::invalid_argument("Stack size cannot be negative.");
    _data = new T[size];
}

template <class T>
Stack<T>::Stack(const Stack& other) :
    _size(other._size),
    _top(other._top) {
    _data = new T[_size];
    for (int i = 0; i < other._size; i++) {
        _data[i] = other._data[i];
    }
}

template<class T>
Stack<T>::~Stack() {
    delete[] _data;
}

template<class T>
void Stack<T>::push(T val) {
    if (is_full()) {
        throw std::out_of_range("Stack is full, cannot push.");
    }
    _data[++_top] = val;
}

template<class T>
void Stack<T>::pop() {
    if (is_empty()) {
        throw std::out_of_range("Stack is empty, cannot pop.");
    }
    --_top;
}

template<class T>
T Stack<T>::top() const {
    if (is_empty()) {
        throw std::out_of_range("Stack is empty, no top element.");
    }
    return _data[_top];
}

template<class T>
inline bool Stack<T>::is_empty() const noexcept {
    return (_top == -1);
}

template<class T>
inline bool Stack<T>::is_full() const noexcept {
    return (_top == _size - 1);
}

template<class T>
void Stack<T>::clear() noexcept {
    _top = -1;
}

#endif  // LIB_STACK_STACK_H_
