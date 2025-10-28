// Copyright 2025 Alewa8131

#include <stdexcept>
#include "../lib_node/node.h"

template <class T>
class List {
    Node<T> *_head; 
    Node<T> *_tail;
    size_t _count;
public:
    List();
    List(const List<T>& other);
    ~List();

    size_t size() const noexcept;
    Node<T>* head() const noexcept;

    inline bool is_empty() const noexcept;

    void push_front(const T& val) noexcept;
    void push_back(const T& val) noexcept;
    void insert(Node<T>* node, const T& val);
    void insert(size_t pos, const T& val);


    void pop_front();
    void pop_back();
    void erase(size_t pos);
    void erase(Node<T>* node);


    class Iterator {
        Node<T>* _current;
    public:
        Iterator();
        Iterator(Node<T>* node);

        Iterator& operator++();
        Iterator operator++(int);
        T& operator*() const;
        bool operator==(const Iterator& other) const;
        bool operator!=(const Iterator& other) const;
    };

    Iterator begin();
    Iterator end();
};


template <class T>
List<T>::List() : _head(nullptr), _tail(nullptr), _count(0) {}

template <class T>
List<T>::List(const List<T>& other) : _head(nullptr), _tail(nullptr), _count(0) {
    Node<T>* current = other._head;
    while (current != nullptr) {
        push_back(current->_value);
        current = current->_next;
    }
}

template <class T>
List<T>::~List() {
    Node<T>* current = _head;
    Node<T>* next_node = nullptr;
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
size_t List<T>::size() const noexcept { return _count; }

template <class T>
Node<T>* List<T>::head() const noexcept { return _head; }

template <class T>
inline bool List<T>::is_empty() const noexcept { return _head == nullptr; }

template <class T>
void List<T>::push_front(const T& val) noexcept {
    Node<T>* node = new Node<T>(val);

    if (is_empty()) { 
        _head = node;
        _tail = node;
    } else { 
        node->_next = _head;
        _head = node;
    }
    _count++;
}

template <class T>
void List<T>::push_back(const T& val) noexcept {
    Node<T>* node = new Node<T>(val);
    if (is_empty()) {
        _head = node;
        _tail = node;
    } else {
        _tail->_next = node;
        _tail = node;
    }
    _count++;
}

template <class T>
void List<T>::insert(Node<T> *node, const T& val) {
    if (node == nullptr || is_empty()) {
        throw std::logic_error("insert error: an empty object is passed");
    }

    Node<T>* new_node = new Node<T>(val);
    new_node->_next = node->_next;
    node->_next = new_node;

    if (node == _tail) { _tail = new_node; }
    _count++;
}

template <class T>
void List<T>::insert(size_t pos, const T& val) {
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

    Node<T>* cur = _head;
    size_t cur_pos = 0;
    while (cur != nullptr) {
        if (cur_pos == pos - 1) break;
        cur_pos++;
        cur = cur->_next;
    }
    if (cur == nullptr) {
        throw std::logic_error("insert error: _head = nullptr");
    }
    insert(cur, val);
}

template <class T>
void List<T>::pop_front() {
    if (is_empty()) {
        throw std::logic_error("pop_front error: list is empty");
    }

    Node<T>* temp = _head;
    _head = _head->_next;
    delete temp;

    if (_head == nullptr) { _tail = nullptr; }
    _count--;
}

template <class T>
void List<T>::pop_back() {
    if (is_empty()) {
        throw std::logic_error("pop error: list is empty");
    }
    if (_head == _tail) { 
        delete _head;
        _head = nullptr;
        _tail = nullptr;
        _count = 0;
        return;
    }

    Node<T>* cur = _head;
    while (cur->_next != _tail) { cur = cur->_next; }

    delete _tail;
    _tail = cur;
    cur->_next = nullptr;
    _count--;
}

template <class T>
void List<T>::erase(size_t pos) {
    if (is_empty()) { throw std::logic_error("erase error: list is empty"); }
    if (pos >= _count) { throw std::out_of_range("erase error: position out of range"); }
    if (pos == 0) {
        pop_front();
        return;
    }

    Node<T>* prev = _head;
    for (size_t i = 0; i < pos - 1; ++i) {
        prev = prev->_next;
    }

    Node<T>* to_delete = prev->_next;
    prev->_next = to_delete->_next;

    if (to_delete == _tail) {
        _tail = prev;
    }

    delete to_delete;
    _count--;
}

template <class T>
void List<T>::erase(Node<T>* node) {
    if (node == nullptr || is_empty()) {
        throw std::logic_error("erase error: invalid node or list is empty");
    }

    if (node == _head) {
        pop_front();
        return;
    }

    Node<T>* prev = _head;
    while (prev != nullptr && prev->_next != node) {
        prev = prev->_next;
    }

    if (prev == nullptr) {
        throw std::logic_error("erase error: node not found in list");
    }

    prev->_next = node->_next;

    if (node == _tail) {
        _tail = prev;
    }

    delete node;
    _count--;
}



template <class T>
List<T>::Iterator::Iterator() : _current(nullptr) {}

template <class T>
List<T>::Iterator::Iterator(Node<T>* node) : _current(node) {}

template <class T>
typename List<T>::Iterator List<T>::begin() {
    return Iterator(_head);
}

template <class T>
typename List<T>::Iterator List<T>::end() {
    return Iterator(nullptr);
}

template <class T>
typename List<T>::Iterator& List<T>::Iterator::operator++() {
    if (_current) {
        _current = _current->_next;
    }
    return *this;
}

template <class T>
typename List<T>::Iterator List<T>::Iterator::operator++(int) {
    typename List<T>::Iterator temp = *this;
    ++(*this);
    return temp;
}

template <class T>
T& List<T>::Iterator::operator*() const {
    if (!_current) {
        throw std::out_of_range("Dereferencing end() iterator");
    }
    return _current->_value;
}

template <class T>
bool List<T>::Iterator::operator==(const Iterator& other) const {
    return _current == other._current;
}

template <class T>
bool List<T>::Iterator::operator!=(const Iterator& other) const {
    return _current != other._current;
}
