// Copyright 2025 Alewa8131

#include <stdexcept>
#include "../lib_point3d/point3d.h"


Point3D::Point3D() : Point(), _z(0) {}
Point3D::Point3D(int x) : Point(x), _z(0) {}
Point3D::Point3D(int x, int y) : Point(x, y), _z(0) {}
Point3D::Point3D(int x, int y, int z) : Point(x, y), _z(z) {}

Point3D::Point3D(const Point& other) : Point(other), _z(0) {}
Point3D::Point3D(const Point& other, int z) : Point(other), _z(z) {}
Point3D::Point3D(const Point3D& other) : Point(other), _z(other._z) {}

int Point3D::get_coord_z() const {
    return _z;
}
