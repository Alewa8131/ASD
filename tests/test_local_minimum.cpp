// Copyright 2025 Alewa8131

#include <gtest/gtest.h>
#include <cstdlib>
#include <ctime>
#include <stdexcept>
#include "../lib_tvector/tvector.h"
#include "../lib_matrix/matrix.h"
#include "../algorithms/local_minimum.h"

template<class T>
bool IsValidLocalMinimum(T result, const TVector<T>& valid_minima) {
    for (size_t i = 0; i < valid_minima.size(); ++i) {
        if (valid_minima.at(i) == result) {
            return true;
        }
    }
    return false;
}

const int NUM_RUNS = 10;

class RandomSeedEnvironment : public testing::Environment {
public:
    void SetUp() override {
        srand(static_cast<unsigned>(time(nullptr)));
    }
};
testing::Environment* const env = testing::AddGlobalTestEnvironment(new RandomSeedEnvironment);

TEST(LocalMinimumTest, SingleMinimum) {
    Matrix<int> B({
        {1, 2, 3},
        {4, 5, 6},
        {7, 8, 9}
        });
    TVector<int> expected_minima = { 1 };

    int successful_runs = 0;

    for (int i = 0; i < NUM_RUNS; ++i) {
        int result = find_minimum(B);
        ASSERT_TRUE(IsValidLocalMinimum(result, expected_minima))
            << "Run " << i + 1 << " failed. Expected: 1. Got: " << result;
        successful_runs++;
    }
    EXPECT_EQ(NUM_RUNS, successful_runs);
}

TEST(LocalMinimumTest, TwoDistinctMinima) {
    Matrix<int> A({
        {3, 1, 2},
        {5, 8, 4},
        {7, 6, 9}
        });
    TVector<int> expected_minima = { 1, 6 };
    int successful_runs = 0;

    for (int i = 0; i < NUM_RUNS; ++i) {
        int result = find_minimum(A);
        ASSERT_TRUE(IsValidLocalMinimum(result, expected_minima))
            << "Run " << i + 1 << " failed. Expected one of: 1, 6. Got: " << result;

        successful_runs++;
    }
    EXPECT_EQ(NUM_RUNS, successful_runs);
}

TEST(LocalMinimumTest, Matrix4x4) {
    Matrix<int> D({
        {30, 20, 40, 50},
        {15, 2, 30, 60},
        {14, 12, 50, 70},
        {10, 11, 80, 90}
        });
    TVector<int> expected_minima = { 2, 10 };
    int successful_runs = 0;

    for (int i = 0; i < NUM_RUNS; ++i) {
        int result = find_minimum(D);
        ASSERT_TRUE(IsValidLocalMinimum(result, expected_minima))
            << "Run " << i + 1 << " failed. Expected one of: 2, 10. Got: " << result;
        successful_runs++;
    }
    EXPECT_EQ(NUM_RUNS, successful_runs);
}

TEST(LocalMinimumTest, Matrix1x1) {
    Matrix<int> E({ {100} });
    TVector<int> expected_minima = { 100 };

    int result = find_minimum(E);
    ASSERT_TRUE(IsValidLocalMinimum(result, expected_minima))
        << "Expected: 100. Got: " << result;
}

TEST(LocalMinimumTest, EmptyMatrixThrows) {
    Matrix<int> F(0, 0);
    EXPECT_THROW(find_minimum(F), std::runtime_error);
}
