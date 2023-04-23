//
// Created by musht on 28.03.2023.
//
#define CONTEST_


#ifndef CONTEST

#include "table_results.h"
#include "solutions/solution1.h"
#include "solutions/solution3.h"
#include "solutions/solution2.h"

int main() {
    generate_all_tests();
    create_table_with_results<Solver1>("naive");
    create_table_with_results<Solver3>("tree", 26144);
    create_table_with_results<Solver2>("map", 2048);
}

#endif

#ifdef CONTEST
#include "solutions/solution1.h"
#include "solutions/solution2.h"
#include "solutions/solution3.h"

#include <iostream>

int main() {
    Solver2 solver(std::cin);
    solver.preprocessing();
    solver.solve(std::cout);
}
#endif

