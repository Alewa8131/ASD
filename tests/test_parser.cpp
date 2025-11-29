// Copyright 2025 Alewa8131

#include <gtest/gtest.h>
#include <stdexcept>
#include "../lib_parser/parser.h"


TEST(ParseTest, SimpleExpression_IteratorCheck) {
    List<Lexem> lexems = Parser::parse("1 + x");
    auto it = lexems.begin();
    EXPECT_TRUE(it != lexems.end());
    EXPECT_TRUE((*it).isConstant()); ++it;
    EXPECT_TRUE((*it).isOperator()); ++it;
    EXPECT_TRUE((*it).isVariable()); ++it;
    EXPECT_TRUE(it == lexems.end());
}

TEST(ParseTest, EmptyExpression) {
    EXPECT_THROW(Parser::parse(""), std::runtime_error);
}

TEST(ParseTest, SingleNumber) {
    List<Lexem> lexems = Parser::parse("42");
    auto it = lexems.begin();
    EXPECT_TRUE((*it).isConstant());
    EXPECT_DOUBLE_EQ((*it).value, 42.0);
    ++it;
    EXPECT_TRUE(it == lexems.end());
}

TEST(ParseTest, SingleVariable) {
    List<Lexem> lexems = Parser::parse("x");
    auto it = lexems.begin();
    EXPECT_TRUE((*it).isVariable());
    EXPECT_EQ((*it).name, "x");
    ++it;
    EXPECT_TRUE(it == lexems.end());
}

TEST(ParseTest, SingleFunction) {
    EXPECT_THROW(Parser::parse("sin()"), std::runtime_error);
}


TEST(ParseTest, MultiDigitNumber) {
    List<Lexem> lexems = Parser::parse("123 + 456");
    auto it = lexems.begin();
    EXPECT_TRUE((*it).isConstant());
    EXPECT_DOUBLE_EQ((*it).value, 123.0); ++it;
    EXPECT_TRUE((*it).isOperator()); ++it;
    EXPECT_TRUE((*it).isConstant());
    EXPECT_DOUBLE_EQ((*it).value, 456.0); ++it;
    EXPECT_TRUE(it == lexems.end());
}

TEST(ParseTest, DecimalNumber) {
    EXPECT_THROW(Parser::parse("12.34"), std::runtime_error);
}

TEST(ParseTest, VariableWithUnderscore) {
    List<Lexem> lexems = Parser::parse("x_y + var_123");
    auto it = lexems.begin();
    EXPECT_TRUE((*it).isVariable());
    EXPECT_EQ((*it).name, "x_y"); ++it;
    EXPECT_TRUE((*it).isOperator()); ++it;
    EXPECT_TRUE((*it).isVariable());
    EXPECT_EQ((*it).name, "var_123"); ++it;
    EXPECT_TRUE(it == lexems.end());
}

TEST(ParseTest, MixedCaseVariables) {
    List<Lexem> lexems = Parser::parse("VarName + MYVAR");
    auto it = lexems.begin();
    EXPECT_TRUE((*it).isVariable());
    EXPECT_EQ((*it).name, "VarName"); ++it;
    EXPECT_TRUE((*it).isOperator()); ++it;
    EXPECT_TRUE((*it).isVariable());
    EXPECT_EQ((*it).name, "MYVAR"); ++it;
    EXPECT_TRUE(it == lexems.end());
}

TEST(ParseTest, AllOperators) {
    List<Lexem> lexems = Parser::parse("a + b - c * d / e ^ f");
    auto it = lexems.begin();
    EXPECT_TRUE((*it).isVariable()); ++it; // a
    EXPECT_TRUE((*it).isOperator()); ++it; // +
    EXPECT_TRUE((*it).isVariable()); ++it; // b
    EXPECT_TRUE((*it).isOperator()); ++it; // -
    EXPECT_TRUE((*it).isVariable()); ++it; // c
    EXPECT_TRUE((*it).isOperator()); ++it; // *
    EXPECT_TRUE((*it).isVariable()); ++it; // d
    EXPECT_TRUE((*it).isOperator()); ++it; // /
    EXPECT_TRUE((*it).isVariable()); ++it; // e
    EXPECT_TRUE((*it).isOperator()); ++it; // ^
    EXPECT_TRUE((*it).isVariable()); ++it; // f
    EXPECT_TRUE(it == lexems.end());
}


