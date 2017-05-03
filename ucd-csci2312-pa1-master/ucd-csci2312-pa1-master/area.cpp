//
// File: area.cpp
// Specification: contains function to compute area of 3 different point objects
// Created by Joe Dodson on 1/31/2016.
//

#include "Point.h"

double computeArea(const Point &a, const Point &b, const Point &c)
{
    // calculate sides and semi-perimeter(s) first for cleaner return formula

    // sideA is point A to B, side B is point B to C, and point C is
    // point C to A
    double sideA, sideB, sideC;
    sideA = a.distanceTo(b);
    sideB = b.distanceTo(c);
    sideC = c.distanceTo(a);

    // semi-perimeter
    double sp;
    sp = (sideA+sideB+sideC)/2;

    //Heron's formula
    return sqrt(sp*(sp-sideA)*(sp-sideB)*(sp-sideC));
}