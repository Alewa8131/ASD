// Copyright 2025 Alewa8131

#include <gtest/gtest.h>
#include <stdexcept>
#include "../lib_list/list.h"

TEST(ListTest, DefaultConstructor) {
    List<int> list;
    ASSERT_TRUE(list.is_empty());
    ASSERT_EQ(list.size(), 0);
}

TEST(ListTest, CopyConstructor_Empty) {
    List<double> original;
    List<double> copy = original;
    ASSERT_TRUE(copy.is_empty());
    ASSERT_EQ(copy.size(), 0);
}

TEST(ListTest, CopyConstructor_NonEmpty) {
    List<int> original;
    original.push_back(10);
    original.push_front(5);

    List<int> copy = original;

    ASSERT_EQ(copy.size(), 2);
    ASSERT_EQ(copy.head()->_value, 5);
    ASSERT_EQ(copy.head()->_next->_value, 10);

    original.pop_front();

    ASSERT_EQ(original.size(), 1);

    ASSERT_EQ(copy.size(), 2);
    ASSERT_EQ(copy.head()->_value, 5);
}


TEST(ListTest, PushFront_Multiple) {
    List<char> list;
    list.push_front('C');
    list.push_front('B');
    list.push_front('A');

    ASSERT_EQ(list.size(), 3);
    ASSERT_EQ(list.head()->_value, 'A');
    ASSERT_EQ(list.head()->_next->_next->_value, 'C');
}

TEST(ListTest, PushBack_Multiple) {
    List<int> list;
    list.push_back(1);
    list.push_back(2);
    list.push_back(3);

    ASSERT_EQ(list.size(), 3);
    ASSERT_EQ(list.head()->_value, 1);
    ASSERT_EQ(list.head()->_next->_next->_value, 3);
}

TEST(ListTest, InsertByPosition_Success) {
    List<int> list;
    list.push_back(10);
    list.push_back(30); // 10, 30

    list.insert(1, 20); // 10, 20, 30
    ASSERT_EQ(list.size(), 3);
    ASSERT_EQ(list.head()->_next->_value, 20);

    list.insert(static_cast<size_t>(0), 5); // 5, 10, 20, 30
    ASSERT_EQ(list.head()->_value, 5);
    ASSERT_EQ(list.size(), 4);

    list.insert(4, 40); // 5, 10, 20, 30, 40
    ASSERT_EQ(list.size(), 5);
}

TEST(ListTest, InsertByPosition_Error_OutOfBounds) {
    List<int> list;
    list.push_back(1);

    EXPECT_THROW(list.insert(2, 99), std::out_of_range);
    ASSERT_NO_THROW(list.insert(1, 2));
    ASSERT_EQ(list.size(), 2);
}

TEST(ListTest, PopFront_Success) {
    List<int> list;
    list.push_back(10);
    list.push_back(20);

    list.pop_front();
    ASSERT_EQ(list.size(), 1);
    ASSERT_EQ(list.head()->_value, 20);

    list.pop_front();
    ASSERT_TRUE(list.is_empty());
}

TEST(ListTest, PopFront_Error_Underflow) {
    List<int> list;
    EXPECT_THROW(list.pop_front(), std::logic_error);

    list.push_front(1);
    list.pop_front();
    EXPECT_THROW(list.pop_front(), std::logic_error);
}

TEST(ListTest, PopBack_Success) {
    List<int> list;
    list.push_back(10);
    list.push_back(20);

    list.pop_back();
    ASSERT_EQ(list.size(), 1);
    ASSERT_EQ(list.head()->_value, 10);

    list.pop_back();
    ASSERT_TRUE(list.is_empty());
}

TEST(ListTest, PopBack_Error_Underflow) {
    List<int> list;
    EXPECT_THROW(list.pop_back(), std::logic_error);

    list.push_back(1);
    list.pop_back();
    EXPECT_THROW(list.pop_back(), std::logic_error);
}


TEST(ListTest, EraseByPosition_Success) {
    List<int> list;
    list.push_back(1);
    list.push_back(2);
    list.push_back(3);

    list.erase(1);  // Удаление 2
    ASSERT_EQ(list.size(), 2);
    ASSERT_EQ(list.head()->_next->_value, 3);

    list.erase(static_cast<size_t>(0));  // Удаление 1
    ASSERT_EQ(list.head()->_value, 3);

    list.erase(static_cast<size_t>(0));  // Удаление 3
    ASSERT_TRUE(list.is_empty());
}

TEST(ListTest, EraseByPosition_Error_OutOfBounds) {
    List<int> list;
    list.push_back(10);

    EXPECT_THROW(list.erase(1), std::out_of_range);
    EXPECT_THROW(list.erase(10), std::out_of_range);
}

TEST(ListTest, StatusFunction_IsEmpty) {
    List<int> list;
    EXPECT_TRUE(list.is_empty());

    list.push_back(1);
    EXPECT_FALSE(list.is_empty());

    list.pop_front();
    EXPECT_TRUE(list.is_empty());
}
