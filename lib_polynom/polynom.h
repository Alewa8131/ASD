// Copyright 2026 Alewa8131

#ifndef LIB_POLYNOM_POLYNOM_H_
#define LIB_POLYNOM_POLYNOM_H_
#pragma once

#include "../lib_list/list.h"
#include "../lib_polynom/monom.h"

class Polynom {
    List<Monom> _polynom;
    std::string _name;
public:
    Polynom();
    Polynom(const Monom monom);
    Polynom(std::string str);

    Polynom operator+(const Polynom& other) const;
    Polynom operator+(const Monom& m) const;
    Polynom& operator+=(const Polynom& other);
    Polynom& operator+=(const Monom& m);

    Polynom operator-(const Polynom& other) const;
    Polynom operator-(const Monom& m) const;
    Polynom& operator-=(const Polynom& other);
    Polynom& operator-=(const Monom& m);
    Polynom operator-() const;

    Polynom operator*(const Polynom& other) const;
    Polynom operator*(const Monom& m) const;
    Polynom& operator*=(const Polynom& other);
    Polynom& operator*=(const Monom& m);

    double value(double x, double y, double z) const;
    void normalize();
};

#endif  // LIB_POLYNOM_POLYNOM_H_
