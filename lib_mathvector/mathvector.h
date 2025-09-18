// Copyright 2025 Alewa8131

#ifndef LIB_MATHVECTOR_MATHVECTOR_H_
#define LIB_MATHVECTOR_MATHVECTOR_H_

#include "../lib_tvector/tvector.h"

template <class T>
class MathVector : private TVector<T> {
public:
    MathVector();
    ~MathVector();
    MathVector(int size);

    T& at(int index);
    const T& at(int index) const;

    MathVector<T> operator+(const MathVector<T>& other) const;
    MathVector<T> operator-(const MathVector<T>& other) const;
    T operator*(const MathVector<T>& other) const;

#ifdef DEBUG
    void debug_print(const std::string& msg) const;
#endif
};

template <class T>
MathVector<T>::MathVector() {}

template <class T>
MathVector<T>::~MathVector() {}

template <class T>
MathVector<T>::MathVector(int size) : TVector<T>(size) {
#ifdef DEBUG
    debug_print("MathVector parameterized constructor called.");
#endif
}

template <class T>
T& MathVector<T>::at(int index) {
    return TVector<T>::at(index);
}

template <class T>
const T& MathVector<T>::at(int index) const {
    return TVector<T>::at(index);
}

template <class T>
MathVector<T> MathVector<T>::operator+(const MathVector<T>& other) const {
#ifdef DEBUG
    debug_print("MathVector operator+ called.");
#endif
    return MathVector<T>();
}

template <class T>
MathVector<T> MathVector<T>::operator-(const MathVector<T>& other) const {
#ifdef DEBUG
    debug_print("MathVector operator- called.");
#endif
    return MathVector<T>();
}

template <class T>
T MathVector<T>::operator*(const MathVector<T>& other) const {
#ifdef DEBUG
    debug_print("MathVector operator* (scalar product) called.");
#endif
    return T();
}

#ifdef DEBUG
template <class T>
void MathVector<T>::debug_print(const std::string& msg) const {
    std::cout << "[DEBUG] MathVector: " << msg << std::endl;
}
#endif

#endif // LIB_MATHVECTOR_MATHVECTOR_H_
