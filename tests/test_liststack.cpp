// Copyright 2025 Alewa8131

#include <gtest/gtest.h>
#include "../lib_liststack/liststack.h"

TEST(ListStackTest, DefaultConstr) {
    ListStack<int> s;
    ASSERT_TRUE(s.is_empty());
    ASSERT_TRUE(s.is_full());
}

TEST(ListStackTest, SizeConstr) {
    ListStack<double> s(5);
    ASSERT_TRUE(s.is_empty());
    ASSERT_FALSE(s.is_full());
}

TEST(ListStackTest, SizeConstr_Error_NegativeSize) {
    EXPECT_THROW(ListStack<int> s(-1), std::invalid_argument);
}

TEST(ListStackTest, SizeConstructor_ZeroSize) {
    ListStack<char> s(0);
    ASSERT_TRUE(s.is_empty());
    ASSERT_TRUE(s.is_full());
}

TEST(ListStackTest, CopyConstructor) {
    ListStack<int> original(3);
    original.push(10);
    original.push(20);

    ListStack<int> copy = original;

    ASSERT_FALSE(copy.is_empty());
    ASSERT_EQ(20, copy.top());

    original.pop();
    copy.push(30);

    ASSERT_EQ(10, original.top());
    ASSERT_EQ(30, copy.top());
    ASSERT_FALSE(original.is_full());
    ASSERT_TRUE(copy.is_full());
}


TEST(ListStackTest, Push_Success) {
    ListStack<int> s(2);
    s.push(1);
    s.push(2);

    ASSERT_EQ(2, s.top());
    ASSERT_TRUE(s.is_full());
}
TEST(ListStackTest, Push_Error_Overflow) {
    ListStack<int> s(1);
    s.push(100);

    EXPECT_THROW(s.push(200), std::out_of_range);
    ASSERT_EQ(100, s.top());
}


TEST(ListStackTest, Pop_Success) {
    ListStack<int> s(2);
    s.push(1);
    s.push(2);
    s.pop();

    ASSERT_EQ(1, s.top());
    ASSERT_FALSE(s.is_full());
}
TEST(ListStackTest, Pop_Error_Underflow_Empty) {
    ListStack<int> s(2);
    EXPECT_THROW(s.pop(), std::out_of_range);
}
TEST(ListStackTest, Pop_Error_Underflow_PopAll) {
    ListStack<int> s(1);
    s.push(5);
    s.pop();

    EXPECT_THROW(s.pop(), std::out_of_range);
    ASSERT_TRUE(s.is_empty());
}


TEST(ListStackTest, Top_Success) {
    ListStack<char> s(3);
    s.push('A');
    s.push('B');

    ASSERT_EQ('B', s.top());
    s.pop();
    ASSERT_EQ('A', s.top());
}
TEST(ListStackTest, Top_Error_Empty) {
    ListStack<int> s(1);
    EXPECT_THROW(s.top(), std::out_of_range);
}
TEST(ListStackTest, Top_Error_AfterClear) {
    ListStack<int> s(2);
    s.push(1);
    s.clear();

    EXPECT_THROW(s.top(), std::out_of_range);
    ASSERT_TRUE(s.is_empty());
}


TEST(ListStackTest, StatusFunctions) {
    ListStack<int> s(3);

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

TEST(ListStackTest, Clear) {
    ListStack<int> s(5);
    s.push(10);
    s.push(20);
    s.push(30);

    ASSERT_FALSE(s.is_empty());

    s.clear();

    ASSERT_TRUE(s.is_empty());
    s.push(5);
    ASSERT_EQ(5, s.top());
}
