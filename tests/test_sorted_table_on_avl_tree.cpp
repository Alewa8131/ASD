// Copyright 2026 Alewa8131

#include <gtest/gtest.h>
#include <stdexcept>
#include "../lib_table/SortedTableOnAVLTree.h"

TEST(SortedTableOnAVLTreeTest, Constructor_EmptyTree) {
    SortedTableOnAVLTree<int, int> tree;
    EXPECT_TRUE(tree.is_empty());
}

TEST(SortedTableOnAVLTreeTest, InsertOneElement) {
    SortedTableOnAVLTree<int, int> tree;

    tree.insert(5, 10);

    ASSERT_FALSE(tree.is_empty());
    EXPECT_EQ(10, tree.find(5));
}

TEST(SortedTableOnAVLTreeTest, InsertSeveralElements) {
    SortedTableOnAVLTree<int, int> tree;

    tree.insert(5, 50);
    tree.insert(2, 20);
    tree.insert(8, 80);
    tree.insert(1, 10);
    tree.insert(3, 30);

    EXPECT_EQ(50, tree.find(5));
    EXPECT_EQ(20, tree.find(2));
    EXPECT_EQ(80, tree.find(8));
    EXPECT_EQ(10, tree.find(1));
    EXPECT_EQ(30, tree.find(3));
}

TEST(SortedTableOnAVLTreeTest, InsertDuplicateKey) {
    SortedTableOnAVLTree<int, int> tree;

    tree.insert(5, 10);
    EXPECT_THROW(tree.insert(5, 20), std::logic_error);
}

TEST(SortedTableOnAVLTreeTest, FindNonExisting) {
    SortedTableOnAVLTree<int, int> tree;

    tree.insert(5, 10);
    tree.insert(3, 20);

    EXPECT_THROW(tree.find(100), std::out_of_range);
}

TEST(SortedTableOnAVLTreeTest, EraseLeaf) {
    SortedTableOnAVLTree<int, int> tree;

    tree.insert(5, 50);
    tree.insert(2, 20);
    tree.insert(8, 80);

    tree.erase(2);

    EXPECT_THROW(tree.find(2), std::out_of_range);
    EXPECT_EQ(50, tree.find(5));
    EXPECT_EQ(80, tree.find(8));
}

TEST(SortedTableOnAVLTreeTest, EraseNodeWithOneChild) {
    SortedTableOnAVLTree<int, int> tree;

    tree.insert(5, 50);
    tree.insert(2, 20);
    tree.insert(1, 10);

    tree.erase(2);

    EXPECT_THROW(tree.find(2), std::out_of_range);
    EXPECT_EQ(10, tree.find(1));
}

TEST(SortedTableOnAVLTreeTest, EraseNodeWithTwoChildren) {
    SortedTableOnAVLTree<int, int> tree;

    tree.insert(5, 50);
    tree.insert(2, 20);
    tree.insert(8, 80);
    tree.insert(1, 10);
    tree.insert(3, 30);

    tree.erase(2);

    EXPECT_THROW(tree.find(2), std::out_of_range);
    EXPECT_EQ(10, tree.find(1));
    EXPECT_EQ(30, tree.find(3));
}

TEST(SortedTableOnAVLTreeTest, EraseRoot) {
    SortedTableOnAVLTree<int, int> tree;

    tree.insert(5, 50);
    tree.insert(2, 20);
    tree.insert(8, 80);

    tree.erase(5);

    EXPECT_THROW(tree.find(5), std::out_of_range);
}

TEST(SortedTableOnAVLTreeTest, EraseNonExisting) {
    SortedTableOnAVLTree<int, int> tree;

    tree.insert(5, 50);

    EXPECT_THROW(tree.erase(100), std::out_of_range);
}

TEST(SortedTableOnAVLTreeTest, ComplexOperations) {
    SortedTableOnAVLTree<int, int> tree;

    tree.insert(10, 1);
    tree.insert(5, 2);
    tree.insert(15, 3);
    tree.insert(3, 4);
    tree.insert(7, 5);
    tree.insert(12, 6);
    tree.insert(18, 7);

    tree.erase(5);
    tree.erase(15);

    EXPECT_THROW(tree.find(5), std::out_of_range);
    EXPECT_THROW(tree.find(15), std::out_of_range);

    EXPECT_EQ(4, tree.find(3));
    EXPECT_EQ(5, tree.find(7));
    EXPECT_EQ(6, tree.find(12));
    EXPECT_EQ(7, tree.find(18));
}
