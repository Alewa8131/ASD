// Copyright 2026 Alewa8131

#ifndef LIB_PRIORITYHEAPQUEUE_PRIORITYHEAPQUEUE_H_
#define LIB_PRIORITYHEAPQUEUE_PRIORITYHEAPQUEUE_H_
#pragma once

#include <stdexcept>
#include "../lib_heap/heap.h"

template <class T>
class PriorityHeapQueue {
    struct PriorVal {
    public:
        T _value;
        int _prior;
        size_t _index;
        PriorVal() : _value(T()), _prior(0), _index(0) {}
        PriorVal(T value, int prior, size_t index) : _value(value), _prior(prior), _index(index) {}
        bool operator<(const PriorVal& other) const {
            if (_prior != other._prior)
                return _prior < other._prior;
            return _index < other._index;
        }
        bool operator>(const PriorVal& other) const {
            return other < *this;
        }
    };

    Heap<PriorVal> _data;
    int _count = 0;
    size_t _index = 0;
public:
    PriorityHeapQueue() = default;
    PriorityHeapQueue(const PriorityHeapQueue& other);
    void push(T val, int prior);
    T pop();
    inline bool is_empty() const noexcept;
};


template<class T>
PriorityHeapQueue<T>::
PriorityHeapQueue(const PriorityHeapQueue& other) :
        _data(other._data), _count(other._count),
        _index(other._index) {}

template<class T>
void PriorityHeapQueue<T>::push(T val, int prior) {
    _data.insert(PriorVal(val, prior, this->_index));

    _index++;
    _count++;
}

template<class T>
T PriorityHeapQueue<T>::pop() {
    if (is_empty())
        throw std::out_of_range("Queue is empty, cannot pop.");

    _count--;
    PriorVal result = _data.pop();
    return result._value;
}

template<class T>
bool PriorityHeapQueue<T>::is_empty() const noexcept {
    return _count == 0;
}

#endif  // LIB_PRIORITYHEAPQUEUE_PRIORITYHEAPQUEUE_H_
