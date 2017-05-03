//
// File: Cluster.h
// Specification: Contains specification for cluster class
// Created by Ivo Georgiev, implemented by Joe Dodson on 3/2/2016.
//

#ifndef CLUSTERING_CLUSTER_H
#define CLUSTERING_CLUSTER_H

#include "Point.h"

namespace Clustering {

    typedef struct LNode *LNodePtr;

    // node struct to create link list for cluster points
    struct LNode {

        Point point;
        LNodePtr next;
        LNode(const Point &p, LNodePtr n);

    };

    class Cluster {

        int __size; // to keep track of number of points in cluster
        LNodePtr __points; // head pointer for linked list

        //void __del();
        //void __cpy(LNodePtr pts);
        //bool __in(const Point &p) const;


    public:
        Cluster();

        // The big three: cpy ctor, overloaded operator=, dtor
        Cluster(const Cluster &);
        Cluster &operator=(const Cluster &);
        ~Cluster();

        // Getters/setters
        int getSize() const; // TODO add to the requirements

        // Set functions: They allow calling c1.add(c2.remove(p));
        void add(const Point &); // TODO add asc order to the requirements
        const Point &remove(const Point &);
        bool contains(const Point &);

        // Overloaded operators

        // Members: Subscript
        const Point &operator[](unsigned int index) const; // notice: const

        // Members: Compound assignment (Point argument)
        Cluster &operator+=(const Point &);
        Cluster &operator-=(const Point &);

        // Members: Compound assignment (Cluster argument)
        Cluster &operator+=(const Cluster &); // union
        Cluster &operator-=(const Cluster &); // (asymmetric) difference

        // Friends: IO
        friend std::ostream &operator<<(std::ostream &, const Cluster &);
        friend std::istream &operator>>(std::istream &, Cluster &);

        // Friends: Comparison
        friend bool operator==(const Cluster &, const Cluster &);
        friend bool operator!=(const Cluster &, const Cluster &);

        // Friends: Arithmetic (Cluster and Point)
        friend const Cluster operator+(const Cluster &, const Point &);
        friend const Cluster operator-(const Cluster &, const Point &);

        // Friends: Arithmetic (two Clusters)
        friend const Cluster operator+(const Cluster &, const Cluster &); // union
        friend const Cluster operator-(const Cluster &, const Cluster &); // (asymmetric) difference

    };

}
#endif //CLUSTERING_CLUSTER_H
