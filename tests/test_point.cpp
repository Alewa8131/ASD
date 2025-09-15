// Copyright 2025 Alewa8131

#include <gtest/gtest.h>
#include "../lib_point/point.h"

TEST(TestPointLib, test_point_default_constructor) {
    Point p;
    EXPECT_EQ(p.get_coord_x(), 0);
    EXPECT_EQ(p.get_coord_y(), 0);
}

TEST(TestPointLib, test_point_one_param_constructor) {
    Point p(10);
    EXPECT_EQ(p.get_coord_x(), 10);
    EXPECT_EQ(p.get_coord_y(), 0);
}

TEST(TestPointLib, test_point_two_param_constructor) {
    Point p(5, 8);
    EXPECT_EQ(p.get_coord_x(), 5);
    EXPECT_EQ(p.get_coord_y(), 8);
}

TEST(TestPointLib, test_point_copy_constructor) {
    Point p1(5, 8);
    Point p2(p1);
    EXPECT_EQ(p1.get_coord_x(), 5);
    EXPECT_EQ(p1.get_coord_y(), 8);
    EXPECT_EQ(p2.get_coord_x(), 5);
    EXPECT_EQ(p2.get_coord_y(), 8);
}
