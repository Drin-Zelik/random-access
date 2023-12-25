#include "tree.hpp"
#include <algorithm>
#include <doctest.h>

TEST_CASE("can iterate") {
    tree t{{{1, 2, 3}, 4, {5, 6, 7}}};
    int v = 1;
    for (int i : t) {
        CHECK(i == v);
        v++;
    }
    REQUIRE(v == 7);
}

TEST_CASE("can reverse iterate") {
    tree t{{{1, 2, 3}, 4, {5, 6, 7}}};
    int v = 7;
    for (auto it = t.end(); it != t.begin(); it--) {
        auto x = (*it);
        CHECK(x == v--);
    }
    REQUIRE(v == 1);
}

TEST_CASE("operator[]") {
    tree t{{{1, 2, 3}, 4, {5, 6, 7}}};
    for (int i = 0; i < 7; ++i) {
        CHECK(t[i] == i + 1);
    }
}

TEST_CASE("operator-") {
    tree t{{{1, 2, 3}, 4, {5, 6, {7, 8, {nil, 9, 10}}}}};
    CHECK(t.end() - t.begin() == 9);
    CHECK(t.begin() + (t.end() - t.begin()) == t.end());
    for (auto i = t.begin(); i != t.end(); ++i)
        for (auto j = t.begin(); j != t.end(); ++j)
            CHECK(i - j == (*i) - (*j));
}

TEST_CASE("throws exception on illegal access request") {
    tree t{{{1, 2, 3}, 4, {5, 6, {7, 8, {nil, 9, 10}}}}};
    CHECK_THROWS_AS((void)t.at(10), std::out_of_range);
    CHECK_THROWS_AS((void)t.at(-1), std::out_of_range);
}
