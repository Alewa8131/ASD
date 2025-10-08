// Copyright 2025 Alewa8131

#ifndef LIB_MATHVECTOR_MATHVECTOR_H_
#define LIB_MATHVECTOR_MATHVECTOR_H_

#include "../lib_tvector/tvector.h"

template <class T>
class MathVector : public TVector<T> {
public:
    MathVector();
    ~MathVector();
    explicit MathVector(size_t size);
    MathVector(std::initializer_list<T> init);

    T& at(size_t index);
    const T& at(size_t index) const;

    size_t size() const;

    MathVector<T> operator+(const MathVector<T>& other) const;
    MathVector<T> operator-(const MathVector<T>& other) const;
    T operator*(const MathVector<T>& other) const;
    MathVector<T> operator*(const T& scalar) const;

#ifdef DEBUG
    void debug_print(const std::string& msg) const;
#endif
};

template <class T>
MathVector<T>::MathVector() : TVector<T>() {}

template <class T>
MathVector<T>::~MathVector() {}

template <class T>
MathVector<T>::MathVector(size_t size) {
    if (size > 0) {
        TVector<T>::assign(size, T{});
    }
#ifdef DEBUG
    debug_print("MathVector parameterized constructor called.");
#endif
}

template <class T>
MathVector<T>::MathVector(std::initializer_list<T> init) : TVector<T>(init) {}

template <class T>
T& MathVector<T>::at(size_t index) {
    return TVector<T>::at(index);
}

template <class T>
const T& MathVector<T>::at(size_t index) const {
    return TVector<T>::at(index);
}

template <class T>
size_t MathVector<T>::size() const {
    return TVector<T>::size();
}


template <class T>
MathVector<T> MathVector<T>::operator+(const MathVector<T>& other) const {
#ifdef DEBUG
    debug_print("MathVector operator+ called.");
#endif
    if (size() != other.size()) {
        throw std::invalid_argument("Vector dimensions must match for addition.");
    }

    MathVector<T> result(size());

    for (size_t i = 0; i < size(); ++i) {
        result.at(i) = this->at(i) + other.at(i);
    }
    return result;
}

template <class T>
MathVector<T> MathVector<T>::operator-(const MathVector<T>& other) const {
#ifdef DEBUG
    debug_print("MathVector operator- called.");
#endif
    if (size() != other.size()) {
        throw std::invalid_argument("Vector dimensions must match for subtraction.");
    }

    MathVector<T> result(size());

    for (size_t i = 0; i < size(); ++i) {
        result.at(i) = this->at(i) - other.at(i);
    }
    return result;
}

template <class T>
T MathVector<T>::operator*(const MathVector<T>& other) const {
#ifdef DEBUG
    debug_print("MathVector operator* (scalar product) called.");
#endif
    if (size() != other.size()) {
        throw std::invalid_argument("Vector dimensions must match for scalar product.");
    }

    T scalar_product = T{};

    for (size_t i = 0; i < size(); ++i) {
        scalar_product += this->at(i) * other.at(i);
    }
    return scalar_product;
}

template <class T>
MathVector<T> MathVector<T>::operator*(const T& scalar) const {
#ifdef DEBUG
    debug_print("MathVector operator* (scalar multiplication) called.");
#endif
    MathVector<T> result(size());

    for (size_t i = 0; i < size(); ++i) {
        result.at(i) = this->at(i) * scalar;
    }
    return result;
}

template<class T>
std::ostream& operator<<(std::ostream& os, const MathVector<T>& vec) {
    size_t vec_size = vec.size();

    os << "[";
    for (size_t i = 0; i < vec_size; ++i) {
        os << std::setw(6) << vec[i];
        if (i < vec_size - 1) {
            os << " ";
        }
    }
    os << "]";
    return os;
}

#ifdef DEBUG
template <class T>
void MathVector<T>::debug_print(const std::string& msg) const {
    std::cout << "[DEBUG] MathVector: " << msg << std::endl;
}
#endif

#endif // LIB_MATHVECTOR_MATHVECTOR_H_
