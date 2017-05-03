//
// Created by GiuseppiCheryl on 3/19/2016.
// new
//

#include <assert.h>
#include <fstream>
#include <iostream>
#include "KMeans.h"
#include "Exceptions.h"

namespace Clustering {

    KMeans::KMeans(unsigned int dim, unsigned int k, std::string filename, unsigned int maxIter){

        if (k == 0)
            throw Clustering::ZeroClustersEx();
        if (dim == 0)
            throw Clustering::ZeroDimensionsEx();

        __dimensionality = dim;
        __k = k;
        __iFileName = filename;
        __maxIter = maxIter;
        __numIter = 0;
        __numNonempty = 0;
        __numMovesLastIter = 0;

        std::ifstream inFile(__iFileName);

        if(!inFile)
            throw Clustering::DataFileOpenEx(__iFileName);

        __clusters = new Cluster*[k];
        for(int count = 0; count < k; ++count)
            __clusters[count] = new Cluster(dim);

        //put all initial points into first cluster to pick initial centroids later
        inFile >> *__clusters[0];
        inFile.close();

        //if read was successful and read in a point, make 1 non-empty cluster
        if ((*__clusters[0]).getSize() != 0)
            __numNonempty++;

        //array to hold initial centroids
        __initCentroids = new Point*[k];
        for(int count = 0; count < k; ++count){
            __initCentroids[count] = new Point(dim);
        }

        __clusters[0]->pickCentroids(k, __initCentroids);

        for(int count = 0; count < k; ++count)
            __clusters[count]->centroid.set(*__initCentroids[count]);
    }

    KMeans::~KMeans() {
        for (int count = 0; count < __k; ++count) {
            delete __clusters[count];
            delete __initCentroids[count];
        }
        delete [] __clusters;
        delete [] __initCentroids;
    }

    unsigned int KMeans::getMaxIter(){
        return __maxIter;
    }
    unsigned int KMeans::getNumIters(){
        return __numIter;
    }
    unsigned int KMeans::getNumNonemptyClusters(){
        return __numNonempty;
    }
    unsigned int KMeans::getNumMovesLastIter(){
        return __numMovesLastIter;
    }

    Cluster &KMeans::operator[](unsigned int u) {
        return *(__clusters)[u];
    }

    const Cluster &KMeans::operator[](unsigned int u) const {
        return *(__clusters)[u];
    }

    std::ostream &operator<<(std::ostream &os, const KMeans &kmeans) {
        for (int k = 0; k < kmeans.__k; ++k) {
            if ((*(kmeans.__clusters)[k]).getSize() > 0)
                for (int pCount = 0; pCount < (*(kmeans.__clusters)[k]).getSize(); ++pCount)
                    os << (*(kmeans.__clusters)[k])[pCount] << " : "
                    << (*(kmeans.__clusters)[k]).getId() << std::endl;
        }

        return os;
    }

    //main clustering algorithm
    void KMeans::run() {
        for (int count = 0; count < __k; ++count) {
            assert((*(__clusters)[count]).centroid.isValid());
        }

        unsigned int moves, iter, closest;
        moves = 100;
        iter = 0;
        closest = 0;
        bool isMoving = false;

        if (__k == 1)
            return;

        //continues to loop until max iteration is hit or no more moves are made
        while (moves > 0 && iter < __maxIter) {
            moves = 0;
            //iterates through each cluster
            for (int clusterCount = 0; clusterCount < __k; ++clusterCount) {
                //iterates through each point of each cluster
                for (int pointCount = 0; pointCount < (*(__clusters)[clusterCount]).getSize(); ++pointCount) {
                    closest = clusterCount;
                    //for each point, check every other centroid to see if it is closer
                    for (int centroidCount = 0; centroidCount < __k; ++centroidCount){
                        //if it is closer then save the index compare distance to that centroid to other centroids
                        if(centroidCount != clusterCount && ((*(__clusters)[clusterCount]).getSize() > 1) &&
                           (((*(__clusters)[clusterCount])[pointCount].distanceTo((*(__clusters)[closest]).centroid.get())) >
                            (((*(__clusters)[clusterCount])[pointCount].distanceTo((*(__clusters)[centroidCount]).centroid.get()))))){
                            closest = centroidCount;
                            isMoving = true;
                        }
                    }
                    //if a closer centroid was found, move it to that new cluster
                    if (isMoving) {
                        Cluster::Move move((*(__clusters)[clusterCount])[pointCount], (*(__clusters)[clusterCount]), (*(__clusters)[closest]));
                        move.perform();
                        moves++;
                        pointCount--;
                        isMoving = false;
                    }
                }
            }
            //after each iteration recompute the centroids and start over
            for (int count = 0; count < __k; ++count)
                if (!(*(__clusters)[count]).centroid.isValid())
                    (*(__clusters)[count]).centroid.compute();
            iter++;
        }

        //count up the number of nonempty clusters
        __numNonempty = 0;
        for (int count = 0; count < __k; ++count)
            if ((*(__clusters)[count]).getSize() > 0)
                __numNonempty++;

        __numIter = iter;
        __numMovesLastIter = moves;

    }
}