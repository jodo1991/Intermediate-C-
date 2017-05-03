//
// File: Point.h
// Specification: Contains declaration for 3-dimensional point class
// Created by Joe Dodson on 1/31/2016.
//

#ifndef __POINT_H
#define __POINT_H

// for pow and sqrt functions used in point.cpp and area.cpp
#include <cmath>

class Point {
    
private:
    double x, y, z;

public:
    // Constructors
    Point();                      // default constructor
    Point(double newX, double newY, double newZ);    // three-argument constructor

    // Mutator methods
    void setX(double newX);
    void setY(double newY);
    void setZ(double newZ);

    // Accessor methods
    double getX() const;
    double getY() const;
    double getZ() const;

    //calculate distance between points
    double distanceTo(const Point& endPoint) const;
    
};

#endif // __POINT_H
