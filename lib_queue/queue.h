// Copyright 2025 Alewa8131

#include <stdexcept>

template <class T>
class Queue {
    T* _data;
    int _size, _count;
    int _head;
public:
    Queue();
    Queue(int size);
    Queue(const Queue& other);
    ~Queue();
    void push(T val);
    void pop();
    inline T head() const;
    inline bool is_empty() const noexcept;
    inline bool is_full() const noexcept;
};

template<class T>
Queue<T>::Queue() : _data(nullptr), _size(0), _count(0), _head(0) {}

template<class T>
Queue<T>::Queue(int size) : _size(size), _count(0), _head(0) {
    if (size < 0) throw std::invalid_argument("Queue size cannot be negative.");
    _data = new T[size];
}

template <class T>
Queue<T>::Queue(const Queue& other) :
    _size(other._size),
    _count(other._count),
    _head(other._head) {
    _data = new T[_size];
    for (int i = 0; i < other._size; i++) {
        _data[i] = other._data[i];
    }
}

template<class T>
Queue<T>::~Queue() {
    delete[] _data;
}

template<class T>
void Queue<T>::push(T val) {
    if (is_full()) {
        throw std::out_of_range("Queue is full, cannot push.");
    }
    _data[(_head + _count) % _size] = val;

    _count++;
}

template<class T>
void Queue<T>::pop() {
    if (is_empty()) {
        throw std::out_of_range("Queue is empty, cannot pop.");
    }
    _head = (_head + 1) % _size;
    _count--;
}

template<class T>
inline T Queue<T>::head() const {
    if (is_empty()) {
        throw std::out_of_range("Queue is empty, no head element.");
    }
    return _data[_head];
}

template<class T>
bool Queue<T>::is_empty() const noexcept {
    return _count == 0;
}

template<class T>
bool Queue<T>::is_full() const noexcept {
    return _count == _size;
}
