#include "ijk.hpp"
#include <iostream>
#include <cassert>
#include <cstddef>
#include <vector>
#include <string>
#include <set>
#include <map>

int  ijk::operator[](std::size_t pos) const {
    assert(pos < 3);
    if (pos == 0) return i;
    if (pos == 1) return j;
    return k;
};

int& ijk::operator[](std::size_t pos) {
    assert(pos < 3);
    if (pos == 0) return i;
    if (pos == 1) return j;
    return k;
}

std::size_t ijk::index() const {
    return index_of_ijk(i,j,k);
}

std::istream& operator>>(std::istream &is, ijk &a) {
    is >> a.i >> a.j >> a.k;
    return is;
}

std::ostream& operator<<(std::ostream &os, const ijk &a) {
    os << a.i << " " << a.j << " " << a.k;
    return os;
}

bool operator<(const ijk &a, const ijk &b) {
    if (a.i != b.i) return a.i < b.i;
    if (a.j != b.j) return a.j < b.j;
    return a.k < b.k;
}

bool operator>(const ijk &a, const ijk &b) {
    if (a.i != b.i) return a.i > b.i;
    if (a.j != b.j) return a.j > b.j;
    return a.k > b.k;
}

bool operator<=(const ijk &a, const ijk &b) {
    return !(a > b);
}

bool operator>=(const ijk &a, const ijk &b) {
    return !(a < b);
}

bool operator==(const ijk &a, const ijk &b) {
    return (a.i == b.i) && 
           (a.j == b.j) &&
           (a.k == b.k);
}

bool operator!=(const ijk &a, const ijk &b) {
    return !(a == b);
}

std::size_t index_of_ijk(int i, int j, int k) {
    assert(i >= 0); assert(j >= 0); assert(k >= 0);
    int n = i + j + k;
    int idx = (2*n - i + 3) * i / 2 + j;
    return static_cast<std::size_t>(idx);
}

std::vector<ijk> generate_ijk(int n) {
    assert(n >= 0);
    std::set<ijk> ijkSet;
    for (int i = 0; i <= n; ++i) {
    for (int j = 0; j <= n; ++j) {
        int k = n - i - j;
        if (k >= 0 && k <= n)
            ijkSet.insert(ijk(i,j,k));
    }}
    assert(ijkSet.size() == (n+1)*(n+2)/2);
    std::vector<ijk> ret(ijkSet.begin(), ijkSet.end());
    return ret;
}