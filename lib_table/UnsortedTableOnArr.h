// Copyright 2026 Alewa8131

#ifndef LIB_TABLE_UNSORTED_TABLE_ON_ARR_H_
#define LIB_TABLE_UNSORTED_TABLE_ON_ARR_H_
#pragma once

#include <stdexcept>
#include "../lib_tvector/tvector.h"
#include "table.h"

template<class TKey, class TValue>
class UnsortedTableOnArr : public Table<TKey, TValue> {
    TVector<std::pair<TKey, TValue>> _rows;

public:
    UnsortedTableOnArr() = default;
    ~UnsortedTableOnArr() override = default;

    void insert(const TKey& key, const TValue& value) override;
    void erase(const TKey& key) override;

    TValue& find(const TKey& key) override;
    const TValue& find(const TKey& key) const override;

protected:
    const std::pair<TKey, TValue>& get_row(size_t index) const override;
    size_t find_index(const TKey& key) const;
};

template<class TKey, class TValue>
void UnsortedTableOnArr<TKey, TValue>::
insert(const TKey& key, const TValue& value) {
    try {
        find_index(key);
        throw std::logic_error("Key already exists");
    } catch (const std::out_of_range&) {
        _rows.push_back({ key, value });
        this->_size++;
    }
}

template<class TKey, class TValue>
void UnsortedTableOnArr<TKey, TValue>::
erase(const TKey& key) {
    size_t index = find_index(key);

    _rows.erase(index);
    this->_size--;
}

template<class TKey, class TValue>
TValue& UnsortedTableOnArr<TKey, TValue>::
find(const TKey& key) {
    return _rows[find_index(key)].second;
}

template<class TKey, class TValue>
const TValue& UnsortedTableOnArr<TKey, TValue>::
find(const TKey& key) const {
    return _rows[find_index(key)].second;
}


template<class TKey, class TValue>
const std::pair<TKey, TValue>&
UnsortedTableOnArr<TKey, TValue>::
get_row(size_t index) const {
    return _rows[index];
}

template<class TKey, class TValue>
size_t UnsortedTableOnArr<TKey, TValue>::
find_index(const TKey& key) const {
    for (size_t i = 0; i < _rows.size(); ++i) {
        if (_rows[i].first == key)
            return i;
    }

    throw std::out_of_range("Key not found");
}

#endif  // LIB_TABLE_UNSORTED_TABLE_ON_ARR_H_
