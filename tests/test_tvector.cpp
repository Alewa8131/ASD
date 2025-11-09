// Copyright 2025 Alewa8131

#include <gtest/gtest.h>
#include "../lib_tvector/tvector.h"

std::mt19937 engine(std::time(nullptr));

TEST(TVectorTest, DefaultConstructor) {
    TVector<int> vec;
    vec.resize(15);
    EXPECT_EQ(0u, vec.size());
    EXPECT_EQ(15u, vec.capacity());
}

TEST(TVectorTest, ConstructorWithSize) {
    TVector<int> vec(5);
    EXPECT_EQ(5u, vec.capacity());
    EXPECT_TRUE(vec.is_empty());
}

TEST(TVectorTest, InitializerListConstructor) {
    TVector<int> vec = { 1, 2, 3 };
    EXPECT_EQ(3u, vec.size());
    EXPECT_EQ(3, vec.at(2));
    EXPECT_EQ(2, vec.at(1));
    EXPECT_EQ(1, vec.front());
}

TEST(TVectorTest, ArrayConstructor) {
    int arr[] = { 10, 20, 30 };
    TVector<int> vec(arr, 3);
    EXPECT_EQ(3u, vec.size());
    EXPECT_EQ(30, vec.back());
}

TEST(TVectorTest, NullMemoryAfterShrink) {
    TVector<int> vec = { 1, 2, 3 };
    vec.pop_back();
    vec.pop_back();
    vec.pop_back();
    vec.shrink_to_fit();
    EXPECT_EQ(0u, vec.size());
    EXPECT_EQ(0u, vec.capacity());
}


TEST(TVectorTest, PushFront) {
    TVector<int> vec;
    vec.push_front(42);
    vec.push_front(7);
    EXPECT_EQ(2u, vec.size());
    EXPECT_EQ(7, vec.at(0));
    EXPECT_EQ(42, vec.at(1));
}

TEST(TVectorTest, PushFrontAfterDelete) {
    TVector<int> vec = { 1, 2, 3, 4 };
    vec.pop_front();
    vec.push_front(7);
    EXPECT_EQ(4u, vec.size());
    EXPECT_EQ(7, vec.at(0));
}

TEST(TVectorTest, PushBack) {
    TVector<int> vec;
    vec.push_back(10);
    vec.push_back(20);
    EXPECT_EQ(2u, vec.size());
    EXPECT_EQ(10, vec.at(0));
    EXPECT_EQ(20, vec.at(1));
}

TEST(TVectorTest, PopBack) {
    TVector<int> vec = { 1, 2, 3 };
    vec.pop_back();
    EXPECT_EQ(2u, vec.size());
    EXPECT_EQ(2, vec.back());
}

TEST(TVectorTest, PopTwoBack) {
    TVector<int> vec = { 1, 2, 3 };
    vec.pop_back();
    vec.pop_back();
    EXPECT_EQ(1u, vec.size());
    EXPECT_EQ(1, vec.back());
    EXPECT_EQ(1, vec.front());
}

TEST(TVectorTest, Erase) {
    TVector<int> vec = { 1, 2, 3, 4, 5, 6, 7, 8 };
    vec.erase(3);
    vec.erase(0);
    vec.erase(5);
    EXPECT_EQ(5u, vec.size());
    EXPECT_EQ(2, vec.at(0));
    EXPECT_EQ(3, vec.at(1));
    EXPECT_EQ(5, vec.at(2));
    EXPECT_EQ(6, vec.at(3));
    EXPECT_EQ(7, vec.at(4));
}

TEST(TVectorTest, InsertMiddle) {
    TVector<int> vec = { 1, 3 };
    vec.insert(1, 2);
    EXPECT_EQ(3u, vec.size());
    EXPECT_EQ(2, vec.at(1));
}

TEST(TVectorTest, EmplaceReplace) {
    TVector<int> vec = { 10, 20, 30 };
    vec.emplace(1, 99);
    EXPECT_EQ(99, vec.at(1));
}

