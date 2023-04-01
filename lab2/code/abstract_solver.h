//
// Created by musht on 28.03.2023.
//

#ifndef LAB1_ALG2_ABSTRACT_SOLVER_H
#define LAB1_ALG2_ABSTRACT_SOLVER_H

#include <vector>
#include <string>
#include <fstream>

struct point {
    int x, y;
};

struct rectangle {
    point start;
    point end;
};

class AbstractSolver {
protected:
    std::vector<rectangle> rectangles;
    std::vector<point> points;

    // reads from given input stream all rectangles and points (supposing that the format is correct)
    explicit AbstractSolver(std::istream &is) {
        int n;
        is >> n;
        rectangles = std::vector<rectangle>(n);
        for (auto &rect : rectangles) {
            is >> rect.start.x >> rect.start.y
               >> rect.end.x >> rect.end.y;
        }

        int k;
        is >> k;
        points = std::vector<point>(k);
        for (auto &pt : points) {
            is >> pt.x >> pt.y;
        }
    }

public:

    static std::fstream open_test_file(const std::string &file_name, std::ios::openmode mode) {
        std::fstream file;
        file.open("../lab2/test/" + file_name, mode);
        if (!file.is_open()) {
            throw std::invalid_argument("wrong file name");
        }
        return file;
    }

    virtual void preprocessing() = 0;

    virtual int answer_for_point(const point &pt) = 0;

    void solve(std::ostream &os) {
        for (const auto &pt : points) {
            os << answer_for_point(pt) << " ";
        }
    }
};

#endif //LAB1_ALG2_ABSTRACT_SOLVER_H
