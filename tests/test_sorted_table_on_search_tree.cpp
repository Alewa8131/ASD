// Copyright 2026 Alewa8131

#include <gtest/gtest.h>
#include "../lib_bstree/bstree.h"

TEST(BSTreeTest, Constructor_EmptyTree) {
    BSTree<int, int> tree;
    EXPECT_TRUE(tree.is_empty());
}

TEST(BSTreeTest, InsertOneElement) {
    BSTree<int, int> tree;

    tree.insert(5, 10);

    ASSERT_FALSE(tree.is_empty());
    ASSERT_NE(nullptr, tree.find(5));
    EXPECT_EQ(10, *tree.find(5));
}

TEST(BSTreeTest, InsertSeveralElements) {
    BSTree<int, int> tree;

    tree.insert(5, 50);
    tree.insert(2, 20);
    tree.insert(8, 80);
    tree.insert(1, 10);
    tree.insert(3, 30);

    EXPECT_EQ(50, *tree.find(5));
    EXPECT_EQ(20, *tree.find(2));
    EXPECT_EQ(80, *tree.find(8));
    EXPECT_EQ(10, *tree.find(1));
    EXPECT_EQ(30, *tree.find(3));
}

TEST(BSTreeTest, InsertDuplicateKey) {
    BSTree<int, int> tree;

    tree.insert(5, 10);
    EXPECT_THROW(tree.insert(5, 20), std::logic_error);
}

TEST(BSTreeTest, FindNonExisting) {
    BSTree<int, int> tree;

    tree.insert(5, 10);
    tree.insert(3, 20);

    EXPECT_EQ(nullptr, tree.find(100));
}

TEST(BSTreeTest, EraseLeaf) {
    BSTree<int, int> tree;

    tree.insert(5, 50);
    tree.insert(2, 20);
    tree.insert(8, 80);

    tree.erase(2);

    EXPECT_EQ(nullptr, tree.find(2));
    EXPECT_NE(nullptr, tree.find(5));
    EXPECT_NE(nullptr, tree.find(8));
}

TEST(BSTreeTest, EraseNodeWithOneChild) {
    BSTree<int, int> tree;

    tree.insert(5, 50);
    tree.insert(2, 20);
    tree.insert(1, 10);

    tree.erase(2);

    EXPECT_EQ(nullptr, tree.find(2));
    EXPECT_EQ(10, *tree.find(1));
}

TEST(BSTreeTest, EraseNodeWithTwoChildren) {
    BSTree<int, int> tree;

    tree.insert(5, 50);
    tree.insert(2, 20);
    tree.insert(8, 80);
    tree.insert(1, 10);
    tree.insert(3, 30);

    tree.erase(2);

    EXPECT_EQ(nullptr, tree.find(2));
    EXPECT_EQ(10, *tree.find(1));
    EXPECT_EQ(30, *tree.find(3));
}

TEST(BSTreeTest, EraseRoot) {
    BSTree<int, int> tree;

    tree.insert(5, 50);
    tree.insert(2, 20);
    tree.insert(8, 80);

    tree.erase(5);

    EXPECT_EQ(nullptr, tree.find(5));
}

TEST(BSTreeTest, EraseNonExisting) {
    BSTree<int, int> tree;

    tree.insert(5, 50);

    EXPECT_THROW(tree.erase(100), std::out_of_range);
}

TEST(BSTreeTest, ComplexOperations) {
    BSTree<int, int> tree;

    tree.insert(10, 1);
    tree.insert(5, 2);
    tree.insert(15, 3);
    tree.insert(3, 4);
    tree.insert(7, 5);
    tree.insert(12, 6);
    tree.insert(18, 7);

    tree.erase(5);
    tree.erase(15);

    EXPECT_EQ(nullptr, tree.find(5));
    EXPECT_EQ(nullptr, tree.find(15));

    EXPECT_EQ(4, *tree.find(3));
    EXPECT_EQ(5, *tree.find(7));
    EXPECT_EQ(6, *tree.find(12));
    EXPECT_EQ(7, *tree.find(18));
}
