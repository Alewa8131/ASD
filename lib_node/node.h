// Copyright 2025 Alewa8131

template <class T>
struct Node {
public:
    T _value;
    Node<T> *_next;
public:
    Node();
    Node(T value, Node<T> *next = nullptr);
};

template <class T>
Node<T>::Node() : _value(T()), _next(nullptr) {}

template <class T>
Node<T>::Node(T value, Node<T> *next) : _value(value), _next(next) {}

