// Copyright 2025 Alewa8131

#include <stdexcept>
#include "../lib_node/node.h"

template <class T>
class DoubleList {
    DoubleNode<T> *_head;
    DoubleNode<T> *_tail;
    size_t _count;
public:
    DoubleList();
    DoubleList(const DoubleList<T>& other);
    ~DoubleList();

    size_t size() const noexcept;
    DoubleNode<T>* head() const noexcept;
    DoubleNode<T>* tail() const noexcept;

    inline bool is_empty() const noexcept;

    void push_front(const T& val) noexcept;
    void push_back(const T& val) noexcept;
    void insert(DoubleNode<T>* node, const T& val);
    void insert(size_t pos, const T& val);


    void pop_front();
    void pop_back();
    void erase(size_t pos);
    void erase(DoubleNode<T>* node);
};


template <class T>
DoubleList<T>::DoubleList() : _head(nullptr), _tail(nullptr), _count(0) {}

template <class T>
DoubleList<T>::DoubleList(const DoubleList<T>& other) : _head(nullptr), _tail(nullptr), _count(0) {
    DoubleNode<T>* current = other._head;
    while (current != nullptr) {
        push_back(current->_value);
        current = current->_next;
    }
}

template <class T>
DoubleList<T>::~DoubleList() {
    DoubleNode<T>* current = _head;
    DoubleNode<T>* next_node = nullptr;
    while (current != nullptr) {
        next_node = current->_next;
        delete current;
        current = next_node;
    }
    _head = nullptr;
    _tail = nullptr;
    _count = 0;
}

template <class T>
size_t DoubleList<T>::size() const noexcept { return _count; }

template <class T>
DoubleNode<T>* DoubleList<T>::head() const noexcept { return _head; }

template <class T>
DoubleNode<T>* DoubleList<T>::tail() const noexcept { return _tail; }

template <class T>
inline bool DoubleList<T>::is_empty() const noexcept { return _head == nullptr; }

template <class T>
void DoubleList<T>::push_front(const T& val) noexcept {
    DoubleNode<T>* node = new DoubleNode<T>(val);

    if (is_empty()) { 
        _head = node;
        _tail = node;
    } else { 
        node->_next = _head;
        _head->_prev = node;
        _head = node;
    }
    _count++;
}

template <class T>
void DoubleList<T>::push_back(const T& val) noexcept {
    DoubleNode<T>* node = new DoubleNode<T>(val);
    if (is_empty()) {
        _head = node;
        _tail = node;
    } else {
        node->_prev = _tail;
        _tail->_next = node;
        _tail = node;
    }
    _count++;
}

template <class T>
void DoubleList<T>::insert(DoubleNode<T> *node, const T& val) {
    if (node == nullptr || is_empty()) {
        throw std::logic_error("insert error: an empty object is passed");
    }

    DoubleNode<T>* new_node = new DoubleNode<T>(val);
    new_node->_next = node->_next;
    new_node->_prev = node;

    node->_next->_prev = new_node;
    node->_next = new_node;

    if (node == _tail) { _tail = new_node; }
    _count++;
}

template <class T>
void DoubleList<T>::insert(size_t pos, const T& val) {
    if (pos > _count) {
        throw std::out_of_range("insert error: position out of range");
    }
    if (pos == 0) {
        push_front(val);
        return;
    }
    if (pos == _count) {
        push_back(val);
        return;
    }

    DoubleNode<T>* cur;
    if (pos < _count / 2) {
        cur = _head;
        for (size_t i = 0; i < pos; ++i) cur = cur->_next;
    } else {
        cur = _tail;
        for (size_t i = 0; i < (_count - pos) - 1; ++i) cur = cur->_prev;
    }
    if (cur == nullptr) {
        throw std::logic_error("insert error: _head = nullptr");
    }

    DoubleNode<T>* prev = cur->_prev;
    insert(prev, val);
}

template <class T>
void DoubleList<T>::pop_front() {
    if (is_empty()) {
        throw std::logic_error("pop_front error: list is empty");
    }

    DoubleNode<T>* temp = _head;
    _head = _head->_next;
    if (_head != nullptr) {
        _head->_prev = nullptr;
    } else {
        _tail = nullptr;
    }
    delete temp;

    _count--;
}

template <class T>
void DoubleList<T>::pop_back() {
    if (is_empty()) {
        throw std::logic_error("pop error: list is empty");
    }

    DoubleNode<T>* temp = _tail;
    _tail = _tail->_prev;
    if (_tail != nullptr) {
        _tail->_next = nullptr;
    }
    else {
        _head = nullptr;
    }
    delete temp;

    _count--;
}

template <class T>
void DoubleList<T>::erase(size_t pos) {
    if (is_empty()) { throw std::logic_error("erase error: list is empty"); }
    if (pos >= _count) { throw std::out_of_range("erase error: position out of range"); }
    if (pos == 0) {
        pop_front(val);
        return;
    }
    if (pos == _count-1) {
        pop_back(val);
        return;
    }

    DoubleNode<T>* cur;
    if (pos < _count / 2) {
        cur = _head;
        for (size_t i = 0; i < pos; ++i) cur = cur->_next;
    } else {
        cur = _tail;
        for (size_t i = 0; i < (_count - pos) - 1; ++i) cur = cur->_prev;
    }
    erase(cur);
}

template <class T>
void DoubleList<T>::erase(DoubleNode<T>* node) {
    if (node == nullptr || is_empty()) {
        throw std::logic_error("erase error: invalid node or list is empty");
    }

    if (node == _head) {
        pop_front();
        return;
    }
    if (node == _tail) {
        pop_back();
        return;
    }

    DoubleNode<T>* prev = node->_prev;
    DoubleNode<T>* next = node->_next;

    if (prev) prev->_next = next;
    if (next) next->_prev = prev;

    delete node;
    _count--;
}

