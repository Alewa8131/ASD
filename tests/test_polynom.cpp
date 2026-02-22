// Copyright 2026 Alewa8131

#include <gtest/gtest.h>
#include <stdexcept>
#include "../lib_polynom/polynom.h"


TEST(PolynomTest, DefaultConstructor_IsZero) {
    Polynom p;
    EXPECT_DOUBLE_EQ(p.value(1, 2, 3), 0.0);
}

TEST(PolynomTest, Construct_FromMonom) {
    Monom m(5, { 1,0,0 }); // 5x
    Polynom p(m);

    EXPECT_DOUBLE_EQ(p.value(2, 1, 1), 10.0);
}


TEST(PolynomTest, Parse_Constant) {
    Polynom p("-5");
    EXPECT_DOUBLE_EQ(p.value(10, 10, 10), -5);
}

TEST(PolynomTest, Parse_SimplePolynomial) {
    Polynom p("x^2 + 2y^3z - 4z^5");

    double val = p.value(2, 3, 1);
    double expected = 4 + 2 * 27 * 1 - 4 * 1;

    EXPECT_DOUBLE_EQ(val, expected);
}

TEST(PolynomTest, Parse_WithFloats) {
    Polynom p("x^2yz^3 + 0.4xyz - 8y^2z + 1.3yz^4 - 2.4");

    double val = p.value(1, 2, 1);
    double expected =
        1 * 2 * 1 +
        0.4 * 1 * 2 * 1 -
        8 * 4 * 1 +
        1.3 * 2 * 1 -
        2.4;

    EXPECT_NEAR(val, expected, 1e-9);
}


TEST(PolynomTest, Addition_Polynom) {
    Polynom p1("x^2");
    Polynom p2("2x^2");

    Polynom sum = p1 + p2;

    EXPECT_DOUBLE_EQ(sum.value(2, 1, 1), 3 * 4);
}

TEST(PolynomTest, Addition_Monom) {
    Polynom p("x^2");
    Monom m(2, { 2,0,0 }); // 2x^2

    Polynom result = p + m;

    EXPECT_DOUBLE_EQ(result.value(3, 1, 1), 3 * 9);
}

TEST(PolynomTest, Addition_EliminatesZero) {
    Polynom p("x^2");
    Polynom q("-x^2");

    Polynom r = p + q;

    EXPECT_DOUBLE_EQ(r.value(5, 5, 5), 0.0);
}


TEST(PolynomTest, Subtraction_Polynom) {
    Polynom p1("3x^2");
    Polynom p2("x^2");

    Polynom result = p1 - p2;

    EXPECT_DOUBLE_EQ(result.value(2, 1, 1), 2 * 4);
}

TEST(PolynomTest, UnaryMinus) {
    Polynom p("5x");
    Polynom neg = -p;

    EXPECT_DOUBLE_EQ(neg.value(2, 1, 1), -10);
}


TEST(PolynomTest, Multiply_Polynom) {
    Polynom p1("x");
    Polynom p2("x");

    Polynom result = p1 * p2;

    EXPECT_DOUBLE_EQ(result.value(3, 1, 1), 9);
}

TEST(PolynomTest, Multiply_ByMonom) {
    Polynom p("x + y");
    Monom m(2, { 1,0,0 }); // 2x

    Polynom result = p * m;

    double val = result.value(2, 3, 1);
    double expected = (2 + 3) * 2 * 2;

    EXPECT_DOUBLE_EQ(val, expected);
}

TEST(PolynomTest, Multiply_ByZeroMonom) {
    Polynom p("x^2 + y");
    Monom zero(0, { 0,0,0 });

    p *= zero;

    EXPECT_DOUBLE_EQ(p.value(5, 5, 5), 0.0);
}


TEST(PolynomTest, PlusEquals) {
    Polynom p("x");
    Polynom q("2x");

    p += q;

    EXPECT_DOUBLE_EQ(p.value(3, 1, 1), 3 * 3);
}

