// Copyright 2026 Alewa8131

#include <gtest/gtest.h>
#include <string>
#include <sstream>
#include "../lib_table/HashTableC.h"

TEST(HashTableC, EmptyTable) {
    HashTableC<int> table;
    EXPECT_EQ(table.count(), 0);
    EXPECT_TRUE(table.is_empty());
}

TEST(HashTableC, InsertOneElement) {
    HashTableC<int> table;
    table.insert("A", 10);

    EXPECT_EQ(table.count(), 1);
    EXPECT_EQ(table.find("A"), 10);
}

TEST(HashTableC, InsertSeveralElements) {
    HashTableC<int> table;
    table.insert("A", 10);
    table.insert("B", 20);
    table.insert("C", 30);

    EXPECT_EQ(table.count(), 3);
    EXPECT_EQ(table.find("A"), 10);
    EXPECT_EQ(table.find("B"), 20);
    EXPECT_EQ(table.find("C"), 30);
}

TEST(HashTableC, DuplicateInsertThrows) {
    HashTableC<int> table;
    table.insert("A", 10);

    EXPECT_THROW(table.insert("A", 20), std::logic_error);
}

TEST(HashTableC, FindNonExistingThrows) {
    HashTableC<int> table;
    table.insert("A", 10);

    EXPECT_THROW(table.find("B"), std::out_of_range);
}

TEST(HashTableC, EraseElement) {
    HashTableC<int> table;
    table.insert("A", 10);
    table.insert("B", 20);

    table.erase("A");

    EXPECT_EQ(table.count(), 1);
    EXPECT_THROW(table.find("A"), std::out_of_range);
    EXPECT_EQ(table.find("B"), 20);
}

TEST(HashTableC, EraseNonExistingThrows) {
    HashTableC<int> table;
    table.insert("A", 10);

    EXPECT_THROW(table.erase("B"), std::logic_error);
}

TEST(HashTableC, InsertEraseInsert) {
    HashTableC<int> table;
    table.insert("A", 1);
    table.erase("A");

    EXPECT_EQ(table.count(), 0);

    table.insert("A", 2);
    EXPECT_EQ(table.find("A"), 2);
    EXPECT_EQ(table.count(), 1);
}

TEST(HashTableC, FindReturnsReference) {
    HashTableC<int> table(10);
    table.insert("A", 10);

    table.find("A") = 50;

    EXPECT_EQ(table.find("A"), 50);
}

TEST(HashTableC, ConstFindWorks) {
    HashTableC<int> table(10);
    table.insert("A", 10);
    table.insert("B", 20);

    const auto& const_table = table;
    EXPECT_EQ(const_table.find("A"), 10);
    EXPECT_EQ(const_table.find("B"), 20);
}


TEST(HashTableC, IterationThroughGetAt) {
    HashTableC<int> table(10);
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

TEST(HashTableC, HeavyLoad) {
    size_t bucket_count = 10;
    HashTableC<int> table(bucket_count);

    for (int i = 0; i < 100; i++) {
        table.insert(std::to_string(i), i);
    }

    EXPECT_EQ(table.count(), 100);
    EXPECT_TRUE(table.is_full());

    for (int i = 0; i < 100; i++) {
        EXPECT_EQ(table.find(std::to_string(i)), i);
    }
}

TEST(HashTableC, CollisionHandling) {
    HashTableC<int> table(5);

    table.insert("key1", 1);
    table.insert("key2", 2);
    table.insert("key3", 3);

    EXPECT_EQ(table.count(), 3);
    EXPECT_EQ(table.find("key1"), 1);
    EXPECT_EQ(table.find("key2"), 2);
    EXPECT_EQ(table.find("key3"), 3);

    table.erase("key2");

    EXPECT_EQ(table.count(), 2);
    EXPECT_THROW(table.find("key2"), std::out_of_range);
    EXPECT_EQ(table.find("key3"), 3);
    EXPECT_EQ(table.find("key1"), 1);
}