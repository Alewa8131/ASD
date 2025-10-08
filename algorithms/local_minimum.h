#include <iostream>
#include <iomanip>
#include "../lib_matrix/matrix.h"
#include "../lib_tvector/tvector.h"
#include "../lib_point/point.h"


template<class T>
T find_minimum(Matrix<T>& A, Point pos) {
    int x = pos.get_coord_x(), y = pos.get_coord_y();
    const int dx[] = { -1, 1, 0, 0 }, dy[] = { 0, 0, -1, 1 };
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

        std::cout << "Moving to: (" << x << ", " << y << ") with value " << value << std::endl;
    }
}