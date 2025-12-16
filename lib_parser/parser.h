// Copyright 2025 Alewa8131

#ifndef LIB_PARSER_PARSER_H_
#define LIB_PARSER_PARSER_H_
#pragma once
#include <string>

#include "../lib_list/list.h"
#include "../lib_lexem/lexem.h"
#include "../algorithms/read_expression.h"

namespace Parser {

    int get_priority(char op) {
        switch (op) {
        case '+': case '-': return 1;
        case '*': case '/': return 2;
        case '^': return 3;
        default: return -1;
        }
    }

    List<Lexem> parse(const std::string& expr) {
        read_expression(expr);
        List<Lexem> result;

        enum class State {
            None,
            Number,
            Identifier
        };

        State state = State::None;
        std::string buffer;

        bool expect_operand = true;
        int abs_depth = 0;

        for (int i = 0; i <= expr.size(); i++) {
            char c = (i < expr.size()) ? expr[i] : '\0';

            if (state == State::Number) {
                if (is_digit(c)) {
                    buffer += c;
                    continue;
                }
                else {
                    result.push_back(
                        Lexem(buffer, TypeLexem::Constant, std::atof(buffer.c_str()))
                    );
                    buffer.clear();
                    state = State::None;
                    i--;
                    expect_operand = false;
                    continue;
                }
            }

            if (state == State::Identifier) {
                if (is_letter(c) || is_digit(c)) {
                    buffer += c;
                    continue;
                }
                else {
                    if (is_function_name(buffer)) {
                        result.push_back(
                            Lexem(buffer, TypeLexem::Function, DBL_MAX, 5)
                        );
                        expect_operand = true;
                    }
                    else {
                        result.push_back(
                            Lexem(buffer, TypeLexem::Variable)
                        );
                        expect_operand = false;
                    }
                    buffer.clear();
                    state = State::None;
                    i--;
                    continue;
                }
            }

            if (c == ' ' || c == '\t') {
                continue;
            }

            else if (is_digit(c)) {
                state = State::Number;
                buffer += c;
            }

            else if (is_letter(c)) {
                state = State::Identifier;
                buffer += c;
            }

            else if (is_open_bracket(c)) {
                result.push_back(
                    Lexem(std::string(1, c), TypeLexem::OpenBracket)
                );
                expect_operand = true;
            }

            else if (is_close_bracket(c)) {
                result.push_back(
                    Lexem(std::string(1, c), TypeLexem::ClosedBracket)
                );
                expect_operand = false;
            }

            else if (c == '|') {
                if (expect_operand) {
                    result.push_back(Lexem("|", TypeLexem::OpenedAbs));
                    abs_depth++;
                    expect_operand = true;
                }
                else {
                    result.push_back(Lexem("|", TypeLexem::ClosedAbs));
                    abs_depth--;
                    expect_operand = false;
                }
            }

            else if (is_operator(c) && c != '-') {
                result.push_back(
                    Lexem(std::string(1, c), TypeLexem::Operator, DBL_MAX, get_priority(c))
                );
                expect_operand = true;
            }

            else if (c == '-') {
                if (expect_operand) {
                    result.push_back(Lexem("-", TypeLexem::UnOperator, DBL_MAX, 4));
                }
                else {
                    result.push_back(Lexem("-", TypeLexem::Operator, DBL_MAX, get_priority('-')));
                    expect_operand = true;
                }
            }

            else if (c == '\0') {
                break;
            }
        }

        return result;
    }

    List<Lexem> to_rpn(const List<Lexem>& input) {
        List<Lexem> output;
        Stack<Lexem> st(256);


        for (List<Lexem>::Iterator it = input.begin(); it != input.end(); ++it) {
            const Lexem& lex = *it;

            if (lex.isConstant() || lex.isVariable()) {
                output.push_back(lex);
            }

            else if (lex.isFunction()) {
                st.push(lex);
            }

            else if (lex.isOpenBracket() || lex.isOpenedAbs()) {
                st.push(lex);
            }

            else if (lex.isClosedBracket()) {
                while (!st.is_empty() && !st.top().isOpenBracket()) {
                    output.push_back(st.top());
                    st.pop();
                }

                if (!st.is_empty() && st.top().isOpenBracket()) {
                    st.pop();
                }

                if (!st.is_empty() && st.top().isFunction()) {
                    output.push_back(st.top());
                    st.pop();
                }
            }

            else if (lex.isClosedAbs()) {
                while (!st.is_empty() && !st.top().isOpenedAbs()) {
                    output.push_back(st.top());
                    st.pop();
                }

                if (!st.is_empty() && st.top().isOpenedAbs()) {
                    st.pop();
                }

                output.push_back(Lexem("abs", TypeLexem::Function, DBL_MAX, 5));
            }

            else if (lex.isUnOperator()) {
                st.push(lex);
            }

            else if (lex.isOperator()) {
                if (lex.name == "+" || lex.name == "-" || lex.name == "*" || lex.name == "/") {
                    while (!st.is_empty() &&
                        (st.top().isOperator() || st.top().isUnOperator() || st.top().isFunction()) &&
                        st.top().priority >= lex.priority) {
                        output.push_back(st.top());
                        st.pop();
                    }
                }

                else if (lex.name == "^") {
                    while (!st.is_empty() &&
                        (st.top().isOperator() || st.top().isUnOperator() || st.top().isFunction()) &&
                        st.top().priority > lex.priority) {
                        output.push_back(st.top());
                        st.pop();
                    }
                }
                st.push(lex);
            }
        }

        while (!st.is_empty()) {
            output.push_back(st.top());
            st.pop();
        }

        return output;
    }
}

#endif  // LIB_PARSER_PARSER_H_
