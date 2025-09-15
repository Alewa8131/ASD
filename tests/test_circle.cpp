// Copyright 2025 Alewa8131

#include <gtest/gtest.h>
#include "../lib_circle/circle.h"

TEST(TestCircleLib, test_circle_default_constructor) {
    Circle p;
    EXPECT_EQ(p.get_coord_x(), 0);
    EXPECT_EQ(p.get_coord_y(), 0);
    EXPECT_EQ(p.get_radius(), 1);
}

TEST(TestCircleLib, test_circle_one_param_constructor) {
    Circle p(5);
    EXPECT_EQ(p.get_coord_x(), 0);
    EXPECT_EQ(p.get_coord_y(), 0);
    EXPECT_EQ(p.get_radius(), 5);
}

TEST(TestCircleLib, test_circle_two_param_constructor) {
    Circle p(10, 20);
    EXPECT_EQ(p.get_coord_x(), 10);
    EXPECT_EQ(p.get_coord_y(), 20);
    EXPECT_EQ(p.get_radius(), 1);
}

TEST(TestCircleLib, test_circle_three_param_constructor) {
    Circle p(10, 20, 5);
    EXPECT_EQ(p.get_coord_x(), 10);
    EXPECT_EQ(p.get_coord_y(), 20);
    EXPECT_EQ(p.get_radius(), 5);
}

TEST(TestCircleLib, test_circle_from_point_constructor) {
    Point p1(15, 25);
    Circle p2(p1);
    EXPECT_EQ(p1.get_coord_x(), 15);
    EXPECT_EQ(p1.get_coord_y(), 25);
    EXPECT_EQ(p2.get_coord_x(), 15);
    EXPECT_EQ(p2.get_coord_y(), 25);
    EXPECT_EQ(p2.get_radius(), 1);
}

TEST(TestCircleLib, test_circle_from_point_and_radius_constructor) {
    Point p1(15, 25);
    Circle p2(p1, 7);
    EXPECT_EQ(p1.get_coord_x(), 15);
    EXPECT_EQ(p1.get_coord_y(), 25);
    EXPECT_EQ(p2.get_coord_x(), 15);
    EXPECT_EQ(p2.get_coord_y(), 25);
    EXPECT_EQ(p2.get_radius(), 7);
}

TEST(TestCircleLib, test_circle_copy_constructor) {
    Circle p1(10, 20, 5);
    Circle p2(p1);
    EXPECT_EQ(p1.get_coord_x(), 10);
    EXPECT_EQ(p1.get_coord_y(), 20);
    EXPECT_EQ(p1.get_radius(), 5);
    EXPECT_EQ(p2.get_coord_x(), 10);
    EXPECT_EQ(p2.get_coord_y(), 20);
    EXPECT_EQ(p2.get_radius(), 5);
}
