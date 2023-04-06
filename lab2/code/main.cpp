//
// Created by musht on 28.03.2023.
//
#include "solution1.h"
#include "solution2.h"
#include "seg_tree.h"
#include "solution3.h"

#define CONTEST_
#ifndef CONTEST
#include <iostream>
int main() {
    std::fstream file = AbstractSolver::open_test_file("test1.txt", std::ios::in);
    Solver3 solver(file);
    file.close();

    solver.preprocessing();

    std::fstream out_file = AbstractSolver::open_test_file("res1.txt", std::ios::out);
    solver.solve(std::cout);
    out_file.close();
}
#endif

#ifdef CONTEST
#include <iostream>

int main() {
    Solver2 solver(std::cin);
    solver.preprocessing();
    solver.solve(std::cout);
}
#endif

