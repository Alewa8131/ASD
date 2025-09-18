// Copyright 2025 Alewa8131

#ifndef LIB_MATRIX_MATRIX_H_
#define LIB_MATRIX_MATRIX_H_

#include <iostream>
#include <vector>
#include <string>
#include "../lib_mathvector/mathvector.h"

template<class T>
class Matrix : public MathVector<MathVector<T>> {
    int _M = 1, _N = 1;
public:
    Matrix();
    ~Matrix();
    Matrix(int M, int N);
    Matrix(const std::vector<std::vector<T>>& data);
    Matrix(const Matrix& other);

    int get_M() const;
    int get_N() const;
    T get_determinant() const;
    void set_M(int M);
    void set_N(int N);

    Matrix<T> operator+(const Matrix& other) const;
    Matrix<T> operator-(const Matrix& other) const;
    Matrix<T> operator*(T val) const;
    std::vector<T> operator*(std::vector<T>& vec) const;
    Matrix<T> operator*(Matrix<T>& matr) const;

    using MathVector<MathVector<T>>::at;
    T& at(int m, int n);
    const T& at(int m, int n) const;

    template<class T>
    friend std::ostream& operator<<(std::ostream& out, const Matrix<T>& obj);
    template<class T>
    friend std::istream& operator>>(std::istream& in, Matrix<T>& obj);

#ifdef DEBUG
    void debug_print(const std::string& msg) const;
#endif
};


#ifdef DEBUG
template<class T>
void Matrix<T>::debug_print(const std::string& msg) const {
    std::cout << "[DEBUG] " << msg << std::endl;
}
#endif

template<class T>
int Matrix<T>::get_M() const {
#ifdef DEBUG
    debug_print("get_M called");
#endif
    return _M;
}

template<class T>
int Matrix<T>::get_N() const {
#ifdef DEBUG
    debug_print("get_N called");
#endif
    return _N;
}

template <class T>
T Matrix<T>::get_determinant() const {
#ifdef DEBUG
    debug_print("get_determinant called.");
#endif
    return T();
}

template<class T>
void Matrix<T>::set_M(int M) {
    _M = M;
#ifdef DEBUG
    debug_print("set_M called with " + std::to_string(M));
#endif
}

template<class T>
void Matrix<T>::set_N(int N) {
    _N = N;
#ifdef DEBUG
    debug_print("set_N called with " + std::to_string(N));
#endif
}

template<class T>
Matrix<T>::Matrix() {
#ifdef DEBUG
    debug_print("Default constructor called.");
#endif
}

template<class T>
Matrix<T>::~Matrix() {
#ifdef DEBUG
    debug_print("Destructor called.");
#endif
}

template<class T>
Matrix<T>::Matrix(int M, int N) : _M(M), _N(N) {
#ifdef DEBUG
    debug_print("Parameterized constructor (M, N) called.");
#endif
}

template<class T>
Matrix<T>::Matrix(const std::vector<std::vector<T>>& data) {
#ifdef DEBUG
    debug_print("Vector constructor called.");
#endif
}

template<class T>
Matrix<T>::Matrix(const Matrix& other) {
#ifdef DEBUG
    debug_print("Copy constructor called.");
#endif
}

template<class T>
Matrix<T> Matrix<T>::operator+(const Matrix& other) const {
#ifdef DEBUG
    debug_print("operator+ called.");
#endif
    return Matrix<T>();
}

template<class T>
Matrix<T> Matrix<T>::operator-(const Matrix& other) const {
#ifdef DEBUG
    debug_print("operator- called.");
#endif
    return Matrix<T>();
}

template<class T>
Matrix<T> Matrix<T>::operator*(T val) const {
#ifdef DEBUG
    debug_print("operator* (scalar) called.");
#endif
    return Matrix<T>();
}

template<class T>
std::vector<T> Matrix<T>::operator*(std::vector<T>& vec) const {
#ifdef DEBUG
    debug_print("operator* (vector) called.");
#endif
    return std::vector<T>();
}

template<class T>
Matrix<T> Matrix<T>::operator*(Matrix<T>& matr) const {
#ifdef DEBUG
    debug_print("operator* (matrix) called.");
#endif
    return Matrix<T>();
}

template<class T>
T& Matrix<T>::at(int m, int n) {
#ifdef DEBUG
    debug_print("at(" + std::to_string(m) + ", " + std::to_string(n) + ") called.");
#endif
    static T dummy_val;
    return dummy_val;
}

template<class T>
const T& Matrix<T>::at(int m, int n) const {
#ifdef DEBUG
    debug_print("const at(" + std::to_string(m) + ", " + std::to_string(n) + ") called.");
#endif
    static T dummy_val = T();
    return dummy_val;
}

template<class T>
std::ostream& operator<<(std::ostream& out, const Matrix<T>& obj) {
#ifdef DEBUG
    obj.debug_print("operator<< called.");
#endif
    return out;
}

template<class T>
std::istream& operator>>(std::istream& in, Matrix<T>& obj) {
#ifdef DEBUG
    obj.debug_print("operator>> called.");
#endif
    int m = obj.get_M();
    int n = obj.get_N();
    T temp;
    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
            in >> temp;
        }
    }
    return in;
}

#endif  // LIB_MATRIX_MATRIX_H_
