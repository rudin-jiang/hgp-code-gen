#pragma once

#include "ijk.hpp"
#include <iostream>
#include <vector>
#include <string>
#include <cstddef>
#include <cassert>

class ijkPair {
public:
    ijk a, b;
    std::size_t m;

    explicit ijkPair(): m(0) {}
    explicit ijkPair(ijk a, ijk b, std::size_t m)
    : a(a), b(b), m(m) {}

    std::size_t sum() const { return a.sum() + b.sum(); }

    ijkPair hgp_hrr_need_a(std::size_t pos) const;
    ijkPair hgp_hrr_need_b(std::size_t pos) const;

    ijkPair hgp_vrr_need_a(std::size_t pos) const;
    ijkPair hgp_vrr_need_b(std::size_t pos) const;
    ijkPair hgp_vrr_need_c(std::size_t pos) const;
    ijkPair hgp_vrr_need_d(std::size_t pos) const;
    ijkPair hgp_vrr_need_e(std::size_t pos) const;

    std::size_t array_index_single() const;
    std::size_t array_index_multip() const;
    
    std::string array_elem(std::size_t idxLen) const;

    std::string to_comment(bool pm = false) const;

    std::size_t  operator[](std::size_t pos) const;
    std::size_t& operator[](std::size_t pos);
};

std::istream& operator>>(std::istream &is, ijkPair &ab);
std::ostream& operator<<(std::ostream &os, const ijkPair &ab);

// rank as a first;
// if ab.a == cd.a, rank as b
bool operator<(const ijkPair &ab, const ijkPair &cd);

bool operator>(const ijkPair &ab, const ijkPair &cd);
bool operator<=(const ijkPair &ab, const ijkPair &cd);
bool operator>=(const ijkPair &ab, const ijkPair &cd);
bool operator==(const ijkPair &ab, const ijkPair &cd);
bool operator!=(const ijkPair &ab, const ijkPair &cd);

// comment: TODO
std::size_t index_of_pair(
    std::size_t a1, std::size_t a2, std::size_t a3,
    std::size_t b1, std::size_t b2, std::size_t b3
);

// generate all pair (ijk)(rst) that 
// i+j+k==na and r+s+t==nb
std::vector<ijkPair> generate_pair(std::size_t na,
                                    std::size_t nb);

