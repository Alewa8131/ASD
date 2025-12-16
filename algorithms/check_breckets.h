// Copyright 2025 Alewa8131

#pragma once
#include <iostream>
#include <cstdlib>
#include "../lib_stack/stack.h"

bool check_breckets(std::string str) {
    Stack<int> stack(str.size());

    for (int i = 0; i < str.size(); i++) {
        if (str[i] == '(' || str[i] == '[' || str[i] == '{') {
            stack.push(str[i]);
            continue;
        }

        if (str[i] != ')' && str[i] != ']' && str[i] != '}') {
            continue;
        }

        if (stack.is_empty()) {
            return false;
        }
        else if (str[i] == ')' && stack.top() == '(') {
            stack.pop();
        }
        else  if (str[i] == ']' && stack.top() == '[') {
            stack.pop();
        }
        else  if (str[i] == '}' && stack.top() == '{') {
            stack.pop();
        }
        else
            return false;
       
    }
    return stack.is_empty();
    
}
