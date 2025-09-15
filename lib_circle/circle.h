// Copyright 2025 Alewa8131

#include "../lib_point/point.h"
#ifndef LIB_CIRCLE_CIRCLE_H_
#define LIB_CIRCLE_CIRCLE_H_


class Circle : public Point {
    int _r;
public:
    Circle();
    Circle(int);
    Circle(int, int);
    Circle(int, int, int);
    Circle(const Point&);
    Circle(const Point&, int);
    Circle(const Circle&);

    int get_radius() const;
    double get_distance(const Circle&);
};


#endif  // LIB_CIRCLE_CIRCLE_H_