TEST(TVectorTest, EmplaceOutOfRange) {
    TVector<int> vec = { 1, 2, 3 };
    EXPECT_THROW(vec.emplace(10, 42), std::out_of_range);
}

TEST(TVectorTest, Clear) {
    TVector<int> vec = { 1, 2, 3 };
    vec.clear();
    EXPECT_EQ(0u, vec.size());
    EXPECT_TRUE(vec.is_empty());
}

TEST(TVectorTest, ClearThenPushBack) {
    TVector<int> vec = { 1, 2, 3 };
    vec.clear();
    vec.push_back(99);
    EXPECT_EQ(1u, vec.size());
    EXPECT_EQ(99, vec.front());
}

TEST(TVectorTest, AssignFill) {
    TVector<int> vec;
    vec.assign(3, 7);
    EXPECT_EQ(3, vec.size());
    EXPECT_EQ(7, vec.at(0));
    EXPECT_EQ(7, vec.at(2));
}


TEST(TVectorTest, ShrinkToFitClearsDeleted) {
    TVector<int> vec = { 1, 2, 3, 4 };
    vec.erase(1);
    vec.shrink_to_fit();
    EXPECT_EQ(3u, vec.size());
    EXPECT_EQ(4u, vec.capacity());
    EXPECT_EQ(1, vec[0]);
    EXPECT_EQ(3, vec[1]);
    EXPECT_EQ(4, vec[2]);
}

TEST(TVectorTest, ShrinkToFitEmptyVector) {
    TVector<int> vec;
    vec.push_back(5);
    vec.clear();
    vec.shrink_to_fit();
    EXPECT_EQ(0u, vec.size());
    EXPECT_EQ(0u, vec.capacity());
}

TEST(TVectorTest, ShrinkToFitNoActionWhenFull) {
    TVector<int> vec;
    for (int i = 0; i < 5; ++i) {
        vec.push_back(i);
    }
    size_t before = vec.capacity();
    vec.shrink_to_fit();
    EXPECT_EQ(before, vec.capacity());
}

TEST(TVectorTest, ResizeExpand) {
    TVector<int> vec = { 1, 2 };
    vec.resize(15);
    EXPECT_EQ(15u, vec.capacity());
    EXPECT_EQ(1, vec[0]);
    EXPECT_EQ(2, vec[1]);
}

TEST(TVectorTest, ResizeShrink) {
    TVector<int> vec = { 1, 2, 3, 4 };
    vec.resize(2);
    EXPECT_EQ(2u, vec.size());
    EXPECT_EQ(2, vec.back());
}

TEST(TVectorTest, ResizeExpandSize) {
    TVector<int> vec = { 7 };
    vec.resize(5);
    EXPECT_EQ(1u, vec.size());
    EXPECT_TRUE(vec.capacity() >= 5);
}

TEST(TVectorTest, EnsureCapacityTriggersReserve) {
    TVector<int> vec;
    vec.push_back(1);
    vec.push_back(2);
    size_t cap_before = vec.capacity();
    vec.push_back(3);
    EXPECT_TRUE(vec.capacity() > cap_before);
}


TEST(TVectorTest, IndexOperator) {
    TVector<int> vec = { 5, 10, 15 };
    vec[1] = 100;
    EXPECT_EQ(100, vec.at(1));
}

TEST(TVectorTest, AtOperator) {
    TVector<int> vec = { 1, 2, 3, 4 };
    vec.erase(1);
    EXPECT_EQ(3, vec.at(1));
}

TEST(TVectorTest, AtOperatorException) {
    TVector<int> vec = { 1, 2 };
    EXPECT_THROW(vec.at(5), std::out_of_range);
}

TEST(TVectorTest, EqualsOperator) {
    TVector<int> a = { 1, 2, 3 };
    TVector<int> b = { 1, 2, 3 };
    EXPECT_EQ(true, a == b);
}