TEST(PolynomTest, MinusEquals) {
    Polynom p("3x");
    Polynom q("x");

    p -= q;

    EXPECT_DOUBLE_EQ(p.value(4, 1, 1), 2 * 4);
}

TEST(PolynomTest, MultiplyEquals) {
    Polynom p("x");
    Polynom q("x");

    p *= q;

    EXPECT_DOUBLE_EQ(p.value(5, 1, 1), 25);
}


TEST(PolynomTest, CombineLikeTerms) {
    Polynom p("x^2 + 2x^2 - 3x^2");

    EXPECT_DOUBLE_EQ(p.value(3, 1, 1), 0.0);
}


TEST(PolynomTest, ComplexExpression) {
    Polynom p("x^2 + y");
    Polynom q("x - y");

    Polynom r = (p + q) * p;

    double val = r.value(2, 3, 1);
    double expected = ((4 + 3) + (2 - 3)) * (4 + 3);

    EXPECT_DOUBLE_EQ(val, expected);
}

TEST(PolynomTest, AssignmentOperator_Copy) {
    Polynom p1("2x^2+3y-5");
    Polynom p2;

    p2 = p1;

    EXPECT_DOUBLE_EQ(p1.value(2, 3, 1), p2.value(2, 3, 1));
}

TEST(PolynomTest, AssignmentOperator_SelfAssignment) {
    Polynom p("2x^2+3y");

    p = p;

    EXPECT_DOUBLE_EQ(p.value(2, 2, 2), 2 * 4 + 3 * 2);
}


TEST(PolynomTest, Output_ZeroPolynom) {
    Polynom p;

    std::ostringstream oss;
    oss << p;

    EXPECT_EQ(oss.str(), "0");
}

TEST(PolynomTest, Output_ConstantPolynom) {
    Polynom p("5");

    std::ostringstream oss;
    oss << p;

    EXPECT_EQ(oss.str(), "5");
}

TEST(PolynomTest, Output_SimplePolynom) {
    Polynom p("2x^2+3y");

    std::ostringstream oss;
    oss << p;

    EXPECT_EQ(oss.str(), "2x^2+3y");
}

TEST(PolynomTest, Output_WithNegativeTerm) {
    Polynom p("2x^2-3y");

    std::ostringstream oss;
    oss << p;

    EXPECT_EQ(oss.str(), "2x^2-3y");
}

TEST(PolynomTest, Output_UnSortPolynom) {
    Polynom p("6+y^2z^3 + 2y^2 + xy");

    std::ostringstream oss;
    oss << p;

    EXPECT_EQ(oss.str(), "xy+y^2z^3+2y^2+6");
}


TEST(PolynomTest, Input_SimplePolynom) {
    std::istringstream iss("2x^2+3y-5");
    Polynom p;

    iss >> p;

    EXPECT_TRUE(iss);
    EXPECT_DOUBLE_EQ(p.value(2, 3, 1), 2 * 4 + 3 * 3 - 5);
}

TEST(PolynomTest, Input_ConstantPolynom) {
    std::istringstream iss("7");
    Polynom p;

    iss >> p;

    EXPECT_TRUE(iss);
    EXPECT_DOUBLE_EQ(p.value(1, 1, 1), 7);
}

TEST(PolynomTest, Input_InvalidPolynom) {
    std::istringstream iss("2x^+3");
    Polynom p;

    iss >> p;

    EXPECT_TRUE(iss.fail());
}


TEST(PolynomTest, IO_RoundTrip) {
    Polynom p1("3x^2+2y-4z+7");

    std::ostringstream oss;
    oss << p1;

    std::istringstream iss(oss.str());
    Polynom p2;
    iss >> p2;

    EXPECT_DOUBLE_EQ(p1.value(2, 3, 4), p2.value(2, 3, 4));
}