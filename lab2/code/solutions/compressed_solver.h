//
// Created by musht on 05.04.2023.
//

#ifndef LAB1_ALG2_COMPRESSED_SOLVER_H
#define LAB1_ALG2_COMPRESSED_SOLVER_H

#include "abstract_solver.h"

#include <map>
#include <set>

class CompressedSolver : public AbstractSolver {
protected:
    std::map<int, int> x_mapper;
    std::map<int, int> y_mapper;

    // O ( n )
    static void construct_mapper(std::map<int, int> &mapper, const std::set<int> &points) {
        int new_cord = 0;
        for (const auto &old_cord: points) {
            mapper[old_cord] = new_cord;
            new_cord += 2;
        }
    }

    // O ( log n )
    static int compressed_cord(const std::map<int, int> &mapper, int cord) {
        auto equal_iter = mapper.find(cord);
        if (equal_iter != mapper.end()) {
            return equal_iter->second;
        }

        auto greater_iter = mapper.upper_bound(cord);
        if (greater_iter == mapper.begin() or greater_iter == mapper.end()) {
            -1;
        }
        return greater_iter->second - 1;
    }

public:
    explicit CompressedSolver(std::istream &is) : AbstractSolver(is) {}
};

#endif //LAB1_ALG2_COMPRESSED_SOLVER_H
