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


TEST(ReadExpressionTest, Valid_Sin) {
    EXPECT_NO_THROW(read_expression("sin(x)"));
}

TEST(ReadExpressionTest, Valid_Cos) {
    EXPECT_NO_THROW(read_expression("cos(y + 1)"));
}

TEST(ReadExpressionTest, Valid_Tg) {
    EXPECT_NO_THROW(read_expression("tg(5)"));
}

TEST(ReadExpressionTest, Valid_Ln) {
    EXPECT_NO_THROW(read_expression("ln(10)"));
}

TEST(ReadExpressionTest, Valid_Exp) {
    EXPECT_NO_THROW(read_expression("exp(x + y)"));
}

TEST(ReadExpressionTest, Valid_FunctionsCombination) {
    EXPECT_NO_THROW(read_expression("sin(x) + cos(y)"));
}


TEST(ReadExpressionTest, Invalid_FunctionWithoutBrackets) {
    EXPECT_THROW(read_expression("sin x"), std::runtime_error);
}

TEST(ReadExpressionTest, Invalid_EmptyFunctionArgs) {
    EXPECT_THROW(read_expression("cos()"), std::runtime_error);
}

TEST(ReadExpressionTest, Invalid_UnknownFunction) {
    EXPECT_THROW(read_expression("abc(x)"), std::runtime_error);
}


TEST(ReadExpressionTest, Valid_AbsSimple) {
    EXPECT_NO_THROW(read_expression("|x|"));
}

TEST(ReadExpressionTest, Valid_AbsExpression) {
    EXPECT_NO_THROW(read_expression("|x + y|"));
}

TEST(ReadExpressionTest, Valid_NestedAbs) {
    EXPECT_NO_THROW(read_expression("||x||"));
}

TEST(ReadExpressionTest, Valid_AbsAndFunctions) {
    EXPECT_NO_THROW(read_expression("|sin(x)|"));
}


TEST(ReadExpressionTest, Invalid_Abs_NoClosing) {
    EXPECT_THROW(read_expression("|x"), std::runtime_error);
}

TEST(ReadExpressionTest, Invalid_Abs_Empty) {
    EXPECT_THROW(read_expression("||"), std::runtime_error);
}

TEST(ReadExpressionTest, Invalid_Abs_DoubleOpen) {
    EXPECT_THROW(read_expression("|||x|"), std::runtime_error);
}


TEST(ReadExpressionTest, Valid_UnaryMinus_Number) {
    EXPECT_NO_THROW(read_expression("-5"));
}

TEST(ReadExpressionTest, Valid_UnaryMinus_Variable) {
    EXPECT_NO_THROW(read_expression("-x"));
}

TEST(ReadExpressionTest, Valid_UnaryMinus_Expression) {
    EXPECT_NO_THROW(read_expression("-(x + 2)"));
}

TEST(ReadExpressionTest, Valid_UnaryMinus_Combined) {
    EXPECT_NO_THROW(read_expression("3 * -x + -sin(y)"));
}

TEST(ReadExpressionTest, Valid_UnaryMinus_Nested) {
    EXPECT_NO_THROW(read_expression("-(-x + 5)"));
}


TEST(ReadExpressionTest, MegaExpression_AllFeatures) {
    EXPECT_NO_THROW(read_expression(
        "|sin(x_1 + 10) + cos(y_2 - 3)| * "
        "{ln(15 + tg(z)) - exp(a_b)} ^ "
        "[x + y * -(z - 7)] + "
        "||x - y||"
    ));
}
