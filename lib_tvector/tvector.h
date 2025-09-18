// Copyright 2025 Alewa8131

#ifndef LIB_VECTOR_VECTOR_H_
#define LIB_VECTOR_VECTOR_H_

#include <iostream>
#include <vector>
#include <string>

#define DEBUG

template <class T>
class TVector {
protected:
    std::vector<T> _data;

public:
    TVector();
    ~TVector();
    TVector(int size);

    T& at(int index);
    const T& at(int index) const;
    int size() const;

#ifdef DEBUG
    void debug_print(const std::string& msg) const;
#endif
};

template <class T>
TVector<T>::TVector() {}

template <class T>
TVector<T>::~TVector() {}

template <class T>
TVector<T>::TVector(int size) {
#ifdef DEBUG
    debug_print("TVector parameterized constructor called.");
#endif
    this->_data.resize(size);
}

template <class T>
T& TVector<T>::at(int index) {
    return _data.at(index);
}

template <class T>
const T& TVector<T>::at(int index) const {
    return _data.at(index);
}

template <class T>
int TVector<T>::size() const {
    return _data.size();
}

#ifdef DEBUG
template <class T>
void TVector<T>::debug_print(const std::string& msg) const {
    std::cout << "[DEBUG] TVector: " << msg << std::endl;
}
#endif

#endif // LIB_VECTOR_VECTOR_H_
