// Copyright 2026 Alewa8131

#ifndef LIB_TABLE_TABLE_H_
#define LIB_TABLE_TABLE_H_
#pragma once

#include "itable.h"
#include <utility>

template<class TKey, class TValue>
class Table : public ITable<TKey, TValue> {
protected:
    size_t _size = 0;

public:
    virtual ~Table() = default;

    size_t size() const noexcept;

    bool is_empty() const noexcept override;
    void print(std::ostream& os) const override;

protected:
    virtual const std::pair<TKey, TValue>& get_row(size_t i) const = 0;
};

template<class TKey, class TValue>
size_t Table<TKey, TValue>::size() const noexcept {
    return _size;
}

template<class TKey, class TValue>
bool Table<TKey, TValue>::is_empty() const noexcept {
    return _size == 0;
}

template<class TKey, class TValue>
void Table<TKey, TValue>::print(std::ostream& os) const {
    for (size_t i = 0; i < size(); ++i) {
        const auto& row = get_row(i);
        os << row.first << " : " << row.second;

        if (i + 1 < size())
            os << '\n';
    }
}

#endif  // LIB_TABLE_TABLE_H_
