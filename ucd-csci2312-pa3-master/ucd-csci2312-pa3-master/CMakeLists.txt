cmake_minimum_required(VERSION 3.3)
project(clustering)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -ffloat-store")

set(SOURCE_FILES main.cpp Point.cpp Cluster.cpp
ErrorContext.cpp ClusteringTests.cpp KMeans.cpp Exceptions.cpp)
add_executable(clustering ${SOURCE_FILES})