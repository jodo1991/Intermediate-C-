//
// File: Point.cpp
// Specification: Contains implementation for point class
// Created by Joe Dodson on 3/2/2016.
//

#include "Point.h"
#include <cmath>
#include <stdlib.h>

using namespace std;
using namespace Clustering;

namespace Clustering {

    unsigned int Point::__idGen = 0; // static var to be assigned to points

    // constr
    Point::Point(int i)
    {
        __dim = i;
        __values = new double[__dim];
        for (int count = 0; count < __dim; ++count)
            __values[count] = 0.0;
        __id = __idGen++;
    }

    // unused constr
    Point::Point(int i, double *pDouble)
    {
        __dim = i;
        __values = pDouble;
        __id = __idGen++;
    }

    // copy const
    Point::Point(const Point &point)
    {
        __dim = point.__dim;
        __values = new double[__dim];
        for (int count = 0; count < __dim; ++count)
            __values[count] = point.__values[count];
        __id = point.__id;
    }

    // memberwise assignment
    Point &Point::operator=(const Point &point)
    {
        if (this == &point)
            return *this;
        else {
            __dim = point.__dim;
            for (int count = 0; count < __dim; ++count)
                __values[count] = point.__values[count];
            __id = point.__id;
        }
        return *this;
    }

    Point::~Point()
    {
        delete  [] __values;
    }

    // getters and setters
    int Point::getId() const
    {
        return __id;
    }

    int Point::getDims() const
    {
        return __dim;
    }

    void Point::setValue(int i, double d)
    {
        __values[i] = d;
    }

    double Point::getValue(int i) const
    {
        return __values[i];
    }

    // calculates distance between points for any dimension
    double Point::distanceTo(const Point &point) const
    {
        double totalDistance = 0.0;
        // uses pythag theorem for arbitrary amount of points
        for (int count = 0; count < __dim; ++count)
        {
            totalDistance += pow((__values[count] - point.__values[count]), 2);
        }

        totalDistance = sqrt(totalDistance);

        return totalDistance;
    }

    // to multiply each dimension by a constant (d)
    Point &Point::operator*=(double d)
    {
        for (int count = 0; count < __dim; ++count)
            __values[count] *= d;
        return *this;
    }

    // to divide each dim by a constant (d)
    Point &Point::operator/=(double d)
    {
        for (int count = 0; count < __dim; ++count)
            __values[count] /= d;
        return *this;
    }

    // multiplies by a constant and returns a new point
    const Point Point::operator*(double d) const
    {
        Point newPoint(*this);

        for(int count = 0; count < __dim; ++count)
            newPoint[count] *= d;

        return newPoint;
    }

    // divides by a constant and returns a new point
    const Point Point::operator/(double d) const
    {
        Point newPoint(*this);

        for(int count = 0; count < __dim; ++count)
            newPoint[count] /= d;

        return newPoint;
    }

    // accepts an index and accesses array to set or get value
    double &Point::operator[](int index)
    {
        return __values[index];
    }

    // to add two points together
    Point &operator+=(Point &point, const Point &point1)
    {
        for (int count = 0; count < point.__dim; ++count)
            point.__values[count] += point1.__values[count];

        return point;
    }

    // to subtract two points
    Point &operator-=(Point &point, const Point &point1)
    {
        for (int count = 0; count < point.__dim; ++count)
            point.__values[count] -= point1.__values[count];

        return point;
    }

    // adds two points together and returns a new point
    const Point operator+(const Point &point, const Point &point1)
    {
        Point newPoint(point);

        for (int count = 0; count < newPoint.__dim; ++count)
            newPoint.__values[count] = (point.__values[count] + point1.__values[count]);

        return newPoint;
    }

    // subtrats two points and returns a new point
    const Point operator-(const Point &point, const Point &point1)
    {
        Point newPoint(point);
        return newPoint -= point1;
    }

    // relational operators for two points

    // postcondition: returns true if points' ids and values match, false otherwise
    bool operator==(const Point &point, const Point &point1)
    {
        bool condition = true;

        if(point.__id != point1.__id)
            condition = false;
        else
        {
            for (int count = 0; count < point.__dim; ++count)
                if (point.__values[count] != point1.__values[count])
                    condition = false;
        }

        return condition;
    }

    bool operator!=(const Point &point, const Point &point1)
    {
        return(!(point == point1));
    }

    bool operator<(const Point &point, const Point &point1)
    {
        bool condition = false;
        for (int count = 0; count < point.__dim; ++count) {
            if (point.__values[count] < point1.__values[count])
                return true;
            if (point.__values[count] > point1.__values[count])
                return false;
        }
        return condition;
    }

    bool operator>(const Point &point, const Point &point1)
    {
        return operator<(point1, point);
    }

    bool operator<=(const Point &point, const Point &point1)
    {
        for (int count = 0; count < point.__dim; ++count)
            if (point.__values[count] <= point1.__values[count])
                return true;

        return false;
    }

    bool operator>=(const Point &point, const Point &point1)
    {
        for (int count = 0; count < point.__dim; ++count)
            if (point.__values[count] >= point1.__values[count])
                return true;

        return false;
    }

    // IO functions to stream one point
    std::ostream &operator<<(ostream &ostream1, const Point &point)
    {
        int count;
        for (count = 0; count < point.__dim-1; ++count)
            ostream1 << point.__values[count] << ", ";
            ostream1 << point.__values[count];

        ostream1 << endl;

        return ostream1;
    }

    std::istream &operator>>(istream &istream1, Clustering::Point &point)
    {
        int i = 0;
        std::string temp;
        double d;
       while(getline(istream1, temp, ',')){
           d = atof(temp.c_str());
           point.setValue(i++, d);
       }

        return istream1;
    }
}