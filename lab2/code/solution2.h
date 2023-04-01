//
// Created by musht on 30.03.2023.
//

#ifndef LAB1_ALG2_SOLUTION2_H
#define LAB1_ALG2_SOLUTION2_H

#include "abstract_solver.h"

#include <map>
#include <set>

class Solver2 : public AbstractSolver {
    std::vector<std::vector<int>> counter;
    std::map<int, int> x_mapper;
    std::map<int, int> y_mapper;

    static void construct_mapper(std::map<int, int> &mapper, const std::set<int> &points) {
        int new_cord = 0;
        for (const auto &old_cord: points) {
            mapper[old_cord] = new_cord++;
        }
    }

    static std::pair<int, bool> compressed_cord(const std::map<int, int> &mapper, int cord) {
        auto equal_iter = mapper.find(cord);
        if (equal_iter != mapper.end()) {
            if (equal_iter == mapper.begin()) {
                return {equal_iter->second, false};
            }
            if (std::next(equal_iter) == mapper.end())
                return {std::prev(equal_iter)->second, false};

            return {equal_iter->second, true};
        }

        auto greater_iter = mapper.upper_bound(cord);
        if (greater_iter == mapper.begin() or greater_iter == mapper.end()) {
            return {-1, false};
        }
        return {std::prev(greater_iter)->second, false};
    }

public:
    explicit Solver2(std::istream &is) : AbstractSolver(is) {}

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

        counter = std::vector<std::vector<int>>(y_mapper.size() - 1, std::vector<int>(x_mapper.size() - 1, 0));
        for (const auto &rect : rectangles) {
            int l = x_mapper[rect.start.x], r = x_mapper[rect.end.x];
            int u = y_mapper[rect.start.y], d = y_mapper[rect.end.y];
            for (int i = u; i < d; ++i) {
                for (int j = l; j < r; ++j) {
                    counter[i][j]++;
                }
            }
        }
    }

    int answer_for_point(const point &pt) override {
        if (rectangles.empty()) {
            return 0;
        }
        auto [y, y_on_border] = compressed_cord(y_mapper, pt.y);
        auto [x, x_on_border] = compressed_cord(x_mapper, pt.x);
        if (y < 0 or x < 0) {
            return 0;
        }
        if (y_on_border and x_on_border) {
            return std::max(std::max(counter[y - 1][x - 1], counter[y - 1][x]),
                            std::max(counter[y][x - 1], counter[y][x]));
        }
        if (y_on_border) {
            return std::max(counter[y - 1][x], counter[y][x]);
        }
        if (x_on_border) {
            return std::max(counter[y][x - 1], counter[y][x]);
        }
        return counter[y][x];
    }
};

#endif //LAB1_ALG2_SOLUTION2_H