TEST(ParseTest, UnaryMinusAtStart) {
    List<Lexem> lexems = Parser::parse("-x");
    auto it = lexems.begin();
    EXPECT_TRUE((*it).isUnOperator()); ++it;
    EXPECT_TRUE((*it).isVariable()); ++it;
    EXPECT_TRUE(it == lexems.end());
}

TEST(ParseTest, UnaryMinusAfterBracket) {
    List<Lexem> lexems = Parser::parse("(-x)");
    auto it = lexems.begin();
    EXPECT_TRUE((*it).isOpenBracket()); ++it;
    EXPECT_TRUE((*it).isUnOperator()); ++it;
    EXPECT_TRUE((*it).isVariable()); ++it;
    EXPECT_TRUE((*it).isClosedBracket()); ++it;
    EXPECT_TRUE(it == lexems.end());
}

TEST(ParseTest, MultipleUnaryMinus) {
    List<Lexem> lexems = Parser::parse("--x");
    auto it = lexems.begin();
    EXPECT_TRUE((*it).isUnOperator()); ++it;
    EXPECT_TRUE((*it).isUnOperator()); ++it;
    EXPECT_TRUE((*it).isVariable()); ++it;
    EXPECT_TRUE(it == lexems.end());
}

TEST(ParseTest, UnaryMinusInExpression) {
    List<Lexem> lexems = Parser::parse("x * -y + -5");
    auto it = lexems.begin();
    EXPECT_TRUE((*it).isVariable()); ++it;
    EXPECT_TRUE((*it).isOperator()); ++it;
    EXPECT_TRUE((*it).isUnOperator()); ++it;
    EXPECT_TRUE((*it).isVariable()); ++it;
    EXPECT_TRUE((*it).isOperator()); ++it;
    EXPECT_TRUE((*it).isUnOperator()); ++it;
    EXPECT_TRUE((*it).isConstant()); ++it;
    EXPECT_TRUE(it == lexems.end());
}


TEST(ParseTest, FunctionAndBrackets) {
    List<Lexem> lexems = Parser::parse("sin(x + 2)");
    auto it = lexems.begin();
    EXPECT_TRUE((*it).isFunction()); ++it;
    EXPECT_TRUE((*it).isOpenBracket()); ++it;
    EXPECT_TRUE((*it).isVariable()); ++it;
    EXPECT_TRUE((*it).isOperator()); ++it;
    EXPECT_TRUE((*it).isConstant()); ++it;
    EXPECT_TRUE((*it).isClosedBracket()); ++it;
    EXPECT_TRUE(it == lexems.end());
}

TEST(ParseTest, NestedFunctions) {
    List<Lexem> lexems = Parser::parse("sin(cos(x))");
    auto it = lexems.begin();
    EXPECT_TRUE((*it).isFunction()); ++it; // sin
    EXPECT_TRUE((*it).isOpenBracket()); ++it;
    EXPECT_TRUE((*it).isFunction()); ++it; // cos
    EXPECT_TRUE((*it).isOpenBracket()); ++it;
    EXPECT_TRUE((*it).isVariable()); ++it; // x
    EXPECT_TRUE((*it).isClosedBracket()); ++it;
    EXPECT_TRUE((*it).isClosedBracket()); ++it;
    EXPECT_TRUE(it == lexems.end());
}

