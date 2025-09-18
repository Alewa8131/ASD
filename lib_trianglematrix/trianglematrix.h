// Copyright 2025 Alewa8131

#ifndef LIB_TRIANGLE_MATRIX_TRIANGLE_MATRIX_H_
#define LIB_TRIANGLE_MATRIX_TRIANGLE_MATRIX_H_

#include "../lib_matrix/matrix.h"
#include <iostream>
#include <string>

template <class T>
class TriangleMatrix : public Matrix<T> {
public:
    TriangleMatrix();
    ~TriangleMatrix();
    TriangleMatrix(int N);

    TriangleMatrix<T> operator+(const TriangleMatrix& other) const;
    TriangleMatrix<T> operator-(const TriangleMatrix& other) const;
    TriangleMatrix<T> operator*(T val) const;
    TriangleMatrix<T> operator*(TriangleMatrix<T>& matr) const;

    template <class U>
    friend std::ostream& operator<<(std::ostream& out, const TriangleMatrix<U>& obj);
    template <class U>
    friend std::istream& operator>>(std::istream& in, TriangleMatrix<U>& obj);

#ifdef DEBUG
    void debug_print(const std::string& msg) const;
#endif
};

template <class T>
TriangleMatrix<T>::TriangleMatrix() {
#ifdef DEBUG
    debug_print("Default constructor called.");
#endif
}

template <class T>
TriangleMatrix<T>::~TriangleMatrix() {
#ifdef DEBUG
    debug_print("Destructor called.");
#endif
}

template <class T>
TriangleMatrix<T>::TriangleMatrix(int N) : Matrix<T>(N, N) {
#ifdef DEBUG
    debug_print("Parameterized constructor called.");
#endif
}

template <class T>
TriangleMatrix<T> TriangleMatrix<T>::operator+(const TriangleMatrix<T>& other) const {
#ifdef DEBUG
    debug_print("operator+ called.");
#endif
    return TriangleMatrix<T>();
}

template <class T>
TriangleMatrix<T> TriangleMatrix<T>::operator-(const TriangleMatrix<T>& other) const {
#ifdef DEBUG
    debug_print("operator- called.");
#endif
    return TriangleMatrix<T>();
}

template <class T>
TriangleMatrix<T> TriangleMatrix<T>::operator*(T val) const {
#ifdef DEBUG
    debug_print("operator* (scalar) called.");
#endif
    return TriangleMatrix<T>();
}
template<class T>
TriangleMatrix<T> TriangleMatrix<T>::operator*(TriangleMatrix<T>& matr) const {
#ifdef DEBUG
    debug_print("operator* (TriangleMatrix) called.");
#endif
    return TriangleMatrix<T>();
}

template <class T>
std::ostream& operator<<(std::ostream& out, const TriangleMatrix<T>& obj) {
#ifdef DEBUG
    obj.debug_print("operator<< called.");
#endif
    return out;
}

template <class T>
std::istream& operator>>(std::istream& in, TriangleMatrix<T>& obj) {
#ifdef DEBUG
    obj.debug_print("operator>> called.");
#endif
    int n = obj.get_M();
    T temp;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            in >> temp;
        }
    }
    return in;
}

#ifdef DEBUG
template <class T>
void TriangleMatrix<T>::debug_print(const std::string& msg) const {
    std::cout << "[DEBUG] TriangleMatrix: " << msg << std::endl;
}
#endif

#endif // LIB_TRIANGLE_MATRIX_TRIANGLE_MATRIX_H_
