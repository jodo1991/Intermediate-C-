//
// File: Point.cpp
// Specification: Contains implementation for Point class
// Created by Joe Dodson on 1/31/2016.
//

#include "Point.h"

// Default constructor to set all variables to 0.0
Point::Point()
{
    x = y = z = 0.0;
}

// 3 parameter constructor
Point::Point(double newX, double newY, double newZ)
{
    x = newX;
    y = newY;
    z = newZ;
}

// Mutator functions
void Point::setX(double newX)
{
    x = newX;
}

void Point::setY(double newY)
{
    y = newY;
}

void Point::setZ(double newZ)
{
    z = newZ;
}

// Accessor functions
double Point::getX() const
{
    return x;
}

double Point::getY() const
{
    return y;
}

double Point::getZ() const
{
    return z;
}

// get distance between two points
double Point::distanceTo(const Point& endPoint) const
{
    double distance;

    // 3-Dimensional Pythagorean Theorem
    distance = sqrt(pow((endPoint.getX() - x), 2)
                    + pow((endPoint.getY() - y), 2)
                    + pow((endPoint.getZ() - z), 2));

    return distance;
}
