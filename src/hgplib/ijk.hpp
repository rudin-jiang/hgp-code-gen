#pragma once

#include <iostream>
#include <cstddef>
#include <vector>
#include <string>
#include <cassert>
#include <set>
#include <map>

class ijk {
public:
    std::size_t i, j, k;

    explicit ijk(std::size_t i = 0,
                 std::size_t j = 0,
                 std::size_t k = 0)
    : i(i), j(j), k(k) {}

    std::size_t  operator[](std::size_t pos) const;
    std::size_t& operator[](std::size_t pos);

    std::size_t index() const;  // see index_of_ijk
    std::size_t sum() const { return i + j + k; }

    bool is_zero() const { return !i && !j && !k; }

    std::string to_comment() const;
};

std::istream& operator>>(std::istream &is, ijk &a);
std::ostream& operator<<(std::ostream &os, const ijk &a);

// lexicographic order
// same order as std::vector<int>
bool operator<(const ijk &a, const ijk &b);
bool operator>(const ijk &a, const ijk &b);
bool operator<=(const ijk &a, const ijk &b);
bool operator>=(const ijk &a, const ijk &b);
bool operator==(const ijk &a, const ijk &b);
bool operator!=(const ijk &a, const ijk &b);


// if all (i,j,k) that i+j+k==n are sort as 
// lexicographic order, then a (i,j,k) will
// be in the position index_of_ijk(i,j,k).
// For more about lexicographic order, see 
// https://en.wikipedia.org/wiki/Lexicographic_order
std::size_t index_of_ijk(
    std::size_t i, std::size_t j, std::size_t k
);

// generate all (i,j,k) that i+j+k==n
// return in lexicographic order
std::vector<ijk> generate_ijk(std::size_t n);


