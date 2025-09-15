// Copyright 2025 Alewa8131

#include <stdexcept>
#include "../lib_point/point.h"

Point::Point() : _x(0), _y(0) {}
Point::Point(int x) : _x(x), _y(0) {}
Point::Point(int x, int y) : _x(x), _y(y) {}
Point::Point(const Point& other) : _x(other._x), _y(other._y) {}

int Point::get_coord_x() const {
    return _x;
}
int Point::get_coord_y() const {
    return _y;
}
