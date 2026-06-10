// Copyright 2026 Alewa8131

#ifndef LIB_AVLTREE_AVLTREE_H_
#define LIB_AVLTREE_AVLTREE_H_
#pragma once

#include <iostream>
#include <utility>
#include "../lib_node/node.h"

template<class TKey, class TValue>
class AVLTree {
    using Row = std::pair<TKey, TValue>;
    using Node = AVLNode<Row>;
    Node* _root;

public:
    AVLTree();
    ~AVLTree();
    Node* get_root() const noexcept;
    TValue* find(const TKey& key) const noexcept;
    void insert(const TKey& key, const TValue& val);
    void erase(const TKey& key);
    bool is_empty() const noexcept;

    void print_DLCR(std::ostream& os = std::cout) const noexcept;
    void print_DLCR_rec(Node* node, std::ostream& os) const noexcept;

    void clear() noexcept;
    void clear_rec(Node* node) noexcept;

private:
    Node* find_parent(const TKey& key) const noexcept;
    Node* find_max_left(Node* node) const noexcept;
    void left_rotate(Node* node);
    void right_rotate(Node* node);
    void RR(Node* node);
    void LL(Node* node);
    void RL(Node* node);
    void LR(Node* node);

    void recovery_balance(Node* node);
    void recalc_height(Node* node);
    int calc_balance(Node* node);
};

template<class TKey, class TValue>
AVLTree<TKey, TValue>::
AVLTree() : _root(nullptr) {}

template<class TKey, class TValue>
AVLTree<TKey, TValue>::
~AVLTree() {
    clear();
}

template<class TKey, class TValue>
typename AVLTree<TKey, TValue>::Node*
AVLTree<TKey, TValue>::
get_root() const noexcept {
    return _root;
}

template<class TKey, class TValue>
typename AVLTree<TKey, TValue>::Node*
AVLTree<TKey, TValue>::
find_parent(const TKey& key) const noexcept {
    if (is_empty() || _root->_data.first == key)
        return nullptr;

    Node* cur = _root;
    Node* parent = nullptr;

    while (cur) {
        if (cur->_data.first == key) 
            return parent;

        parent = cur;

        if (key < cur->_data.first) {
            cur = cur->_left;
        } else {
            cur = cur->_right;
        }
    }

    return parent;
}

template<class TKey, class TValue>
TValue* AVLTree<TKey, TValue>::
find(const TKey& key) const noexcept {
    if (_root && _root->_data.first == key)
        return &_root->_data.second;

    Node* parent = find_parent(key);
    if (!parent) return nullptr;

    if (parent->_left && parent->_left->_data.first == key)
        return &parent->_left->_data.second;
    if (parent->_right && parent->_right->_data.first == key)
        return &parent->_right->_data.second;
    return nullptr;
}

template<class TKey, class TValue>
void AVLTree<TKey, TValue>::
insert(const TKey& key, const TValue& val) {
    Node* parent = find_parent(key);
    Node* newNode = new Node(Row(key, val));
    newNode->_height = 1;

    if (!parent) {
        if (_root) {
            delete newNode;
            throw std::logic_error("Key already exists");
        }
        _root = newNode;
        return;
    }

    if (key > parent->_data.first && !parent->_right) {
        newNode->_parent = parent;
        parent->_right = newNode;
    }
    else if (key < parent->_data.first && !parent->_left) {
        newNode->_parent = parent;
        parent->_left = newNode;
    }
    else {
        delete newNode;
        throw std::logic_error("Key already exists");
    }

    Node* cur = parent;
    while (cur) {
        recalc_height(cur);
        int balance = calc_balance(cur);

        if (abs(balance) > 1) {
            recovery_balance(cur);
            return;
        }

        cur = cur->_parent;
    }
}

template<class TKey, class TValue>
void AVLTree<TKey, TValue>::
erase(const TKey& key) {
    if (is_empty()) throw std::out_of_range("Key not found");

    Node* parent = find_parent(key);
    Node* node = nullptr;

    if (!parent && _root && _root->_data.first == key)
        node = _root;
    else if (parent->_left && parent->_left->_data.first == key)
        node = parent->_left;
    else if (parent->_right && parent->_right->_data.first == key)
        node = parent->_right;
    else
        throw std::out_of_range("Key not found");

    Node* balance_start_node = nullptr;

    if (!node->_left && !node->_right) {
        if (node == _root)
            _root = nullptr;
        else if (parent->_left == node)
            parent->_left = nullptr;
        else
            parent->_right = nullptr;

        balance_start_node = parent;
        delete node;
    }
    else if (!node->_left || !node->_right) {
        Node* child = node->_left ? node->_left : node->_right;

        if (node == _root) {
            _root = child;
            child->_parent = nullptr;
        }
        else if (parent->_left == node) {
            parent->_left = child;
            child->_parent = parent;
        }
        else {
            parent->_right = child;
            child->_parent = parent;
        }

        balance_start_node = parent;
        delete node;
    } 
    else {
        Node* replace = find_max_left(node);
        Row tmp = replace->_data;

        erase(replace->_data.first);

        node->_data = tmp;

        balance_start_node = node;
    }

    Node* cur = balance_start_node;
    while (cur) {
        recalc_height(cur);
        int balance = calc_balance(cur);

        if (abs(balance) > 1) {
            Node* next_cur = cur->_parent;
            recovery_balance(cur);
            cur = next_cur;
        } else {
            cur = cur->_parent;
        }
    }
}

template<class TKey, class TValue>
bool AVLTree<TKey, TValue>::
is_empty() const noexcept {
    return _root == nullptr;
}

