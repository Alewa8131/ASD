// Copyright 2025 Alewa8131

#include <stdexcept>
#include "../lib_sphere/sphere.h"
#include <cmath>

Sphere::Sphere() : Circle(), _z(0) {}
Sphere::Sphere(int r) : Circle(r), _z(0) {}
Sphere::Sphere(int x, int y, int z) : Circle(x, y), _z(z) {}
Sphere::Sphere(int x, int y, int z, int r) : Circle(x, y, r), _z(z) {}

Sphere::Sphere(const Point& p) : Circle(p), _z(0) {}
Sphere::Sphere(const Point& p, int z, int r) : Circle(p, r), _z(z) {}

Sphere::Sphere(const Point3D& p) : Circle(p), _z(p.get_coord_z()) {}
Sphere::Sphere(const Point3D& p, int r) : Circle(p, r), _z(p.get_coord_z()) {}

Sphere::Sphere(const Circle& c) : Circle(c), _z(0) {}
Sphere::Sphere(const Circle& c, int z) : Circle(c), _z(z) {}

Sphere::Sphere(const Sphere& c) : Circle(c), _z(c.get_coord_z()) {}


int Sphere::get_coord_z() const { return _z; }
double Sphere::get_distance(const Sphere& obj2) {
    double dx = obj2.get_coord_x() - this->get_coord_x();
    double dy = obj2.get_coord_y() - this->get_coord_y();
    double dz = obj2.get_coord_z() - this->get_coord_z();
    return std::sqrt(dx * dx + dy * dy + dz * dz);
}
