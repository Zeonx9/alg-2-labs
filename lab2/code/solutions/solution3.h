//
// Created by musht on 31.03.2023.
//

#ifndef LAB1_ALG2_SOLUTION3_H
#define LAB1_ALG2_SOLUTION3_H

#include "compressed_solver.h"
#include "seg_tree.h"

#include <algorithm>

struct boundary {
    int cord;
    bool is_opening;
    int from;
    int to;
    boundary(int c, bool o, const rectangle &r) : cord(c), is_opening(o), from(r.start.y), to(r.end.y) {}

    bool operator<(const boundary & other) const {
        return cord < other.cord or (cord == other.cord and is_opening > other.is_opening);
    }
};

class Solver3 : public CompressedSolver {
    PersistentTree tree;

    // O ( log n )
    void apply_boundary_change(const boundary &b) {
        tree.add_range_modify(y_mapper[b.from], y_mapper[b.to] + 1, (b.is_opening ? 1 : -1));
    }

    // O* ( log n )
    void create_version(
            std::vector<boundary>::iterator &it,
            const std::vector<boundary>::const_iterator &end,
            int cord,
            bool is_open
    ) {
        tree.copy_last_version();
        while (it < end and it->cord == cord and is_open == it->is_opening) {
            apply_boundary_change(*it);
            ++it;
        }
    }

public:
    explicit Solver3(std::istream &is) : CompressedSolver(is) {}

    // Complexity O ( n * log n )
    void preprocessing() override {
        if (rectangles.empty()) {
            return;
        }
        std::vector<boundary> x_points;
        std::set<int> y_points;
        for (const auto &rect : rectangles) {
            x_points.emplace_back(rect.start.x, true, rect);
            x_points.emplace_back(rect.end.x, false, rect);
            y_points.insert(rect.start.y);
            y_points.insert(rect.end.y);
        }
        construct_mapper(y_mapper, y_points);
        std::sort(x_points.begin(), x_points.end());

        tree.init(2 * (int) y_mapper.size() - 1);
        auto it = x_points.begin();
        while (it < x_points.end()) {
            int cord = it->cord;
            x_mapper[it->cord] = tree.count_versions();
            create_version(it, x_points.end(), cord, true);
            create_version(it, x_points.end(), cord, false);
        }
    }

    // Complexity O ( log n )
    int answer_for_point(const point &pt) override {
        if (rectangles.empty()) {
            return 0;
        }
        auto y = compressed_cord(y_mapper, pt.y);
        auto x = compressed_cord(x_mapper, pt.x);
        if (y < 0) {
            return 0;
        }
        return tree.get_version(x)->get_accumulated(y);
    }
};


#endif //LAB1_ALG2_SOLUTION3_H
