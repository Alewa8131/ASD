// Copyright 2025 Alewa8131

#include <iostream>
#include <cstdlib>
#include <string>
#include "../lib_stack/stack.h"

bool is_letter(char c) {
    return (c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || c == '_';
}

bool is_digit(char c) {
    return (c >= '0' && c <= '9');
}

bool is_operator(char c) {
    return (c == '+' || c == '-' || c == '*' || c == '/' || c == '^');
}

bool is_open_bracket(char c) {
    return (c == '(' || c == '[' || c == '{');
}

bool is_close_bracket(char c) {
    return (c == ')' || c == ']' || c == '}');
}

bool brackets_match(char open, char close) {
    return (open == '(' && close == ')') ||
        (open == '[' && close == ']') ||
        (open == '{' && close == '}');
}

bool is_function_name(const std::string& s) {
    return (s == "sin" || s == "cos" || s == "tg" ||
        s == "ln" || s == "exp");
}

void throw_parse_error(const std::string& expr, int pos, const std::string& message) {
    std::string out = "Input expression: " + expr + "\n";
    out += std::string(18, ' ');

    for (int i = 0; i < pos; i++) out += ' ';
    out += "^\n";

    out += "Error in function 'Parser::parse()' at " + std::to_string(pos);
    out += " symbol: " + message;

    throw std::runtime_error(out);
}

void read_expression(const std::string& expr) {

    bool has_data = false;
    for (int i = 0; i < expr.size(); i++) {
        if (expr[i] != ' ' && expr[i] != '\t') {
            has_data = true;
            break;
        }
    }
    if (!has_data) {
        throw_parse_error(expr, 0, "empty expression");
    }

    Stack<char> brackets(expr.size());

    int abs_depth = 0;
    bool expect_operand = true;
    bool last_was_abs_open = false;
    bool abs_contains_operand = false;

    for (int i = 0; i < expr.size(); i++) {
        char c = expr[i];

        if (c == ' ' || c == '\t') continue;

        if (is_digit(c)) {
            if (!expect_operand) {
                throw_parse_error(expr, i, "unexpected number");
            }

            while (i + 1 < expr.size() && is_digit(expr[i + 1])) {
                i++;
            }

            expect_operand = false;
            abs_contains_operand = true;
            last_was_abs_open = false;
        }

        else if (is_letter(c)) {
            if (!expect_operand) {
                throw_parse_error(expr, i, "unexpected variable/function");
            }

            std::string word = "";
            while (i < expr.size() &&
                (is_letter(expr[i]) || is_digit(expr[i]))) {
                word += expr[i];
                i++;
            }
            i--;

            bool is_func = is_function_name(word);

            int j = i + 1;
            while (j < expr.size() && (expr[j] == ' ')) j++;

            if (j < expr.size() && is_open_bracket(expr[j])) {
                if (!is_func) {
                    throw_parse_error(expr, i, "unknown function '" + word + "'");
                }
            }

            expect_operand = false;
            abs_contains_operand = true;
            last_was_abs_open = false;
        }

        else if (is_open_bracket(c)) {
            brackets.push(c);
            expect_operand = true;
            last_was_abs_open = false;
        }

        else if (is_close_bracket(c)) {
            if (expect_operand) {
                throw_parse_error(expr, i, "missing operand before closing bracket");
            }

            if (brackets.is_empty()) {
                throw_parse_error(expr, i, "extra closing bracket");
            }

            char open = brackets.top();
            brackets.pop();

            if (!brackets_match(open, c)) {
                throw_parse_error(expr, i, "bracket type mismatch");
            }

            expect_operand = false;
            last_was_abs_open = false;
        }

        else if (c == '|') {
            if (expect_operand) {
                // открытие модуля
                abs_depth++;
                expect_operand = true;
            }
            else {
                // закрытие модуля
                if (abs_depth == 0) {
                    throw_parse_error(expr, i, "unexpected closing |");
                }
                abs_depth--;
                expect_operand = false;
            }
        }

        else if (is_operator(c)) {
            if (c == '-' && expect_operand) {
                expect_operand = true;
            }
            else {
                if (expect_operand) {
                    throw_parse_error(expr, i, "operator without left operand");
                }
                expect_operand = true;
            }
            last_was_abs_open = false;
        }

        else {
            throw_parse_error(expr, i, std::string("unknown symbol '") + c + "'");
        }
    }

    if (!brackets.is_empty()) {
        throw_parse_error(expr, expr.size(), "missing closing bracket");
    }

    if (abs_depth != 0) {
        throw_parse_error(expr, expr.size(), "missing closing |");
    }

    if (expect_operand) {
        throw_parse_error(expr, expr.size(), "expression ends incorrectly");
    }
}