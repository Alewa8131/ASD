// Copyright 2026 Alewa8131

#include <gtest/gtest.h>
#include "../lib_table/UnsortedTableOnList.h"

TEST(UnsortedTableOnList, EmptyTable) {

    UnsortedTableOnList<std::string, int> table;

    EXPECT_TRUE(table.is_empty());
}

TEST(UnsortedTableOnList, InsertOneElement) {

    UnsortedTableOnList<std::string, int> table;

    table.insert("A", 10);

    EXPECT_FALSE(table.is_empty());
    EXPECT_EQ(table.find("A"), 10);
}

TEST(UnsortedTableOnList, InsertSeveralElements) {

    UnsortedTableOnList<std::string, int> table;

    table.insert("A", 10);
    table.insert("B", 20);
    table.insert("C", 30);

    EXPECT_EQ(table.find("A"), 10);
    EXPECT_EQ(table.find("B"), 20);
    EXPECT_EQ(table.find("C"), 30);
}

TEST(UnsortedTableOnList, DuplicateInsertThrows) {

    UnsortedTableOnList<std::string, int> table;

    table.insert("A", 10);

    EXPECT_THROW(
        table.insert("A", 20),
        std::logic_error
    );
}

TEST(UnsortedTableOnList, FindNonExistingThrows) {

    UnsortedTableOnList<std::string, int> table;

    table.insert("A", 10);

    EXPECT_THROW(
        table.find("B"),
        std::out_of_range
    );
}

TEST(UnsortedTableOnList, EraseElement) {

    UnsortedTableOnList<std::string, int> table;

    table.insert("A", 10);
    table.insert("B", 20);

    table.erase("A");

    EXPECT_THROW(
        table.find("A"),
        std::out_of_range
    );

    EXPECT_EQ(table.find("B"), 20);
}

TEST(UnsortedTableOnList, EraseNonExistingThrows) {

    UnsortedTableOnList<std::string, int> table;

    table.insert("A", 10);

    EXPECT_THROW(
        table.erase("B"),
        std::out_of_range
    );
}

TEST(UnsortedTableOnList, InsertEraseInsert) {

    UnsortedTableOnList<std::string, int> table;

    table.insert("A", 1);
    table.erase("A");

    EXPECT_TRUE(table.is_empty());

    table.insert("A", 2);

    EXPECT_EQ(table.find("A"), 2);
}

TEST(UnsortedTableOnList, FindReturnsReference) {

    UnsortedTableOnList<std::string, int> table;

    table.insert("A", 10);

    table.find("A") = 50;

    EXPECT_EQ(table.find("A"), 50);
}

TEST(UnsortedTableOnList, ConstFindWorks) {

    UnsortedTableOnList<std::string, int> table;

    table.insert("A", 10);
    table.insert("B", 20);

    const auto& const_table = table;

    EXPECT_EQ(const_table.find("A"), 10);
    EXPECT_EQ(const_table.find("B"), 20);
}

TEST(UnsortedTableOnList, OutputOperator) {

    UnsortedTableOnList<std::string, int> table;

    table.insert("A", 10);
    table.insert("B", 20);

    std::stringstream ss;

    ss << table;

    std::string output = ss.str();

    EXPECT_TRUE(output.find("A : 10") != std::string::npos);
    EXPECT_TRUE(output.find("B : 20") != std::string::npos);
}

TEST(UnsortedTableOnList, ManyElements) {

    UnsortedTableOnList<int, int> table;

    for (int i = 0; i < 100; i++)
        table.insert(i, i * 5);

    for (int i = 0; i < 100; i++)
        EXPECT_EQ(table.find(i), i * 5);
}

TEST(UnsortedTableOnList, RemoveAllElements) {

    UnsortedTableOnList<int, int> table;

    table.insert(1, 10);
    table.insert(2, 20);
    table.insert(3, 30);

    table.erase(1);
    table.erase(2);
    table.erase(3);

    EXPECT_TRUE(table.is_empty());
}
