// Copyright 2026 Alewa8131

#include <gtest/gtest.h>
#include "../lib_table/SortedTableOnArr.h"

TEST(SortedTableOnArr, EmptyTable) {

    SortedTableOnArr<std::string, int> table;

    EXPECT_TRUE(table.is_empty());
}

TEST(SortedTableOnArr, InsertOneElement) {

    SortedTableOnArr<std::string, int> table;

    table.insert("A", 10);

    EXPECT_EQ(table.find("A"), 10);
}

TEST(SortedTableOnArr, InsertKeepsOrder) {

    SortedTableOnArr<int, int> table;

    table.insert(5, 50);
    table.insert(1, 10);
    table.insert(3, 30);

    EXPECT_EQ(table.find(1), 10);
    EXPECT_EQ(table.find(3), 30);
    EXPECT_EQ(table.find(5), 50);
}

TEST(SortedTableOnArr, DuplicateInsertThrows) {

    SortedTableOnArr<int, int> table;

    table.insert(1, 10);

    EXPECT_THROW(
        table.insert(1, 20),
        std::logic_error
    );
}

TEST(SortedTableOnArr, FindNonExistingThrows) {

    SortedTableOnArr<int, int> table;

    table.insert(1, 10);

    EXPECT_THROW(
        table.find(5),
        std::out_of_range
    );
}

TEST(SortedTableOnArr, EraseElement) {

    SortedTableOnArr<int, int> table;

    table.insert(1, 10);
    table.insert(2, 20);

    table.erase(1);

    EXPECT_THROW(
        table.find(1),
        std::out_of_range
    );

    EXPECT_EQ(table.find(2), 20);
}

TEST(SortedTableOnArr, EraseNonExistingThrows) {

    SortedTableOnArr<int, int> table;

    table.insert(1, 10);

    EXPECT_THROW(
        table.erase(2),
        std::out_of_range
    );
}

TEST(SortedTableOnArr, InsertEraseInsert) {

    SortedTableOnArr<int, int> table;

    table.insert(1, 10);
    table.erase(1);

    EXPECT_TRUE(table.is_empty());

    table.insert(1, 50);

    EXPECT_EQ(table.find(1), 50);
}

TEST(SortedTableOnArr, FindReturnsReference) {

    SortedTableOnArr<int, int> table;

    table.insert(1, 10);

    table.find(1) = 100;

    EXPECT_EQ(table.find(1), 100);
}

TEST(SortedTableOnArr, ConstFindWorks) {

    SortedTableOnArr<int, int> table;

    table.insert(1, 10);
    table.insert(2, 20);

    const auto& const_table = table;

    EXPECT_EQ(const_table.find(1), 10);
    EXPECT_EQ(const_table.find(2), 20);
}

TEST(SortedTableOnArr, OutputOperator) {

    SortedTableOnArr<int, int> table;

    table.insert(2, 20);
    table.insert(1, 10);

    std::stringstream ss;

    ss << table;

    std::string output = ss.str();

    EXPECT_TRUE(output.find("1 : 10") != std::string::npos);
    EXPECT_TRUE(output.find("2 : 20") != std::string::npos);
}

TEST(SortedTableOnArr, ManyElements) {

    SortedTableOnArr<int, int> table;

    for (int i = 0; i < 100; i++)
        table.insert(i, i * 10);

    for (int i = 0; i < 100; i++)
        EXPECT_EQ(table.find(i), i * 10);
}

TEST(SortedTableOnArr, RemoveAllElements) {

    SortedTableOnArr<int, int> table;

    table.insert(1, 10);
    table.insert(2, 20);
    table.insert(3, 30);

    table.erase(1);
    table.erase(2);
    table.erase(3);

    EXPECT_TRUE(table.is_empty());
}

#include <../lib_polynom/polynom.h>
TEST(SortedTableOnArr, WorkWithPolynom) {

    SortedTableOnArr<std::string, Polynom> table;

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
