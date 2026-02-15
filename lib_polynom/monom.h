// Copyright 2026 Alewa8131

#ifndef LIB_MONOM_MONOM_H_
#define LIB_MONOM_MONOM_H_
#pragma once

#include <stdexcept>
#include <iostream>
#include <string>

class Monom {
private:
    double _coef;
    int _px;
    int _py;
    int _pz;
public:
    Monom();
    Monom(double coef, int px, int py, int pz);
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

Monom::Monom() : _coef(0), _px(0), _py(0), _pz(0) {}
Monom::Monom(double coef, int px, int py, int pz)
    : _coef(coef), _px(px), _py(py), _pz(pz) {
    if (px < 0 || py < 0 || pz < 0)
        throw std::invalid_argument("Negative power is not allowed");
}
Monom::Monom(const Monom& other)
    : _coef(other._coef),
    _px(other._px),
    _py(other._py),
    _pz(other._pz) {}

Monom& Monom::operator=(const Monom& other) {
    if (this != &other) {
        _coef = other._coef;
        _px = other._px;
        _py = other._py;
        _pz = other._pz;
    }
    return *this;
}
bool Monom::operator==(const Monom & other) const {
    return _px == other._px &&
        _py == other._py &&
        _pz == other._pz;
}
bool Monom::operator!=(const Monom& other) const {
    return !(*this == other);
}

bool Monom::operator<(const Monom& other) const {
    if (_px != other._px) return _px > other._px;
    if (_py != other._py) return _py > other._py;
    return _pz > other._pz;
}

Monom Monom::operator+(const Monom& other) const {
    if (*this != other)
        throw std::logic_error("Monoms are not similar");
    return Monom(_coef + other._coef, _px, _py, _pz);
}
Monom Monom::operator-(const Monom& other) const {
    if (*this != other)
        throw std::logic_error("Monoms are not similar");
    return Monom(_coef - other._coef, _px, _py, _pz);
}
Monom Monom::operator*(const Monom& other) const {
    return Monom(
        _coef * other._coef,
        _px + other._px,
        _py + other._py,
        _pz + other._pz
    );
}
Monom Monom::operator/(const Monom& other) const {
    if (other._coef == 0)
        throw std::logic_error("Division by zero monom");
    return Monom(
        _coef / other._coef,
        _px - other._px,
        _py - other._py,
        _pz - other._pz
    );
}

Monom Monom::operator*(double value) const {
    return Monom(_coef * value, _px, _py, _pz);
}
Monom Monom::operator/(double value) const {
    if (value == 0)
        throw std::logic_error("Division by zero");
    return Monom(_coef / value, _px, _py, _pz);
}
Monom Monom::operator-() const {
    return Monom(-_coef, _px, _py, _pz);
}

Monom& Monom::operator+=(const Monom& other) {
    *this = *this + other;
    return *this;
}
Monom& Monom::operator-=(const Monom& other) {
    *this = *this - other;
    return *this;
}
Monom& Monom::operator*=(const Monom& other) {
    *this = *this * other;
    return *this;
}
Monom& Monom::operator/=(const Monom& other) {
    *this = *this / other;
    return *this;
}

Monom& Monom::operator*=(double value) {
    _coef *= value;
    return *this;
}
Monom& Monom::operator/=(double value) {
    if (value == 0)
        throw std::logic_error("Division by zero");
    _coef /= value;
    return *this;
}

double Monom::value(double x, double y, double z) const {
    return _coef *
        pow(x, _px) *
        pow(y, _py) *
        pow(z, _pz);
}

std::ostream& operator<<(std::ostream& os, const Monom& m) {
    if (m._coef == 0) {
        os << "0";
        return os;
    }

    if (m._coef != 1 || (m._px == 0 && m._py == 0 && m._pz == 0)) {
        os << m._coef;
    }

    if (m._px != 0) {
        os << "x";
        if (m._px != 1) os << "^" << m._px;
    }

    if (m._py != 0) {
        os << "y";
        if (m._py != 1) os << "^" << m._py;
    }

    if (m._pz != 0) {
        os << "z";
        if (m._pz != 1) os << "^" << m._pz;
    }

    return os;
}
std::istream& operator>>(std::istream& is, Monom& m) {
    std::string input;
    is >> input;

    if (!is) return is;

    double coef = 1.0;
    int px = 0, py = 0, pz = 0;

    size_t i = 0;

    if (input[i] == '-') {
        coef = -1.0;
        ++i;
    }
    else if (input[i] == '+') {
        ++i;
    }


    size_t start = i;
    while (i < input.size() && (std::isdigit(input[i]) || input[i] == '.'))
        ++i;

    if (i > start) {
        coef *= std::stod(input.substr(start, i - start));
    }


    while (i < input.size()) {
        char var = input[i];
        if (var != 'x' && var != 'y' && var != 'z') {
            is.setstate(std::ios::failbit);
            return is;
        }

        ++i;

        int power = 1;

        if (i < input.size() && input[i] == '^') {
            ++i;
            size_t power_start = i;

            while (i < input.size() && std::isdigit(input[i]))
                ++i;

            if (power_start == i) {
                is.setstate(std::ios::failbit);
                return is;
            }

            power = std::stoi(input.substr(power_start, i - power_start));
        }

        if (power < 0) {
            is.setstate(std::ios::failbit);
            return is;
        }

        if (var == 'x') px = power;
        if (var == 'y') py = power;
        if (var == 'z') pz = power;
    }

    m = Monom(coef, px, py, pz);
    return is;
}



#endif  // LIB_MONOM_MONOM_H_