TEST(ParseTest, FunctionWithComplexArgument) {
    List<Lexem> lexems = Parser::parse("exp(x^2 + y*3)");
    auto it = lexems.begin();
    EXPECT_TRUE((*it).isFunction()); ++it; // exp
    EXPECT_TRUE((*it).isOpenBracket()); ++it;
    EXPECT_TRUE((*it).isVariable()); ++it; // x
    EXPECT_TRUE((*it).isOperator()); ++it; // ^
    EXPECT_TRUE((*it).isConstant()); ++it; // 2
    EXPECT_TRUE((*it).isOperator()); ++it; // +
    EXPECT_TRUE((*it).isVariable()); ++it; // y
    EXPECT_TRUE((*it).isOperator()); ++it; // *
    EXPECT_TRUE((*it).isConstant()); ++it; // 3
    EXPECT_TRUE((*it).isClosedBracket()); ++it;
    EXPECT_TRUE(it == lexems.end());
}


TEST(ParseTest, AbsAndUnaryMinus) {
    List<Lexem> lexems = Parser::parse("|-x + 5|");
    auto it = lexems.begin();
    EXPECT_TRUE((*it).isOpenedAbs()); ++it;
    EXPECT_TRUE((*it).isUnOperator()); ++it;
    EXPECT_TRUE((*it).isVariable()); ++it;
    EXPECT_TRUE((*it).isOperator()); ++it;
    EXPECT_TRUE((*it).isConstant()); ++it;
    EXPECT_TRUE((*it).isClosedAbs()); ++it;
    EXPECT_TRUE(it == lexems.end());
}

TEST(ParseTest, NestedAbs) {
    List<Lexem> lexems = Parser::parse("||x||");
    auto it = lexems.begin();
    EXPECT_TRUE((*it).isOpenedAbs()); ++it;
    EXPECT_TRUE((*it).isOpenedAbs()); ++it;
    EXPECT_TRUE((*it).isVariable()); ++it;
    EXPECT_TRUE((*it).isClosedAbs()); ++it;
    EXPECT_TRUE((*it).isClosedAbs()); ++it;
    EXPECT_TRUE(it == lexems.end());
}

TEST(ParseTest, AbsWithExpression) {
    List<Lexem> lexems = Parser::parse("|x + y| * |z - w|");
    auto it = lexems.begin();
    EXPECT_TRUE((*it).isOpenedAbs()); ++it;
    EXPECT_TRUE((*it).isVariable()); ++it;
    EXPECT_TRUE((*it).isOperator()); ++it;
    EXPECT_TRUE((*it).isVariable()); ++it;
    EXPECT_TRUE((*it).isClosedAbs()); ++it;
    EXPECT_TRUE((*it).isOperator()); ++it;
    EXPECT_TRUE((*it).isOpenedAbs()); ++it;
    EXPECT_TRUE((*it).isVariable()); ++it;
    EXPECT_TRUE((*it).isOperator()); ++it;
    EXPECT_TRUE((*it).isVariable()); ++it;
    EXPECT_TRUE((*it).isClosedAbs()); ++it;
    EXPECT_TRUE(it == lexems.end());
}


TEST(ParseTest, DifferentBracketTypes) {
    List<Lexem> lexems = Parser::parse("(x + [y * {z - w}])");
    auto it = lexems.begin();
    EXPECT_TRUE((*it).isOpenBracket()); ++it;   // (
    EXPECT_TRUE((*it).isVariable()); ++it;      // x
    EXPECT_TRUE((*it).isOperator()); ++it;      // +
    EXPECT_TRUE((*it).isOpenBracket()); ++it;   // [
    EXPECT_TRUE((*it).isVariable()); ++it;      // y
    EXPECT_TRUE((*it).isOperator()); ++it;      // *
    EXPECT_TRUE((*it).isOpenBracket()); ++it;   // {
    EXPECT_TRUE((*it).isVariable()); ++it;      // z
    EXPECT_TRUE((*it).isOperator()); ++it;      // -
    EXPECT_TRUE((*it).isVariable()); ++it;      // w
    EXPECT_TRUE((*it).isClosedBracket()); ++it; // }
    EXPECT_TRUE((*it).isClosedBracket()); ++it; // ]
    EXPECT_TRUE((*it).isClosedBracket()); ++it; // )
    EXPECT_TRUE(it == lexems.end());
}


