// Copyright 2026 Alewa8131

#ifndef LIB_SKIPLIST_SKIPLIST_H_
#define LIB_SKIPLIST_SKIPLIST_H_
#pragma once
#include <stdexcept>
#include "../lib_node/node.h"
#include "../lib_list/list.h"
#include "../lib_tvector/tvector.h"

template<typename TKey, typename TValue>
class SkipList {
    size_t MAX_LVL;
    size_t _lvl;
    List<SkipNode<TKey, TValue>*> _heads;

public:
    SkipList(size_t max_lvl = 6);
    ~SkipList();
    void insert(const TKey key, const TValue value);
    void print() const noexcept;
protected:
    size_t flip_coin() const noexcept;
    SkipNode<TKey, TValue>* find_nearest(const TKey& key) const noexcept;
};

template<typename TKey, typename TValue>
SkipList<TKey, TValue>::
SkipList(size_t max_lvl)
    : MAX_LVL(max_lvl), _lvl(1), _heads() {
    std::srand((unsigned)std::time(nullptr));
}

template<typename TKey, typename TValue>
SkipList<TKey, TValue>::~SkipList() {
    auto wrapper = _heads.head();

    while (wrapper) {
        delete wrapper->_value;
        wrapper = wrapper->_next;
    }
}

template<typename TKey, typename TValue>
void SkipList<TKey, TValue>::
insert(const TKey key, const TValue value) {
    size_t nodeLevel = flip_coin();

    if (nodeLevel > _lvl)
        _lvl = nodeLevel;

    SkipNode<TKey, TValue>* newNode =
        new SkipNode<TKey, TValue>(nodeLevel, key, value);

    if (_heads.is_empty()) {
        _heads.push_back(newNode);
        return;
    }

    SkipNode<TKey, TValue>* nearest = find_nearest(key);

    Node<SkipNode<TKey, TValue>*>* wrapper = _heads.head();
    while (wrapper && wrapper->_value != nearest)
        wrapper = wrapper->_next;

    if (!wrapper)
        _heads.push_front(newNode);
    else
        _heads.insert(wrapper, newNode);

    for (size_t lvl = 0; lvl < nodeLevel; ++lvl) {

        if (nearest && lvl < nearest->_level) {
            newNode->_next[lvl] = nearest->_next[lvl];
            nearest->_next[lvl] = newNode;
        } else {
            newNode->_next[lvl] = nullptr;
        }
    }
}

template<typename TKey, typename TValue>
void SkipList<TKey, TValue>::
print() const noexcept {
    for (int lvl = static_cast<int>(_lvl) - 1; lvl >= 0; --lvl) {
        std::cout << "[LVL " << lvl + 1 << "]: ";

        for (auto it = _heads.begin(); it != _heads.end(); ++it) {
            SkipNode<TKey, TValue>* node = *it;

            if (node->_level > lvl)
                std::cout << node->_data.first << " ";
            else
                std::cout << "  ";
        }

        std::cout << "\n";
    }
}


template<typename TKey, typename TValue>
size_t SkipList<TKey, TValue>::
flip_coin() const noexcept {
    size_t lvl = 1;

    while ((std::rand() % 2) && lvl < MAX_LVL)
        ++lvl;

    return lvl;
}

template<typename TKey, typename TValue>
SkipNode<TKey, TValue>* SkipList<TKey, TValue>::
find_nearest(const TKey& key) const noexcept {
    if (_heads.is_empty())
        return nullptr;

    Node<SkipNode<TKey, TValue>*>* wrapper = _heads.head();
    SkipNode<TKey, TValue>* current = wrapper->_value;

    if (key < current->_data.first)
        return nullptr;

    for (int lvl = static_cast<int>(_lvl) - 1; lvl >= 0; --lvl) {
        while (current &&
            lvl < current->_level &&
            current->_next[lvl] &&
            current->_next[lvl]->_data.first < key) {

            current = current->_next[lvl];
        }
    }

    return current;
}
#endif  // LIB_SKIPLIST_SKIPLIST_H_
