// Copyright 2025 Alewa8131

#ifndef LIB_POINT_POINT_H_
#define LIB_POINT_POINT_H_

class Point {
    int _x, _y;
public:
    Point();
    Point(int);
    Point(int, int);
    Point(const Point&);
    int get_coord_x() const;
    int get_coord_y() const;
};


#endif  // LIB_POINT_POINT_H_
