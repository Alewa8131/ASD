// Copyright 2025 Alewa8131

#include <iostream>
#include <cstdlib>
#include <string>
#include "../lib_stack/stack.h"

void read_expression(const std::string& expr) {
    bool has_symbols = false;
    for (int i = 0; i < expr.size(); i++) {
        if (expr[i] != ' ' && expr[i] != '\t') {
            has_symbols = true;
            break;
        }
    }

    if (!has_symbols) {
        throw std::runtime_error("Empty expression");
    }


    Stack<char> brackets(expr.size());
    bool expect_operand = true;
    char prev = 0;

    for (int i = 0; i < expr.size(); i++) {
        char c = expr[i];

        if (c == ' ' || c == '\t') continue;


        if (c >= '0' && c <= '9') {
            if (!expect_operand) {
                throw std::runtime_error(
                    "Unexpected number at position " + std::to_string(i)
                );
            }

            // пропускаем все оставшиеся цифры числа
            while (i + 1 < expr.size() &&
                expr[i + 1] >= '0' && expr[i + 1] <= '9') {
                i++;
            }

            expect_operand = false;
        }


        else if ((c >= 'A' && c <= 'Z') ||
            (c >= 'a' && c <= 'z') ||
            (c == '_')) {

            if (!expect_operand) {
                throw std::runtime_error(
                    "Unexpected variable at position " + std::to_string(i)
                );
            }

            // пропускаем всё имя переменной
            while (i + 1 < expr.size()) {
                char n = expr[i + 1];
                if ((n >= 'A' && n <= 'Z') ||
                    (n >= 'a' && n <= 'z') ||
                    (n >= '0' && n <= '9') ||
                    (n == '_')) {
                    i++;
                }
                else {
                    break;
                }
            }

            expect_operand = false;
        }


        else if (c == '(' || c == '[' || c == '{') {
            brackets.push(c);
            expect_operand = true;
        }


        else if (c == ')' || c == ']' || c == '}') {
            if (expect_operand) {
                throw std::runtime_error(
                    "Missing operand before closing bracket at position " + std::to_string(i)
                );
            }

            if (brackets.is_empty()) {
                throw std::runtime_error(
                    "Extra closing bracket at position " + std::to_string(i)
                );
            }

            char open = brackets.top();
            brackets.pop();

            if ((open == '(' && c != ')') ||
                (open == '[' && c != ']') ||
                (open == '{' && c != '}')) {
                throw std::runtime_error(
                    "Bracket mismatch at position " + std::to_string(i)
                );
            }

            expect_operand = false;
        }


        else if (c == '+' || c == '-' || c == '*' || c == '/' || c == '^') {
            if (expect_operand) {
                throw std::runtime_error(
                    "Missing operand before operator at position " + std::to_string(i)
                );
            }
            expect_operand = true;
        }


        else {
            throw std::runtime_error(
                std::string("Unknown symbol '") + c +
                "' at position " + std::to_string(i)
            );
        }

        prev = c;
    }

    if (!brackets.is_empty()) {
        throw std::runtime_error("Missing closing bracket");
    }

    if (expect_operand && prev != 0) {
        throw std::runtime_error("Expression ends with operator");
    }
}
