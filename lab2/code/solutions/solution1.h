//
// Created by musht on 28.03.2023.
//

#ifndef LAB1_ALG2_SOLUTION1_H
#define LAB1_ALG2_SOLUTION1_H

#include "abstract_solver.h"

class Solver1 : public AbstractSolver {
public:
    explicit Solver1(std::istream &is) : AbstractSolver(is) {}

    // complexity O ( 1 )
    void preprocessing() override {}

    // complexity O ( n )
    int answer_for_point(const point &pt) override {
        int count = 0;
        for (auto &rect : rectangles) {
            if (rect.start.x <= pt.x and pt.x <= rect.end.x and
                rect.start.y <= pt.y and pt.y <= rect.end.y) {
                ++count;
            }
        }
        return count;
    }
};

#endif //LAB1_ALG2_SOLUTION1_H
