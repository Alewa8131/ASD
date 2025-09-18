// Copyright 2025 Alewa8131


//#define CIRCLE
#ifdef CIRCLE

#include <iostream>
#include <iomanip>
#include "../lib_circle/circle.h"

int check_circle_position(Circle& c1, Circle& c2) {
    double distance = c1.get_distance(c2);
    double sum_radius = c1.get_radius() + c2.get_radius();
    double diff_radius = std::abs(c1.get_radius() - c2.get_radius());

    if (distance == 0 && c1.get_radius() == c2.get_radius()) {
        return 0; // "The objects match."
    }
    else if (distance < diff_radius) {
        return 1; // "One object is nested inside another and does not touch."
    }
    else if (distance == diff_radius) {
        return 2; // "The objects touch in an internal way."
    }
    else if (distance < sum_radius) {
        return 3; // "The objects intersect."
    }
    else if (distance == sum_radius) {
        return 4; // "The objects touch in an external way."
    }
    else {
        return 5; // "The objects are separate."
    }
}

void print_position(int code) {
    switch (code) {
    case 0:
        std::cout << "The objects match." << std::endl;
        break;
    case 1:
        std::cout << "One object is nested inside another and does not touch." << std::endl;
        break;
    case 2:
        std::cout << "The objects touch in an internal way." << std::endl;
        break;
    case 3:
        std::cout << "The circles intersect." << std::endl;
        break;
    case 4:
        std::cout << "The objects touch in an external way." << std::endl;
        break;
    case 5:
        std::cout << "The circles are separate." << std::endl;
        break;
    }
}

int main() {
    std::cout << "--- Circle Position Example ---" << std::endl;

    Circle c1(0, 0, 5);
    Circle c2(0, 0, 5);
    std::cout << "Example 1 (Identical):" << std::endl;
    print_position(check_circle_position(c1, c2));
    std::cout << std::endl;

    Circle c3(0, 0, 10);
    Circle c4(2, 0, 5);
    std::cout << "Example 2 (Contained):" << std::endl;
    print_position(check_circle_position(c3, c4));
    std::cout << std::endl;

    Circle c5(0, 0, 10);
    Circle c6(5, 0, 5);
    std::cout << "Example 3 (Internal touch):" << std::endl;
    print_position(check_circle_position(c5, c6));
    std::cout << std::endl;

    Circle c7(0, 0, 5);
    Circle c8(7, 0, 5);
    std::cout << "Example 4 (Intersecting):" << std::endl;
    print_position(check_circle_position(c7, c8));
    std::cout << std::endl;

    Circle c9(0, 0, 5);
    Circle c10(10, 0, 5);
    std::cout << "Example 5 (External touch):" << std::endl;
    print_position(check_circle_position(c9, c10));
    std::cout << std::endl;

    Circle c11(0, 0, 5);
    Circle c12(12, 0, 5);
    std::cout << "Example 6 (Separate):" << std::endl;
    print_position(check_circle_position(c11, c12));
    std::cout << std::endl;

    return 0;
}

#endif  // CIRCLE


#define MATRIX
#ifdef MATRIX

#include <iostream>
#include <iomanip>
#include "../lib_matrix/matrix.h"

int main() {
    std::cout << "--- Matrix ---" << std::endl;
    Matrix<int> Matr;
    int m, n;

    std::cout << "Enter a value for M: ";
    std::cin >> m;
    Matr.set_M(m);
    std::cout << "M = " << Matr.get_M() << std::endl;

    std::cout << "Enter a value for N: ";
    std::cin >> n;
    Matr.set_N(n);
    std::cout << "N = " << Matr.get_N() << std::endl;

    int a;


    for (int i = 1; i <= m; i++) {
        std::cout << "Enter the numbers of line " << i <<" in the amount of " << m << " pieces: ";
        for (int j = 1; j <= n; j++) {
            std::cin >> a;
        }
    }

    return 0;
}

#endif  // MATRIX