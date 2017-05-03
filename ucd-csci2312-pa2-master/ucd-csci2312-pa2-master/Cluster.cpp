//
// File: Cluster.cpp
// Specification: Contains implementation for cluster class
// Created by Joe Dodson on 3/2/2016.
//

#include <cstdlib>
#include <assert.h>
#include <sstream>
#include <fstream>
#include <algorithm>
#include "Cluster.h"

namespace Clustering{

    // node constructor
    LNode::LNode(const Point &p, LNodePtr n = nullptr) : point(p) {
        point = p;
        next = n;
    }

    // cluster constructor
    Cluster::Cluster() {
        __size = 0;
        __points = nullptr;
    }

    // copy constr
    Cluster::Cluster(const Cluster &cluster) : Cluster() {
            for(int count = 0; count < cluster.__size; ++count) {
                add(cluster[count]);
            }
    }

    // memb assignment
    Cluster &Cluster::operator=(const Cluster &cluster) {
        if(this == &cluster)
            return *this;
        else {
            if(__points != nullptr){
                LNodePtr currPtr = __points;
                LNodePtr nextPtr = nullptr;
                while(currPtr != nullptr){
                    nextPtr = currPtr->next;
                    delete currPtr;
                    currPtr = nextPtr;
                }
                __size = 0;
                __points = nullptr;
            }
            for(int count = 0; count < cluster.__size; ++count) {
                add(cluster[count]);
            }
        }
        return *this;
    }

    // postcondition: clears each node from linked list until no nodes are left and sets head pointer to null
    Cluster::~Cluster(){
        if(__points != nullptr){
            LNodePtr prevPtr = __points;
            LNodePtr currPtr = nullptr;
            while( prevPtr != nullptr){
                currPtr =  prevPtr->next;
                delete  prevPtr;
                 prevPtr = currPtr;
            }
        }
        else
            assert(__size==0);
    }

    int Cluster::getSize() const {
        return __size;
    }

    // postcondition: returns true if both clusters are same size and points are equal by Point::operator==
    // false otherwise
    bool operator==(const Cluster &cluster1, const Cluster &cluster2) {
        if(cluster1.__size != cluster2.__size)
            return false;
        LNodePtr cursor1 = cluster1.__points;
        LNodePtr cursor2 = cluster2.__points;
        bool condition = true;

        // iterate through both clusters and check for point equality
        while (cursor1 != nullptr && cursor2 != nullptr)
        {
            if(cursor1->point != cursor2->point)
                condition = false;
            cursor1 = cursor1->next;
            cursor2 = cursor2->next;
        }

        return condition;
    }

    // postcondition: point will be added to the cluster in pseudo-lexicographic order and size incremented
    void Cluster::add(const Point &point) {
        Point p(point);
        LNodePtr insertPtr = new LNode(p, nullptr);
        LNodePtr prev = __points;
        LNodePtr next = __points;

        // if list is empty insert at "front"
        if(__points == nullptr) {
            __points = insertPtr;
            __size++;
        }

        // if only one item in list
        else if(__points->next == nullptr){

            // if passed point is less than existing, insert at head of list
             if (point < __points->point) {
                __points = insertPtr;
                 insertPtr->next = prev;
                __size++;
            }
            // otherwise, insert at back
            else {
                 __points->next = insertPtr;
                 __size++;
             }
        }

        // 2 or more items in list
        else{
            next = next->next;

            // if passed point is less than first point, insert at head
            if(point < prev->point){
                __points = insertPtr;
                insertPtr->next = prev;
                __size++;
                return;
            }

            // else, find traverse list until find a point greater than passed point, then insert behind it
            while(next != nullptr){
                if(point < next->point) {
                    prev->next = insertPtr;
                    insertPtr->next = next;
                    __size++;
                    return;
                }
                next = next->next;
                prev = prev->next;
            }
            prev->next = insertPtr;
            __size++;
        }
    }