TEST(TVectorTest, NotEqualsOperator) {
    TVector<int> a = { 1, 2, 3 };
    TVector<int> b = { 1, 2 };
    EXPECT_EQ(true, a != b);
}


TEST(TVectorTest, ShuffleEmptyVector) {
    TVector<int> vec;
    shuffle(vec);
    EXPECT_EQ(0u, vec.size());
}

TEST(TVectorTest, ShuffleSingleElement) {
    TVector<int> vec;
    vec.push_back(777);
    shuffle(vec);
    EXPECT_EQ(1u, vec.size());
    EXPECT_EQ(777, vec[0]);
}

TEST(TVectorTest, HoarSortDeleted) {
    TVector<int> vec = { 5, 2, 9, 1, 4, 13, 18, 3 };
    vec.resize(10);
    vec.erase(2);
    vec.erase(2);
    hoar_sort(vec);
    EXPECT_EQ(6u, vec.size());
    EXPECT_EQ(2, vec.at(0));
    EXPECT_EQ(3, vec.at(1));
    EXPECT_EQ(4, vec.at(2));
    EXPECT_EQ(5, vec.at(3));
    EXPECT_EQ(13, vec.at(4));
    EXPECT_EQ(18, vec.at(5));
}

TEST(TVectorTest, HoarSortEmpty) {
    TVector<int> vec;
    hoar_sort(vec);
    EXPECT_EQ(0u, vec.size());
}

TEST(TVectorTest, HoarSortDuplicates) {
    TVector<int> vec = { 3, 1, 2, 1, 3 };
    hoar_sort(vec);
    EXPECT_EQ(5u, vec.size());
    EXPECT_EQ(1, vec.at(0));
    EXPECT_EQ(1, vec.at(1));
    EXPECT_EQ(2, vec.at(2));
    EXPECT_EQ(3, vec.at(3));
    EXPECT_EQ(3, vec.at(4));
}

TEST(TVectorTest, HoarSortReverseSorted) {
    TVector<int> vec = { 5, 4, 3, 2, 1, 0, -1, -2 };
    hoar_sort(vec);
    EXPECT_EQ(8u, vec.size());
    EXPECT_EQ(-2, vec.at(0));
    EXPECT_EQ(-1, vec.at(1));
    EXPECT_EQ(0, vec.at(2));
    EXPECT_EQ(1, vec.at(3));
    EXPECT_EQ(2, vec.at(4));
    EXPECT_EQ(3, vec.at(5));
    EXPECT_EQ(4, vec.at(6));
    EXPECT_EQ(5, vec.at(7));
}


TEST(TVectorTest, FindFirstBasic) {
    TVector<int> vec = { 10, 20, 30, 20, 40 };
    EXPECT_EQ(1, find_first(vec, 20));
    EXPECT_EQ(0, find_first(vec, 10));
    EXPECT_EQ(4, find_first(vec, 40));
    EXPECT_EQ(-1, find_first(vec, 99));
}

TEST(TVectorTest, FindLastBasic) {
    TVector<int> vec = { 10, 20, 30, 20, 40 };
    EXPECT_EQ(3, find_last(vec, 20));
    EXPECT_EQ(0, find_last(vec, 10));
    EXPECT_EQ(4, find_last(vec, 40));
    EXPECT_EQ(-1, find_last(vec, 99));
}

TEST(TVectorTest, FindAllBasic) {
    TVector<int> vec = { 5, 7, 5, 1, 5, 3 };
    TVector<size_t> result = find_all(vec, 5);
    EXPECT_EQ(3u, result.size());
    EXPECT_EQ(0u, result[0]);
    EXPECT_EQ(2u, result[1]);
    EXPECT_EQ(4u, result[2]);
}

TEST(TVectorTest, FindAllEmptyResult) {
    TVector<int> vec = { 1, 2, 3, 4 };
    vec.push_back(5);
    TVector<size_t> result = find_all(vec, 0);
    EXPECT_EQ(0u, result.size());
}


