// Copyright 2026 Alewa8131

#ifndef LIB_BSTREE_BSTREE_H_
#define LIB_BSTREE_BSTREE_H_
#pragma once

#include <iostream>
#include <utility>
#include "../lib_node/node.h"

template<class TKey, class TValue>
class BSTree {
private:
    using Row = std::pair<TKey, TValue>;
    using Node = DoubleNode<Row>;
    Node* _root;

public:
    BSTree();
    ~BSTree();
    TValue* find(const TKey& key) const noexcept;
    Node* insert(const TKey& key, const TValue& val);
    Node* erase(const TKey& key);
    bool is_empty() const noexcept;
    void print_DLCR(std::ostream& os = std::cout) const noexcept;
    void print_DLCR_rec(Node* node, std::ostream& os) const noexcept;

    void clear() noexcept;
    void clear_rec(Node* node) noexcept;
private:
    Node* find_parent(const TKey& key) const noexcept;
    Node* find_max_left(Node* node) const noexcept;
};

template<class TKey, class TValue>
BSTree<TKey, TValue>::
BSTree() : _root(nullptr) {}

template<class TKey, class TValue>
BSTree<TKey, TValue>::~BSTree() {
    clear();
}

template<class TKey, class TValue>
typename BSTree<TKey, TValue>::Node* 
BSTree<TKey, TValue>::
find_parent(const TKey& key) const noexcept {
    if (is_empty()) return nullptr;
    if (_root->_value.first == key)
        return _root;

    Node* cur = _root;

    while (cur) {
        if (key < cur->_value.first) {
            if (!cur->_prev || cur->_prev->_value.first == key) return cur;
            cur = cur->_prev;
        } else if (key > cur->_value.first) {
            if (!cur->_next || cur->_next->_value.first == key) return cur;
            cur = cur->_next;
        }
    }

    return nullptr;
}
 
template<class TKey, class TValue>
TValue* BSTree<TKey, TValue>::
find(const TKey& key) const noexcept {
    if (_root && _root->_value.first == key)
        return &_root->_value.second;

    Node* parent = find_parent(key);
    if (!parent) return nullptr;

    if (parent->_prev && parent->_prev->_value.first == key)
        return &parent->_prev->_value.second;
    if (parent->_next && parent->_next->_value.first == key)
        return &parent->_next->_value.second;
    return nullptr;
}

template<class TKey, class TValue>
typename BSTree<TKey, TValue>::Node*
BSTree<TKey, TValue>::
insert(const TKey& key, const TValue& val) {
    Node* parent = find_parent(key);
    Node* newNode = new Node(Row(key, val));

    if (!parent) {
        _root = newNode;
        return newNode;
    }
    if (key > parent->_value.first && !parent->_next) {
        parent->_next = newNode;
        return newNode;
    }
    if (key < parent->_value.first && !parent->_prev) {
        parent->_prev = newNode;
        return newNode;
    }

    delete newNode;
    throw std::logic_error("Key already exists");
}

template<class TKey, class TValue>
typename BSTree<TKey, TValue>::Node*
BSTree<TKey, TValue>::
erase(const TKey& key) {
    Node* parent = find_parent(key);

    if (!parent)
        throw std::out_of_range("Key not found");

    Node* node = nullptr;

    if (parent == _root && _root->_value.first == key)
        node = _root;
    else if (parent->_prev && parent->_prev->_value.first == key)
        node = parent->_prev;
    else if (parent->_next && parent->_next->_value.first == key)
        node = parent->_next;
    else
        throw std::out_of_range("Key not found");


    if (!node->_prev && !node->_next) {

        if (node == _root)
            _root = nullptr;
        else if (parent->_prev == node)
            parent->_prev = nullptr;
        else
            parent->_next = nullptr;
        delete node;
        return parent;
    }

    if (!node->_prev || !node->_next) {

        Node* child = node->_prev ? node->_prev : node->_next;

        if (node == _root)
            _root = child;
        else if (parent->_prev == node)
            parent->_prev = child;
        else
            parent->_next = child;
        delete node;
        return parent;
    }

    Node* replace = find_max_left(node);

    Row tmp = replace->_value;
    erase(replace->_value.first);
    node->_value = tmp;
    return node;
}

template<class TKey, class TValue>
bool BSTree<TKey, TValue>::
is_empty() const noexcept {
    return _root == nullptr;
}

template<class TKey, class TValue>
typename BSTree<TKey, TValue>::Node*
BSTree<TKey, TValue>::
find_max_left(Node* node) const noexcept {
    node = node->_prev;
    while (node->_next)
        node = node->_next;
    return node;
}

template<class TKey, class TValue>
void BSTree<TKey, TValue>::
print_DLCR(std::ostream& os) const noexcept {
    print_DLCR_rec(_root, os);
}

template<class TKey, class TValue>
void BSTree<TKey, TValue>::
print_DLCR_rec(Node* node, std::ostream& os) const noexcept {
    if (!node)
        return;
    print_DLCR_rec(node->_prev, os);
    os << node->_value.second << " ";
    print_DLCR_rec(node->_next, os);
}

template<class TKey, class TValue>
void BSTree<TKey, TValue>::
clear() noexcept {
    if (!_root)
        return;
    clear_rec(_root);
    _root = nullptr;
}

template<class TKey, class TValue>
void BSTree<TKey, TValue>::
clear_rec(Node* node) noexcept {
    if (!node)
        return;
    clear_rec(node->_prev);
    clear_rec(node->_next);
    delete node;
}

#endif  // LIB_BSTREE_BSTREE_H_
