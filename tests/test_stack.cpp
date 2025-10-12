// Copyright 2025 Alewa8131

#include <gtest/gtest.h>
#include "../lib_stack/stack.h"

TEST(StackTest, DefaultConstr) {
    Stack<int> s;
    ASSERT_TRUE(s.is_empty());
    ASSERT_TRUE(s.is_full());
}

TEST(StackTest, SizeConstr) {
    Stack<double> s(5);
    ASSERT_TRUE(s.is_empty());
    ASSERT_FALSE(s.is_full());
}

TEST(StackTest, SizeConstr_Error_NegativeSize) {
    EXPECT_THROW(Stack<int> s(-1), std::invalid_argument);
}

TEST(StackTest, SizeConstructor_ZeroSize) {
    Stack<char> s(0);
    ASSERT_TRUE(s.is_empty());
    ASSERT_TRUE(s.is_full());
}

TEST(StackTest, CopyConstructor) {
    Stack<int> original(3);
    original.push(10);
    original.push(20);

    Stack<int> copy = original;

    ASSERT_FALSE(copy.is_empty());
    ASSERT_EQ(20, copy.top());

    original.pop();
    copy.push(30);

    ASSERT_EQ(10, original.top());
    ASSERT_EQ(30, copy.top());
    ASSERT_FALSE(original.is_full());
    ASSERT_TRUE(copy.is_full());
}


TEST(StackTest, Push_Success) {
    Stack<int> s(2);
    s.push(1);
    s.push(2);

    ASSERT_EQ(2, s.top());
    ASSERT_TRUE(s.is_full());
}
TEST(StackTest, Push_Error_Overflow) {
    Stack<int> s(1);
    s.push(100);

    EXPECT_THROW(s.push(200), std::out_of_range);
    ASSERT_EQ(100, s.top());
}


TEST(StackTest, Pop_Success) {
    Stack<int> s(2);
    s.push(1);
    s.push(2);
    s.pop();

    ASSERT_EQ(1, s.top());
    ASSERT_FALSE(s.is_full());
}
TEST(StackTest, Pop_Error_Underflow_Empty) {
    Stack<int> s(2);
    EXPECT_THROW(s.pop(), std::out_of_range);
}
TEST(StackTest, Pop_Error_Underflow_PopAll) {
    Stack<int> s(1);
    s.push(5);
    s.pop();

    EXPECT_THROW(s.pop(), std::out_of_range);
    ASSERT_TRUE(s.is_empty());
}


TEST(StackTest, Top_Success) {
    Stack<char> s(3);
    s.push('A');
    s.push('B');

    ASSERT_EQ('B', s.top());
    s.pop();
    ASSERT_EQ('A', s.top());
}
TEST(StackTest, Top_Error_Empty) {
    Stack<int> s(1);
    EXPECT_THROW(s.top(), std::out_of_range);
}
TEST(StackTest, Top_Error_AfterClear) {
    Stack<int> s(2);
    s.push(1);
    s.clear();

    EXPECT_THROW(s.top(), std::out_of_range);
    ASSERT_TRUE(s.is_empty());
}


TEST(StackTest, StatusFunctions) {
    Stack<int> s(3);

    EXPECT_TRUE(s.is_empty());
    EXPECT_FALSE(s.is_full());

    s.push(1);
    EXPECT_FALSE(s.is_empty());
    EXPECT_FALSE(s.is_full());

    s.push(2);
    s.push(3); // Full
    EXPECT_FALSE(s.is_empty());
    EXPECT_TRUE(s.is_full());

    s.pop();
    EXPECT_FALSE(s.is_full());
}

TEST(StackTest, Clear) {
    Stack<int> s(5);
    s.push(10);
    s.push(20);
    s.push(30);

    ASSERT_FALSE(s.is_empty());

    s.clear();

    ASSERT_TRUE(s.is_empty());
    s.push(5);
    ASSERT_EQ(5, s.top());
}
