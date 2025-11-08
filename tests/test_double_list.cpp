// Copyright 2025 Alewa8131

#include <gtest/gtest.h>
#include <stdexcept>
#include "../lib_double_list/double_list.h"

TEST(DoubleListTest, DefaultConstructor) {
    DoubleList<int> list;
    ASSERT_TRUE(list.is_empty());
    ASSERT_EQ(list.size(), 0);
    ASSERT_EQ(list.head(), nullptr);
    ASSERT_EQ(list.tail(), nullptr);
}

TEST(DoubleListTest, StatusFunction_IsEmptyAndSize) {
    DoubleList<int> list;
    EXPECT_TRUE(list.is_empty());
    EXPECT_EQ(list.size(), 0);

    list.push_back(1);
    EXPECT_FALSE(list.is_empty());
    EXPECT_EQ(list.size(), 1);

    list.pop_front();
    EXPECT_TRUE(list.is_empty());
    EXPECT_EQ(list.size(), 0);
}

TEST(DoubleListTest, CopyConstructor_NonEmpty) {
    DoubleList<int> original;
    original.push_back(10);
    original.push_front(5);

    DoubleList<int> copy = original;

    ASSERT_EQ(copy.size(), 2);
    ASSERT_EQ(copy.head()->_value, 5);
    ASSERT_EQ(copy.tail()->_value, 10);

    ASSERT_EQ(copy.head()->_next, copy.tail());
    ASSERT_EQ(copy.tail()->_prev, copy.head());


    original.pop_front();

    ASSERT_EQ(original.size(), 1);
    ASSERT_EQ(copy.size(), 2);
    ASSERT_EQ(copy.head()->_value, 5);
}


TEST(DoubleListTest, PushFront_Multiple) {
    DoubleList<char> list;
    list.push_front('C');
    list.push_front('B');
    list.push_front('A');

    ASSERT_EQ(list.size(), 3);
    ASSERT_EQ(list.head()->_value, 'A');
    ASSERT_EQ(list.tail()->_value, 'C');

    ASSERT_EQ(list.head()->_next->_value, 'B'); // A -> B
    ASSERT_EQ(list.tail()->_prev->_value, 'B'); // B <- C
    ASSERT_EQ(list.head()->_next->_prev->_value, 'A'); // A <-> B
}

TEST(DoubleListTest, PushBack_Multiple) {
    DoubleList<int> list;
    list.push_back(1);
    list.push_back(2);
    list.push_back(3);

    ASSERT_EQ(list.size(), 3);
    ASSERT_EQ(list.head()->_value, 1);
    ASSERT_EQ(list.tail()->_value, 3);

    ASSERT_EQ(list.head()->_next->_value, 2); // 1 -> 2
    ASSERT_EQ(list.tail()->_prev->_value, 2); // 2 <- 3
}

TEST(DoubleListTest, InsertByPosition_Success) {
    DoubleList<int> list;
    list.push_back(10);
    list.push_back(40);

    list.insert(static_cast<size_t>(1), 20); // 10 20 40
    ASSERT_EQ(list.size(), 3);
    ASSERT_EQ(list.head()->_next->_value, 20);
    ASSERT_EQ(list.tail()->_prev->_value, 20);

    list.insert(static_cast<size_t>(0), 5); // 5 10 20 40
    ASSERT_EQ(list.head()->_value, 5);
    ASSERT_EQ(list.head()->_next->_prev->_value, 5);

    list.insert(static_cast<size_t>(4), 50); // 5 10 20 40 50
    ASSERT_EQ(list.tail()->_value, 50);
    ASSERT_EQ(list.tail()->_prev->_value, 40);
    ASSERT_EQ(list.size(), 5);
}

TEST(DoubleListTest, InsertByNode_Success) {
    DoubleList<int> list;
    list.push_back(10);
    list.push_back(30); 

    DoubleNode<int>* n10 = list.head();
    list.insert(n10, 20); // 10 20 30

    ASSERT_EQ(list.size(), 3);
    ASSERT_EQ(n10->_next->_value, 20); // 10 -> 20
    ASSERT_EQ(list.head()->_next->_prev->_value, 10); // 10 <- 20
    ASSERT_EQ(list.tail()->_prev->_value, 20); // 20 <- 30

    DoubleNode<int>* n30 = list.tail();
    list.insert(n30, 40); // 10 20 30 40

    ASSERT_EQ(list.tail()->_value, 40);
    ASSERT_EQ(list.tail()->_prev->_value, 30);
    ASSERT_EQ(n30->_next->_value, 40);
}

TEST(DoubleListTest, Insert_Error_OutOfBounds) {
    DoubleList<int> list;
    list.push_back(1);

    EXPECT_THROW(list.insert(static_cast<size_t>(2), 99), std::out_of_range);
    EXPECT_THROW(list.insert(list.head()->_next, 99), std::logic_error);
}


TEST(DoubleListTest, PopFront_Success) {
    DoubleList<int> list;
    list.push_back(10);
    list.push_back(20);

    list.pop_front(); // 20
    ASSERT_EQ(list.size(), 1);
    ASSERT_EQ(list.head()->_value, 20);
    ASSERT_EQ(list.head(), list.tail());
    ASSERT_EQ(list.head()->_prev, nullptr);

    list.pop_front();
    ASSERT_TRUE(list.is_empty());
}

