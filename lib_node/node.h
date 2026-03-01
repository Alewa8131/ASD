// Copyright 2025 Alewa8131

#ifndef LIB_NODE_NODE_H_
#define LIB_NODE_NODE_H_
#pragma once
#include <utility>

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


template<typename TKey, typename TValue>
struct SkipNode {
    std::pair<TKey, TValue> _data;
    SkipNode** _next;
    int _level;

    SkipNode();
    SkipNode(int lvl);
    SkipNode(int lvl, const TKey& key, const TValue& value);
    ~SkipNode();
};

template<typename TKey, typename TValue>
SkipNode<TKey, TValue>::
SkipNode()
    : _level(1), _data(TKey(), TValue()) {
    _next = new SkipNode * [_level];
    for (int i = 0; i < _level; ++i)
        _next[i] = nullptr;
}

template<typename TKey, typename TValue>
SkipNode<TKey, TValue>::
SkipNode(int lvl)
    : _data(TKey(), TValue()) {
    _level = (lvl < 1) ? 1 : lvl;

    _next = new SkipNode*[_level];
    for (int i = 0; i < _level; ++i)
        _next[i] = nullptr;
}

template<typename TKey, typename TValue>
SkipNode<TKey, TValue>::
SkipNode(int lvl, const TKey& key, const TValue& value)
    : _data(key, value) {
    _level = (lvl < 1) ? 1 : lvl;

    _next = new SkipNode * [_level];
    for (int i = 0; i < _level; ++i)
        _next[i] = nullptr;
}

template<typename TKey, typename TValue>
SkipNode<TKey, TValue>::
~SkipNode() {
    delete[] _next;
}

#endif  // LIB_NODE_NODE_H_
