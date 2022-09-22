#include "ijk.hpp"
#include "pair.hpp"
#include "gen_utility.hpp"
#include <vector>
#include <string>
#include <cassert>
#include <set>
#include <map>

// hrr need
ijkPair ijkPair::hgp_hrr_need_a(std::size_t pos) const {
    assert(pos < 3);
    assert(b[pos] > 0);
    
    ijkPair needA = (*this);
    ++(needA.a[pos]);
    --(needA.b[pos]);
    return needA;
}

ijkPair ijkPair::hgp_hrr_need_b(std::size_t pos) const {
    assert(pos < 3);
    assert(b[pos] > 0);
    
    ijkPair needB = (*this);
    --(needB.b[pos]);
    return needB;
}

// vrr need
ijkPair ijkPair::hgp_vrr_need_a(std::size_t pos) const {
    assert(pos < 6);
    assert((*this)[pos] > 0);

    ijkPair need = (*this);
    --need[pos];
    return need;
}

ijkPair ijkPair::hgp_vrr_need_b(std::size_t pos) const {
    assert(pos < 6);
    assert((*this)[pos] > 0);
    
    ijkPair need = (*this);
    --need[pos];
    ++need.m;
    return need;
}

ijkPair ijkPair::hgp_vrr_need_c(std::size_t pos) const {
    assert(pos < 6);
    assert((*this)[pos] > 1);

    ijkPair need = (*this);
    need[pos] -= 2;
    return need;
}

ijkPair ijkPair::hgp_vrr_need_d(std::size_t pos) const {
    assert(pos < 6);
    assert((*this)[pos] > 0);

    ijkPair need = (*this);
    need[pos] -= 2;
    ++need.m;
    return need;
}

ijkPair ijkPair::hgp_vrr_need_e(std::size_t pos) const {
    assert(pos < 6);
    assert((*this)[pos] > 0);

    std::size_t countPos = (pos + 3) % 6;
    assert((*this)[countPos] > 0);

    ijkPair need = (*this);
    --need[pos];
    --need[countPos];
    ++need.m;
    return need;
}

std::size_t ijkPair::array_index_single() const {
    return index_of_pair( a.i, a.j, a.k,
                          b.i, b.j, b.k );
}

std::size_t ijkPair::array_index_multip() const {
    return m * array_size_single(a.sum(), b.sum())
            + array_index_single();
}

std::string ijkPair::array_elem(std::size_t idxLen) const {
    return array_name(a.sum(), b.sum()) + "[" + 
            format_number(array_index_multip(), idxLen) + "]";
}

std::string ijkPair::to_comment(bool pm) const {
    std::string ret = "[" + a.to_comment() + b.to_comment() + "]";
    if (pm) ret += "^{" + encode_number(m) + "}";
    return ret;
}

std::size_t  ijkPair::operator[](std::size_t pos) const {
    assert(pos < 6);
    if (pos < 3) return a[pos];
    return b[pos-3];
}

std::size_t& ijkPair::operator[](std::size_t pos) {
    assert(pos < 6);    
    if (pos < 3) return a[pos];
    return b[pos-3];
}

std::istream& operator>>(std::istream &is, ijkPair &ab){
    is >> ab.a >> ab.b >> ab.m;
    return is;
}

std::ostream& operator<<(std::ostream &os, const ijkPair &ab) {
    os << ab.a << "  " << ab.b << "  " << ab.m;
    return os;
}

bool operator<(const ijkPair &ab, const ijkPair &cd) {
    std::size_t abSumA = ab.a.sum();
    std::size_t abSumB = ab.b.sum();
    std::size_t cdSumA = cd.a.sum();
    std::size_t cdSumB = cd.b.sum();

    if (abSumA != cdSumA) return abSumA < cdSumA;
    if (abSumB != cdSumB) return abSumB < cdSumB;

    if (ab.m != cd.m) return ab.m < cd.m;

    if (ab.a != cd.a) return ab.a < cd.a;
    return ab.b < cd.b;
}

bool operator>(const ijkPair &ab, const ijkPair &cd)
{ return !(ab == cd) && !(ab < cd); }

bool operator<=(const ijkPair &ab, const ijkPair &cd)
{ return !(ab > cd); }

bool operator>=(const ijkPair &ab, const ijkPair &cd)
{ return !(ab < cd); }

bool operator==(const ijkPair &ab, const ijkPair &cd)
{ return (ab.a == cd.a) && (ab.b == cd.b); }

bool operator!=(const ijkPair &ab, const ijkPair &cd)
{ return !(ab == cd); }

std::size_t index_of_pair(
    std::size_t a1, std::size_t a2, std::size_t a3,
    std::size_t b1, std::size_t b2, std::size_t b3
) {
    std::size_t nb = b1 + b2 + b3;
    std::size_t nbs = (nb + 1) * (nb + 2) / 2;
    std::size_t ai = index_of_ijk(a1, a2, a3);
    std::size_t bi = index_of_ijk(b1, b2, b3);
    return ai * nbs + bi;
}

std::vector<ijkPair> generate_pair(
    std::size_t na, std::size_t nb
) {
    std::vector<ijk> aVec = generate_ijk(na);
    std::vector<ijk> bVec = generate_ijk(nb);

    // generate pairs
    std::set<ijkPair> pairSet;
    for (const ijk &a : aVec)
    for (const ijk &b : bVec)
        pairSet.insert(ijkPair(a, b, 0));

    return std::vector<ijkPair>(pairSet.begin(),
                                pairSet.end());
}


