cmake_minimum_required(VERSION 3.23)
project(lab1_alg2)

set(CMAKE_CXX_STANDARD 17)

add_executable(lab1 lab1/main.cpp)

add_executable(lab2 lab2/code/main.cpp lab2/code/solutions/abstract_solver.h lab2/code/solutions/solution1.h lab2/code/solutions/solution2.h lab2/code/solutions/solution3.h lab2/code/solutions/seg_tree.h lab2/code/solutions/compressed_solver.h lab2/code/test_generation.h lab2/code/test_generation.h lab2/code/timing.h lab2/code/table_results.h)
