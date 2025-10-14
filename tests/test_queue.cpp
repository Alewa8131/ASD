// Copyright 2025 Alewa8131

#include <gtest/gtest.h>
#include "../lib_queue/queue.h"


TEST(QueueTest, Constructor_Error_NegativeSize) {
    EXPECT_THROW(Queue<int> q(-1), std::invalid_argument);
}

TEST(QueueTest, StatusFunctions) {
    Queue<int> q(2);

    EXPECT_TRUE(q.is_empty());
    EXPECT_FALSE(q.is_full());

    q.push(1);
    EXPECT_FALSE(q.is_empty());
    EXPECT_FALSE(q.is_full());

    q.push(2);
    EXPECT_TRUE(q.is_full());
}

TEST(QueueTest, Basic_PushPop) {
    Queue<int> q(5);
    ASSERT_TRUE(q.is_empty());

    q.push(10);
    q.push(20);

    ASSERT_EQ(10, q.head());
    q.pop();

    ASSERT_EQ(20, q.head());
    q.pop();

    ASSERT_TRUE(q.is_empty());
}

TEST(QueueTest, WrapAroundLogic) {
    Queue<int> q(3);

    q.push(1); // 1
    q.push(2); // 1 2
    q.pop(); // 2

    q.push(3); // 2 3
    q.pop(); // 3

    q.push(4); // 3 4

    ASSERT_EQ(3, q.head());
    q.pop(); // 4

    ASSERT_EQ(4, q.head());
    q.pop();

    ASSERT_TRUE(q.is_empty());
}


TEST(QueueTest, Push_Error_Overflow) {
    Queue<int> q(2);
    q.push(1);
    q.push(2);

    ASSERT_TRUE(q.is_full());
    EXPECT_THROW(q.push(3), std::out_of_range);
}
TEST(QueueTest, Push_Error_Overflow_AfterPop) {
    Queue<int> q(2);
    q.push(1);
    q.pop();
    q.push(2);
    q.push(3);

    EXPECT_THROW(q.push(4), std::out_of_range);
    ASSERT_EQ(2, q.head());
}


TEST(QueueTest, Pop_Error_Underflow_Empty) {
    Queue<int> q(5);
    EXPECT_THROW(q.pop(), std::out_of_range);
}
TEST(QueueTest, Pop_Error_Underflow_AfterPopAll) {
    Queue<int> q(1);
    q.push(10);
    q.pop();

    EXPECT_THROW(q.pop(), std::out_of_range);
    ASSERT_TRUE(q.is_empty());
}


TEST(QueueTest, Head_Error_Empty) {
    Queue<int> q(5);
    EXPECT_THROW(q.head(), std::out_of_range);
}
TEST(QueueTest, Head_Error_AfterCycle) {
    Queue<int> q(2);
    q.push(1);
    q.push(2);
    q.pop();
    q.pop();

    EXPECT_THROW(q.head(), std::out_of_range);
    ASSERT_TRUE(q.is_empty());
}