TEST(ParseTest, SpacesIgnored) {
    List<Lexem> lexems1 = Parser::parse("x+y");
    List<Lexem> lexems2 = Parser::parse("x + y");
    List<Lexem> lexems3 = Parser::parse("  x  +  y  ");

    auto it1 = lexems1.begin();
    auto it2 = lexems2.begin();
    auto it3 = lexems3.begin();

    while (it1 != lexems1.end() && it2 != lexems2.end() && it3 != lexems3.end()) {
        EXPECT_EQ((*it1).type, (*it2).type);
        EXPECT_EQ((*it1).type, (*it3).type);
        ++it1; ++it2; ++it3;
    }
    EXPECT_TRUE(it1 == lexems1.end() && it2 == lexems2.end() && it3 == lexems3.end());
}

TEST(ParseTest, TabsIgnored) {
    List<Lexem> lexems = Parser::parse("\tx\t+\ty\t");
    auto it = lexems.begin();
    EXPECT_TRUE((*it).isVariable()); ++it;
    EXPECT_TRUE((*it).isOperator()); ++it;
    EXPECT_TRUE((*it).isVariable()); ++it;
    EXPECT_TRUE(it == lexems.end());
}


TEST(ParseTest, UnknownSymbolThrows) {
    EXPECT_THROW(Parser::parse("x @ y"), std::runtime_error);
    EXPECT_THROW(Parser::parse("x & y"), std::runtime_error);
    EXPECT_THROW(Parser::parse("x # 5"), std::runtime_error);
}

TEST(ParseTest, UnclosedAbsThrows) {
    EXPECT_THROW(Parser::parse("|x + y"), std::runtime_error);
    EXPECT_THROW(Parser::parse("||x|"), std::runtime_error);
}


TEST(ToRPNTest, SingleOperandRPN) {
    List<Lexem> lexems = Parser::parse("42");
    List<Lexem> rpn = Parser::to_rpn(lexems);
    auto it = rpn.begin();
    EXPECT_TRUE((*it).isConstant());
    EXPECT_DOUBLE_EQ((*it).value, 42.0);
    ++it;
    EXPECT_TRUE(it == rpn.end());
}

TEST(ToRPNTest, SimpleRPN) {
    List<Lexem> lexems = Parser::parse("1 + 2 * 3");
    List<Lexem> rpn = Parser::to_rpn(lexems);
    auto it = rpn.begin();
    EXPECT_TRUE((*it).isConstant()); ++it; // 1
    EXPECT_TRUE((*it).isConstant()); ++it; // 2
    EXPECT_TRUE((*it).isConstant()); ++it; // 3
    EXPECT_TRUE((*it).isOperator()); ++it; // *
    EXPECT_TRUE((*it).isOperator()); ++it; // +
    EXPECT_TRUE(it == rpn.end());
}

TEST(ToRPNTest, SimpleRPNWithBrackets) {
    List<Lexem> lexems = Parser::parse("(1 + 2) * 3");
    List<Lexem> rpn = Parser::to_rpn(lexems);
    auto it = rpn.begin();
    EXPECT_TRUE((*it).isConstant()); ++it; // 1
    EXPECT_TRUE((*it).isConstant()); ++it; // 2
    EXPECT_TRUE((*it).isOperator()); ++it; // +
    EXPECT_TRUE((*it).isConstant()); ++it; // 3
    EXPECT_TRUE((*it).isOperator()); ++it; // *
    EXPECT_TRUE(it == rpn.end());
}

