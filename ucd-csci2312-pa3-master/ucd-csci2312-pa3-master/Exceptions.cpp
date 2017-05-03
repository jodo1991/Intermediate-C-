//
// Created by GiuseppiCheryl on 3/19/2016.
// new
//

#include "Exceptions.h"

namespace Clustering {

    //*************************************************************************************
    //OutOfBoundsEx
    //*************************************************************************************
    OutOfBoundsEx::OutOfBoundsEx(unsigned int c, int r) {
        __current = c;
        __rhs = r;
        __name = "OutOfBoundsEx";
    }

    unsigned int OutOfBoundsEx::getCurrent() const {
        return __current;
    }

    int OutOfBoundsEx::getRhs() const {
        return __rhs;
    }

    std::string OutOfBoundsEx::getName() const {
        return __name;
    }

    std::ostream &operator<<(std::ostream &os, const Clustering::OutOfBoundsEx &ex) {
        os << ex.__name;
        return os;
    }

    //*************************************************************************************
    //DimensionalityMisMatch
    //*************************************************************************************
    DimensionalityMismatchEx::DimensionalityMismatchEx(unsigned int c, unsigned int r) {
        __current = c;
        __rhs = r;
        __name = "DimensionalityMismatchEx";
    }

    unsigned int DimensionalityMismatchEx::getCurrent() const {
        return __current;
    }

    unsigned int DimensionalityMismatchEx::getRhs() const {
        return __rhs;
    }

    std::string DimensionalityMismatchEx::getName() const {
        return __name;
    }

    std::ostream &operator<<(std::ostream &os, const DimensionalityMismatchEx &ex) {
        os << ex.__name;
        return os;
    }

    //*************************************************************************************
    //ZeroClusters
    //*************************************************************************************
    ZeroClustersEx::ZeroClustersEx() {
        __name = "ZeroClustersEx";
    }

    std::string ZeroClustersEx::getName() const {
        return __name;
    }

    std::ostream &operator<<(std::ostream &os, const ZeroClustersEx &ex) {
        os << ex.__name;
        return os;
    }

    //*************************************************************************************
    //DataFileOpen
    //*************************************************************************************
    DataFileOpenEx::DataFileOpenEx(std::string filename) {
        __filename = filename;
        __name = "DataFileOpenEx";
    }

    std::string DataFileOpenEx::getFilename() const {
        return __filename;
    }

    std::string DataFileOpenEx::getName() const {
        return __name;
    }

    std::ostream &operator<<(std::ostream &os, const DataFileOpenEx &ex) {
        os << ex.__name;
        return os;
    }

    //*************************************************************************************
    //ZeroDimensions
    //*************************************************************************************
    ZeroDimensionsEx::ZeroDimensionsEx() {
        __name = "ZeroDimensionsEx";
    }

    std::string ZeroDimensionsEx::getName() const {
        return __name;
    }

    std::ostream &operator<<(std::ostream &os, const ZeroDimensionsEx &ex) {
        os << ex.__name;
        return os;
    }

    //*************************************************************************************
    //EmptyCluster
    //*************************************************************************************
    EmptyClusterEx::EmptyClusterEx() {
        __name = "EmptyClusterEx";
    }

    std::string EmptyClusterEx::getName() const {
        return __name;
    }

    std::ostream &operator<<(std::ostream &os, const EmptyClusterEx &ex) {
        os << ex.__name;
        return os;
    }
}