template<class TKey, class TValue>
typename AVLTree<TKey, TValue>::Node*
AVLTree<TKey, TValue>::
find_max_left(Node* node) const noexcept {
    if (!node || !node->_left) return nullptr;
    node = node->_left;
    while (node->_right)
        node = node->_right;
    return node;
}

//        PG                      PG
//        |                       |
//        G                       P
//       / \     left_rotate     / \
//      T1  P    ----------->   G  T3
//         / \                 / \
//        T2  T3              T1 T2
template<class TKey, class TValue>
void AVLTree<TKey, TValue>::
left_rotate(Node* node) {
    if (!node || !node->_right) return;
    Node* G = node;
    Node* P = G->_right;
    Node* PG = G->_parent;

    G->_right = P->_left;
    if (P->_left) {
        P->_left->_parent = G;
    }

    P->_left = G;
    G->_parent = P;
    P->_parent = PG;

    if (!PG) {
        _root = P;
    } else {
        if (PG->_left == G) PG->_left = P;
        else PG->_right = P;
    }

    recalc_height(G);
    recalc_height(P);
}

//        PG                     PG
//        |                      |
//        G                      P
//       / \     right_rotate   / \
//      P  T3    -----------> T1   G
//     / \                        / \
//   T1  T2                     T2  T3
template<class TKey, class TValue>
void AVLTree<TKey, TValue>::
right_rotate(Node* node) {
    if (!node || !node->_left) return;
    Node* G = node;
    Node* P = G->_left;
    Node* PG = G->_parent;

    G->_left = P->_right;
    if (P->_right) {
        P->_right->_parent = G;
    }

    P->_right = G;
    G->_parent = P;
    P->_parent = PG;

    if (!PG) {
        _root = P;
    } else {
        if (PG->_right == G) PG->_right = P;
        else PG->_left = P;
    }

    recalc_height(G);
    recalc_height(P);
}

//        G                       P
//       / \      RR (Left)      / \
//      T1  P    ----------->   G  T3
//         / \                 / \
//       T2  T3              T1  T2
template<class TKey, class TValue>
void AVLTree<TKey, TValue>::
RR(Node* node) {
    Node* G = node;
    left_rotate(G);
}

//        G                      P
//       / \     LL (Right)     / \
//      P  T3    -----------> T1   G
//     / \                        / \
//   T1  T2                     T2  T3
template<class TKey, class TValue>
void AVLTree<TKey, TValue>::
LL(Node* node) {
    Node* G = node;
    right_rotate(G);
}

//       G                G                 C
//      / \    Right(P)  / \    Left(G)   /   \
//     T1  P   -------> T1  C   -------> G     P
//        / \              / \          / \   / \
//       C  T4            T2  P        T1 T2 T3 T4
//      / \                  / \       
//     T2 T3                T3 T4
template<class TKey, class TValue>
void AVLTree<TKey, TValue>::
RL(Node* node) {
    Node* G = node, *P = node->_right;
    right_rotate(P);
    left_rotate(G);
}

//        G                G                  C
//       / \    Left(P)   / \    Right(G)   /   \
//      P  T4   ------>  C  T4   ------->  P     G
//     / \              / \               / \   / \
//    T1  C            P   T3            T1 T2 T3 T4
//       / \          / \                 
//      T2 T3        T1 T2
template<class TKey, class TValue>
void AVLTree<TKey, TValue>::
LR(Node* node) {
    Node* G = node, *P = node->_left;
    left_rotate(P);
    right_rotate(G);
}

template<class TKey, class TValue>
void AVLTree<TKey, TValue>::
recovery_balance(Node* node) {
    int balance = calc_balance(node);

    if (balance == -2) {
        if (calc_balance(node->_right) <= 0) {
            RR(node);
        } else {
            RL(node);
        }
    } else if (balance == 2) {
        if (calc_balance(node->_left) >= 0) {
            LL(node);
        } else {
            LR(node);
        }
    }
}

template<class TKey, class TValue>
void AVLTree<TKey, TValue>::
recalc_height(Node* node) {
    if (!node) return;

    size_t h_left = (node->_left) ? node->_left->_height : 0;
    size_t h_right = (node->_right) ? node->_right->_height : 0;

    node->_height = 1 + std::max(h_left, h_right);
}

template<class TKey, class TValue>
int AVLTree<TKey, TValue>::
calc_balance(Node* node) {
    if (!node) return 0;

    int h_left = (node->_left) ? static_cast<int>(node->_left->_height) : 0;
    int h_right = (node->_right) ? static_cast<int>(node->_right->_height) : 0;

    return h_left - h_right;
}

template<class TKey, class TValue>
void AVLTree<TKey, TValue>::
print_DLCR(std::ostream& os) const noexcept {
    print_DLCR_rec(_root, os);
}

template<class TKey, class TValue>
void AVLTree<TKey, TValue>::
print_DLCR_rec(Node* node, std::ostream& os) const noexcept {
    if (!node)
        return;
    print_DLCR_rec(node->_left, os);
    os << node->_data.second << " ";
    print_DLCR_rec(node->_right, os);
}

template<class TKey, class TValue>
void AVLTree<TKey, TValue>::
clear() noexcept {
    if (!_root)
        return;
    clear_rec(_root);
    _root = nullptr;
}

template<class TKey, class TValue>
void AVLTree<TKey, TValue>::
clear_rec(Node* node) noexcept {
    if (!node)
        return;
    clear_rec(node->_left);
    clear_rec(node->_right);
    delete node;
}

#endif  // LIB_AVLTREE_AVLTREE_H_
