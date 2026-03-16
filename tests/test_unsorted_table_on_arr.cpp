// Copyright 2026 Alewa8131

#include <gtest/gtest.h>
#include "../lib_table/UnsortedTableOnArr.h"

TEST(UnsortedTableOnArr, EmptyTable) {

    UnsortedTableOnArr<std::string, int> table;

    EXPECT_TRUE(table.is_empty());
}

TEST(UnsortedTableOnArr, InsertOneElement) {

    UnsortedTableOnArr<std::string, int> table;

    table.insert("A", 10);

    EXPECT_FALSE(table.is_empty());
    EXPECT_EQ(table.find("A"), 10);
}

TEST(UnsortedTableOnArr, InsertSeveralElements) {

    UnsortedTableOnArr<std::string, int> table;

    table.insert("A", 10);
    table.insert("B", 20);
    table.insert("C", 30);

    EXPECT_EQ(table.find("A"), 10);
    EXPECT_EQ(table.find("B"), 20);
    EXPECT_EQ(table.find("C"), 30);
}

TEST(UnsortedTableOnArr, DuplicateInsertThrows) {

    UnsortedTableOnArr<std::string, int> table;

    table.insert("A", 10);

    EXPECT_THROW(
        table.insert("A", 20),
        std::logic_error
    );
}

TEST(UnsortedTableOnArr, FindNonExistingThrows) {

    UnsortedTableOnArr<std::string, int> table;

    table.insert("A", 10);

    EXPECT_THROW(
        table.find("B"),
        std::out_of_range
    );
}

TEST(UnsortedTableOnArr, EraseElement) {

    UnsortedTableOnArr<std::string, int> table;

    table.insert("A", 10);
    table.insert("B", 20);

    table.erase("A");

    EXPECT_THROW(
        table.find("A"),
        std::out_of_range
    );

    EXPECT_EQ(table.find("B"), 20);
}

TEST(UnsortedTableOnArr, EraseNonExistingThrows) {

    UnsortedTableOnArr<std::string, int> table;

    table.insert("A", 10);

    EXPECT_THROW(
        table.erase("B"),
        std::out_of_range
    );
}

TEST(UnsortedTableOnArr, InsertEraseInsert) {

    UnsortedTableOnArr<std::string, int> table;

    table.insert("A", 1);
    table.erase("A");

    EXPECT_TRUE(table.is_empty());

    table.insert("A", 2);

    EXPECT_EQ(table.find("A"), 2);
}

TEST(UnsortedTableOnArr, FindReturnsReference) {

    UnsortedTableOnArr<std::string, int> table;

    table.insert("A", 10);

    table.find("A") = 50;

    EXPECT_EQ(table.find("A"), 50);
}

TEST(UnsortedTableOnArr, ConstFindWorks) {

    UnsortedTableOnArr<std::string, int> table;

    table.insert("A", 10);
    table.insert("B", 20);

    const auto& const_table = table;

    EXPECT_EQ(const_table.find("A"), 10);
    EXPECT_EQ(const_table.find("B"), 20);
}

TEST(UnsortedTableOnArr, OutputOperator) {

    UnsortedTableOnArr<std::string, int> table;

    table.insert("A", 10);
    table.insert("B", 20);

    std::stringstream ss;

    ss << table;

    std::string output = ss.str();

    EXPECT_TRUE(output.find("A : 10") != std::string::npos);
    EXPECT_TRUE(output.find("B : 20") != std::string::npos);
}

TEST(UnsortedTableOnArr, ManyElements) {

    UnsortedTableOnArr<int, int> table;

    for (int i = 0; i < 100; i++)
        table.insert(i, i * 10);

    for (int i = 0; i < 100; i++)
        EXPECT_EQ(table.find(i), i * 10);
}

TEST(UnsortedTableOnArr, RemoveAllElements) {

    UnsortedTableOnArr<int, int> table;

    table.insert(1, 10);
    table.insert(2, 20);
    table.insert(3, 30);

    table.erase(1);
    table.erase(2);
    table.erase(3);

    EXPECT_TRUE(table.is_empty());
}

#include <../lib_polynom/polynom.h>
TEST(UnsortedTableOnArr, WorkWithPolynom) {

    UnsortedTableOnArr<std::string, Polynom> table;

    Polynom p1("x^2+y");
    Polynom p2("x^2yz+2y^3");

    table.insert("P1", p1);
    table.insert("P2", p2);

    EXPECT_EQ(
        table.find("P1").value(1, 1, 1),
        p1.value(1, 1, 1)
    );
    EXPECT_EQ(
        table.find("P2").value(1, 1, 1),
        p2.value(1, 1, 1)
    );
}
