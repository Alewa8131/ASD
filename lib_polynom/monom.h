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
    Monom(double coef);
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

Monom::Monom(double coef = 0.0) : _coef(coef) {
    for (int i = 0; i < vars_count; i++) {
        _powers[i] = 0;
    }
}
Monom::Monom(double coef, std::initializer_list<int> powers)
    : _coef(coef) {
    if (powers.size() != vars_count)
        throw std::invalid_argument("Invalid number of powers");

    int i = 0;
    for (int p : powers) {
        if (p < 0)
            throw std::invalid_argument("Negative power is not allowed");

        _powers[i++] = p;
    }
}
Monom::Monom(const Monom& other)
    : _coef(other._coef)
{
    for (int i = 0; i < vars_count; ++i)
        _powers[i] = other._powers[i];
}

Monom& Monom::operator=(const Monom& other) {
    if (this != &other) {
        _coef = other._coef;
        for (int i = 0; i < vars_count; ++i)
            _powers[i] = other._powers[i];
    }
    return *this;
}
bool Monom::operator==(const Monom & other) const {
    for (int i = 0; i < vars_count; ++i)
        if (_powers[i] != other._powers[i])
            return false;
    return true;
}
bool Monom::operator!=(const Monom& other) const {
    return !(*this == other);
}

bool Monom::operator<(const Monom& other) const {
    for (int i = 0; i < vars_count; ++i) {
        if (_powers[i] != other._powers[i])
            return _powers[i] > other._powers[i];
    }
    return false;
}

Monom Monom::operator+(const Monom& other) const {
    if (*this != other)
        throw std::logic_error("Monoms are not similar");
    Monom result(*this);
    result._coef += other._coef;
    return result;
}
Monom Monom::operator-(const Monom& other) const {
    if (*this != other)
        throw std::logic_error("Monoms are not similar");
    Monom result(*this);
    result._coef -= other._coef;
    return result;
}
Monom Monom::operator*(const Monom& other) const {
    Monom result(_coef * other._coef);

    for (int i = 0; i < vars_count; ++i)
        result._powers[i] = _powers[i] + other._powers[i];

    return result;
}
Monom Monom::operator/(const Monom& other) const {
    if (other._coef == 0)
        throw std::logic_error("Division by zero monom");

    Monom result(_coef / other._coef);

    for (int i = 0; i < vars_count; ++i) {
        int p = _powers[i] - other._powers[i];
        if (p < 0)
            throw std::logic_error("Negative power after division");
        result._powers[i] = p;
    }

    return result;
}

Monom Monom::operator*(double value) const {
    Monom result(*this);
    result._coef *= value;
    return result;
}
Monom Monom::operator/(double value) const {
    if (value == 0)
        throw std::logic_error("Division by zero");

    Monom result(*this);
    result._coef /= value;
    return result;
}
Monom Monom::operator-() const {
    Monom result(*this);
    result._coef = -_coef;
    return result;
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
    double vars[vars_count] = { x, y, z };

    double result = _coef;
    for (int i = 0; i < vars_count; ++i)
        result *= std::pow(vars[i], _powers[i]);

    return result;
}

std::ostream& operator<<(std::ostream& os, const Monom& m) {
    if (m._coef == 0) {
        os << "0";
        return os;
    }

    bool is_constant = true;
    for (int i = 0; i < vars_count; ++i)
        if (m._powers[i] != 0)
            is_constant = false;

    if (m._coef != 1 || is_constant)
        os << m._coef;

    const char vars[vars_count] = { 'x','y','z' };

    for (int i = 0; i < vars_count; ++i) {
        if (m._powers[i] != 0) {
            os << vars[i];
            if (m._powers[i] != 1)
                os << "^" << m._powers[i];
        }
    }

    return os;
}

std::istream& operator>>(std::istream& is, Monom& m) {
    std::string input;
    is >> input;
    if (!is) return is;

    double coef = 1.0;
    int powers[vars_count] = { 0 };

    size_t i = 0;

    if (input[i] == '-') { coef = -1.0; ++i; }
    else if (input[i] == '+') { ++i; }

    size_t start = i;
    while (i < input.size() && (std::isdigit(input[i]) || input[i] == '.'))
        ++i;

    if (i > start)
        coef *= std::stod(input.substr(start, i - start));

    const char vars[vars_count] = { 'x','y','z' };

    while (i < input.size()) {
        char var = input[i++];
        int index = -1;

        for (int j = 0; j < vars_count; ++j)
            if (var == vars[j])
                index = j;

        if (index == -1) {
            is.setstate(std::ios::failbit);
            return is;
        }

        int power = 1;

        if (i < input.size() && input[i] == '^') {
            ++i;
            size_t pstart = i;

            while (i < input.size() && std::isdigit(input[i]))
                ++i;

            if (pstart == i) {
                is.setstate(std::ios::failbit);
                return is;
            }

            power = std::stoi(input.substr(pstart, i - pstart));
        }

        if (power < 0) {
            is.setstate(std::ios::failbit);
            return is;
        }

        powers[index] = power;
    }

    m = Monom(coef, { powers[0], powers[1], powers[2] });
    return is;
}



#endif  // LIB_MONOM_MONOM_H_
