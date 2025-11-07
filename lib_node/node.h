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


template <class T>
struct DoubleNode {
public:
    DoubleNode<T>* _prev;
    T _value;
    DoubleNode<T>* _next;
public:
    DoubleNode();
    DoubleNode(T value, DoubleNode<T>* prev = nullptr, DoubleNode<T>* next = nullptr);
};

template <class T>
DoubleNode<T>::DoubleNode() : _prev(nullptr), _value(T()), _next(nullptr) {}

template <class T>
DoubleNode<T>::DoubleNode(T value, DoubleNode<T>* prev, DoubleNode<T>* next)
    : _value(value), _prev(prev), _next(next) {};
