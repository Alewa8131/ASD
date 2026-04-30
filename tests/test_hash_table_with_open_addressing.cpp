// Copyright 2026 Alewa8131

#include <gtest/gtest.h>
#include <string>
#include <sstream>
#include "../lib_table/HashTableOA.h"

TEST(HashTableOA, EmptyTable) {
    HashTableOA<int> table;
    EXPECT_EQ(table.count(), 0);
    EXPECT_TRUE(table.is_empty());
}

TEST(HashTableOA, InsertOneElement) {
    HashTableOA<int> table;
    table.insert("A", 10);

    EXPECT_EQ(table.count(), 1);
    EXPECT_EQ(table.find("A"), 10);
}

TEST(HashTableOA, InsertSeveralElements) {
    HashTableOA<int> table;
    table.insert("A", 10);
    table.insert("B", 20);
    table.insert("C", 30);

    EXPECT_EQ(table.count(), 3);
    EXPECT_EQ(table.find("A"), 10);
    EXPECT_EQ(table.find("B"), 20);
    EXPECT_EQ(table.find("C"), 30);
}

TEST(HashTableOA, DuplicateInsertThrows) {
    HashTableOA<int> table;
    table.insert("A", 10);

    EXPECT_THROW(table.insert("A", 20), std::logic_error);
}

TEST(HashTableOA, FindNonExistingThrows) {
    HashTableOA<int> table;
    table.insert("A", 10);

    EXPECT_THROW(table.find("B"), std::out_of_range);
}

TEST(HashTableOA, EraseElement) {
    HashTableOA<int> table;
    table.insert("A", 10);
    table.insert("B", 20);

    table.erase("A");

    EXPECT_EQ(table.count(), 1);
    EXPECT_THROW(table.find("A"), std::out_of_range);
    EXPECT_EQ(table.find("B"), 20);
}

TEST(HashTableOA, EraseNonExistingThrows) {
    HashTableOA<int> table;
    table.insert("A", 10);

    EXPECT_THROW(table.erase("B"), std::logic_error);
}

TEST(HashTableOA, InsertEraseInsert) {
    HashTableOA<int> table;
    table.insert("A", 1);
    table.erase("A");

    EXPECT_EQ(table.count(), 0);

    table.insert("A", 2);
    EXPECT_EQ(table.find("A"), 2);
    EXPECT_EQ(table.count(), 1);
}

TEST(HashTableOA, FindReturnsReference) {
    HashTableOA<int> table;
    table.insert("A", 10);

    table.find("A") = 50;

    EXPECT_EQ(table.find("A"), 50);
}

TEST(HashTableOA, ConstFindWorks) {
    HashTableOA<int> table;
    table.insert("A", 10);
    table.insert("B", 20);

    const auto& const_table = table;
    EXPECT_EQ(const_table.find("A"), 10);
    EXPECT_EQ(const_table.find("B"), 20);
}


TEST(HashTableOA, IterationThroughGetAt) {
    HashTableOA<int> table(10);
    table.insert("A", 10);
    table.insert("B", 20);

    size_t count = 0;
    for (size_t i = 0; i < table.count(); ++i) {
        std::string key = table.get_key_at(i);
        int val = table.get_value_at(i);
        if (key == "A") EXPECT_EQ(val, 10);
        else if (key == "B") EXPECT_EQ(val, 20);
        count++;
    }
    EXPECT_EQ(count, 2);
}

TEST(HashTableOA, FillToCapacity) {
    size_t size = 50;
    HashTableOA<int> table(size);

    for (int i = 0; i < size; i++) {
        table.insert(std::to_string(i), i);
    }

    EXPECT_TRUE(table.is_full());
    EXPECT_EQ(table.count(), size);
    EXPECT_THROW(table.insert("overflow", 999), std::out_of_range);

    for (int i = 0; i < size; i++) {
        EXPECT_EQ(table.find(std::to_string(i)), i);
    }
}

TEST(HashTableOA, CollisionHandling) {
    HashTableOA<int> table(5);

    table.insert("aA", 1);
    table.insert("aF", 2);
    table.insert("aK", 3);

    EXPECT_EQ(table.find("aA"), 1);  // hash = 97 * 31 + 65 = 3007 + 65 = 3072
    EXPECT_EQ(table.find("aF"), 2);  // hash = 97 * 31 + 70 = 3007 + 70 = 3077
    EXPECT_EQ(table.find("aK"), 3);  // hash = 97 * 31 + 75 = 3007 + 75 = 3082

    table.erase("aF");

    EXPECT_EQ(table.find("aK"), 3);

    EXPECT_THROW(table.find("aF"), std::out_of_range);

    EXPECT_NO_THROW(table.insert("aF", 2));
}
