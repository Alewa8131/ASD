// Copyright 2025 Alewa8131

#ifndef LIB_LISTQUEUE_LISTQUEUE_H_
#define LIB_LISTQUEUE_LISTQUEUE_H_
#pragma once
#include <stdexcept>

#include "../lib_list/list.h"

template <class T>
class ListQueue {
    List<T>* _data;
    int _count;
public:
    ListQueue();
    ListQueue(const ListQueue& other);
    ~ListQueue();
    void push(T val);
    void pop();
    inline T head() const;
    inline bool is_empty() const noexcept;
};

template<class T>
ListQueue<T>::ListQueue() : _count(0) {
    _data = new List<T>();
}

template <class T>
ListQueue<T>::ListQueue(const ListQueue& other) : _count(other._count) {
    _data = new List<T>();
    for (typename List<T>::Iterator it = other._data->begin(); 
        it != other._data->end(); ++it) {
        _data->push_back(*it);
    }
}

template<class T>
ListQueue<T>::~ListQueue() {
    delete _data;
}

template<class T>
void ListQueue<T>::push(T val) {
    _data->push_back(val);
    _count++;
}

template<class T>
void ListQueue<T>::pop() {
    if (is_empty()) {
        throw std::out_of_range("Queue is empty, cannot pop.");
    }
    _data->pop_front();
    _count--;
}

template<class T>
inline T ListQueue<T>::head() const {
    if (is_empty()) {
        throw std::out_of_range("Queue is empty, no head element.");
    }
    return _data->head()->_value;
}

template<class T>
bool ListQueue<T>::is_empty() const noexcept {
    return _count == 0;
}

#endif  // LIB_LISTQUEUE_LISTQUEUE_H_
