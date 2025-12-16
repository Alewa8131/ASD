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


//#define MATRIX
#ifdef MATRIX

#include <iostream>
#include <iomanip>
#include <exception>

#include "../lib_matrix/matrix.h"
#include "../lib_trianglematrix/trianglematrix.h"


template<class T>
void run_matrix_operations(T& A, T& B, T& C) {
    int choice = -1;
    while (choice != 0) {
        std::cout << "\nChoose an operation:" << std::endl;
        std::cout << "1. Input Matrix A" << std::endl;
        std::cout << "2. Input Matrix B" << std::endl;
        std::cout << "3. Add A + B" << std::endl;
        std::cout << "4. Subtract A - B" << std::endl;
        std::cout << "5. Multiply A by a scalar" << std::endl;
        std::cout << "6. Calculate a determinant" << std::endl;
        std::cout << "7. Output Matrix A" << std::endl;
        std::cout << "8. Output Matrix B" << std::endl;
        std::cout << "9. Output Result C" << std::endl;
        std::cout << "0. Exit" << std::endl;
        std::cout << "Your choice: ";
        std::cin >> choice;

        switch (choice) {
        case 1:
            std::cin >> A;
            break;
        case 2:
            std::cin >> B;
            break;
        case 3:
            C = A + B;
            std::cout << "Addition operation started. Result stored in C." << std::endl;
            break;
        case 4:
            C = A - B;
            std::cout << "Subtraction operation started. Result stored in C." << std::endl;
            break;
        case 5:
            int scalar;
            std::cout << "Enter a scalar value: ";
            std::cin >> scalar;
            C = A * scalar;
            std::cout << "Scalar multiplication started. Result stored in C." << std::endl;
            break;
        case 6:
            int det_choice;
            std::cout << "Choose a matrix to calculate the determinant for:" << std::endl;
            if (A.get_M() == A.get_N()) {
                std::cout << "1. Matrix A" << std::endl;
            }
            if (B.get_M() == B.get_N()) {
                std::cout << "2. Matrix B" << std::endl;
            }
            if (C.get_M() == C.get_N()) {
                std::cout << "3. Result C" << std::endl;
            }
            std::cout << "0. Back" << std::endl;
            std::cout << "Your choice: ";
            std::cin >> det_choice;

            if (det_choice == 0) {
                continue;
            }
            else if (det_choice == 1 && A.get_M() == A.get_N()) {
                std::cout << "Determinant of A: " << A.determinant() << std::endl;
            }
            else if (det_choice == 2 && B.get_M() == B.get_N()) {
                std::cout << "Determinant of B: " << B.determinant() << std::endl;
            }
            else if (det_choice == 3 && C.get_M() == C.get_N()) {
                std::cout << "Determinant of C: " << C.determinant() << std::endl;
            }
            else {
                std::cout << "Error: Invalid choice or selected matrix is not square." << std::endl;
            }
            break;
        case 7:
            std::cout << A;
            break;
        case 8:
            std::cout << B;
            break;
        case 9:
            std::cout << C;
            break;
        case 0:
            std::cout << "Exiting..." << std::endl;
            break;
        default:
            std::cout << "Invalid choice. Please try again." << std::endl;
        }
    }
}

int main() {
    std::cout << "--- Matrix ---" << std::endl;
    int matrix_type_choice;
    std::cout << "Select the type of matrix to work with:" << std::endl;
    std::cout << "1. Regular Matrix" << std::endl;
    std::cout << "2. Triangular Matrix" << std::endl;
    std::cout << "Your choice: ";
    std::cin >> matrix_type_choice;

    if (matrix_type_choice == 1) {
        Matrix<int> C;
        int m, n;
        std::cout << "Enter dimensions for Matrix A (M N): ";
        std::cin >> m >> n;
        Matrix<int> A(m, n);

        std::cout << "Enter dimensions for Matrix B (M N): ";
        std::cin >> m >> n;
        Matrix<int> B(m, n);
        run_matrix_operations(A, B, C);
    }
    else if (matrix_type_choice == 2) {
            TriangleMatrix<int> T_Result;
            int n;
            std::cout << "Enter dimension N for Triangular Matrix T1: ";
            std::cin >> n;
            TriangleMatrix<int> T1(n);
            std::cout << "Enter dimension N for Triangular Matrix T2: ";
            std::cin >> n;
            TriangleMatrix<int> T2(n);
            run_matrix_operations(T1, T2, T_Result);
        }
    else {
        std::cout << "Invalid matrix type selected." << std::endl;
    }

    return 0;
}

#endif  // MATRIX

#define EXPRESSION
#ifdef EXPRESSION

#include <iostream>
#include <iomanip>
#include <string>
#include <exception>

#include "../lib_tvector/tvector.h"
#include "../lib_expression/expression.h"

struct ExpressionItem {
    int id = 0;
    Expression expr = Expression("0");

    ExpressionItem() = default;
    ExpressionItem(int _id, const std::string& s)
        : id(_id), expr(s) {}
};

