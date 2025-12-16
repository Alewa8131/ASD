// Copyright 2025 Alewa8131

#pragma once
#include <iostream>
#include <cstdlib>
#include <ctime>
#include "../lib_matrix/matrix.h"

template<class T>
T find_minimum(Matrix<T>& A) {
    if (A.get_M() == 0 || A.get_N() == 0) {
        throw std::runtime_error("Matrix is empty.");
    }
    const int dx[] = { -1, 1, 0, 0 }, dy[] = { 0, 0, -1, 1 };
    size_t x = static_cast<size_t>(rand() % A.get_M());
    size_t y = static_cast<size_t>(rand() % A.get_N());
    while (true) {
        T value = A.at(x, y);
        size_t next_x = x;
        size_t next_y = y;
        T min_neighbor = value;

        for (int i = 0; i < 4; ++i) {
            int neighbor_x = x + dx[i];
            int neighbor_y = y + dy[i];

            if (neighbor_x >= 0 && neighbor_x < A.get_M() &&
                neighbor_y >= 0 && neighbor_y < A.get_N()) {

                T neighbor_value = A.at(neighbor_x, neighbor_y);

                if (neighbor_value < min_neighbor) {
                    min_neighbor = neighbor_value;
                    next_x = neighbor_x;
                    next_y = neighbor_y;
                }
            }
        }

        if (min_neighbor == value) {
            return value;
        }

        x = next_x;
        y = next_y;

        //std::cout << "Moving to: (" << x << ", " << y << ") with value " << value << std::endl;
    }
}
