// Copyright 2025 Alewa8131

#include <iostream>
#include <cstdlib>
#include <string>
#include "../lib_stack/stack.h"

bool is_letter(char c);
bool is_digit(char c);
bool is_operator(char c);
bool is_open_bracket(char c);
bool is_close_bracket(char c);
bool brackets_match(char a, char b);
bool is_function_name(const std::string& name);
void throw_parse_error(const std::string& expr, int pos, const std::string& msg);
void read_expression(const std::string& expr);
