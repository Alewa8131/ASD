// Copyright 2026 Alewa8131

#ifndef LIB_MONOM_MONOM_H_
#define LIB_MONOM_MONOM_H_
#pragma once

#include <stdexcept>
#include <iostream>
#include <string>

#define vars_count 3
class Monom {
private:
    double _coef;
    int _powers[vars_count];
public:
    Monom(double coef = 0.0);
    Monom(double coef, std::initializer_list<int> powers);
    Monom(const Monom& other);

    Monom& operator=(const Monom& other);
    bool operator==(const Monom& other) const;
    bool operator!=(const Monom& other) const;

    bool operator<(const Monom& other) const;

    Monom operator+(const Monom& other) const;
    Monom operator-(const Monom& other) const;
    Monom operator*(const Monom& other) const;
    Monom operator/(const Monom& other) const;

    Monom operator*(double value) const;
    Monom operator/(double value) const;
    Monom operator-() const;

    Monom& operator+=(const Monom& other);
    Monom& operator-=(const Monom& other);
    Monom& operator*=(const Monom& other);
    Monom& operator/=(const Monom& other);

    Monom& operator*=(double value);
    Monom& operator/=(double value);

    double value(double x, double y, double z) const;

    friend std::ostream& operator<<(std::ostream& os, const Monom& m);
    friend std::istream& operator>>(std::istream& is, Monom& m);

};





#endif  // LIB_MONOM_MONOM_H_