TEST(ToRPNTest, OperatorPrecedence) {
    List<Lexem> lexems = Parser::parse("a + b * c ^ d - e / f");
    List<Lexem> rpn = Parser::to_rpn(lexems);
    auto it = rpn.begin();
    EXPECT_TRUE((*it).isVariable()); ++it; // a
    EXPECT_TRUE((*it).isVariable()); ++it; // b
    EXPECT_TRUE((*it).isVariable()); ++it; // c
    EXPECT_TRUE((*it).isVariable()); ++it; // d
    EXPECT_TRUE((*it).isOperator()); ++it; // ^
    EXPECT_TRUE((*it).isOperator()); ++it; // *
    EXPECT_TRUE((*it).isOperator()); ++it; // +
    EXPECT_TRUE((*it).isVariable()); ++it; // e
    EXPECT_TRUE((*it).isVariable()); ++it; // f
    EXPECT_TRUE((*it).isOperator()); ++it; // /
    EXPECT_TRUE((*it).isOperator()); ++it; // -
    EXPECT_TRUE(it == rpn.end());
}


TEST(ToRPNTest, UnaryMinusRPN) {
    List<Lexem> lexems = Parser::parse("-x + 5");
    List<Lexem> rpn = Parser::to_rpn(lexems);
    auto it = rpn.begin();
    EXPECT_TRUE((*it).isVariable()); ++it;   // x
    EXPECT_TRUE((*it).isUnOperator()); ++it; // -
    EXPECT_TRUE((*it).isConstant()); ++it;   // 5
    EXPECT_TRUE((*it).isOperator()); ++it;   // +
    EXPECT_TRUE(it == rpn.end());
}

TEST(ToRPNTest, MultipleUnaryMinusRPN) {
    List<Lexem> lexems = Parser::parse("--x");
    List<Lexem> rpn = Parser::to_rpn(lexems);
    auto it = rpn.begin();
    EXPECT_TRUE((*it).isVariable()); ++it;   // x
    EXPECT_TRUE((*it).isUnOperator()); ++it; // -
    EXPECT_TRUE((*it).isUnOperator()); ++it; // -
    EXPECT_TRUE(it == rpn.end());
}

TEST(ToRPNTest, ComplexUnaryMinusRPN) {
    List<Lexem> lexems = Parser::parse("x * -y + -5");
    List<Lexem> rpn = Parser::to_rpn(lexems);
    auto it = rpn.begin();
    EXPECT_TRUE((*it).isVariable()); ++it;   // x
    EXPECT_TRUE((*it).isVariable()); ++it;   // y
    EXPECT_TRUE((*it).isUnOperator()); ++it; // -
    EXPECT_TRUE((*it).isOperator()); ++it;   // *
    EXPECT_TRUE((*it).isConstant()); ++it;   // 5
    EXPECT_TRUE((*it).isUnOperator()); ++it; // -
    EXPECT_TRUE((*it).isOperator()); ++it;   // +
    EXPECT_TRUE(it == rpn.end());
}


TEST(ToRPNTest, SimpleFunctionRPN) {
    List<Lexem> lexems = Parser::parse("sin(x)");
    List<Lexem> rpn = Parser::to_rpn(lexems);
    auto it = rpn.begin();
    EXPECT_TRUE((*it).isVariable()); ++it;
    EXPECT_TRUE((*it).isFunction()); ++it;
    EXPECT_TRUE(it == rpn.end());
}

TEST(ToRPNTest, FunctionWithExpressionRPN) {
    List<Lexem> lexems = Parser::parse("cos(x + y)");
    List<Lexem> rpn = Parser::to_rpn(lexems);
    auto it = rpn.begin();
    EXPECT_TRUE((*it).isVariable()); ++it;   // x
    EXPECT_TRUE((*it).isVariable()); ++it;   // y
    EXPECT_TRUE((*it).isOperator()); ++it;   // +
    EXPECT_TRUE((*it).isFunction()); ++it;   // cos
    EXPECT_TRUE(it == rpn.end());
}

TEST(ToRPNTest, NestedFunctionsRPN) {
    List<Lexem> lexems = Parser::parse("sin(cos(tg(x)))");
    List<Lexem> rpn = Parser::to_rpn(lexems);
    auto it = rpn.begin();
    EXPECT_TRUE((*it).isVariable()); ++it;   // x
    EXPECT_TRUE((*it).isFunction()); ++it;   // tg
    EXPECT_TRUE((*it).isFunction()); ++it;   // cos
    EXPECT_TRUE((*it).isFunction()); ++it;   // sin
    EXPECT_TRUE(it == rpn.end());
}