void print_table(const TVector<ExpressionItem>& items) {
    std::cout << "\n+--------------------------------------------------------------------------------+\n";
    std::cout << "| ID  | EXPRESSION                                   | VARIABLES VALUES          |\n";
    std::cout << "+--------------------------------------------------------------------------------+\n";

    for (auto it = items.begin(); it != items.end(); ++it) {
        std::cout << "| "
            << std::setw(3) << it->id << " | "
            << std::setw(44) << std::left << it->expr.get_source() << " | ";

        std::string vars;
        for (auto v = it->expr.get_variables().begin(); v != it->expr.get_variables().end(); ++v) {
            vars += (*v).name + " = ";
            if ((*v).value == DBL_MAX) vars += "?";
            else {
                vars += std::to_string((*v).value);
                vars.pop_back();
                vars.pop_back();
                vars.pop_back();
                vars.pop_back();
            }
            vars += ", ";
        }
        if (!vars.empty()) vars.pop_back(), vars.pop_back();

        std::cout << std::setw(26) << vars;
        std::cout << "|\n";
    }

    std::cout << "+--------------------------------------------------------------------------------+\n";
}

int find_expression_index(const TVector<ExpressionItem>& vec, int id) {
    int idx = 0;
    for (auto it = vec.begin(); it != vec.end(); ++it, ++idx) {
        if (it->id == id)
            return idx;
    }
    return -1;
}


int main() {
    TVector<ExpressionItem> expressions;
    int next_id = 1;

    int choice = -1;

    while (choice != 0) {
        print_table(expressions);

        std::cout << "\nMenu:\n";
        std::cout << "1. Create new expression\n";
        std::cout << "2. Delete expression\n";
        std::cout << "3. Set variables\n";
        std::cout << "4. Calculate expression value\n";
        std::cout << "0. Exit\n";
        std::cout << "Your choice: ";
        std::cin >> choice;
        std::cin.ignore();

        try {
            switch (choice) {
            case 1: {
                std::string expr;
                std::cout << "Enter expression: ";
                std::getline(std::cin, expr);

                try {
                    ExpressionItem item(next_id, expr);
                    expressions.push_back(item);
                    ++next_id;
                    std::cout << "Expression added successfully.\n";
                }
                catch (const std::exception& e) {
                    std::cout << "" << e.what() << "\n";
                }

                break;
            }

            case 2: {
                int id;
                std::cout << "Enter expression ID to delete: ";
                std::cin >> id;

                int idx = find_expression_index(expressions, id);
                if (idx >= 0) {
                    expressions.erase(idx);
                    std::cout << "Expression deleted.\n";
                }
                else {
                    std::cout << "Expression not found.\n";
                }
                break;
            }

            case 3: {
                int id;
                std::cout << "Enter expression ID: ";
                std::cin >> id;

                int idx = find_expression_index(expressions, id);
                if (idx < 0) {
                    std::cout << "Expression not found.\n";
                    break;
                }

                Expression& expr = expressions[idx].expr;
                auto& vars = expr.get_variables();

                std::cout << "Setting values for " << vars.size() << " variables.\n";

                for (List<Lexem>::Iterator it = vars.begin(); it != vars.end(); ++it) {
                    double value = 0;
                    bool valid = false;

                    while (!valid) {
                        std::string input;
                        std::cout << (*it).name << " = ";
                        std::cin >> input;

                        valid = true;
                        int dot_count = 0;

                        for (char c : input) {
                            if (c == '.') {
                                dot_count++;
                                if (dot_count > 1) {
                                    valid = false;
                                    break;
                                }
                            }
                            else if (!is_digit(c)) {
                                valid = false;
                                break;
                            }
                        }

                        if (valid) {
                            try { value = std::stod(input); }
                            catch (...) { valid = false; }
                        }

                        if (!valid) {
                            std::cout << "Invalid input. Please enter a number.\n";
                        }
                    }

                    expr.set_variable((*it).name, value);
                }

                std::cout << "Variables updated.\n";
                break;
            }

            case 4: {
                int id;
                std::cout << "Enter expression ID: ";
                std::cin >> id;

                int idx = find_expression_index(expressions, id);
                if (idx < 0) {
                    std::cout << "Expression not found.\n";
                    break;
                }

                Expression& expr = expressions[idx].expr;

                for (auto it = expr.get_variables().begin(); it != expr.get_variables().end(); ++it) {
                    if ((*it).value == DBL_MAX) {
                        std::cout << "Enter value for variable '" << (*it).name << "': ";
                        std::cin >> (*it).value;
                    }
                }

                try {
                    double result = expr.calculate();
                    std::cout << "Result = " << result << "\n";
                }
                catch (const std::exception& e) {
                    std::cout << "Error: " << e.what() << "\n";
                }

                break;
            }

            case 0:
                std::cout << "Exiting...\n";
                break;

            default:
                std::cout << "Invalid choice. Try again.\n";
            }
        }
        catch (const std::exception& e) {
            std::cout << "\nERROR:\n" << e.what() << "\n";
        }
    }

    return 0;
}
#endif  // EXPRESSION
