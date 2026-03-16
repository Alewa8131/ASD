// Copyright 2026 Alewa8131

#include <gtest/gtest.h>
#include "../lib_tree/Tree.h"

TEST(UnsortedTableOnTree, EmptyTree) {

    Tree<std::string, int> tree;

    EXPECT_TRUE(tree.is_empty());
}

TEST(UnsortedTableOnTree, InsertOneElement) {

    Tree<std::string, int> tree;

    tree.insert("A", 10);

    EXPECT_FALSE(tree.is_empty());
    EXPECT_EQ(tree.find("A"), 10);
}

TEST(UnsortedTableOnTree, InsertSeveralElements) {

    Tree<std::string, int> tree;

    tree.insert("A", 10);
    tree.insert("B", 20);
    tree.insert("C", 30);

    EXPECT_EQ(tree.find("A"), 10);
    EXPECT_EQ(tree.find("B"), 20);
    EXPECT_EQ(tree.find("C"), 30);
}

TEST(UnsortedTableOnTree, DuplicateInsertThrows) {

    Tree<std::string, int> tree;

    tree.insert("A", 10);

    EXPECT_THROW(
        tree.insert("A", 20),
        std::logic_error
    );
}

TEST(UnsortedTableOnTree, FindNonExistingThrows) {

    Tree<std::string, int> tree;

    tree.insert("A", 10);

    EXPECT_THROW(
        tree.find("B"),
        std::out_of_range
    );
}

TEST(UnsortedTableOnTree, EraseElement) {

    Tree<std::string, int> tree;

    tree.insert("A", 10);
    tree.insert("B", 20);

    tree.erase("A");

    EXPECT_THROW(
        tree.find("A"),
        std::out_of_range
    );

    EXPECT_EQ(tree.find("B"), 20);
}



TEST(UnsortedTableOnTree, EraseNonExistingThrows) {

    Tree<std::string, int> tree;

    tree.insert("A", 10);

    EXPECT_THROW(
        tree.erase("B"),
        std::out_of_range
    );
}

TEST(UnsortedTableOnTree, InsertEraseInsert) {

    Tree<std::string, int> tree;

    tree.insert("A", 1);
    tree.erase("A");

    EXPECT_TRUE(tree.is_empty());

    tree.insert("A", 2);

    EXPECT_EQ(tree.find("A"), 2);
}

TEST(UnsortedTableOnTree, FindReturnsReference) {

    Tree<std::string, int> tree;

    tree.insert("A", 10);

    tree.find("A") = 50;

    EXPECT_EQ(tree.find("A"), 50);
}

TEST(UnsortedTableOnTree, ConstFindWorks) {

    Tree<std::string, int> tree;

    tree.insert("A", 10);
    tree.insert("B", 20);

    const auto& const_tree = tree;

    EXPECT_EQ(const_tree.find("A"), 10);
    EXPECT_EQ(const_tree.find("B"), 20);
}

TEST(UnsortedTableOnTree, ManyElements) {

    Tree<int, int> tree;

    for (int i = 0; i < 100; i++)
        tree.insert(i, i * 10);

    for (int i = 0; i < 100; i++)
        EXPECT_EQ(tree.find(i), i * 10);
}

TEST(UnsortedTableOnTree, RemoveAllElements) {

    Tree<int, int> tree;

    tree.insert(1, 10);
    tree.insert(2, 20);
    tree.insert(3, 30);

    tree.erase(1);
    tree.erase(2);
    tree.erase(3);

    EXPECT_TRUE(tree.is_empty());
}
