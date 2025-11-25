// Copyright 2025 Alewa8131

#include <iostream>
#include "../lib_list/list.h"

template <class T>
bool is_looped1(List<T> &list) {
    if (list.size() == 0) return false;
    if (list.size() == 1) {
        if (list.head()->_next == nullptr) {
            return false;
        }
        else if (list.head()->_next == list.head()) {
            return true;
        }
    }
    List<T>::Iterator turtle = list.begin();
    List<T>::Iterator bunny = list.begin();

    while (true) {
        turtle++;

        bunny++;
        bunny++;

        if (turtle == bunny) {
            if (turtle == list.end()) {
                return false;
            } else {
                return true;
            }
        }
    }
    return false;
}

template <class T>
bool is_looped2(List<T>& list) {
    Node<T>* prev = nullptr;
    Node<T>* cur = list.head();

    while (cur) {
        Node<T>* next = cur->_next;

        if (next == list.head()) return true;

        cur->_next = prev;
        prev = cur;
        cur = next;
    }

    return false;
}



template <class T>
typename Node<T>* find_list_loop_break_point(List<T>& list) {
    if (list.size() < 1) return nullptr;

    Node<T>* turtle = list.head();
    Node<T>* bunny = list.head();

    while (bunny != nullptr && bunny->_next != nullptr) {
        turtle = turtle->_next;
        bunny = bunny->_next->_next;

        if (turtle == bunny) {  // цикл найден
            break;
        }
    }

    if (bunny == nullptr || bunny->_next == nullptr) {
        return nullptr;
    }

    turtle = list.head();

    while (turtle != bunny) {  // если встретились снова, значит это мето начала цикла
        turtle = turtle->_next;
        bunny = bunny->_next;
    }

    return turtle;
}
