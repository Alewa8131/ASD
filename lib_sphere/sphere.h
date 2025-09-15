// Copyright 2025 Alewa8131

#include "../lib_circle/circle.h"
#include "../lib_point3d/point3d.h"
#ifndef LIB_SPHERE_SPHERE_H_
#define LIB_SPHERE_SPHERE_H_


class Sphere : public Circle {
    int _z;
public:
    Sphere();
    Sphere(int);
    Sphere(int, int, int);
    Sphere(int, int, int, int);
    Sphere(const Point&);
    Sphere(const Point&, int, int);
    Sphere(const Point3D&);
    Sphere(const Point3D&, int);
    Sphere(const Circle&);
    Sphere(const Circle&, int);
    Sphere(const Sphere&);

    int get_coord_z() const;
    double get_distance(const Sphere&);
};


#endif  // LIB_SPHERE_SPHERE_H_
