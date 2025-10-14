// Copyright 2025 Alewa8131

#include <gtest/gtest.h>
#include "../lib_priority_queue/priority_queue.h"

TEST(PriorityQueueTest, PushWithDifferentPriorities) {
    PriorityQueue<int> queue(5);

    queue.push(10, 1);
    queue.push(20, 3);
    queue.push(30, 2);

    EXPECT_EQ(queue.head(), 20);
}

TEST(PriorityQueueTest, PushWithSamePriorities) {
    PriorityQueue<int> queue(3);

    queue.push(10, 2);
    queue.push(20, 2);
    queue.push(30, 2);

    EXPECT_EQ(queue.head(), 10);
}

TEST(PriorityQueueTest, StabilityTest) {
    PriorityQueue<int> queue(4);

    queue.push(10, 2);
    queue.push(20, 2);
    queue.push(30, 1);
    queue.push(40, 2);

    queue.pop(); // priority 2 (10)
    EXPECT_EQ(queue.head(), 20); // Next priority 2

    queue.pop(); // 20
    EXPECT_EQ(queue.head(), 40); // Last priority 2

    queue.pop(); // 40
    EXPECT_EQ(queue.head(), 30); // priority 1
}


TEST(PriorityQueueTest, ComplexPriorityScenario) {
    PriorityQueue<int> queue(6);

    queue.push(10, 5);
    queue.push(20, 8);
    queue.push(30, 3);
    queue.push(40, 6);
    queue.push(50, 8);
    queue.push(60, 4);


    EXPECT_EQ(queue.head(), 20); // priority 8
    queue.pop();

    EXPECT_EQ(queue.head(), 50);  // priority 8
    queue.pop();

    EXPECT_EQ(queue.head(), 40);  // priority 6
    queue.pop();

    EXPECT_EQ(queue.head(), 10);  // priority 5
    queue.pop();

    EXPECT_EQ(queue.head(), 60);  // priority 4
    queue.pop();

    EXPECT_EQ(queue.head(), 30);  // priority 3
    queue.pop();

    EXPECT_TRUE(queue.is_empty());
}