TEST(ToRPNTest, FunctionAndAbsRPN) {
    List<Lexem> lexems = Parser::parse("|sin(x + y)|");
    List<Lexem> rpn = Parser::to_rpn(lexems);
    auto it = rpn.begin();
    EXPECT_TRUE((*it).isVariable()); ++it;   // x
    EXPECT_TRUE((*it).isVariable()); ++it;   // y
    EXPECT_TRUE((*it).isOperator()); ++it;   // +
    EXPECT_TRUE((*it).isFunction()); ++it;   // sin
    EXPECT_TRUE((*it).isFunction()); ++it;   // abs
    EXPECT_TRUE(it == rpn.end());
}

TEST(ToRPNTest, SimpleAbsRPN) {
    List<Lexem> lexems = Parser::parse("|x|");
    List<Lexem> rpn = Parser::to_rpn(lexems);
    auto it = rpn.begin();
    EXPECT_TRUE((*it).isVariable()); ++it;   // x
    EXPECT_TRUE((*it).isFunction()); ++it;   // abs
    EXPECT_TRUE(it == rpn.end());
}

TEST(ToRPNTest, NestedAbsRPN) {
    List<Lexem> lexems = Parser::parse("||x||");
    List<Lexem> rpn = Parser::to_rpn(lexems);
    auto it = rpn.begin();
    EXPECT_TRUE((*it).isVariable()); ++it;   // x
    EXPECT_TRUE((*it).isFunction()); ++it;   // abs (внутренний)
    EXPECT_TRUE((*it).isFunction()); ++it;   // abs (внешний)
    EXPECT_TRUE(it == rpn.end());
}

TEST(ToRPNTest, AbsWithUnaryMinusRPN) {
    List<Lexem> lexems = Parser::parse("|-x|");
    List<Lexem> rpn = Parser::to_rpn(lexems);
    auto it = rpn.begin();
    EXPECT_TRUE((*it).isVariable()); ++it;   // x
    EXPECT_TRUE((*it).isUnOperator()); ++it; // -
    EXPECT_TRUE((*it).isFunction()); ++it;   // abs
    EXPECT_TRUE(it == rpn.end());
}


TEST(ToRPNTest, ComplexExpressionRPN) {
    List<Lexem> lexems = Parser::parse("(a + b) * (c - d) / (e ^ f)");
    List<Lexem> rpn = Parser::to_rpn(lexems);
    auto it = rpn.begin();
    EXPECT_TRUE((*it).isVariable()); ++it; // a
    EXPECT_TRUE((*it).isVariable()); ++it; // b
    EXPECT_TRUE((*it).isOperator()); ++it; // +
    EXPECT_TRUE((*it).isVariable()); ++it; // c
    EXPECT_TRUE((*it).isVariable()); ++it; // d
    EXPECT_TRUE((*it).isOperator()); ++it; // -
    EXPECT_TRUE((*it).isOperator()); ++it; // *
    EXPECT_TRUE((*it).isVariable()); ++it; // e
    EXPECT_TRUE((*it).isVariable()); ++it; // f
    EXPECT_TRUE((*it).isOperator()); ++it; // ^
    EXPECT_TRUE((*it).isOperator()); ++it; // /
    EXPECT_TRUE(it == rpn.end());
}

TEST(ToRPNTest, FunctionWithMultipleArgsRPN) {
    List<Lexem> lexems = Parser::parse("sin(x) + cos(y) * tg(z)");
    List<Lexem> rpn = Parser::to_rpn(lexems);
    auto it = rpn.begin();
    EXPECT_TRUE((*it).isVariable()); ++it; // x
    EXPECT_TRUE((*it).isFunction()); ++it; // sin
    EXPECT_TRUE((*it).isVariable()); ++it; // y
    EXPECT_TRUE((*it).isFunction()); ++it; // cos
    EXPECT_TRUE((*it).isVariable()); ++it; // z
    EXPECT_TRUE((*it).isFunction()); ++it; // tg
    EXPECT_TRUE((*it).isOperator()); ++it; // *
    EXPECT_TRUE((*it).isOperator()); ++it; // +
    EXPECT_TRUE(it == rpn.end());
}

