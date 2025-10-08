#include "../algorithms/local_minimum.h"
#include "../lib_point/point.h"

int main() {
    std::cout << "--- Minimum ---" << std::endl;
    Matrix<int> A({
        {3, 1, 2},
        {5, 8, 4},
        {7, 6, 9}
        });
    std::cout << A << std::endl;

    for (int i = 0; i < A.get_M(); ++i) {
        for (int j = 0; j < A.get_N(); ++j) {
            Point pos(i, j);
            int res = find_minimum(A, pos);
            std::cout << res << std::endl;
        }
    }

    return 0;

}