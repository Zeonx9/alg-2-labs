//
// Created by musht on 31.03.2023.
//

#ifndef LAB1_ALG2_SEG_TREE_H
#define LAB1_ALG2_SEG_TREE_H


#include <memory>

class SegTree {
    int delta = 0;
    int from = 0;
    int to = 0;
    std::shared_ptr<SegTree> left = nullptr;
    std::shared_ptr<SegTree> right = nullptr;

public:
    SegTree(const SegTree &root) = default;
    explicit SegTree(int index) : from(index), to(index + 1) {}
    SegTree(const std::shared_ptr<SegTree>& lef, const std::shared_ptr<SegTree> &rig, int d = 0) :
        left(lef), right(rig),
        from(lef->from), to(rig->to),
        delta(d) {}

    // recursively build the tree that represents range given
    static std::shared_ptr<SegTree> build(int from, int to) {
        if (from + 1 == to) {
            return std::make_shared<SegTree>(from);
        }
        int middle = (from + to) / 2;
        std::shared_ptr<SegTree> left_ = build(from, middle);
        std::shared_ptr<SegTree> right_ = build(middle, to);
        return std::make_shared<SegTree>(left_, right_);
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

    std::shared_ptr<SegTree> add_to_range(int l, int r, int num, const std::shared_ptr<SegTree> &shared_this) {
        if (to <= l or r <= from) {
            return shared_this;
        }
        if (l <= from and to <= r) {
            auto copy = std::make_shared<SegTree>(*this);
            copy->delta += num;
            return copy;
        }
        auto new_left = left ? left->add_to_range(l, r, num, left) : nullptr;
        auto new_right = right ? right->add_to_range(l, r, num, right) : nullptr;
        return std::make_shared<SegTree>(new_left, new_right, delta);
    }
};

class PersistentTree {
    std::vector<std::shared_ptr<SegTree>> versions;
public:
    PersistentTree() = default;

    void init(int size) {
        versions.push_back(SegTree::build(0, size));
    }

    void copy_last_version() {
        versions.push_back(versions.back());
    }

    void add_range_modify(int from, int to, int num) {
        versions.back() = versions.back()->add_to_range(from, to, num, versions.back());
    }

    int count_versions() const {
        return (int) versions.size();
    }

    const std::shared_ptr<SegTree> get_version(int i) const {
        return versions[i];
    }
};


#endif //LAB1_ALG2_SEG_TREE_H
