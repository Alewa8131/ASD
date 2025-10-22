// Copyright 2025 Alewa8131

#include <gtest/gtest.h>
#include <stdexcept>
#include "../algorithms/read_expression.h"


TEST(ReadExpressionTest, Valid_Simple) {
    EXPECT_NO_THROW(read_expression("1 + 2"));
}

TEST(ReadExpressionTest, Valid_WithVariables) {
    EXPECT_NO_THROW(read_expression("x + y"));
}

TEST(ReadExpressionTest, Valid_WithBrackets) {
    EXPECT_NO_THROW(read_expression("3 * (2 + 5)"));
}

TEST(ReadExpressionTest, Valid_LongExpression) {
    EXPECT_NO_THROW(read_expression("3 * (15 + (x + y) * (2 * x - 7 * y^2))"));
}

TEST(ReadExpressionTest, Valid_OnlyNumber) {
    EXPECT_NO_THROW(read_expression("12345"));
}

TEST(ReadExpressionTest, Valid_OnlyVariable) {
    EXPECT_NO_THROW(read_expression("abc"));
}


TEST(ReadExpressionTest, Invalid_DoubleOperator) {
    EXPECT_THROW(read_expression("2 + * 3"), std::runtime_error);
}

TEST(ReadExpressionTest, Invalid_EndsWithOperator) {
    EXPECT_THROW(read_expression("2 +"), std::runtime_error);
}

TEST(ReadExpressionTest, Invalid_StartsWithOperator) {
    EXPECT_THROW(read_expression("* 2 + 3"), std::runtime_error);
}

TEST(ReadExpressionTest, Invalid_MissingOperandInBrackets) {
    EXPECT_THROW(read_expression("(2 + )"), std::runtime_error);
}

TEST(ReadExpressionTest, Invalid_ExtraClosingBracket) {
    EXPECT_THROW(read_expression("2 + 3)"), std::runtime_error);
}

TEST(ReadExpressionTest, Invalid_MissingClosingBracket) {
    EXPECT_THROW(read_expression("(2 + 3"), std::runtime_error);
}

TEST(ReadExpressionTest, Invalid_WrongBracketType) {
    EXPECT_THROW(read_expression("(2 + 3]"), std::runtime_error);
}

TEST(ReadExpressionTest, Invalid_UnknownSymbol) {
    EXPECT_THROW(read_expression("2 + @"), std::runtime_error);
}

TEST(ReadExpressionTest, Invalid_TwoNumbersWithoutOp) {
    EXPECT_THROW(read_expression("12 34"), std::runtime_error);
}

TEST(ReadExpressionTest, Invalid_TwoVariablesWithoutOp) {
    EXPECT_THROW(read_expression("x y"), std::runtime_error);
}

TEST(ReadExpressionTest, Invalid_NumberThenVariable) {
    EXPECT_THROW(read_expression("123abc"), std::runtime_error);
}


TEST(ReadExpressionTest, EmptyString) {
    EXPECT_THROW(read_expression(""), std::runtime_error);
}

TEST(ReadExpressionTest, OnlySpaces) {
    EXPECT_THROW(read_expression("   "), std::runtime_error);
}

TEST(ReadExpressionTest, OnlyBrackets) {
    EXPECT_THROW(read_expression("()"), std::runtime_error);
}

TEST(ReadExpressionTest, NestedBracketsOk) {
    EXPECT_NO_THROW(read_expression("((2 + 3) * (4 + 5))"));
}

TEST(ReadExpressionTest, NestedBracketsBroken) {
    EXPECT_THROW(read_expression("((2 + 3) * (4 + 5)"), std::runtime_error);
}