TEST(TVectorTest, Iterator_EmptyVectorIterating) {
    TVector<int> vec;
    EXPECT_EQ(vec.Ibegin(), vec.Iend());
    int count = 0;
    for (TVector<int>::Iterator it = vec.Ibegin(); it != vec.Iend(); ++it) {
        count++;
    }
    EXPECT_EQ(0, count);
}

TEST(TVectorTest, Iterator_ForwardIterationBasic) {
    TVector<int> vec = { 1, 2, 3, 4, 5 };
    std::vector<int> expected = { 1, 2, 3, 4, 5 };
    std::vector<int> result;

    for (int val : vec) {
        result.push_back(val);
    }
    EXPECT_EQ(expected, result);
}

TEST(TVectorIteratorTest, ForwardIterationSkipDeleted) {
    TVector<int> vec = { 10, 20, 30, 40, 50 };
    vec.erase(1);
    vec.erase(2);

    int expected_values[] = { 10, 30, 50 };
    int expected_index = 0;

    for (TVector<int>::Iterator it = vec.Ibegin(); it != vec.Iend(); ++it) {
        EXPECT_EQ(expected_values[expected_index], *it);
        expected_index++;
    }
    EXPECT_EQ(3u, vec.size());
}

TEST(TVectorIteratorTest, WriteAccessThroughDereference) {
    TVector<int> vec = { 1, 2, 3 };
    *vec.Ibegin() = 99;
    EXPECT_EQ(99, vec.at(0));
}

TEST(TVectorIteratorTest, WriteAccessInLoop) {
    TVector<int> vec = { 1, 2, 3, 4, 5 };
    int expected_values[] = { 2, 4, 6, 8, 10 };
    int multiplier = 2;

    for (int& val : vec) {
        val *= multiplier;
    }

    for (size_t i = 0; i < vec.size(); ++i) {
        EXPECT_EQ(expected_values[i], vec.at(i));
    }
}

TEST(TVectorIteratorTest, WriteAccessSkipDeleted) {
    TVector<int> vec = { 1, 2, 3, 4, 5 };
    vec.erase(1);

    TVector<int>::Iterator it = vec.Ibegin();
    ++it;
    *it = 333;

    EXPECT_EQ(1, vec.at(0));
    EXPECT_EQ(333, vec.at(1));
    EXPECT_EQ(4, vec.at(2));
}

TEST(TVectorIteratorTest, IncrementAndDecrementOperators) {
    TVector<int> vec = { 1, 2, 3, 4, 5 };

    TVector<int>::Iterator it = vec.Ibegin();
    ++it;
    EXPECT_EQ(2, *it);

    auto next_it = it++;
    EXPECT_EQ(2, *next_it);
    EXPECT_EQ(3, *it);

    --it;
    EXPECT_EQ(2, *it);

    auto prev_it = it--;
    EXPECT_EQ(2, *prev_it);
    EXPECT_EQ(1, *it);
}

TEST(TVectorIteratorTest, PlusEqualOperator) {
    TVector<int> vec = { 10, 20, 30, 40, 50, 60 };
    vec.erase(2); // 30
    vec.erase(3); // 50

    // 10, 20, 40, 60
    TVector<int>::Iterator it = vec.Ibegin();

    it += 2;
    EXPECT_EQ(40, *it);

    it += 1;
    EXPECT_EQ(60, *it);

    it += 10;
    EXPECT_EQ(vec.Iend(), it);
}

TEST(TVectorIteratorTest, MinusEqualOperator) {
    TVector<int> vec = { 10, 20, 30, 40, 50, 60 };
    vec.erase(1); // 20
    vec.erase(3); // 50

    // 10, 30, 40, 60
    TVector<int>::Iterator it = vec.Iend();
    --it;

    it -= 1;
    EXPECT_EQ(40, *it);

    it -= 2;
    EXPECT_EQ(10, *it);

    it -= 10;
    EXPECT_EQ(10, *it);
}
