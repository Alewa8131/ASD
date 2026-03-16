// Copyright 2026 Alewa8131

#ifndef LIB_TREE_TREE_H_
#define LIB_TREE_TREE_H_
#pragma once

#include <iostream>
#include "../lib_node/node.h"
#include "../lib_listqueue/listqueue.h"

template<class TKey, class TValue>
class Tree {
    using Row = std::pair<TKey, TValue>;
    using Node = DoubleNode<Row>;

    Node* _root;
public:
    Tree();
    ~Tree();
    void insert(const TKey&, const TValue&);
    TValue& find(const TKey&) const;
    void erase(const TKey&);
    bool is_empty() const noexcept;

    void print_W() const noexcept;
    void print_DLCR() const noexcept;
    void print_DLRC() const noexcept;
    void print_DCLR() const noexcept;
    void print_DLCR_rec(Node*) const noexcept;
    void print_DLRC_rec(Node*) const noexcept;
    void print_DCLR_rec(Node*) const noexcept;

    void clear() noexcept;
    void clear_rec(Node*) noexcept;
};

template<class TKey, class TValue>
Tree<TKey, TValue>::Tree() : _root(nullptr) {}

template<class TKey, class TValue>
Tree<TKey, TValue>::~Tree() {
    clear();
}


template<class TKey, class TValue>
void Tree<TKey, TValue>::insert(const TKey& key, const TValue& val) {
    try {
        find(key);
        throw std::logic_error("Key already exists");
    } catch (const std::out_of_range&) {}

    Node* node = new Node({ key, val });

    if (is_empty()) {
        _root = node;
        return;
    }

    Node* cur = nullptr;
    ListQueue<Node*> q;
    q.push(_root);
    while (!q.is_empty()) {
        cur = q.head();
        q.pop();
        if (!cur->_prev) {
            cur->_prev = node;
            return;
        } 
        if (!cur->_next) {
            cur->_next = node;
            return;
        }
        q.push(cur->_prev);
        q.push(cur->_next);
    }
}

template<class TKey, class TValue>
TValue& Tree<TKey, TValue>::find(const TKey& key) const {
    if (is_empty()) 
        throw std::out_of_range("Key not found");

    ListQueue<Node*> q;
    q.push(_root);

    while (!q.is_empty()) {
        Node* cur = q.head();
        q.pop();

        if (cur->_value.first == key) {
            return cur->_value.second;
        }
        if (cur->_prev) {
            q.push(cur->_prev);
        }
        if (cur->_next) {
            q.push(cur->_next);
        }
    }
    throw std::out_of_range("Key not found");
}

template<class TKey, class TValue>
void Tree<TKey, TValue>::erase(const TKey& key) {
    if (is_empty())
        throw std::out_of_range("Key not found");

    Node* target = nullptr;
    Node* last = nullptr;
    Node* parent_last = nullptr;

    ListQueue<Node*> q;
    q.push(_root);

    while (!q.is_empty()) {
        Node* cur = q.head();
        q.pop();

        if (cur->_value.first == key)
            target = cur;
        if (cur->_prev) {
            parent_last = cur;
            q.push(cur->_prev);
        }
        if (cur->_next) {
            parent_last = cur;
            q.push(cur->_next);
        }

        last = cur;
    }

    if (!target)
        throw std::out_of_range("Key not found");

    target->_value = last->_value;

    if (parent_last) {
        if (parent_last->_next == last)
            parent_last->_next = nullptr;
        else
            parent_last->_prev = nullptr;
    }
    else {
        _root = nullptr;
    }

    delete last;
}

template<class TKey, class TValue>
bool Tree<TKey, TValue>::is_empty() const noexcept {
    return _root == nullptr;
}


template<class TKey, class TValue>
void Tree<TKey, TValue>::print_W() const noexcept {
    if (is_empty())
        return;
    ListQueue<Node*> q;
    q.push(_root);
    Node* cur = nullptr;
    while (!q.is_empty()) {
        cur = q.head();
        std::cout << cur->_value.second << " ";
        q.pop();
        if (cur->_prev)
            q.push(cur->_prev);
        if (cur->_next)
            q.push(cur->_next);
    }
}

template<class TKey, class TValue>
void Tree<TKey, TValue>::print_DLCR() const noexcept {
    print_DLCR_rec(_root);
}

template<class TKey, class TValue>
void Tree<TKey, TValue>::print_DLRC() const noexcept {
    print_DLRC_rec(_root);
}

template<class TKey, class TValue>
void Tree<TKey, TValue>::print_DCLR() const noexcept {
    print_DCLR_rec(_root);
}

template<class TKey, class TValue>
void Tree<TKey, TValue>::print_DLCR_rec(Node* node) const noexcept {
    if (!node)
        return;
    print_DLCR_rec(node->_prev);
    std::cout << node->_value.second << " ";
    print_DLCR_rec(node->_next);
}

template<class TKey, class TValue>
void Tree<TKey, TValue>::print_DLRC_rec(Node* node) const noexcept {
    if (!node)
        return;
    print_DLRC_rec(node->_prev);
    print_DLRC_rec(node->_next);
    std::cout << node->_value.second << " ";
}

template<class TKey, class TValue>
void Tree<TKey, TValue>::print_DCLR_rec(Node* node) const noexcept {
    if (!node)
        return;
    std::cout << node->_value.second << " ";
    print_DCLR_rec(node->_prev);
    print_DCLR_rec(node->_next);
}


template<class TKey, class TValue>
void Tree<TKey, TValue>::clear() noexcept {
    if (!_root)
        return;
    clear_rec(_root);
    _root = nullptr;
}

template<class TKey, class TValue>
void Tree<TKey, TValue>::clear_rec(Node* node) noexcept {
    if (!node)
        return;
    clear_rec(node->_prev);
    clear_rec(node->_next);
    delete node;
}

#endif  // LIB_TREE_TREE_H_
