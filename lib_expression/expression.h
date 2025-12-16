// Copyright 2025 Alewa8131

#ifndef LIB_EXPRESSION_EXPRESSION_H_
#define LIB_EXPRESSION_EXPRESSION_H_
#pragma once
#include <string>
#include <stdexcept>
#include <cmath>

#include "../lib_parser/parser.h"


class Expression {
    std::string _source;
    List<Lexem> _lexems;
    List<Lexem> _rpn;
    List<Lexem> _variables;

public:
    Expression(const std::string& expr);

    void parse();
    void build_rpn();

    void set_variable(const std::string& name, double value);

    double calculate() const;

    const std::string& get_source() const;
    const List<Lexem>& get_lexems() const;
    const List<Lexem>& get_rpn() const;
    const List<Lexem>& Expression::get_variables() const;

private:
    void init_variables_from_lexems();
};

Expression::Expression(const std::string& expr)
    : _source(expr) {
    parse();
    init_variables_from_lexems();
    build_rpn();
}

void Expression::parse() {
    _lexems = Parser::parse(_source);
}

void Expression::build_rpn() {
    _rpn = Parser::to_rpn(_lexems);
}

void Expression::set_variable(const std::string& name, double value) {
    bool found = false;

    for (List<Lexem>::Iterator it = _variables.begin(); it != _variables.end(); ++it) {
        if ((*it).name == name) {
            (*it).value = value;
            found = true;
            break;
        }
    }

    if (!found) {
        _variables.push_back(Lexem(name, TypeLexem::Variable, value));
    }
}

void Expression::init_variables_from_lexems() {
    _variables = List<Lexem>();

    for (List<Lexem>::Iterator it = _lexems.begin(); it != _lexems.end(); ++it) {
        if ((*it).isVariable()) {
            this->set_variable((*it).name, DBL_MAX);
        }
    }
}


double Expression::calculate() const {
    if (_rpn.size() == 0)
        throw std::runtime_error("RPN is empty. Call build_rpn().");

    Stack<double> st(_rpn.size());

    for (auto it = _rpn.begin(); it != _rpn.end(); ++it) {
        const Lexem& lex = *it;


        if (lex.isConstant()) {
            st.push(lex.value);
        }


        else if (lex.isVariable()) {
            bool found = false;

            for (auto v = _variables.begin(); v != _variables.end(); ++v) {
                if ((*v).name == lex.name) {
                    st.push((*v).value);
                    found = true;
                    break;
                }
            }

            if (!found)
                throw std::runtime_error("Variable not set: " + lex.name);
        }


        else if (lex.isOperator()) {
            if (st.is_empty())
                throw std::runtime_error("Not enough operands for operator " + lex.name);
            double b = st.top(); st.pop();

            if (st.is_empty())
                throw std::runtime_error("Not enough operands for operator " + lex.name);
            double a = st.top(); st.pop();

            if (lex.name == "+")       st.push(a + b);
            else if (lex.name == "-")  st.push(a - b);
            else if (lex.name == "*")  st.push(a * b);
            else if (lex.name == "/") {
                if (b == 0.0)
                    throw std::runtime_error("Division by zero");
                st.push(a / b);
            }
            else if (lex.name == "^")  st.push(std::pow(a, b));
            else
                throw std::runtime_error("Unknown operator: " + lex.name);
        }


        else if (lex.isUnOperator()) {
            if (st.is_empty())
                throw std::runtime_error("Not enough operands for unary operator");

            double a = st.top(); st.pop();

            if (lex.name == "-")
                st.push(-a);
            else
                throw std::runtime_error("Unknown unary operator: " + lex.name);
        }


        else if (lex.isFunction()) {
            if (st.is_empty())
                throw std::runtime_error("Not enough operands for function: " + lex.name);

            double a = st.top(); st.pop();

            if (lex.name == "sin") st.push(std::sin(a));
            else if (lex.name == "cos") st.push(std::cos(a));
            else if (lex.name == "tg")  st.push(std::tan(a));
            else if (lex.name == "ln") {
                if (a <= 0.0)
                    throw std::runtime_error("ln(x): x must be > 0");
                st.push(std::log(a));
            }
            else if (lex.name == "exp") st.push(std::exp(a));
            else if (lex.name == "abs") st.push(std::fabs(a));
            else
                throw std::runtime_error("Unknown function: " + lex.name);
        }

        else {
            throw std::runtime_error("Invalid lexem in RPN");
        }
    }

    if (st.is_empty())
        throw std::runtime_error("Invalid expression: empty result stack");

    double result = st.top();
    st.pop();

    if (!st.is_empty())
        throw std::runtime_error("Invalid expression: extra values in stack");

    return result;
}

const std::string& Expression::get_source() const {
    return _source;
}

const List<Lexem>& Expression::get_lexems() const {
    return _lexems;
}

const List<Lexem>& Expression::get_rpn() const {
    return _rpn;
}

const List<Lexem>& Expression::get_variables() const {
    return _variables;
}

#endif  // LIB_EXPRESSION_EXPRESSION_H_
