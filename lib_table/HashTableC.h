// Copyright 2026 Alewa8131

#ifndef LIB_TABLE_HASH_TABLE_C_H_
#define LIB_TABLE_HASH_TABLE_C_H_
#pragma once

#include <stdexcept>
#include "../lib_tvector/tvector.h"
#include "../lib_list/list.h"
#include "table.h"

template<class TValue>
class HashTableC : public Table<std::string, TValue> {
    TVector<List<std::pair<std::string, TValue>>> _rows;
    size_t _count = 0;

public:
    HashTableC(size_t s = 100);
    ~HashTableC() override = default;

    void insert(const std::string& key, const TValue& value) override;
    void erase(const std::string& key) override;

    TValue& find(const std::string& key) override;
    const TValue& find(const std::string& key) const override;

    const std::string& get_key_at(size_t index) const;
    const TValue& get_value_at(size_t index) const;

    size_t size() const noexcept;
    size_t count() const noexcept;
    bool is_full() const noexcept;
    bool is_empty() const noexcept;
protected:
    size_t h(const std::string& key) const noexcept;
    const std::pair<std::string, TValue>& get_row(size_t index) const override;
};

template<class TValue>
HashTableC<TValue>::
HashTableC(size_t s) : _rows(s), _count(0) {
    this->_size = s;
}

template<class TValue>
void HashTableC<TValue>::
insert(const std::string& key, const TValue& value) {
    size_t hash = h(key);

    auto it = _rows[hash].begin();
    auto end = _rows[hash].end();

    for (; it != end; ++it) {
        if ((*it).first == key) {
            throw std::logic_error("Key already exists");
        }
    }
    _rows[hash].push_back(std::make_pair(key, value));
    _count++;
}

template<class TValue>
void HashTableC<TValue>::
erase(const std::string& key) {
    size_t hash = h(key);

    Node<std::pair<std::string, TValue>>* current = _rows[hash].head();

    while (current != nullptr) {
        if (current->_value.first == key) {
            _rows[hash].erase(current);
            _count--;
            return;
        }
        current = current->_next;
    }

    throw std::logic_error("Key not found for erasing");
}


template<class TValue>
TValue& HashTableC<TValue>::
find(const std::string& key) {
    size_t hash = h(key);

    auto it = _rows[hash].begin();
    auto end = _rows[hash].end();

    for (; it != end; ++it) {
        if ((*it).first == key) {
            return (*it).second;
        }
    }

    throw std::out_of_range("Key not found");
}

template<class TValue>
const TValue& HashTableC<TValue>::
find(const std::string& key) const {
    size_t hash = h(key);

    auto it = _rows[hash].begin();
    auto end = _rows[hash].end();

    for (; it != end; ++it) {
        if ((*it).first == key) {
            return (*it).second;
        }
    }

    throw std::out_of_range("Key not found");
}


template<class TValue>
const std::string& HashTableC<TValue>::
get_key_at(size_t index) const {
    return this->get_row(index).first;
}

template<class TValue>
const TValue& HashTableC<TValue>::
get_value_at(size_t index) const {
    return this->get_row(index).second;
}


template<class TValue>
size_t HashTableC<TValue>::
size() const noexcept {
    return _size;
}

template<class TValue>
size_t HashTableC<TValue>::
count() const noexcept {
    return _count;
}

template<class TValue>
bool HashTableC<TValue>::
is_full() const noexcept {
    return _count >= this->_size;
}

template<class TValue>
bool HashTableC<TValue>::
is_empty() const noexcept {
    return _count == 0;
}


template<class TValue>
size_t HashTableC<TValue>::
h(const std::string& key) const noexcept {
    size_t hash = 0;
    const size_t p = 31;
    for (unsigned char c : key) {
        hash = hash * p + c;
    }
    return hash % this->_size;
}

template<class TValue>
const std::pair<std::string, TValue>&
HashTableC<TValue>::
get_row(size_t index) const {
    size_t current_idx = 0;
    for (size_t i = 0; i < _rows.capacity(); ++i) {
        auto it = _rows[i].begin();
        auto end = _rows[i].end();
        for (; it != end; ++it) {
            if (current_idx == index) {
                return (*it);
            }
            current_idx++;
        }
    }
    throw std::out_of_range("Index out of range");
}

#endif  // LIB_TABLE_HASH_TABLE_C_H_
