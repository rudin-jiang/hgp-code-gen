#include "ijk.hpp"
#include "gen_utility.hpp"
#include <iostream>
#include <cassert>
#include <cstddef>
#include <vector>
#include <string>
#include <set>
#include <map>

std::size_t  ijk::operator[](std::size_t pos) const {
    assert(pos < 3);
    if (pos == 0) return i;
    if (pos == 1) return j;
    return k;
};

std::size_t& ijk::operator[](std::size_t pos) {
    assert(pos < 3);
    if (pos == 0) return i;
    if (pos == 1) return j;
    return k;
}

std::size_t ijk::index() const
{ return index_of_ijk(i,j,k); }

std::string ijk::to_comment() const {
    return "(" + encode_number(i)
               + encode_number(j)
               + encode_number(k) + ")";
}

std::istream& operator>>(std::istream &is, ijk &a) {
    is >> a.i >> a.j >> a.k; return is;
}

std::ostream& operator<<(std::ostream &os, const ijk &a) {
    os << a.i << " " << a.j << " " << a.k;
    return os;
}

bool operator<(const ijk &a, const ijk &b) {
    std::size_t aSum = a.sum();
    std::size_t bSum = b.sum();
    if (aSum != bSum) return aSum < bSum;
    if (a.i != b.i) return a.i < b.i;
    if (a.j != b.j) return a.j < b.j;
    return a.k < b.k;
}

bool operator>(const ijk &a, const ijk &b)
{ return !(a < b) && !(a == b); }

bool operator<=(const ijk &a, const ijk &b)
{ return !(a > b); }

bool operator>=(const ijk &a, const ijk &b)
{ return !(a < b); }

bool operator==(const ijk &a, const ijk &b)
{ return (a.i == b.i) &&  (a.j == b.j) && (a.k == b.k); }

bool operator!=(const ijk &a, const ijk &b)
{ return !(a == b); }

std::size_t index_of_ijk(
    std::size_t i, std::size_t j, std::size_t k
) {
    std::size_t n = i + j + k;
    return (2*n - i + 3) * i / 2 + j;
}

std::vector<ijk> generate_ijk(std::size_t n) {
    std::set<ijk> ijkSet;
    for (std::size_t i = 0; i <= n; ++i) {
    for (std::size_t j = 0; j <= n; ++j) {
    for (std::size_t k = 0; k <= n; ++k) {
        if (i + j + k == n)
            ijkSet.insert(ijk(i,j,k));
    }}}
    assert(ijkSet.size() == (n+1)*(n+2)/2);
    std::vector<ijk> ret(ijkSet.begin(), ijkSet.end());
    return ret;
}