    // precondition: the point exists in the cluster
    // postcondition: the point will be removed from the cluster and returned from the function
    const Point &Cluster::remove(const Point &point) {
        LNodePtr currPtr = __points;
        LNodePtr nextPtr = __points;

        // exit function if point doesn't exist
        if(__points == nullptr)
            return point;

        // if first point is equal to passed point, remove it
        else if(__points->point == point){
            __points = __points->next;
            delete currPtr;
            __size--;
        }

        // traverse list until point is found and remove it
        else{
            currPtr = __points;
            nextPtr = __points->next;
            while(nextPtr != nullptr){
                if(nextPtr->point == point){
                    currPtr->next = nextPtr->next;
                    delete nextPtr;
                    __size--;
                    break;
                }
                currPtr = nextPtr;
                nextPtr = nextPtr->next;
            }
        }
        return point;
    }

    // postcondition: returns true if point is found in cluster using Point::operator==, false otherwise
    bool Cluster::contains(const Point &point) {
        LNodePtr cursor = __points;

        // traverse through list and only return true if point is found
        while(cursor != nullptr){
            if (cursor->point == point)
                return true;
            cursor = cursor->next;
        }
        return false;
    }

    // precondition: index passed is a valid index of the list
    // postcondition: returns point located at index of list
    const Point &Cluster::operator[](unsigned int index) const {
        assert(__points != nullptr && index < __size);
        LNodePtr cursor = __points;
        for(int count = 0; count < index; ++count)
            cursor = cursor->next;
        return cursor->point;
    }

    // postcondition: inserts each point in list into ostream object
    std::ostream &operator<<(std::ostream &ostream1, const Cluster &cluster) {
        LNodePtr cursor = cluster.__points;
       for(int count = 0; count < cluster.__size; ++count){
           ostream1 << cursor->point;
           cursor = cursor->next;
       }
        return ostream1;
    }

    // precondition: values contained in istream are comma seperated and each point is on new line
    // postcondition: extracts each point from istream and inserts into cluster
    std::istream &operator>>(std::istream &istream, Clustering::Cluster &cluster) {
        std::string line;
        while (getline(istream,line)) {
            // count commas to determine point dimension - 1
            int d = std::count(line.begin(),
                                     line.end(),
                                     ',');
            // create point with correct dimension
            Point *pointPtr = new Clustering::Point(d+1);
            std::stringstream lineStream(line);

            // call to Point::operator>>
            lineStream >> *pointPtr;

            cluster.add(*pointPtr);
        }
    return istream;
    }

    bool operator!=(const Cluster &cluster, const Cluster &cluster1) {
        return(!(cluster == cluster1));
    }

    // postcondition: adds point to cluster
    Cluster &Cluster::operator+=(const Point &point) {
        add(point);
        return *this;
    }

    // postcondition: subtracts point from cluster if it exists
    Cluster &Cluster::operator-=(const Point &point) {
        remove(point);
        return *this;
    }

    // postcondition: adds only unique points from passed cluster
    Cluster &Cluster::operator+=(const Cluster &cluster) {
        for(int count = 0; count < cluster.__size; ++count){
            if(!contains(cluster[count]))
                add(cluster[count]);
        }
        return *this;
    }

    // postcondition: removes only similar points
    Cluster &Cluster::operator-=(const Cluster &cluster) {
        for(int count = 0; count < cluster.__size; ++count){
            if(contains(cluster[count]))
                remove(cluster[count]);
        }
        return *this;
    }

    // postcondition: creates new cluster with added point and returns it
    const Cluster operator+(const Cluster &cluster, const Point &point) {
        Cluster c(cluster);
        c+=point;
        return c;
    }

    // postcondition: creates new cluster with subtracted point and returns it
    const Cluster operator-(const Cluster &cluster, const Point &point) {
        Cluster c(cluster);
        c-=point;
        return c;
    }

    // postcondition: creates new cluster with unique points of both clusters and returns it
    const Cluster operator+(const Cluster &cluster, const Cluster &cluster1) {
        Cluster c(cluster);
        c+=cluster1;
        return c;
    }

    // postcondition: creates new cluster with similar points removed and returns it
    const Cluster operator-(const Cluster &cluster, const Cluster &cluster1) {
        Cluster c(cluster);
        c-=cluster1;
        return c;
    }
}

