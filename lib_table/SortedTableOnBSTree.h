// Copyright 2026 Alewa8131

#ifndef LIB_TABLE_SORTED_TABLE_ON_BSTREE_H_
#define LIB_TABLE_SORTED_TABLE_ON_BSTREE_H_
#pragma once

#include "../lib_bstree/BSTree.h"
#include "table.h"

template<class TKey, class TValue>
class SortedTableOnBSTree : public Table<TKey, TValue> {
    BSTree<TKey, TValue> _tree;

public:
    SortedTableOnBSTree() = default;
    ~SortedTableOnBSTree() override = default;

    void insert(const TKey& key, const TValue& value) override;
    void erase(const TKey& key) override;

    TValue& find(const TKey& key) override;
    const TValue& find(const TKey& key) const override;

    void print(std::ostream& os) const override;

protected:
    const std::pair<TKey, TValue>& get_row(size_t index) const override;
};


template<class TKey, class TValue>
void SortedTableOnBSTree<TKey, TValue>::
insert(const TKey& key, const TValue& value) {
    _tree.insert(key, value);
    this->_size++;
}

template<class TKey, class TValue>
void SortedTableOnBSTree<TKey, TValue>::
erase(const TKey& key) {
    _tree.erase(key);
    this->_size--;
}

template<class TKey, class TValue>
TValue& SortedTableOnBSTree<TKey, TValue>::
find(const TKey& key) {
    TValue* res = _tree.find(key);
    if (!res) throw std::out_of_range("Key not found");
    return *res;
}

template<class TKey, class TValue>
const TValue& SortedTableOnBSTree<TKey, TValue>::
find(const TKey& key) const {
    TValue* res = _tree.find(key);
    if (!res) throw std::out_of_range("Key not found");
    return *res;
}


template<class TKey, class TValue>
const std::pair<TKey, TValue>&
SortedTableOnBSTree<TKey, TValue>::
get_row(size_t index) const {
    throw std::logic_error("get_row is not supported for BSTreeTable. Use print() instead.");
}

template<class TKey, class TValue>
void SortedTableOnBSTree<TKey, TValue>::
print(std::ostream& os) const {
    _tree.print_DLCR(os);
}

#endif  // LIB_TABLE_SORTED_TABLE_ON_BSTREE_H_
