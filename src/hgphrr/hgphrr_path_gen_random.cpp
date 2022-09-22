#include "ijk.hpp"
#include "pair.hpp"
#include <iostream>
#include <vector>
#include <set>
#include <queue>
#include <random>
#include <fstream>
#include <cstdio>
#include <utility>

std::vector<ijkPair>
hgp_hrr_path_gen_random(std::size_t a, std::size_t b);

int main() {

    // try times
    std::size_t maxTryTimes = 10000;

    std::size_t a = 0, b = 0;
    std::cin >> a >> b;

    // result
    std::vector<ijkPair> pathMin;

    for (std::size_t i = 0; i < maxTryTimes; ++i) {
        std::printf("a = %2ld    b = %2ld    try = %4ld / %4ld\n",
                                            a, b, i, maxTryTimes);
        
        std::vector<ijkPair>
        thisTurn = hgp_hrr_path_gen_random(a, b);

        if (i == 0 || thisTurn.size() < pathMin.size()) {
            pathMin = std::move(thisTurn);
        }
    }


    std::string pathFileName = "path_hgp_hrr_" 
        + std::to_string(a) + "_" + std::to_string(b) + "_"
        + std::to_string(pathMin.size()) + "_.txt";

    std::ofstream ofs(pathFileName);

    ofs << a << " " << b << std::endl;
    for (const ijkPair &p : pathMin) {
        ofs << p << std::endl;
    }

    ofs.close();

    return 0;
}

std::vector<ijkPair>
hgp_hrr_path_gen_random(std::size_t a, std::size_t b) {
    std::vector<ijkPair> pairVec = generate_pair(a, b);

    std::set<ijkPair>   pairSet;
    std::queue<ijkPair> pairQue;

    for (const ijkPair &p : pairVec) {
        pairQue.push(p);
    }

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distrib(1, 6);

    while (! pairQue.empty()) {
        ijkPair p = pairQue.front();
        pairQue.pop();

        // insert set first
        pairSet.insert(p);

        if (p.b.is_zero()) {
            continue;
        }

        // get index of non-zero elements
        std::vector<std::size_t> nonZeroIdx;
        for (std::size_t i = 0; i < 3; ++i) {
            if (p.b[i] != 0)
                nonZeroIdx.push_back(i);
        }

        std::size_t randNum = distrib(gen);
        std::size_t choose = randNum % nonZeroIdx.size();
        std::size_t hrrIdx = nonZeroIdx[choose];

        pairQue.push(p.hgp_hrr_need_a(hrrIdx));
        pairQue.push(p.hgp_hrr_need_b(hrrIdx));
    }

    return std::vector<ijkPair>(pairSet.begin(), pairSet.end());
}