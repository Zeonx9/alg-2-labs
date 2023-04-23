//
// Created by musht on 08.04.2023.
//

#ifndef LAB1_ALG2_TABLE_RESULTS_H
#define LAB1_ALG2_TABLE_RESULTS_H

#include <memory>
#include <iostream>
#include "test_generation.h"
#include "timing.h"

template<class T>
void create_table_with_results(const std::string &label, int to = 524288, int from = 1, int step = 2) {
    // create file and write header into .csv file
    auto table_file = files::open_file("tables/table_" + label + ".csv", std::ios::out);
    table_file << "n,algorithm,operation,time\n";

    for (int i = from; i <= to; i *= step) {
        std::cout << i << "\n";

        // construct a solver using given file
        auto file_in = files::open_test_file(i);
        T solver(file_in);
        file_in.close();

        // test the solver
        auto file_out = files::open_result_file(i);
        auto [t1, t2] = test_solver_class(solver, file_out);
        file_out.close();

        // write result to table
        table_file << i << "," << label << "," << "process" << "," << t1 << "\n";
        table_file << i << "," << label << "," << "answer" << "," << t2 << "\n";

        std::cout << "done\n";
    }
    table_file.close();
}


#endif //LAB1_ALG2_TABLE_RESULTS_H
