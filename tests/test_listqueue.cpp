// Copyright 2026 Alewa8131

#include <gtest/gtest.h>
#include "../lib_listqueue/listqueue.h"

TEST(ListQueueTest, Constructor) {
    ListQueue<int> q;
    EXPECT_TRUE(q.is_empty());
}

TEST(ListQueueTest, PushChangesState) {
    ListQueue<int> q;

    q.push(1);

    EXPECT_FALSE(q.is_empty());
}

TEST(ListQueueTest, Basic_PushPop) {
    ListQueue<int> q;
    ASSERT_TRUE(q.is_empty());

    q.push(10);
    q.push(20);

    ASSERT_EQ(10, q.head());
    q.pop();

    ASSERT_EQ(20, q.head());
    q.pop();

    ASSERT_TRUE(q.is_empty());
}

TEST(ListQueueTest, WrapAroundLogic) {
    ListQueue<int> q;

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

TEST(ListQueueTest, LargeSequence) {
    ListQueue<int> q;

    for (int i = 0; i < 100; ++i)
        q.push(i);

    for (int i = 0; i < 100; ++i) {
        ASSERT_EQ(i, q.head());
        q.pop();
    }
}

TEST(ListQueueTest, Pop_Error_Empty) {
    ListQueue<int> q;
    EXPECT_THROW(q.pop(), std::out_of_range);
}
TEST(ListQueueTest, Pop_Error_AfterPopAll) {
    ListQueue<int> q;
    q.push(10);
    q.pop();

    EXPECT_THROW(q.pop(), std::out_of_range);
    ASSERT_TRUE(q.is_empty());
}

TEST(ListQueueTest, Head_Error_Empty) {
    ListQueue<int> q;
    EXPECT_THROW(q.head(), std::out_of_range);
}
TEST(ListQueueTest, Head_Error_AfterCycle) {
    ListQueue<int> q;
    q.push(1);
    q.push(2);
    q.pop();
    q.pop();

    EXPECT_THROW(q.head(), std::out_of_range);
    ASSERT_TRUE(q.is_empty());
}
