//
// Created by musht on 30.03.2023.
//

#ifndef LAB1_ALG2_SOLUTION2_H
#define LAB1_ALG2_SOLUTION2_H

#include "compressed_solver.h"

class Solver2 : public CompressedSolver {
    std::vector<std::vector<int>> counter;

public:
    explicit Solver2(std::istream &is) : CompressedSolver(is) {}

    // complexity O ( n ^ 3 )
    void preprocessing() override {
        if (rectangles.empty()) {
            return;
        }
        std::set<int> x_points, y_points;
        for (const auto &rect : rectangles) {
            x_points.insert(rect.start.x);
            y_points.insert(rect.start.y);
            x_points.insert(rect.end.x);
            y_points.insert(rect.end.y);
        }
        construct_mapper(x_mapper, x_points);
        construct_mapper(y_mapper, y_points);

        counter = std::vector<std::vector<int>>( 2 * y_mapper.size() - 1, std::vector<int>( 2 * x_mapper.size() - 1, 0));
        for (const auto &rect : rectangles) {
            int l = x_mapper[rect.start.x], r = x_mapper[rect.end.x] + 1;
            int u = y_mapper[rect.start.y], d = y_mapper[rect.end.y] + 1;
            for (int i = u; i < d; ++i) {
                for (int j = l; j < r; ++j) {
                    counter[i][j]++;
                }
            }
        }
    }

    // complexity O ( log n )
    int answer_for_point(const point &pt) override {
        if (rectangles.empty()) {
            return 0;
        }
        auto y = compressed_cord(y_mapper, pt.y);
        auto x = compressed_cord(x_mapper, pt.x);
        if (x < 0 or y < 0) {
            return 0;
        }
        return counter[y][x];
    }
};

#endif //LAB1_ALG2_SOLUTION2_H
