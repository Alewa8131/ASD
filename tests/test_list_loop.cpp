// Copyright 2025 Alewa8131

#include <gtest/gtest.h>
#include <stdexcept>
#include "../algorithms/list_loop.h"

TEST(ListLoopTest, NotLoop) {
    List<int> list;
    list.push_back(1);
    list.push_back(2);
    list.push_back(3);
    list.push_back(4);
    list.push_back(5);

    ASSERT_FALSE(is_looped1(list));
}

TEST(ListLoopTest, FirstLoop) {
    List<int> list;
    list.push_back(1);
    list.push_back(2);
    list.push_back(3);
    list.push_back(4);

    list.head()->_next->_next->_next->_next = list.head()->_next;

    ASSERT_TRUE(is_looped1(list));

    list.head()->_next->_next->_next->_next = nullptr;
}

TEST(ListLoopTest, OneLoop) {
    List<int> list;
    list.push_back(1);

    list.head()->_next = list.head();

    ASSERT_TRUE(is_looped1(list));

    list.head()->_next = nullptr;
}

TEST(ListLoopTest, OneNotLoop) {
    List<int> list;
    list.push_back(1);

    ASSERT_FALSE(is_looped1(list));
}

TEST(ListLoopTest, NullNotLoop) {
    List<int> list;

    ASSERT_FALSE(is_looped1(list));
}


TEST(ListLoopTest2, NotLoop) {
    List<int> list;
    list.push_back(1);
    list.push_back(2);
    list.push_back(3);
    list.push_back(4);
    list.push_back(5);

    ASSERT_FALSE(is_looped2(list));
}

TEST(ListLoopTest2, FirstLoop) {
    List<int> list;
    list.push_back(1);
    list.push_back(2);
    list.push_back(3);
    list.push_back(4);

    list.head()->_next->_next->_next->_next = list.head()->_next;

    ASSERT_TRUE(is_looped2(list));
}

TEST(ListLoopTest2, OneLoop) {
    List<int> list;
    list.push_back(1);

    list.head()->_next = list.head();

    ASSERT_TRUE(is_looped2(list));

    list.head()->_next = nullptr;
}

TEST(ListLoopTest2, OneNotLoop) {
    List<int> list;
    list.push_back(1);

    ASSERT_FALSE(is_looped2(list));
}

TEST(ListLoopTest2, NullNotLoop) {
    List<int> list;

    ASSERT_FALSE(is_looped2(list));
}

TEST(ListLoopTest2, LoopStartsAtHead) {
    List<int> list;
    list.push_back(1); // (Точка поломки)
    list.push_back(2);
    list.push_back(3);

    Node<int>* head_node = list.head();
    Node<int>* last_node = head_node->_next->_next;

    last_node->_next = head_node;

    ASSERT_TRUE(is_looped2(list));

    last_node->_next = nullptr;
}

TEST(ListLoopTest2, LoopStartsInMiddle) {
    List<int> list;
    list.push_back(10);
    list.push_back(20); // (Точка поломки)
    list.push_back(30);
    list.push_back(40);

    Node<int>* node_b = list.head()->_next;
    Node<int>* node_d = node_b->_next->_next;

    node_d->_next = node_b;

    ASSERT_TRUE(is_looped2(list));

    node_d->_next = nullptr;
}

TEST(ListLoopTest2, LoopStartsNearTail) {
    List<int> list;
    list.push_back(10);
    list.push_back(20);
    list.push_back(30); // (Точка поломки)
    list.push_back(40);
    list.push_back(50);

    Node<int>* node_c = list.head()->_next->_next;
    Node<int>* node_e = node_c->_next->_next;

    node_e->_next = node_c;

    ASSERT_TRUE(is_looped2(list));

    node_e->_next = nullptr;
}


TEST(ListLoopBreakPointTest, NoLoop_LargeList) {
    List<int> list;
    list.push_back(10);
    list.push_back(20);
    list.push_back(30);
    list.push_back(40);
    list.push_back(50);

    ASSERT_EQ(nullptr, find_list_loop_break_point(list));
}

TEST(ListLoopBreakPointTest, NoLoop_SmallList) {
    List<int> list;
    list.push_back(10);
    list.push_back(20);

    ASSERT_EQ(nullptr, find_list_loop_break_point(list));
}

TEST(ListLoopBreakPointTest, NoLoop_EdgeCases) {
    List<int> list;
    list.push_back(10);

    ASSERT_EQ(nullptr, find_list_loop_break_point(list));

    List<int> empty_list;
    ASSERT_EQ(nullptr, find_list_loop_break_point(empty_list));
}

TEST(ListLoopBreakPointTest, LoopStartsAtHead) {
    List<int> list;
    list.push_back(1); // (Точка поломки)
    list.push_back(2);
    list.push_back(3);

    Node<int>* head_node = list.head();
    Node<int>* last_node = head_node->_next->_next;

    last_node->_next = head_node;

    ASSERT_EQ(head_node, find_list_loop_break_point(list));

    last_node->_next = nullptr;
}

TEST(ListLoopBreakPointTest, LoopStartsAtHead_SingleNodeLoop) {
    List<int> list;
    list.push_back(1); // (Точка поломки)


    Node<int>* head_node = list.head();

    ASSERT_EQ(nullptr, find_list_loop_break_point(list));


    head_node->_next = head_node;

    ASSERT_EQ(head_node, find_list_loop_break_point(list)); 

    head_node->_next = nullptr;
}

TEST(ListLoopBreakPointTest, LoopStartsInMiddle) {
    List<int> list;
    list.push_back(10);
    list.push_back(20); // (Точка поломки)
    list.push_back(30);
    list.push_back(40);

    Node<int>* node_b = list.head()->_next;
    Node<int>* node_d = node_b->_next->_next;

    node_d->_next = node_b;

    ASSERT_EQ(node_b, find_list_loop_break_point(list));

    node_d->_next = nullptr;
}

TEST(ListLoopBreakPointTest, LoopStartsNearTail) {
    List<int> list;
    list.push_back(10);
    list.push_back(20);
    list.push_back(30); // (Точка поломки)
    list.push_back(40);
    list.push_back(50);

    Node<int>* node_c = list.head()->_next->_next;
    Node<int>* node_e = node_c->_next->_next;

    node_e->_next = node_c;

    ASSERT_EQ(node_c, find_list_loop_break_point(list));

    node_e->_next = nullptr;
}
