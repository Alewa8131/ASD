// Copyright 2026 Alewa8131

#ifndef LIB_TABLE_ITABLE_H_
#define LIB_TABLE_ITABLE_H_
#pragma once

#include <iostream>

template<class TKey, class TValue>
class ITable {
public:
    virtual ~ITable() = default;

    virtual void insert(const TKey& key, const TValue& value) = 0;
    virtual void erase(const TKey& key) = 0;

    virtual TValue& find(const TKey& key) = 0;
    virtual const TValue& find(const TKey& key) const = 0;

    virtual bool is_empty() const noexcept = 0;
    virtual void print(std::ostream& os) const = 0;
};

template<class TKey, class TValue>
std::ostream& operator<<(std::ostream& os, const ITable<TKey, TValue>& table) {
    table.print(os);
    return os;
}

#endif  // LIB_TABLE_ITABLE_H_