TEST(ToRPNTest, RightAssociativeExponentiationRPN) {
    List<Lexem> lexems = Parser::parse("a ^ b ^ c");
    List<Lexem> rpn = Parser::to_rpn(lexems);
    auto it = rpn.begin();
    EXPECT_TRUE((*it).isVariable()); ++it; // a
    EXPECT_TRUE((*it).isVariable()); ++it; // b
    EXPECT_TRUE((*it).isVariable()); ++it; // c
    EXPECT_TRUE((*it).isOperator()); ++it; // ^ (c к b)
    EXPECT_TRUE((*it).isOperator()); ++it; // ^ (результат к a)
    EXPECT_TRUE(it == rpn.end());
}


TEST(ToRPNTest, MegaExpression_AllFeatures) {
    List<Lexem> lexems = Parser::parse(
        "|sin(x_1 + 10) + cos(y_2 - 3)| * "
        "{ln(15 + tg(z)) - exp(a_b)} ^ "
        "[x + y * -(z - 7)] + "
        "||x - y||"
    );
    EXPECT_NO_THROW(Parser::to_rpn(lexems));
}

TEST(ToRPNTest, LeftAssociativeOperators) {
    List<Lexem> lexems = Parser::parse("a - b - c");
    List<Lexem> rpn = Parser::to_rpn(lexems);
    auto it = rpn.begin();
    EXPECT_TRUE((*it).isVariable()); ++it; // a
    EXPECT_TRUE((*it).isVariable()); ++it; // b
    EXPECT_TRUE((*it).isOperator()); ++it; // -
    EXPECT_TRUE((*it).isVariable()); ++it; // c
    EXPECT_TRUE((*it).isOperator()); ++it; // -
    EXPECT_TRUE(it == rpn.end());
}


TEST(ParserTest, ParseAndRPNRoundTrip) {
    std::string expressions[] = {
        "x + y",
        "a * b - c / d",
        "sin(x) + cos(y)",
        "|x - y| * z",
        "-a + b * -c",
        "(x + y) * (z - w)",
        "||x|| + |y|"
    };

    for (const auto& expr : expressions) {
        List<Lexem> parsed = Parser::parse(expr);
        EXPECT_NO_THROW(Parser::to_rpn(parsed));
    }
}

TEST(ParserTest, LargeExpressionNoCrash) {
    std::string large_expr;
    for (int i = 0; i < 100; i++) {
        large_expr += "x_" + std::to_string(i) + " + ";
    }
    large_expr += "x_100";

    EXPECT_NO_THROW({
        List<Lexem> parsed = Parser::parse(large_expr);
        List<Lexem> rpn = Parser::to_rpn(parsed);
        });
}

TEST(ParseTest, LexemTypesPreserved) {
    List<Lexem> lexems = Parser::parse("sin(|x + 5|) * -y");
    auto it = lexems.begin();

    EXPECT_TRUE((*it).isFunction()); ++it;
    EXPECT_TRUE((*it).isOpenBracket()); ++it;
    EXPECT_TRUE((*it).isOpenedAbs()); ++it;
    EXPECT_TRUE((*it).isVariable()); ++it;
    EXPECT_TRUE((*it).isOperator()); ++it;
    EXPECT_TRUE((*it).isConstant()); ++it;
    EXPECT_TRUE((*it).isClosedAbs()); ++it;
    EXPECT_TRUE((*it).isClosedBracket()); ++it;
    EXPECT_TRUE((*it).isOperator()); ++it;
    EXPECT_TRUE((*it).isUnOperator()); ++it;
    EXPECT_TRUE((*it).isVariable()); ++it;
    EXPECT_TRUE(it == lexems.end());
}
