// Copyright 2025 Alewa8131

#ifndef LIB_POINT3D_POINT3D_H_
#define LIB_POINT3D_POINT3D_H_
#pragma once
#include "../lib_point/point.h"

class Point3D : public Point {
    int _z;
public:
    Point3D();
    Point3D(int);
    Point3D(int, int);
    Point3D(int, int, int);
    Point3D(const Point&);
    Point3D(const Point&, int);
    Point3D(const Point3D&);
    int get_coord_z() const;
};


#endif  // LIB_POINT3D_POINT3D_H_
