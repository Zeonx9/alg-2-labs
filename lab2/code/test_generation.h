//
// Created by musht on 07.04.2023.
//

#ifndef LAB1_ALG2_TEST_GENERATION_H
#define LAB1_ALG2_TEST_GENERATION_H

#include "solutions/abstract_solver.h"
#include <cmath>

// fast power algorithms with modulo
long long fast_pow_mod(long long base, long long exp, long long mod) {
    if (exp == 0) {
        return 1;
    }
    base %= mod;
    if (exp == 1) {
        return base;
    }

    long long res = fast_pow_mod((base * base) % mod, exp / 2, mod);
    if (exp % 2 != 0) {
        res *= base;
    }
    return res % mod;
}

// creates a vector with rectangles
std::vector<rectangle> generate_rectangles(int n) {
    std::vector<rectangle> result;
    for (int i = 0; i < n; ++i) {
        int s = 10 * i, e = 10 * (2 * n - i);
        result.push_back({{s, s}, {e, e}});
    }
    return result;
}

// calculates coordinate of point
int point_cord(int seed, int i, int n) {
    return (int) fast_pow_mod(seed * i, 31, 20 * n);
}

// creates a vector with points
std::vector<point> generate_points(int m, int n) {
    std::vector<point> result;
    int prime_x = 71, prime_y = 31;
    for (int i = 0; i < m; ++i) {
        result.push_back({point_cord(prime_x, i, n), point_cord(prime_y, i, n)});
    }
    return result;
}

// opens file in "data" directory of the project and returns it
static std::fstream open_file(const std::string &file_name, std::ios::openmode mode) {
    std::fstream file;
    std::string name = "../lab2/data/" + file_name;
    file.open(name, mode);
    if (!file.is_open()) {
        throw std::invalid_argument("wrong file name");
    }
    return file;
}

std::fstream open_test_file(int i) {
    std::string file_name = "tests/test" + std::to_string(i) + ".txt";
    return open_file(file_name, std::ios::in);
}

std::fstream open_result_file(int i) {
    std::string file_name = "results/result" + std::to_string(i) + ".txt";
    return open_file(file_name, std::ios::out);
}

//generates n rectangles and m points and writes them to the provided output stream
void write_data_of_input_file(std::ostream &os, int n, int m) {
    os << n << "\n";
    auto rects = generate_rectangles(n);
    for (auto &r : rects) {
        os << r.start.x << " " << r.start.y << " " << r.end.x << " " << r.end.y << "\n";
    }
    os << m << "\n";
    auto pts = generate_points(m, n);
    for (auto &p : pts) {
        os << p.x << " " << p.y << "\n";
    }
}

// creates a test (input) file in "test" directory with provided number of rectangles and 10000 points
void generate_test_file(int n) {
    std::string file_name = "tests/test" + std::to_string(n) + ".txt";
    auto file = open_file(file_name, std::ios::out);
    write_data_of_input_file(file, n, 1000);
    file.close();
}


void generate_all_tests(int from = 2, int to = 524288, int step = 2) {
    for (int i = from; i <= to; i *= step) {
        generate_test_file(i);
        std::cout << "created test for n = " << i << "\n";
    }
}

#endif //LAB1_ALG2_TEST_GENERATION_H
