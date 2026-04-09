// Copyright 2026 Alewa8131

#ifndef LIB_TABLE_HASH_TABLE_OA_H_
#define LIB_TABLE_HASH_TABLE_OA_H_
#pragma once

#include <stdexcept>
#include "../lib_tvector/tvector.h"
#include "../lib_list/list.h"
#include "table.h"


template<class TValue>
class HashTableOA : public Table<std::string, TValue> {
    struct HashData {
    public:
        State _state;
        std::string _key;
        TValue _value;
        HashData() : _state(empty), _key(""), _value(TValue()) {}
        HashData(std::string key, TValue val) : _key(key), _value(val), _state(busy) {}
    };
    std::vector<HashData> _rows;
    size_t _count = 0;
    size_t _shift = 7;

public:
    HashTableOA(size_t s = 100);
    ~HashTableOA() override = default;

    void insert(const std::string& key, const TValue& value) override;
    void erase(const std::string& key) override;

    TValue& find(const std::string& key) override;
    const TValue& find(const std::string& key) const override;

    const std::string& get_key_at(size_t index) const;
    const TValue& get_value_at(size_t index) const;

    size_t size() const noexcept;
    size_t shift() const noexcept;
    size_t count() const noexcept;
    bool is_full() const noexcept;
    bool is_empty() const noexcept;
protected:
    size_t h(const std::string& key) const noexcept;
    size_t hh(size_t hash) const noexcept;
    const std::pair<std::string, TValue>& get_row(size_t index) const override;
    bool is_simple(size_t n, size_t size) const noexcept;
};

template<class TValue>
HashTableOA<TValue>::
HashTableOA(size_t s) : _rows(s), _count(0) {
    this->_size = s;
    for (size_t i = std::max<size_t>(2, s / 15); i < s; i++) {
        if (is_simple(i, this->_size)) _shift = i;
    }
}

template<class TValue>
void HashTableOA<TValue>::
insert(const std::string& key, const TValue& value) {
    if (is_full())
        throw std::out_of_range("HashTableOA is full");

    size_t hash = h(key);
    size_t first_hash = hash;

    while (1) {
        if (_rows[hash]._state != busy) {
            _rows[hash] = HashData(key, value);
            _count++;
            return;
        }
        if (_rows[hash]._key == key)
            throw std::logic_error("Key already exists");

        hash = hh(hash);
        if (first_hash == hash)
            break;
    }
}

template<class TValue>
void HashTableOA<TValue>::
erase(const std::string& key) {
    size_t hash = h(key);
    size_t first_hash = hash;

    while (1) {
        if (_rows[hash]._state == empty)
            break;
        if (_rows[hash]._state == busy && _rows[hash]._key == key) {
            _rows[hash]._state = deleted;
            _count--;
            return;
        }
        hash = hh(hash);
        if (first_hash == hash)
            break;
    }
    throw std::logic_error("Key not found");
}


template<class TValue>
TValue& HashTableOA<TValue>::find(const std::string& key) {
    size_t hash = h(key);
    size_t first_hash = hash;

    while (1) {
        if (_rows[hash]._state == empty) 
            break;
        if (_rows[hash]._state == busy && _rows[hash]._key == key)
            return _rows[hash]._value;
        
        hash = hh(hash);
        if (first_hash == hash)
            break;
    }

    throw std::out_of_range("Key not found");
}

template<class TValue>
const TValue& HashTableOA<TValue>::
find(const std::string& key) const {
    size_t hash = h(key);
    size_t first_hash = hash;

    while (1) {
        if (_rows[hash]._state == empty)
            break;
        if (_rows[hash]._state == busy && _rows[hash]._key == key)
            return _rows[hash]._value;

        hash = hh(hash);
        if (first_hash == hash)
            break;
    }

    throw std::out_of_range("Key not found");
}


template<class TValue>
const std::string& HashTableOA<TValue>::
get_key_at(size_t index) const {
    return this->get_row(index).first;
}

template<class TValue>
const TValue& HashTableOA<TValue>::
get_value_at(size_t index) const {
    return this->get_row(index).second;
}


template<class TValue>
size_t HashTableOA<TValue>::
size() const noexcept {
    return this->_size;
}

template<class TValue>
size_t HashTableOA<TValue>::
shift() const noexcept {
    return _shift;
}

template<class TValue>
size_t HashTableOA<TValue>::
count() const noexcept {
    return _count;
}

template<class TValue>
bool HashTableOA<TValue>::
is_full() const noexcept {
    return _count >= this->_size;
}

template<class TValue>
bool HashTableOA<TValue>::
is_empty() const noexcept {
    return _count == 0;
}


template<class TValue>
size_t HashTableOA<TValue>::
h(const std::string& key) const noexcept {
    size_t hash = 0;
    const size_t p = 31;
    for (unsigned char c : key) {
        hash = hash * p + c;
    }
    return hash % this->_size;
}

template<class TValue>
size_t HashTableOA<TValue>::
hh(size_t hash) const noexcept {
    return (hash + _shift) % this->_size;
}

template<class TValue>
const std::pair<std::string, TValue>&
HashTableOA<TValue>::
get_row(size_t index) const {
    if (index >= _count) throw std::out_of_range("Index out of range");

    size_t current_idx = 0;
    for (size_t i = 0; i < this->_size; ++i) {
        if (_rows[i]._state == busy) {
            if (current_idx == index) {
                static std::pair<std::string, TValue> res;
                res.first = _rows[i]._key;
                res.second = _rows[i]._value;
                return res;
            }
            current_idx++;
        }
    }
    throw std::out_of_range("Not found");
}

template<class TValue>
bool HashTableOA<TValue>::
is_simple(size_t n, size_t size) const noexcept {
    if (n < 2) return false;

    for (size_t i = 2; i * i <= n; i++) {
        if (n % i == 0) return false;
    }

    size_t a = n;
    size_t b = size;
    while (b > 0) {
        a %= b;
        std::swap(a, b);
    }

    return (a == 1);
}

#endif  // LIB_TABLE_HASH_TABLE_OA_H_