TEST(DoubleListTest, PopBack_Success) {
    DoubleList<int> list;
    list.push_back(10);
    list.push_back(20);

    list.pop_back(); // 10
    ASSERT_EQ(list.size(), 1);
    ASSERT_EQ(list.head()->_value, 10);
    ASSERT_EQ(list.head(), list.tail());
    ASSERT_EQ(list.tail()->_next, nullptr);

    list.pop_back();
    ASSERT_TRUE(list.is_empty());
}

TEST(DoubleListTest, Pop_Error_Underflow) {
    DoubleList<int> list;
    EXPECT_THROW(list.pop_front(), std::logic_error);
    EXPECT_THROW(list.pop_back(), std::logic_error);
}

TEST(DoubleListTest, EraseByPosition_Success) {
    DoubleList<int> list;
    list.push_back(10);
    list.push_back(20);
    list.push_back(30);
    list.push_back(40); // 10 20 30 40

    list.erase(static_cast<size_t>(1)); // 10 30 40
    ASSERT_EQ(list.size(), 3);
    ASSERT_EQ(list.head()->_next->_value, 30);
    ASSERT_EQ(list.head()->_next->_prev->_value, 10); // 10 <-> 30

    list.erase(static_cast<size_t>(2)); // 10 30
    ASSERT_EQ(list.size(), 2);
    ASSERT_EQ(list.tail()->_value, 30);
    ASSERT_EQ(list.tail()->_next, nullptr);

    list.erase(static_cast<size_t>(0)); //30
    ASSERT_EQ(list.size(), 1);
    ASSERT_EQ(list.head()->_value, 30);
}

TEST(DoubleListTest, EraseByNode_Success) {
    DoubleList<int> list;
    list.push_back(10);
    list.push_back(20);
    list.push_back(30); // 10 20 30

    DoubleNode<int>* n20 = list.head()->_next;

    list.erase(n20); // 10 30
    ASSERT_EQ(list.size(), 2);
    ASSERT_EQ(list.head()->_next, list.tail()); // 10 -> 30
    ASSERT_EQ(list.tail()->_prev, list.head()); // 10 <- 30

    DoubleNode<int>* n10 = list.head();
    list.erase(n10); // 30

    DoubleNode<int>* n30 = list.head();
    list.erase(n30);
    ASSERT_TRUE(list.is_empty());
}

TEST(DoubleListTest, Erase_Error) {
    DoubleList<int> list;
    list.push_back(10);

    EXPECT_THROW(list.erase(static_cast<size_t>(1)), std::out_of_range);
    EXPECT_THROW(list.erase(nullptr), std::logic_error);

    list.pop_back();
    EXPECT_THROW(list.erase(static_cast<size_t>(0)), std::logic_error);
}


TEST(DoubleListTest, Iterator_ForwardIteration) {
    DoubleList<int> list;
    list.push_back(10);
    list.push_back(20);
    list.push_back(30);

    DoubleList<int>::Iterator it = list.begin();
    ASSERT_EQ(*it, 10);

    ++it;
    ASSERT_EQ(*it, 20);

    DoubleList<int>::Iterator old_it = it++;
    ASSERT_EQ(*old_it, 20);
    ASSERT_EQ(*it, 30);
}

TEST(DoubleListTest, Iterator_BackwardIteration_Modified) {
    DoubleList<int> list;
    list.push_back(10);
    list.push_back(20);
    list.push_back(30); // 10 20 30

    DoubleList<int>::Iterator it = list.begin();
    while (*it != 30) {
        ++it;
    }

    ASSERT_EQ(*it, 30);

    DoubleList<int>::Iterator old_it = it--;
    ASSERT_EQ(*old_it, 30);
    ASSERT_EQ(*it, 20);

    --it;
    ASSERT_EQ(*it, 10);

    old_it = it--;
    ASSERT_EQ(*old_it, 10);

    ASSERT_TRUE(it == nullptr);

    ASSERT_NO_THROW(--it);
    ASSERT_TRUE(it == nullptr);
}

TEST(DoubleListTest, Iterator_ReadWriteAccess) {
    DoubleList<int> list;
    list.push_back(1);
    list.push_back(2);
    list.push_back(3);

    DoubleList<int>::Iterator it = list.begin();

    ASSERT_EQ(*it, 1);

    *it = 100; // 100 2 3

    it++;
    *it = 200; // 100 200 3

    ASSERT_EQ(list.head()->_value, 100);
    ASSERT_EQ(list.head()->_next->_value, 200);

    --it;
    ASSERT_EQ(*it, 100);

    --it;
    ASSERT_TRUE(it == nullptr);

    EXPECT_THROW(*it, std::out_of_range);
}

TEST(DoubleListTest, Iterator_EmptyListAndEndBehavior) {
    DoubleList<int> empty_list;

    DoubleList<int>::Iterator it_empty = empty_list.begin();
    ASSERT_TRUE(it_empty == empty_list.end());

    ASSERT_NO_THROW(++it_empty);
    ASSERT_NO_THROW(--it_empty);
    ASSERT_TRUE(it_empty == nullptr);

    DoubleList<int> list;
    list.push_back(1);

    DoubleList<int>::Iterator it_end = list.end();
    ASSERT_TRUE(it_end == nullptr);

    ASSERT_TRUE(it_end != list.begin());

    EXPECT_THROW(*it_end, std::out_of_range);

    ASSERT_NO_THROW(--it_end);
    ASSERT_TRUE(it_end == nullptr);
}
