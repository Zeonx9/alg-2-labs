cmake_minimum_required(VERSION 3.23)
project(lab1_alg2)

set(CMAKE_CXX_STANDARD 17)

add_executable(lab1 lab1/main.cpp)

add_executable(lab2 lab2/code/main.cpp lab2/code/abstract_solver.h lab2/code/solution1.h lab2/code/solution2.h lab2/code/solution3.h lab2/code/seg_tree.h)
