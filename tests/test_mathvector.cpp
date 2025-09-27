// Copyright 2025 Alewa8131

#include <gtest/gtest.h>
#include "../lib_mathvector/mathvector.h"

TEST(MathVectorTest, ParameterizedConstructorInt) {
    MathVector<int> vec(5);
    ASSERT_EQ(5u, vec.size());
    for (size_t i = 0; i < 5; ++i) {
        EXPECT_EQ(0, vec.at(i));
    }
}

TEST(MathVectorTest, ParameterizedConstructorDouble) {
    MathVector<double> vec(3);
    ASSERT_EQ(3u, vec.size());
    for (size_t i = 0; i < 3; ++i) {
        EXPECT_EQ(0.0, vec.at(i));
    }
}

TEST(MathVectorTest, AtAccessAndModification) {
    MathVector<int> vec(3);

    vec.at(0) = 10;
    vec.at(2) = 20;

    EXPECT_EQ(10, vec.at(0));
    EXPECT_EQ(20, vec.at(2));
    EXPECT_THROW(vec.at(3), std::out_of_range);
}

TEST(MathVectorTest, AdditionOperatorInt) {
    MathVector<int> v1(3);
    v1.at(0) = 1; v1.at(1) = 2; v1.at(2) = 3;
    MathVector<int> v2(3);
    v2.at(0) = 4; v2.at(1) = 5; v2.at(2) = 6;

    MathVector<int> v3 = v1 + v2;

    ASSERT_EQ(3u, v3.size());
    EXPECT_EQ(5, v3.at(0));
    EXPECT_EQ(7, v3.at(1));
    EXPECT_EQ(9, v3.at(2));
}

TEST(MathVectorTest, SubtractionOperatorInt) {
    MathVector<int> v1(3);
    v1.at(0) = 10; v1.at(1) = 5; v1.at(2) = 1;
    MathVector<int> v2(3);
    v2.at(0) = 3; v2.at(1) = 5; v2.at(2) = 7;

    MathVector<int> v3 = v1 - v2;

    ASSERT_EQ(3u, v3.size());
    EXPECT_EQ(7, v3.at(0));
    EXPECT_EQ(0, v3.at(1));
    EXPECT_EQ(-6, v3.at(2));
}

TEST(MathVectorTest, AdditionMismatchThrows) {
    MathVector<int> v1(3);
    MathVector<int> v2(2);

    EXPECT_THROW(v1 + v2, std::invalid_argument);
}


TEST(MathVectorTest, ScalarProductOperatorInt) {
    MathVector<int> v1(3);
    v1.at(0) = 1; v1.at(1) = 2; v1.at(2) = 3;
    MathVector<int> v2(3);
    v2.at(0) = 4; v2.at(1) = 5; v2.at(2) = 6;

    int dot_product = v1 * v2; // 4 + 10 + 18 = 32

    EXPECT_EQ(32, dot_product);
}

TEST(MathVectorTest, ScalarProductOrthogonal) {
    MathVector<int> v1(2);
    v1.at(0) = 1; v1.at(1) = 0;
    MathVector<int> v2(2);
    v2.at(0) = 0; v2.at(1) = 1;

    int dot_product = v1 * v2; // (1*0) + (0*1) = 0

    EXPECT_EQ(0, dot_product);
}

TEST(MathVectorTest, ScalarProductMismatchThrows) {
    MathVector<int> v1(5);
    MathVector<int> v2(4);

    EXPECT_THROW(v1 * v2, std::invalid_argument);
}


TEST(MathVectorTest, ScalarMultiplicationRightInt) {
    MathVector<int> v1(3);
    v1.at(0) = 1; v1.at(1) = 10; v1.at(2) = -5;
    int scalar = 3;

    MathVector<int> v2 = v1 * scalar;

    ASSERT_EQ(3u, v2.size());
    EXPECT_EQ(3, v2.at(0));
    EXPECT_EQ(30, v2.at(1));
    EXPECT_EQ(-15, v2.at(2));
}

TEST(MathVectorTest, ScalarMultiplicationByZero) {
    MathVector<int> v1(2);
    v1.at(0) = 100; v1.at(1) = 500;
    int scalar = 0;

    MathVector<int> v2 = v1 * scalar;

    ASSERT_EQ(2u, v2.size());
    EXPECT_EQ(0, v2.at(0));
    EXPECT_EQ(0, v2.at(1));
}


TEST(MathVectorTest, OperationsDoublePrecision) {
    MathVector<double> v1(2);
    v1.at(0) = 1.5; v1.at(1) = 2.0;
    MathVector<double> v2(2);
    v2.at(0) = 2.0; v2.at(1) = 3.5;
    double scalar = 0.5;
    double tolerance = 1e-9;

    MathVector<double> v_sum = v1 + v2;
    EXPECT_NEAR(3.5, v_sum.at(0), tolerance);
    EXPECT_NEAR(5.5, v_sum.at(1), tolerance);


    MathVector<double> v_diff = v1 - v2;
    EXPECT_NEAR(-0.5, v_diff.at(0), tolerance);
    EXPECT_NEAR(-1.5, v_diff.at(1), tolerance);


    double dot_product = v1 * v2; // 3.0 + 7.0 = 10.0
    EXPECT_NEAR(10.0, dot_product, tolerance);


    MathVector<double> v_scaled = v1 * scalar;
    EXPECT_NEAR(0.75, v_scaled.at(0), tolerance);
    EXPECT_NEAR(1.0, v_scaled.at(1), tolerance);
}
