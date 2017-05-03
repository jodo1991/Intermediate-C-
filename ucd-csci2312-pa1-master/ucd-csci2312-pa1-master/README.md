## CSCI 2312: Programming Assignment 1
#### Written By: Joseph Dodson

_working with objects_

* * *


##### Description of the program
---

This program allows the user to create points consisting of 3 dimensions (x, y, and z). The user can has the ability to
create new points with initial coordinates, or input new coordinates at any time. The user can also call a point's member 
function to calculate the distance from one point to another. Finally, the user can call a function to calculate the area
between 3 points.

NOTE: Currently configured only for a testing suite. 

##### Source Files
---

Name: main.cpp
    Main program. Currently configured to run a test suite.
Name: area.cpp
    Implements a function that accepts three point objects and calculates the area using Heron's formula.
Name: Point.h
    Declaration for Point class
Name: Point.cpp
    Implementation of Point class. Contains default constructor, overloaded constructor, basic accessor and mutator functions,
    and a function for calculating distance to another point.
    
**Also includes files for test suite: ErrorContext.cpp ErrorContext.h PointTests.cpp PointTests.h
    
##### Circumstances of Program
---

Program ran successfully in supplied test suite on 1/31/2016 with 56/56 tests passed. 
