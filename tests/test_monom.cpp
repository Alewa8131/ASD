// Copyright 2026 Alewa8131

#include <gtest/gtest.h>
#include <stdexcept>
#include "../lib_polynom/monom.h"

TEST(MonomTest, DefaultConstructor) {
    Monom m;
    EXPECT_DOUBLE_EQ(m.value(1, 1, 1), 0);
}

TEST(MonomTest, ParamConstructor_Valid) {
    EXPECT_NO_THROW(Monom(5.0, { 2, 1, 0 }));
}

TEST(MonomTest, ParamConstructor_NegativePower) {
    EXPECT_THROW(Monom(1.0, { -1, 0, 0 }), std::invalid_argument);
}

TEST(MonomTest, CopyConstructor) {
    Monom m1(3.0, { 1, 2, 3 });
    Monom m2(m1);
    EXPECT_TRUE(m1 == m2);
}


TEST(MonomTest, Equality_IgnoresCoefficient) {
    Monom m1(3.0, { 1, 2, 3 });
    Monom m2(10.0, { 1, 2, 3 });
    EXPECT_TRUE(m1 == m2);
}

TEST(MonomTest, Inequality_DifferentPowers) {
    Monom m1(3.0, { 1, 2, 3 });
    Monom m2(3.0, { 0, 2, 3 });
    EXPECT_TRUE(m1 != m2);
}

TEST(MonomTest, LessOperator_OrderByPowers) {
    Monom m1(1, { 2, 0, 0 });
    Monom m2(1, { 1, 5, 5 });
    EXPECT_TRUE(m1 < m2);
}


TEST(MonomTest, Addition_Valid) {
    Monom m1(2, { 1, 0, 0 });
    Monom m2(3, { 1, 0, 0 });
    Monom result = m1 + m2;

    EXPECT_DOUBLE_EQ(result.value(2, 1, 1), 10); // (2+3)*2^1
}

TEST(MonomTest, Addition_InvalidDifferentPowers) {
    Monom m1(2, { 1, 0, 0 });
    Monom m2(3, { 2, 0, 0 });
    EXPECT_THROW(m1 + m2, std::logic_error);
}

TEST(MonomTest, Multiplication) {
    Monom m1(2, { 1, 0, 0 });
    Monom m2(3, { 2, 1, 0 });
    Monom result = m1 * m2;

    EXPECT_DOUBLE_EQ(result.value(2, 3, 1),
        6 * pow(2, 3) * pow(3, 1));
}

TEST(MonomTest, Division_ByZeroMonom) {
    Monom m1(2, { 1, 0, 0 });
    Monom m2(0, { 0, 0, 0 });
    EXPECT_THROW(m1 / m2, std::logic_error);
}

TEST(MonomTest, Division_ByScalarZero) {
    Monom m(2, { 1, 0, 0 });
    EXPECT_THROW(m / 0.0, std::logic_error);
}

TEST(MonomTest, UnaryMinus) {
    Monom m(5, { 1, 0, 0 });
    Monom neg = -m;
    EXPECT_DOUBLE_EQ(neg.value(2, 1, 1), -10);
}


TEST(MonomTest, ValueComputation) {
    Monom m(2, { 2, 1, 0 }); // 2x^2y
    double val = m.value(3, 4, 10);
    EXPECT_DOUBLE_EQ(val, 2 * 9 * 4);
}


TEST(MonomTest, Output_Zero) {
    Monom m;
    std::ostringstream oss;
    oss << m;
    EXPECT_EQ(oss.str(), "0");
}

TEST(MonomTest, Output_Constant) {
    Monom m(7, { 0, 0, 0 });
    std::ostringstream oss;
    oss << m;
    EXPECT_EQ(oss.str(), "7");
}

TEST(MonomTest, Output_WithPowers) {
    Monom m(3, { 2, 1, 0 }); // 3x^2y
    std::ostringstream oss;
    oss << m;
    EXPECT_EQ(oss.str(), "3x^2y");
}


TEST(MonomTest, Input_Constant) {
    std::istringstream iss("7");
    Monom m;
    iss >> m;

    EXPECT_TRUE(iss);
    EXPECT_DOUBLE_EQ(m.value(1, 1, 1), 7);
}

TEST(MonomTest, Input_SimpleMonom) {
    std::istringstream iss("3x^2y^2z^7");
    Monom m;
    iss >> m;

    EXPECT_TRUE(iss);
    EXPECT_DOUBLE_EQ(m.value(2, 2, 2),
        3 * pow(2, 2) * pow(2, 2) * pow(2, 7));
}

TEST(MonomTest, Input_WithSign) {
    std::istringstream iss("-x^2");
    Monom m;
    iss >> m;

    EXPECT_TRUE(iss);
    EXPECT_DOUBLE_EQ(m.value(3, 1, 1), -9);
}

TEST(MonomTest, Input_InvalidVariable) {
    std::istringstream iss("3a^2");
    Monom m;
    iss >> m;

    EXPECT_FALSE(iss);
}

TEST(MonomTest, Input_InvalidPower) {
    std::istringstream iss("3x^");
    Monom m;
    iss >> m;

    EXPECT_FALSE(iss);
}

TEST(MonomTest, Input_NegativePower) {
    std::istringstream iss("3x^-2");
    Monom m;
    iss >> m;

    EXPECT_FALSE(iss);
}

TEST(MonomDoubleCoefTest, Input_FractionalCoef) {
    std::istringstream iss("2.5x^2");
    Monom m;
    iss >> m;

    EXPECT_TRUE(iss);
    EXPECT_DOUBLE_EQ(m.value(2, 1, 1),
        2.5 * pow(2, 2));
}

TEST(MonomDoubleCoefTest, Input_FractionalNegativeCoef) {
    std::istringstream iss("-3.75y^2");
    Monom m;
    iss >> m;

    EXPECT_TRUE(iss);
    EXPECT_DOUBLE_EQ(m.value(1, 2, 1),
        -3.75 * pow(2, 2));
}

TEST(MonomDoubleCoefTest, Output_FractionalCoef) {
    Monom m(2.5, { 2, 0, 0 });

    std::ostringstream oss;
    oss << m;

    EXPECT_EQ(oss.str(), "2.5x^2");
}

TEST(MonomDoubleCoefTest, PrecisionCheck) {
    Monom m(0.1, { 1, 0, 0 });
    double val = m.value(10, 1, 1);

    EXPECT_NEAR(val, 1.0, 1e-9);
}
