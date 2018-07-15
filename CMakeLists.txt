cmake_minimum_required(VERSION 3.10)
project(UCI_CPP_MLAlgo)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_EXE_LINKER_FLAGS -static)

add_executable(KMeans_test UCI_app/KMeans_test.cpp lib/KMeans.h)
add_executable(DBSCAN_test UCI_app/DBSCAN_test.cpp lib/DBSCAN.h)
add_executable(HCA_test UCI_app/HCA.cpp lib/HCA.h)