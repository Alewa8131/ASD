// Copyright 2026 Alewa8131

#ifndef LIB_TABLE_UNSORTED_TABLE_ON_LIST_H_
#define LIB_TABLE_UNSORTED_TABLE_ON_LIST_H_
#pragma once

#include <stdexcept>
#include "../lib_list/list.h"
#include "table.h"

template<class TKey, class TValue>
class UnsortedTableOnList : public Table<TKey, TValue> {
    List<std::pair<TKey, TValue>> _rows;

public:
    UnsortedTableOnList() = default;
    ~UnsortedTableOnList() override = default;

    void insert(const TKey& key, const TValue& value) override;
    void erase(const TKey& key) override;

    TValue& find(const TKey& key) override;
    const TValue& find(const TKey& key) const override;

protected:
    const std::pair<TKey, TValue>& get_row(size_t index) const override;
    Node<std::pair<TKey, TValue>>* find_node(const TKey& key) const;
};

template<class TKey, class TValue>
void UnsortedTableOnList<TKey, TValue>::
insert(const TKey& key, const TValue& value) {
    try {
        find_node(key);
        throw std::logic_error("Key already exists");
    } catch (const std::out_of_range&) {
        _rows.push_back({ key, value });
        this->_size++;
    }
}

template<class TKey, class TValue>
void UnsortedTableOnList<TKey, TValue>::
erase(const TKey& key) {
    auto node = find_node(key);

    _rows.erase(node);
    this->_size--;
}

template<class TKey, class TValue>
TValue& UnsortedTableOnList<TKey, TValue>::
find(const TKey& key) {
    return find_node(key)->_value.second;
}

template<class TKey, class TValue>
const TValue& UnsortedTableOnList<TKey, TValue>::
find(const TKey& key) const {
    return find_node(key)->_value.second;
}


template<class TKey, class TValue>
const std::pair<TKey, TValue>& 
UnsortedTableOnList<TKey, TValue>::
get_row(size_t index) const {
    auto node = _rows.head();

    for (size_t i = 0; i < index; ++i)
        node = node->_next;

    return node->_value;
}

template<class TKey, class TValue>
Node<std::pair<TKey, TValue>>*
UnsortedTableOnList<TKey, TValue>::
find_node(const TKey& key) const {
    auto node = _rows.head();

    while (node) {
        if (node->_value.first == key)
            return node;

        node = node->_next;
    }

    throw std::out_of_range("Key not found");
}

#endif  // LIB_TABLE_UNSORTED_TABLE_ON_LIST_H_
