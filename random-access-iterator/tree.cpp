#include "tree.hpp"

tree::iterator operator+(tree::iterator const &self, ptrdiff_t diff) {

    if (diff == 0) {
        return self;
    }
    if (diff > 0) {
        if (self.p == nullptr) {
            throw std::out_of_range("-1");
        }
        /*if (diff < 0 || diff > self.p->subtree_size) {
            throw std::out_of_range("0");
        }*/
        auto cur = self.p;
        while (diff != 0) {
            if (cur->left == nullptr && cur->right == nullptr) {
                if (cur->up == nullptr) {
                    throw std::out_of_range("1");
                }
                while (cur->up->right.get() == cur) {
                    cur = cur->up;
                    if (cur->up == nullptr) {
                        throw std::out_of_range("1.5");
                    }
                }
                if (cur->up == nullptr) {
                    throw std::out_of_range("2");
                }
                cur = cur->up;
                diff--;
                continue;
            }
            if (cur->right == nullptr) {
                throw std::out_of_range("3");
            }
            if (cur->right->left == nullptr) {
                cur = cur->right.get();
            } else {
                cur = cur->right->left.get();
            }
            diff--;
        }
        return tree::iterator{cur};
    } else {
        if (self.p == nullptr) {
            throw std::out_of_range("-1");
        }


        auto cur = self.p;
        if (diff > 0 || std::abs(diff) > cur->subtree_size) {
            throw std::out_of_range("0");
        }
        while (diff != 0) {
            if (cur->right == nullptr && cur->left == nullptr) {
                if (cur->up == nullptr) {
                    throw std::out_of_range("1");
                }
                while (cur->up->left.get() == cur) {
                    cur = cur->up;
                    if (cur->up == nullptr) {
                        throw std::out_of_range("1.5");
                    }
                }
                if (cur->up == nullptr) {
                    throw std::out_of_range("2");
                }
                cur = cur->up;
                diff++;
                continue;
            }
            if (cur->left == nullptr) {
                throw std::out_of_range("3");
            }
            if (cur->left->right == nullptr) {
                cur = cur->left.get();
            } else {
                cur = cur->left->right.get();
            }
            diff++;
        }
        return tree::iterator{cur};
    }

}

ptrdiff_t operator-(tree::iterator const &self, tree::iterator other) {
    if (self.p == nullptr) {
        return 0;
    }
    return self.p->value - other.p->value;
}

auto tree::begin() const -> iterator {
    auto current = root->left.get();
    auto before = root.get();
    while (current != nullptr) {
        before = current;
        current = current->left.get();
    }
    return iterator{before};
}

auto tree::end() const -> iterator {
    auto current = root->right.get();
    auto before = root.get();
    while (current != nullptr) {
        before = current;
        current = current->right.get();
    }

    return iterator{before};
}
