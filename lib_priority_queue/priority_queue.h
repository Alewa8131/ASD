// Copyright 2025 Alewa8131

#include <stdexcept>

template <class T>
class PriorityQueue {
    T* _data;
    int* _priority;
    int _size, _count;
    int _head;
public:
    PriorityQueue();
    PriorityQueue(int size);
    PriorityQueue(const PriorityQueue& other);
    ~PriorityQueue();
    void push(T val, int prior);
    void pop();
    inline T head() const;
    inline bool is_empty() const noexcept;
    inline bool is_full() const noexcept;
};

template<class T>
PriorityQueue<T>::PriorityQueue() : _data(nullptr), _priority(nullptr), _size(0), _count(0), _head(0) {}

template<class T>
PriorityQueue<T>::PriorityQueue(int size) : _size(size), _count(0), _head(0) {
    if (size < 0) throw std::invalid_argument("Queue size cannot be negative.");
    _data = new T[size];
    _priority = new int[size];
}

template <class T>
PriorityQueue<T>::PriorityQueue(const PriorityQueue& other) :
    _size(other._size),
    _count(other._count),
    _head(other._head) {
    _data = new T[_size];
    _priority = new int[_size];
    for (int i = 0; i < other._size; i++) {
        _data[i] = other._data[i];
        _priority[i] = other._priority[i];
    }
}

template<class T>
PriorityQueue<T>::~PriorityQueue() {
    delete[] _data;
    delete[] _priority;
}

template<class T>
void PriorityQueue<T>::push(T val, int prior) {
    if (is_full()) {
        throw std::out_of_range("Queue is full, cannot push.");
    }

    if (_count == 0) {  // at the beginning
        _data[_head] = val;
        _priority[_head] = prior;
        _count++;
        return;
    }

    int insert_pos = _head;
    for (int i = 0; i < _count; i++) {
        int current_pos = (_head + i) % _size;
        if (prior > _priority[current_pos]) {
            insert_pos = current_pos;
            break;
        }

        if (i == _count - 1) {
            insert_pos = (_head + _count) % _size;
        }
    }

    if (insert_pos == (_head + _count) % _size) {  // at the end
        _data[insert_pos] = val;
        _priority[insert_pos] = prior;
    }
    else {
        for (int i = _count; i > 0; i--) {  // shifting
            int current = (_head + i) % _size;
            int prev = (_head + i - 1) % _size;

            if (prev == (insert_pos - 1 + _size) % _size) {
                break;
            }

            _data[current] = _data[prev];
            _priority[current] = _priority[prev];
        }

        _data[insert_pos] = val;
        _priority[insert_pos] = prior;
    }

    _count++;
}

template<class T>
void PriorityQueue<T>::pop() {
    if (is_empty()) {
        throw std::out_of_range("Queue is empty, cannot pop.");
    }
    _head = (_head + 1) % _size;
    _count--;
}

template<class T>
inline T PriorityQueue<T>::head() const {
    if (is_empty()) {
        throw std::out_of_range("Queue is empty, no head element.");
    }
    return _data[_head];
}

template<class T>
bool PriorityQueue<T>::is_empty() const noexcept {
    return _count == 0;
}

template<class T>
bool PriorityQueue<T>::is_full() const noexcept {
    return _count == _size;
}
