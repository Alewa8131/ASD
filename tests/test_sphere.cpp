// Copyright 2025 Alewa8131

#include <gtest/gtest.h>
#include "../lib_sphere/sphere.h"


TEST(TestSphereLib, test_sphere_default_constructor) {
    Sphere s;
    EXPECT_EQ(s.get_coord_x(), 0);
    EXPECT_EQ(s.get_coord_y(), 0);
    EXPECT_EQ(s.get_coord_z(), 0);
    EXPECT_EQ(s.get_radius(), 1);
}
TEST(TestSphereLib, test_sphere_one_param_constructor) {
    Sphere s(5);
    EXPECT_EQ(s.get_coord_x(), 0);
    EXPECT_EQ(s.get_coord_y(), 0);
    EXPECT_EQ(s.get_coord_z(), 0);
    EXPECT_EQ(s.get_radius(), 5);
}
TEST(TestSphereLib, test_sphere_three_param_constructor) {
    Sphere s(10, 20, 30);
    EXPECT_EQ(s.get_coord_x(), 10);
    EXPECT_EQ(s.get_coord_y(), 20);
    EXPECT_EQ(s.get_coord_z(), 30);
    EXPECT_EQ(s.get_radius(), 1);
}
TEST(TestSphereLib, test_sphere_four_param_constructor) {
    Sphere s(10, 20, 30, 5);
    EXPECT_EQ(s.get_coord_x(), 10);
    EXPECT_EQ(s.get_coord_y(), 20);
    EXPECT_EQ(s.get_coord_z(), 30);
    EXPECT_EQ(s.get_radius(), 5);
}
TEST(TestSphereLib, test_sphere_from_point_constructor) {
    Point p(15, 25);
    Sphere s(p);
    EXPECT_EQ(s.get_coord_x(), 15);
    EXPECT_EQ(s.get_coord_y(), 25);
    EXPECT_EQ(s.get_coord_z(), 0);
    EXPECT_EQ(s.get_radius(), 1);
}
TEST(TestSphereLib, test_sphere_from_point_and_z_coord_and_radius_constructor) {
    Point p(15, 25);
    Sphere s(p, 35, 7);
    EXPECT_EQ(s.get_coord_x(), 15);
    EXPECT_EQ(s.get_coord_y(), 25);
    EXPECT_EQ(s.get_coord_z(), 35);
    EXPECT_EQ(s.get_radius(), 7);
}
TEST(TestSphereLib, test_sphere_from_point3d_constructor) {
    Point3D p(15, 25, 35);
    Sphere s(p);
    EXPECT_EQ(s.get_coord_x(), 15);
    EXPECT_EQ(s.get_coord_y(), 25);
    EXPECT_EQ(s.get_coord_z(), 35);
    EXPECT_EQ(s.get_radius(), 1);
}
TEST(TestSphereLib, test_sphere_from_point3d_and_radius_constructor) {
    Point3D p(15, 25, 35);
    Sphere s(p, 7);
    EXPECT_EQ(s.get_coord_x(), 15);
    EXPECT_EQ(s.get_coord_y(), 25);
    EXPECT_EQ(s.get_coord_z(), 35);
    EXPECT_EQ(s.get_radius(), 7);
}
TEST(TestSphereLib, test_sphere_from_circle_constructor) {
    Circle c(10, 20, 5);
    Sphere s(c);
    EXPECT_EQ(s.get_coord_x(), 10);
    EXPECT_EQ(s.get_coord_y(), 20);
    EXPECT_EQ(s.get_coord_z(), 0);
    EXPECT_EQ(s.get_radius(), 5);
}
TEST(TestSphereLib, test_sphere_from_circle_and_z_constructor) {
    Circle c(10, 20, 5);
    Sphere s(c, 30);
    EXPECT_EQ(s.get_coord_x(), 10);
    EXPECT_EQ(s.get_coord_y(), 20);
    EXPECT_EQ(s.get_coord_z(), 30);
    EXPECT_EQ(s.get_radius(), 5);
}
TEST(TestSphereLib, test_sphere_copy_constructor) {
    Sphere s1(10, 20, 30, 5);
    Sphere s2(s1);
    EXPECT_EQ(s1.get_coord_x(), 10);
    EXPECT_EQ(s1.get_coord_y(), 20);
    EXPECT_EQ(s1.get_coord_z(), 30);
    EXPECT_EQ(s1.get_radius(), 5);
    EXPECT_EQ(s2.get_coord_x(), 10);
    EXPECT_EQ(s2.get_coord_y(), 20);
    EXPECT_EQ(s2.get_coord_z(), 30);
    EXPECT_EQ(s2.get_radius(), 5);
}
