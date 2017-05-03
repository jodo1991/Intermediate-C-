//
// File: Point.cpp
// Specification: Contains implementation for point class
// Created by Joe Dodson on 3/2/2016.
// new
//

#include "Point.h"
#include "Exceptions.h"
#include <cmath>
#include <stdlib.h>
#include <algorithm>

using namespace std;
using namespace Clustering;

namespace Clustering {

    unsigned int Point::__idGen = 0; // static var to be assigned to points
    const char Point::POINT_VALUE_DELIM = ',';

    // constr
    Point::Point(unsigned int i){
        if(i == 0)
            throw Clustering::ZeroDimensionsEx();
        __dim = i;
        __values = new double[__dim];
        for (int count = 0; count < __dim; ++count)
            __values[count] = 0.0;
        __id = __idGen++;
    }

    // unused constr
    Point::Point(unsigned int i, double *pDouble){
        __dim = i;
        __values = pDouble;
        __id = __idGen++;
    }

    // copy const
    Point::Point(const Point &point){
        __dim = point.__dim;
        __values = new double[__dim];
        for (int count = 0; count < __dim; ++count)
            __values[count] = point.__values[count];
        __id = point.__id;
    }

    // memberwise assignment
    Point &Point::operator=(const Point &point){
        if(__dim != point.__dim)
            throw Clustering::DimensionalityMismatchEx(__dim, point.__dim);
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

    Point::~Point(){
        delete  [] __values;
    }

    //to rewind the idgen for exception handling
    void Point::rewindIdGen() {
        __idGen--;
    }

    // getters and setters
    int Point::getId() const{
        return __id;
    }

    unsigned int Point::getDims() const{
        return __dim;
    }

    void Point::setValue(unsigned int i, double d){
        if(i < 0 || i >= __dim)
            throw Clustering::OutOfBoundsEx(__dim, i);
        else
            __values[i] = d;
    }

    double Point::getValue(unsigned int i) const{
        if(i < 0 || i >= __dim)
            throw Clustering::OutOfBoundsEx(__dim, i);
        else
            return __values[i];
    }

    // calculates distance between points for any dimension
    double Point::distanceTo(const Point &point) const{
        if(point.__dim != __dim)
            throw Clustering::DimensionalityMismatchEx(__dim, point.__dim);
        else {
            double totalDistance = 0.0;
            double tempSquare;
            // uses pythag theorem for arbitrary amount of points
            for (int count = 0; count < __dim; ++count) {
                tempSquare = 0;
                tempSquare = (__values[count] - point.__values[count]);
                totalDistance += (tempSquare * tempSquare);
            }

            totalDistance = sqrt(totalDistance);

            return totalDistance;
        }
    }

    // to multiply each dimension by a constant (d)
    Point &Point::operator*=(double d){
        for (int count = 0; count < __dim; ++count)
            __values[count] *= d;
        return *this;
    }

    // to divide each dim by a constant (d)
    Point &Point::operator/=(double d){
        for (int count = 0; count < __dim; ++count)
            __values[count] /= d;
        return *this;
    }

    // multiplies by a constant and returns a new point
    const Point Point::operator*(double d) const{
        Point newPoint(*this);

        for(int count = 0; count < __dim; ++count)
            newPoint[count] *= d;

        return newPoint;
    }

    // divides by a constant and returns a new point
    const Point Point::operator/(double d) const{
        Point newPoint(*this);

        for(int count = 0; count < __dim; ++count)
            newPoint[count] /= d;

        return newPoint;
    }

    // accepts an index and accesses array to set or get value
    double &Point::operator[](unsigned int index){
        if(index < 0 || index >= __dim)
            throw Clustering::OutOfBoundsEx(__dim, index);
        else
            return __values[index];
    }

    const double &Point::operator[](unsigned int index) const{
        if(index < 0 || index >= __dim)
            throw Clustering::OutOfBoundsEx(__dim, index);
        else
            return __values[index];
    }

    // to add two points together
    Point &operator+=(Point &point, const Point &point1){
        if(point.__dim != point1.__dim)
            throw Clustering::DimensionalityMismatchEx(point.__dim, point1.__dim);
        else {
            for (int count = 0; count < point.__dim; ++count)
                point.__values[count] += point1.__values[count];

            return point;
        }
    }

    // to subtract two points
    Point &operator-=(Point &point, const Point &point1){
        if(point.__dim != point1.__dim)
            throw Clustering::DimensionalityMismatchEx(point.__dim, point1.__dim);
        else {
            for (int count = 0; count < point.__dim; ++count)
                point.__values[count] -= point1.__values[count];

            return point;
        }
    }

    // adds two points together and returns a new point
    const Point operator+(const Point &point, const Point &point1){
        Point newPoint(point);
        return newPoint += point1;
    }

    // subtrats two points and returns a new point
    const Point operator-(const Point &point, const Point &point1){
        Point newPoint(point);
        return newPoint -= point1;
    }

    // relational operators for two points

    // postcondition: returns true if points' ids and values match, false otherwise
    bool operator==(const Point &point, const Point &point1){
        if(point.__dim != point1.__dim)
            throw Clustering::DimensionalityMismatchEx(point.__dim, point1.__dim);
        else {
            bool condition = true;

            if (point.__id != point1.__id)
                condition = false;
            else {
                for (int count = 0; count < point.__dim; ++count)
                    if (point.__values[count] != point1.__values[count])
                        condition = false;
            }

            return condition;
        }
    }

    bool operator!=(const Point &point, const Point &point1){
        return(!(point == point1));
    }

    bool operator<(const Point &point, const Point &point1){
        if(point.__dim != point1.__dim)
            throw Clustering::DimensionalityMismatchEx(point.__dim, point1.__dim);
        else {
            bool condition = false;
            for (int count = 0; count < point.__dim; ++count) {
                if (point.__values[count] < point1.__values[count])
                    return true;
                if (point.__values[count] > point1.__values[count])
                    return false;
            }
            return condition;
        }
    }

    bool operator>(const Point &point, const Point &point1){
        return operator<(point1, point);
    }

    bool operator<=(const Point &point, const Point &point1){
        if(point.__dim != point1.__dim)
            throw Clustering::DimensionalityMismatchEx(point.__dim, point1.__dim);
        else {
            for (int count = 0; count < point.__dim; ++count)
                if (point.__values[count] <= point1.__values[count])
                    return true;

            return false;
        }
    }

    bool operator>=(const Point &point, const Point &point1){
        if(point.__dim != point1.__dim)
            throw Clustering::DimensionalityMismatchEx(point.__dim, point1.__dim);
        else {
            for (int count = 0; count < point.__dim; ++count)
                if (point.__values[count] >= point1.__values[count])
                    return true;

            return false;
        }
    }

    // IO functions to stream one point
    std::ostream &operator<<(ostream &ostream1, const Point &point){
        int count;
        for (count = 0; count < point.__dim-1; ++count)
            ostream1 << point.__values[count] << ", ";
        ostream1 << point.__values[count];

        return ostream1;
    }

    std::istream &operator>>(istream &istream1, Clustering::Point &point){
        int i = 0;
        std::string line;
        double d;

        getline(istream1, line);
        int lhsDim = std::count(line.begin(), line.end(), ',');
        lhsDim++;

        if(lhsDim != point.__dim)
            throw Clustering::DimensionalityMismatchEx(point.__dim, lhsDim);

        istream1.seekg(0, ios::beg);
        while(getline(istream1, line, point.POINT_VALUE_DELIM)){
            d = atof(line.c_str());
            point.setValue(i++, d);
        }

        return istream1;
    }

    void getlineCSV(istream& is, string& str, char delim = '\n') {
        char temp;
        int count = 0;
        while (is.peek() != delim) {
            is.get(temp);
            str[count] = temp;
            count++;
        }
        is.get();
    }
}
