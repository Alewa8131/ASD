// Copyright 2025 Alewa8131

#include <gtest/gtest.h>
#include "../lib_point3d/point3d.h"

TEST(TestPoint3DLib, test_point3D_default_constructor) {
    Point3D p;
    EXPECT_EQ(p.get_coord_x(), 0);
    EXPECT_EQ(p.get_coord_y(), 0);
    EXPECT_EQ(p.get_coord_z(), 0);
}

TEST(TestPoint3DLib, test_point3D_one_param_constructor) {
    Point3D p(10);
    EXPECT_EQ(p.get_coord_x(), 10);
    EXPECT_EQ(p.get_coord_y(), 0);
    EXPECT_EQ(p.get_coord_z(), 0);
}

TEST(TestPoint3DLib, test_point3D_two_param_constructor) {
    Point3D p(5, 8);
    EXPECT_EQ(p.get_coord_x(), 5);
    EXPECT_EQ(p.get_coord_y(), 8);
    EXPECT_EQ(p.get_coord_z(), 0);
}

TEST(TestPoint3DLib, test_point3D_three_param_constructor) {
    Point3D p(2, 4, 6);
    EXPECT_EQ(p.get_coord_x(), 2);
    EXPECT_EQ(p.get_coord_y(), 4);
    EXPECT_EQ(p.get_coord_z(), 6);
}

TEST(TestPoint3DLib, test_point3d_from_point_constructor) {
    Point p1(7, 9);
    Point3D p2(p1);
    EXPECT_EQ(p1.get_coord_x(), 7);
    EXPECT_EQ(p1.get_coord_y(), 9);
    EXPECT_EQ(p2.get_coord_x(), 7);
    EXPECT_EQ(p2.get_coord_y(), 9);
    EXPECT_EQ(p2.get_coord_z(), 0);
}

TEST(TestPoint3DLib, test_point3d_from_point_and_param_constructor) {
    Point p1(8, 2);
    Point3D p2(p1, 25);
    EXPECT_EQ(p1.get_coord_x(), 8);
    EXPECT_EQ(p1.get_coord_y(), 2);
    EXPECT_EQ(p2.get_coord_x(), 8);
    EXPECT_EQ(p2.get_coord_y(), 2);
    EXPECT_EQ(p2.get_coord_z(), 25);
}

TEST(TestPoint3DLib, test_point3D_copy_constructor) {
    Point3D p1(1, 2, 3);
    Point3D p2(p1);
    EXPECT_EQ(p1.get_coord_x(), 1);
    EXPECT_EQ(p1.get_coord_y(), 2);
    EXPECT_EQ(p1.get_coord_z(), 3);
    EXPECT_EQ(p2.get_coord_x(), 1);
    EXPECT_EQ(p2.get_coord_y(), 2);
    EXPECT_EQ(p2.get_coord_z(), 3);
}
