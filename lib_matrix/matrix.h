// Copyright 2025 Alewa8131

#ifndef LIB_MATRIX_MATRIX_H_
#define LIB_MATRIX_MATRIX_H_

#include <iostream>
#include <vector>
#include <string>
#include "../lib_mathvector/mathvector.h"

template<class T>
class Matrix : public MathVector<MathVector<T>> {
    size_t _M = 1, _N = 1;
public:
    Matrix();
    ~Matrix() = default;
    Matrix(size_t M, size_t N);
    Matrix(const MathVector<MathVector<T>>& data);
    Matrix(const Matrix& other);

    size_t get_M() const;
    size_t get_N() const;
    void set_M(size_t M);
    void set_N(size_t N);

    Matrix<T> operator+(const Matrix& other) const;
    Matrix<T> operator-(const Matrix& other) const;
    Matrix<T> operator*(T val) const;
    MathVector<T> operator*(const MathVector<T>& vec) const;
    Matrix<T> operator*(const Matrix<T>& matr) const;

    Matrix<T> minor(size_t m, size_t n) const;
    T determinant() const;
    Matrix<T> transpose() const;

    using MathVector<MathVector<T>>::assign;
    MathVector<T>& operator[](size_t index);
    const MathVector<T>& operator[](size_t index) const;
    T& at(size_t m, size_t n);
    const T& at(size_t m, size_t n) const;

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
Matrix<T>::Matrix() : MathVector<MathVector<T>>(), _M(0), _N(0) {
#ifdef DEBUG
    debug_print("Default constructor called.");
#endif
}

template<class T>
Matrix<T>::Matrix(size_t M, size_t N) : _M(M), _N(N) {
#ifdef DEBUG
    debug_print("Parameterized constructor (M, N) called.");
#endif
    if (M > 0) {
        MathVector<T> row(N);
        this->MathVector<MathVector<T>>::assign(M, row);
    }
}

template<class T>
Matrix<T>::Matrix(const MathVector<MathVector<T>>& data) : MathVector<MathVector<T>>(data) {
#ifdef DEBUG
    debug_print("Vector constructor called.");
#endif
    if (data.is_empty()) {
        _M = 0;
        _N = 0;
        return;
}
    _M = data.size();
    _N = data[0].size();

    for (size_t i = 0; i < _M; ++i) {
        if (data[i].size() != _N) {
            throw std::invalid_argument("Matrix::constructor rows in initializer data must have consistent size");
        }
    }
}

template<class T>
Matrix<T>::Matrix(const Matrix& other) :
    MathVector<MathVector<T>>(other),
    _M(other._M), _N(other._N) {
#ifdef DEBUG
    debug_print("Copy constructor called.");
#endif
}



template<class T>
size_t Matrix<T>::get_M() const {
#ifdef DEBUG
    debug_print("get_M called");
#endif
    return _M;
}

template<class T>
size_t Matrix<T>::get_N() const {
#ifdef DEBUG
    debug_print("get_N called");
#endif
    return _N;
}

template<class T>
void Matrix<T>::set_M(size_t M) {
    _M = M;
#ifdef DEBUG
    debug_print("set_M called with " + std::to_string(M));
#endif
}

template<class T>
void Matrix<T>::set_N(size_t N) {
    _N = N;
#ifdef DEBUG
    debug_print("set_N called with " + std::to_string(N));
#endif
}



template<class T>
Matrix<T> Matrix<T>::operator+(const Matrix& other) const {
#ifdef DEBUG
    debug_print("operator+ called.");
#endif
    if (_M != other._M || _N != other._N) {
        throw std::invalid_argument("Matrix::+ Matrix dimensions must match for addition.");
    }
    return this->MathVector<MathVector<T>>::operator+(other);
}

template<class T>
Matrix<T> Matrix<T>::operator-(const Matrix& other) const {
#ifdef DEBUG
    debug_print("operator- called.");
#endif
    if (_M != other._M || _N != other._N) {
        throw std::invalid_argument("Matrix::- Matrix dimensions must match for subtraction.");
    }
    return Matrix<T>(this->MathVector<MathVector<T>>::operator-(other));
}

template<class T>
Matrix<T> Matrix<T>::operator*(T val) const {
#ifdef DEBUG
    debug_print("operator* (scalar) called.");
#endif
    Matrix<T> result(_M, _N);
    for (size_t i = 0; i < _M; i++) {
        result[i] = (*this)[i] * val;
    }
    return result;
}

template<class T>
MathVector<T> Matrix<T>::operator*(const MathVector<T>& vec) const {
#ifdef DEBUG
    debug_print("operator* (vector) called.");
#endif
    if (_N != vec.size()) {
        throw std::invalid_argument("Matrix::* Matrix width must match vector length for multiplication.");
    }
    MathVector<T> result(_M);
    for (size_t i = 0; i < _M; i++) {
        result.at(i) = (*this)[i] * vec;
    }
    return result;
}

template<class T>
Matrix<T> Matrix<T>::operator*(const Matrix<T>& matr) const {
#ifdef DEBUG
    debug_print("operator* (matrix) called.");
#endif
    Matrix<T> result(_M, matr._N);
    Matrix<T> matr_t = matr.transpose();

    for (int i = 0; i < _M; i++) {
        for (int j = 0; j < matr._N; j++) {
            result[i].at(j) = (*this)[i] * matr_t[j];
        }
    }
    return result;
}



template<class T>
Matrix<T> Matrix<T>::minor(size_t m, size_t n) const {
#ifdef DEBUG
    debug_print("minor called.");
#endif
    if (_M <= 1 || _N <= 1) {
        throw std::logic_error("Cannot get a minor from a 1x1 or non-square matrix.");
    }

    Matrix<T> minor(_M - 1, _N - 1);
    size_t minor_i = 0;

    for (size_t i = 0; i < _M; ++i) {
        if (i == m) continue; // skip m row

        size_t minor_j = 0;
        for (size_t j = 0; j < _N; ++j) {
            if (j == n) continue; // skip n col

            minor.at(minor_i, minor_j) = this->at(i, j);
            ++minor_j;
        }
        ++minor_i;
    }
    return minor;
    }

template<class T>
T Matrix<T>::determinant() const {
#ifdef DEBUG
    debug_print("determinant called.");
#endif
    if (_M != _N) {
        throw std::invalid_argument("Determinant is only defined for square matrices.");
    }

    size_t size = _M;

    if (size == 1) {
        return this->at(0, 0);
    }

    if (size == 2) {
        return this->at(0, 0) * this->at(1, 1) - this->at(0, 1) * this->at(1, 0);
    }

    T determinant = T(0);

    for (size_t j = 0; j < size; ++j) {
        Matrix<T> minor = this->minor(0, j);

        // Adjugate A_0j = (-1)^(0+j) * det(M_0j)
        T term = this->at(0, j) * minor.determinant();

        if (j % 2 != 0) {
            determinant -= term;
        }
        else {
            determinant += term;
        }
    }

    return determinant;
}

template<class T>
Matrix<T> Matrix<T>::transpose() const {
#ifdef DEBUG
    debug_print("transpose called.");
#endif
    Matrix<T> result(_N, _M);
    for (size_t i = 0; i < _M; ++i) {
        for (size_t j = 0; j < _N; ++j) {
            result.at(j, i) = this->at(i, j);
        }
    }
    return result;
}



template<class T>
MathVector<T>& Matrix<T>::operator[](size_t index) {
    return this->MathVector<MathVector<T>>::operator[](index);
}

template<class T>
const MathVector<T>& Matrix<T>::operator[](size_t index) const {
    return this->MathVector<MathVector<T>>::operator[](index);
}

template<class T>
T& Matrix<T>::at(size_t m, size_t n) {
#ifdef DEBUG
    debug_print("at(" + std::to_string(m) + ", " + std::to_string(n) + ") called.");
#endif
    if (m >= _M || n >= _N) {
        throw std::out_of_range("Matrix::at index out of bounds");
    }
    return this->MathVector<MathVector<T>>::at(m).at(n);
}

template<class T>
const T& Matrix<T>::at(size_t m, size_t n) const {
#ifdef DEBUG
    debug_print("const at(" + std::to_string(m) + ", " + std::to_string(n) + ") called.");
#endif
    if (m >= _M || n >= _N) {
        throw std::out_of_range("Matrix::at index out of bounds (const)");
    }
    return this->MathVector<MathVector<T>>::at(m).at(n);
}



template<class U>
std::ostream& operator<<(std::ostream& out, const Matrix<U>& obj) {
#ifdef DEBUG
    obj.debug_print("operator<< called.");
#endif
    for (size_t i = 0; i < obj.get_M(); ++i) {
        out << obj[i] << "\n";
    }
    return out;
    }

template<class T>
std::istream& operator>>(std::istream& in, Matrix<T>& obj) {
#ifdef DEBUG
    obj.debug_print("operator>> called.");
#endif
    size_t m = obj.get_M();
    size_t n = obj.get_N();

    if (m == 0 || n == 0) return in;

    std::cout << "Enter " << m * n << " values for Matrix (" << m << "x" << n << "):" << std::endl;

    for (size_t i = 0; i < m; ++i) {
        std::cout << "Row " << i + 1 << " (" << n << " values): ";
        for (size_t j = 0; j < n; ++j) {
            in >> obj.at(i, j);
        }
    }
    return in;
}

#endif  // LIB_MATRIX_MATRIX_H_
