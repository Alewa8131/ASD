// Copyright 2026 Alewa8131

#include "../lib_polynom/polynom.h"

Polynom::Polynom() = default;

Polynom::Polynom(const Monom monom) {
    if (monom != Monom(0.0))
        _polynom.push_back(monom);
}

Polynom::Polynom(std::string str) {
    std::string s;
    for (char c : str)
        if (!std::isspace(static_cast<unsigned char>(c)))
            s += c;

    if (s.empty())
        return;

    size_t i = 0;

    while (i < s.size())
    {
        int sign = 1;

        if (s[i] == '+') {
            ++i;
        }
        else if (s[i] == '-') {
            sign = -1;
            ++i;
        }


        double coef = 0.0;
        bool coef_specified = false;

        size_t start = i;

        while (i < s.size() && (std::isdigit(s[i]) || s[i] == '.'))
            ++i;

        if (start != i) {
            coef = std::stod(s.substr(start, i - start));
            coef_specified = true;
        }
        else {
            coef = 1.0;
        }
        coef *= sign;


        int px = 0, py = 0, pz = 0;

        while (i < s.size() && (s[i] == 'x' || s[i] == 'y' || s[i] == 'z'))
        {
            char var = s[i++];
            int power = 1;

            if (i < s.size() && s[i] == '^') {
                ++i;
                size_t pstart = i;
                while (i < s.size() && std::isdigit(s[i]))
                    ++i;

                if (pstart == i)
                    throw std::runtime_error("Invalid power format");

                power = std::stoi(s.substr(pstart, i - pstart));
            }

            if (var == 'x') px += power;
            if (var == 'y') py += power;
            if (var == 'z') pz += power;
        }

        if (!coef_specified && px == 0 && py == 0 && pz == 0)
            coef = 1.0 * sign;

        *this += Monom(coef, { px, py, pz });
    }
}

Polynom Polynom::operator+(const Polynom& other) const {
    Polynom result(*this);
    result += other;
    return result;
}
Polynom Polynom::operator+(const Monom& m) const {
    Polynom result(*this);
    result += m;
    return result;
}
Polynom& Polynom::operator+=(const Polynom& other) {
    for (auto it = other._polynom.begin(); it != other._polynom.end(); ++it)
        *this += *it;
    return *this;
}
Polynom& Polynom::operator+=(const Monom& m) {

    if (m.value(1, 1, 1) == 0)
        return *this;

    Node<Monom>* prev = nullptr;
    Node<Monom>* curr = _polynom.head();

    while (curr) {

        if (curr->_value == m) {
            curr->_value += m;

            if (curr->_value.value(1, 1, 1) == 0)
                _polynom.erase(curr);

            return *this;
        }

        if (curr->_value < m) {

            if (prev == nullptr)
                _polynom.push_front(m);
            else
                _polynom.insert(prev, m);

            return *this;
        }

        prev = curr;
        curr = curr->_next;
    }

    _polynom.push_back(m);
    return *this;
}

Polynom Polynom::operator-(const Polynom& other) const {
    Polynom result(*this);
    result -= other;
    return result;
}
Polynom Polynom::operator-(const Monom& m) const {
    Polynom result(*this);
    result += -m;
    return result;
}
Polynom& Polynom::operator-=(const Polynom& other) {
    for (auto it = other._polynom.begin(); it != other._polynom.end(); ++it)
        *this += -(*it);
    return *this;
}
Polynom& Polynom::operator-=(const Monom& m) {
    *this += -m;
    return *this;
}
Polynom Polynom::operator-() const {
    Polynom result;
    for (auto it = _polynom.begin(); it != _polynom.end(); ++it)
        result += -(*it);
    return result;
}

Polynom Polynom::operator*(const Polynom& other) const {
    Polynom result;
    for (auto it1 = _polynom.begin(); it1 != _polynom.end(); ++it1)
        for (auto it2 = other._polynom.begin(); it2 != other._polynom.end(); ++it2)
            result += (*it1) * (*it2);
    return result;
}
Polynom Polynom::operator*(const Monom& m) const {
    Polynom result;

    for (auto it = _polynom.begin(); it != _polynom.end(); ++it)
        result += (*it) * m;

    return result;
}

Polynom& Polynom::operator*=(const Polynom& other) {
    Polynom result;
    for (auto it1 = _polynom.begin(); it1 != _polynom.end(); ++it1)
        for (auto it2 = other._polynom.begin(); it2 != other._polynom.end(); ++it2)
            result += (*it1) * (*it2);

    *this = result;
    return *this;
}
Polynom& Polynom::operator*=(const Monom& m) {

    if (m.value(1, 1, 1) == 0) {
        _polynom = List<Monom>();
        return *this;
    }

    Polynom result;

    for (auto it = _polynom.begin(); it != _polynom.end(); ++it)
        result += (*it) * m;

    *this = result;
    return *this;
}


double Polynom::value(double x, double y, double z) const {
    double result = 0.0;

    for (auto it = _polynom.begin(); it != _polynom.end(); ++it)
        result += (*it).value(x, y, z);

    return result;
}

void Polynom::normalize() {

    auto node = _polynom.head();

    while (node) {
        auto next = node->_next;

        if (node->_value.value(1, 1, 1) == 0) {
            _polynom.erase(node);
        }

        node = next;
    }

    for (auto n1 = _polynom.head(); n1; n1 = n1->_next) {
        for (auto n2 = n1->_next; n2; n2 = n2->_next) {
            if (n2->_value < n1->_value) {
                Monom tmp = n1->_value;
                n1->_value = n2->_value;
                n2->_value = tmp;
            }
        }
    }
}
