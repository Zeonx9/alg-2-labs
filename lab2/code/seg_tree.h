//
// Created by musht on 31.03.2023.
//

#ifndef LAB1_ALG2_SEG_TREE_H
#define LAB1_ALG2_SEG_TREE_H


#include <iostream>

class SegTree {
    int delta = 0;
    int from = 0;
    int to = 0;
    SegTree *left = nullptr;
    SegTree *right = nullptr;

public:
    SegTree(const SegTree &root) = default;
    explicit SegTree(int index) : from(index), to(index + 1) {}
    SegTree(SegTree *left_, SegTree *right_) : left(left_), right(right_), from(left_->from), to(right_->to) {}

    // recursively build the tree that represents range given
    static SegTree *build(int from, int to) {
        if (from + 1 == to) {
            return new SegTree(from);
        }
        int middle = (from + to) / 2;
        SegTree *left_ = build(from, middle);
        SegTree *right_ = build(middle, to);
        return new SegTree(left_, right_);
    }

    int get_accumulated(int index, int prev_value = 0) const {
        int value = prev_value + delta;
        if (to - from == 1) {
            return value;
        }
        if (index < left->to) {
            return left->get_accumulated(index, value);
        } else {
            return right->get_accumulated(index, value);
        }
    }

    SegTree *add_to_range(int l, int r, int num) {
        if (to <= l or r <= from) {
            return this;
        }
        if (l <= from and to <= r) {
            auto *copy = new SegTree(*this);
            copy->delta += num;
            return copy;
        }
        auto new_left = left ? left->add_to_range(l, r, num) : nullptr;
        auto new_right = right ? right->add_to_range(l, r, num) : nullptr;
        return new SegTree(new_left, new_right);
    }

    void print(int depth = 0) const {
        if (right)
            right->print(depth + 1);
        for (int i = 0; i < depth; ++i) {
            std::cout << "   ";
        }
        std::cout << delta << "\n";
        if (left) {
            left->print(depth + 1);
        }
    }
};

class PersistentTree {
    std::vector<SegTree *> versions;
public:
    PersistentTree() = default;

    SegTree *current_version() {
        return versions.back();
    }

    void save_version(SegTree * new_version) {
        versions.push_back(new_version);
    }

    const SegTree *get_version(int i) const {
        return versions[i];
    }

    int count_versions() const {
        return (int) versions.size();
    }
};


#endif //LAB1_ALG2_SEG_TREE_H
