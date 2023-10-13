cmake_minimum_required(VERSION 3.23)
project(expressions_complex)

set(CMAKE_CXX_STANDARD 20)

add_executable(expressions_complex include/complex.h include/expression.h src/complex.cpp src/expression.cpp src/main.cpp)
