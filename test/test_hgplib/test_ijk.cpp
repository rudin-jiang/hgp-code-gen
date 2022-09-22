#include <gtest/gtest.h>
#include "ijk.hpp"

#include <cstddef>
#include <vector>
#include <algorithm>

TEST(TestIjk, TestConstructor) {
    // default constructor
    ijk a;
    EXPECT_EQ(a.i, 0);
    EXPECT_EQ(a.j, 0);
    EXPECT_EQ(a.k, 0);

    // given value
    for (std::size_t i = 0; i < 30; ++i) {
    for (std::size_t j = 0; j < 30; ++j) {
    for (std::size_t k = 0; k < 30; ++k) {
        ijk a(i,j,k);
        EXPECT_EQ(a.i, i);
        EXPECT_EQ(a.j, j);
        EXPECT_EQ(a.k, k);
    }}}
}

TEST(TestIjk, TestOperatorPos) {
    for (std::size_t i = 0; i <= 30; ++i) {
    for (std::size_t j = 0; j <= 30; ++j) {
    for (std::size_t k = 0; k <= 30; ++k) {
        ijk a(i, j, k);
        EXPECT_EQ(a[0], i);
        EXPECT_EQ(a[1], j);
        EXPECT_EQ(a[2], k);

        ijk b;
        b[0] = i;
        b[1] = j;
        b[2] = k;
        EXPECT_EQ(b.i, i);
        EXPECT_EQ(b.j, j);
        EXPECT_EQ(b.k, k);
    }}}
}

TEST(TestIjk, TestIndex) {
    for (std::size_t n = 0; n <= 30; ++n) {
        std::vector<ijk> ijkVec = generate_ijk(n);

        // test number of ijk generate
        std::size_t ijkGenNum = ijkVec.size();
        std::size_t ijkCalNum = (n+1)*(n+2)/2;
        EXPECT_EQ(ijkGenNum, ijkCalNum);

        // test ijk::index()
        for (std::size_t i = 0; i < ijkVec.size(); ++i) {
            EXPECT_EQ(ijkVec[i].index(), i);
        }
    }
}

TEST(TestIjk, TestSum) {
    for (std::size_t i = 0; i <= 30; ++i) {
    for (std::size_t j = 0; j <= 30; ++j) {
    for (std::size_t k = 0; k <= 30; ++k) {
        ijk a(i, j, k);
        EXPECT_EQ(a.sum(), i + j + k);
    }}}
}

TEST(TestIjk, TestIsZero) {
    for (std::size_t i = 0; i <= 30; ++i) {
    for (std::size_t j = 0; j <= 30; ++j) {
    for (std::size_t k = 0; k <= 30; ++k) {
        ijk a(i, j, k);
        if (i == 0 && j == 0 && k == 0) {
            EXPECT_TRUE(a.is_zero());
        }
        else {
            EXPECT_FALSE(a.is_zero());
        }
    }}}
}

TEST(TestIjk, TestOperatorCmp) {
    for (std::size_t n = 0; n <= 30; ++n) {
        std::vector<ijk> ijkVec = generate_ijk(n);
        std::vector<std::vector<std::size_t>> vecVec;
        for (const ijk &a : ijkVec) {
            vecVec.push_back({a.i, a.j, a.k});
        }
        // sort as operator< of vector<int>
        std::sort(vecVec.begin(), vecVec.end());

        // check for operator < > <= >= == !=
        for (std::size_t i = 0; i < vecVec.size(); ++i) {
        for (std::size_t j = 0; j < vecVec.size(); ++j) {
            ijk a(vecVec[i][0], vecVec[i][1], vecVec[i][2]);
            ijk b(vecVec[j][0], vecVec[j][1], vecVec[j][2]);

            if (i < j) {
                EXPECT_TRUE(a <  b);
                EXPECT_TRUE(a <= b);
                EXPECT_TRUE(a != b);

                EXPECT_FALSE(a >  b);
                EXPECT_FALSE(a >= b);
                EXPECT_FALSE(a == b);
            }

            if (i > j) {
                EXPECT_TRUE(a >  b);
                EXPECT_TRUE(a >= b);
                EXPECT_TRUE(a != b);

                EXPECT_FALSE(a <  b);
                EXPECT_FALSE(a <= b);
                EXPECT_FALSE(a == b);
            }

            if (i == j) {
                EXPECT_TRUE(a <=  b);
                EXPECT_TRUE(a >= b);
                EXPECT_TRUE(a == b);

                EXPECT_FALSE(a <  b);
                EXPECT_FALSE(a >  b);
                EXPECT_FALSE(a != b);
            }
        }}

    }
}


