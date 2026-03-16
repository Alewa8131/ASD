// Copyright 2026 Alewa8131

#ifndef LIB_TABLE_SORTED_TABLE_ON_ARR_H_
#define LIB_TABLE_SORTED_TABLE_ON_ARR_H_
#pragma once

#include <stdexcept>
#include "../lib_tvector/tvector.h"
#include "table.h"

template<class TKey, class TValue>
class SortedTableOnArr : public Table<TKey, TValue> {
    TVector<std::pair<TKey, TValue>> _rows;

public:
    SortedTableOnArr() = default;
    ~SortedTableOnArr() override = default;

    void insert(const TKey& key, const TValue& value) override;
    void erase(const TKey& key) override;

    TValue& find(const TKey& key) override;
    const TValue& find(const TKey& key) const override;

protected:
    const std::pair<TKey, TValue>& get_row(size_t index) const override;
    size_t find_index(const TKey& key) const;
};


template<class TKey, class TValue>
void SortedTableOnArr<TKey, TValue>::
insert(const TKey& key, const TValue& value) {
    size_t left = 0;
    size_t right = _rows.size();

    while (left < right) {
        size_t mid = (left + right) / 2;

        if (_rows[mid].first < key)
            left = mid + 1;
        else
            right = mid;
    }

    if (left < _rows.size() && _rows[left].first == key)
        throw std::logic_error("Key already exists");

    _rows.insert(left, { key, value });
    this->_size++;
}

template<class TKey, class TValue>
void SortedTableOnArr<TKey, TValue>::
erase(const TKey& key) {
    size_t index = find_index(key);

    _rows.erase(index);
    this->_size--;
}

template<class TKey, class TValue>
TValue& SortedTableOnArr<TKey, TValue>::
find(const TKey& key) {
    return _rows[find_index(key)].second;
}

template<class TKey, class TValue>
const TValue& SortedTableOnArr<TKey, TValue>::
find(const TKey& key) const {
    return _rows[find_index(key)].second;
}


template<class TKey, class TValue>
const std::pair<TKey, TValue>&
SortedTableOnArr<TKey, TValue>::
get_row(size_t index) const {
    return _rows[index];
}

template<class TKey, class TValue>
size_t SortedTableOnArr<TKey, TValue>::
find_index(const TKey& key) const {
    size_t left = 0;
    size_t right = _rows.size();

    while (left < right) {
        size_t mid = (left + right) / 2;

        if (_rows[mid].first == key)
            return mid;

        if (_rows[mid].first < key)
            left = mid + 1;
        else
            right = mid;
    }

    throw std::out_of_range("Key not found");
}

#endif  // LIB_TABLE_SORTED_TABLE_ON_ARR_H_
