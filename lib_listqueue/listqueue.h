// Copyright 2025 Alewa8131

#include <stdexcept>
#include "../lib_list/list.h"

template <class T>
class ListQueue {
    List<T>* _data;
    int _size, _count;
public:
    ListQueue();
    ListQueue(int size);
    ListQueue(const ListQueue& other);
    ~ListQueue();
    void push(T val);
    void pop();
    inline T head() const;
    inline bool is_empty() const noexcept;
    inline bool is_full() const noexcept;
};

template<class T>
ListQueue<T>::ListQueue() : _size(0), _count(0) {
    _data = new List<T>();
}

template<class T>
ListQueue<T>::ListQueue(int size) : _size(size), _count(0) {
    if (size < 0) throw std::invalid_argument("Queue size cannot be negative.");
    _data = new List<T>();
}

template <class T>
ListQueue<T>::ListQueue(const ListQueue& other) :
    _size(other._size),
    _count(other._count) {
    _data = new List<T>();
    for (List<int>::Iterator it = other._data->begin(); it != other._data->end(); ++it) {
        _data->push_back(*it);
    }
}

template<class T>
ListQueue<T>::~ListQueue() {
    delete _data;
}

template<class T>
void ListQueue<T>::push(T val) {
    if (is_full()) {
        throw std::out_of_range("Queue is full, cannot push.");
    }
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

template<class T>
bool ListQueue<T>::is_full() const noexcept {
    return _count == _size;
}
