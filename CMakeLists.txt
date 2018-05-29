cmake_minimum_required(VERSION 3.10)
project(UCI_CPP_MLAlgo)

set(CMAKE_CXX_STANDARD 11)

add_executable(UCI_CPP_MLAlgo UCI_app/main.cpp lib/Matrix.h lib/clustering.h)