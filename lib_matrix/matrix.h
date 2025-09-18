// Copyright 2025 Alewa8131

#ifndef LIB_MATRIX_MATRIX_H_
#define LIB_MATRIX_MATRIX_H_
#include <vector>

template <class T>
class Matrix : public std::vector<std::vector<T>> {
    int _M = 1, _N = 1;
    std::vector<std::vector<T>> _data;
public:
    Matrix();
    ~Matrix();
    Matrix(const std::vector<std::vector<T>>&);
    Matrix(const Matrix&);
    Matrix<T> operator+(const Matrix& other);
    Matrix<T> operator*(T val);
    std::vector<T> operator*(std::vector<T> vec);
    Matrix<T> operator*(Matrix<T> matr);
    void set_M(int M);
    void set_N(int N);

    int get_M();
    int get_N();
};

template<class T>
void Matrix<T>::set_M(int M)
{
    _M = M;
}
template<class T>
void Matrix<T>::set_N(int N)
{
    _N = N;
}

template<class T>
int Matrix<T>::get_M()
{
    return _M;
}

template<class T>
int Matrix<T>::get_N()
{
    return _N;
}

template <class T>
Matrix<T>::Matrix() {}

template <class T>
Matrix<T>::~Matrix() {}

template<class T>
inline Matrix<T>::Matrix(const std::vector<std::vector<T>>&)
{
}

template<class T>
inline Matrix<T>::Matrix(const Matrix&)
{
}

template<class T>
inline Matrix<T> Matrix<T>::operator+(const Matrix& other)
{
    return Matrix<T>();
}

template<class T>
inline Matrix<T> Matrix<T>::operator*(T val)
{
    return Matrix<T>();
}

template<class T>
inline std::vector<T> Matrix<T>::operator*(std::vector<T> vec)
{
    return std::vector<T>();
}

template<class T>
inline Matrix<T> Matrix<T>::operator*(Matrix<T> matr)
{
    return Matrix<T>();
}


#endif  // LIB_MATRIX_MATRIX_H_
