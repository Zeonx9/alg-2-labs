//
// Created by musht on 07.04.2023.
//

#ifndef LAB1_ALG2_TIMING_H
#define LAB1_ALG2_TIMING_H

#include <functional>
#include <chrono>
#include "solutions/abstract_solver.h"

long long measure_method_executing_time(const std::function<void(void)> &method) {
    auto start = std::chrono::high_resolution_clock::now();
    method();
    auto end = std::chrono::high_resolution_clock::now();
    return std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
}

std::pair<long long, long long> test_solver_class(AbstractSolver &solver, std::ostream &os) {
    long long process_time = measure_method_executing_time([&solver]() {
        solver.preprocessing();
    });
    std::cout << "processed " << process_time << "\n";

    long long answer_time = measure_method_executing_time([&solver, &os]() {
        solver.solve(os);
    });
    std::cout << "answered " << answer_time << "\n";
    return {process_time, answer_time};
}

#endif //LAB1_ALG2_TIMING_H
