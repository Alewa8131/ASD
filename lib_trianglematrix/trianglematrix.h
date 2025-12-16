// Copyright 2025 Alewa8131

#ifndef LIB_TRIANGLE_MATRIX_TRIANGLE_MATRIX_H_
#define LIB_TRIANGLE_MATRIX_TRIANGLE_MATRIX_H_
#pragma once
#include <iostream>
#include <string>

#include "../lib_matrix/matrix.h"

template <class T>
class TriangleMatrix : public Matrix<T> {
private:
    static const T ZERO_VALUE = T{0}; // Elem under diagonal
public:
    TriangleMatrix();
    ~TriangleMatrix() = default;
    TriangleMatrix(size_t N);


    TriangleMatrix<T> operator+(const TriangleMatrix& other) const;
    TriangleMatrix<T> operator-(const TriangleMatrix& other) const;
    TriangleMatrix<T> operator*(T val) const;
    TriangleMatrix<T> operator*(const TriangleMatrix<T>& matr) const;

    T& at(size_t i, size_t j);
    const T& at(size_t i, size_t j) const;

    template <class U>
    friend std::ostream& operator<<(std::ostream& out, const TriangleMatrix<U>& obj);
    template <class U>
    friend std::istream& operator>>(std::istream& in, TriangleMatrix<U>& obj);

#ifdef DEBUG
    void debug_print(const std::string& msg) const;
#endif
};

template <class T>
TriangleMatrix<T>::TriangleMatrix() : Matrix<T>() {
#ifdef DEBUG
    debug_print("Default constructor called.");
#endif
}


template <class T>
TriangleMatrix<T>::TriangleMatrix(size_t N) : Matrix<T>() {
#ifdef DEBUG
    debug_print("Parameterized constructor called. Creating compressed structure without clear().");
#endif
    if (N == 0) {
        this->set_M(0);
        this->set_N(0);
        return;
    }

    this->set_M(N);
    this->set_N(N);

    for (size_t i = 0; i < N; ++i) {
        size_t row_len = (N - i) + 1;

        MathVector<T> compact_row(row_len);

        compact_row[0] = T(i);

        this->MathVector<MathVector<T>>::push_back(compact_row);
    }
}

template <class T>
TriangleMatrix<T> TriangleMatrix<T>::operator+(const TriangleMatrix<T>& other) const {
#ifdef DEBUG
    debug_print("operator+ called.");
#endif
    if (this->get_M() != other.get_M()) {
        throw std::invalid_argument("Matrices must have the same dimension for addition.");
    }
    size_t N = this->get_M();
    TriangleMatrix<T> result(N);

    for (size_t i = 0; i < N; ++i) {
        for (size_t j = i; j < N; ++j) {
            result.at(i, j) = this->at(i, j) + other.at(i, j);
        }
}
    return result;
}

template <class T>
TriangleMatrix<T> TriangleMatrix<T>::operator-(const TriangleMatrix<T>& other) const {
#ifdef DEBUG
    debug_print("operator- called.");
#endif
    if (this->get_M() != other.get_M()) {
        throw std::invalid_argument("Matrices must have the same dimension for subtraction.");
    }
    size_t N = this->get_M();
    TriangleMatrix<T> result(N);

    for (size_t i = 0; i < N; ++i) {
        for (size_t j = i; j < N; ++j) {
            result.at(i, j) = this->at(i, j) - other.at(i, j);
        }
    }
    return result;
}

template <class T>
TriangleMatrix<T> TriangleMatrix<T>::operator*(T val) const {
#ifdef DEBUG
    debug_print("operator* (scalar) called.");
#endif
    size_t N = this->get_M();
    TriangleMatrix<T> result(N);

    for (size_t i = 0; i < N; ++i) {
        for (size_t j = i; j < N; ++j) {
            result.at(i, j) = this->at(i, j) * val;
        }
    }
    return result;
}

template<class T>
TriangleMatrix<T> TriangleMatrix<T>::operator*(const TriangleMatrix<T>& matr) const {
#ifdef DEBUG
    debug_print("operator* (TriangleMatrix) called.");
#endif
    if (this->get_N() != matr.get_M()) {
        throw std::invalid_argument("Matrix dimensions are not compatible for multiplication.");
    }

    size_t N = this->get_M();
    TriangleMatrix<T> result(N);

    for (size_t i = 0; i < N; ++i) {
        for (size_t j = i; j < N; ++j) {
            T sum = T{};

            for (size_t k = i; k <= j; ++k) {
                sum += this->at(i, k) * matr.at(k, j);
            }
            result.at(i, j) = sum;
        }
    }
    return result;
}

template <class T>
T& TriangleMatrix<T>::at(size_t i, size_t j) {
    if (i >= this->get_M() || j >= this->get_N()) {
        throw std::out_of_range("TriangleMatrix index out of bounds.");
    }

    if (j < i) {
        static T discard_value{};
        return discard_value;
    }

    size_t compact_j = j - i + 1;

    return this->MathVector<MathVector<T>>::at(i).at(compact_j);
}

template <class T>
const T& TriangleMatrix<T>::at(size_t i, size_t j) const {
    if (i >= this->get_M() || j >= this->get_N()) {
        throw std::out_of_range("TriangleMatrix index out of bounds (const).");
    }

    if (j < i) {
        return ZERO_VALUE;
    }

    size_t compact_j = j - i + 1;
    return this->MathVector<MathVector<T>>::at(i).at(compact_j);
}

template <class T>
std::ostream& operator<<(std::ostream& out, const TriangleMatrix<T>& obj) {
#ifdef DEBUG
    obj.debug_print("operator<< called.");
#endif
    size_t N = obj.get_M();

    if (N > 0) {
        out << "--- Triangle Matrix (" << N << "x" << N << ") ---\n";
    }

    for (size_t i = 0; i < N; ++i) {
        for (size_t k = 0; k < i; ++k) {
            out << std::setw(6) << TriangleMatrix<T>::ZERO_VALUE << " ";
    }

        const MathVector<T>& compact_row = obj.MathVector<MathVector<T>>::at(i);

        for (size_t j = 0+1; j < compact_row.size(); ++j) { // shift + 1
            out << std::setw(6) << compact_row.at(j) << " ";
        }
        out << "\n";
    }
    return out;
}

template <class T>
std::istream& operator>>(std::istream& in, TriangleMatrix<T>& obj) {
#ifdef DEBUG
    obj.debug_print("operator>> called.");
#endif
    size_t N = obj.get_M();
    T temp;

    if (N == 0) return in;

    std::cout << "\nEnter only the triangular elements for TriangleMatrix (" << N << "x" << N << "):" << std::endl;
    size_t total_elements = (N * (N + 1)) / 2;
    std::cout << "You only need to enter " << total_elements << " values (on and above the diagonal) row by row." << std::endl;

    for (size_t i = 0; i < N; ++i) {
        size_t values_to_enter = N - i;

        std::cout << "Row " << i + 1 << " (" << values_to_enter << " values): ";

        for (size_t j = 0; j < i; ++j) {
            std::cout << std::setw(6) << 0 << " ";
        }

        for (size_t j = i; j < N; ++j) {
            if (!(in >> temp)) {
                throw std::runtime_error("Input error during reading matrix elements.");
            }
            obj.at(i, j) = temp;
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
