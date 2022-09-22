#include "ijk.hpp"
#include "pair.hpp"
#include <iostream>
#include <fstream>
#include <string>
#include <set>
#include <queue>
#include <random>

std::vector<ijkPair>
hgp_vrr_path_gen_random(std::size_t e, std::size_t f);

int main() {

    // try times
    std::size_t maxTryTimes = 1000;

    std::size_t e = 0, f = 0;
    std::cin >> e >> f;

    std::vector<ijkPair> pathMin;

    for (std::size_t i = 0; i < maxTryTimes; ++i) {
        std::printf("e = %2ld    f = %2ld    try = %4ld / %4ld\n",
                                            e, f, i, maxTryTimes);
        
        std::vector<ijkPair>
        thisTurn = hgp_vrr_path_gen_random(e, f);

        if (i == 0 || thisTurn.size() < pathMin.size()) {
            pathMin = std::move(thisTurn);
        }
    }

    std::string pathFileName = "path_hgp_vrr_" 
        + std::to_string(e) + "_" + std::to_string(f) + "_"
        + std::to_string(pathMin.size()) + "_.txt";

    std::ofstream ofs(pathFileName);

    ofs << e << " " << f << std::endl;
    for (const ijkPair &p : pathMin) {
        ofs << p << std::endl;
    }

    ofs.close();

    return 0;
}

std::vector<ijkPair>
hgp_vrr_path_gen_random(std::size_t e, std::size_t f) {
    std::vector<ijkPair> pairVec = generate_pair(e, f);

    std::set<ijkPair>   pairSet;
    std::queue<ijkPair> pairQue;

    for (const ijkPair &p : pairVec) {
        pairQue.push(p);
    }

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distrib(1, 1024);

    while (! pairQue.empty()) {
        ijkPair p = pairQue.front();
        pairQue.pop();

        pairSet.insert(p);

        if (p.a.is_zero() && p.b.is_zero()) {
            continue;
        }

        // get index of non-zero elements
        std::vector<std::size_t> nonZeroIdx;
        for (std::size_t i = 0; i < 6; ++i) {
            if (p[i] != 0)
                nonZeroIdx.push_back(i);
        }

        std::size_t randNum = distrib(gen);
        std::size_t choose = randNum % nonZeroIdx.size();
        std::size_t vrrIdx = nonZeroIdx[choose];

        // must can be add need_a and need_b
        pairQue.push(p.hgp_vrr_need_a(vrrIdx));
        pairQue.push(p.hgp_vrr_need_b(vrrIdx));

        // if p[pos] > 1, then can be added
        if (p[vrrIdx] > 1) {
            pairQue.push(p.hgp_vrr_need_c(vrrIdx));
            pairQue.push(p.hgp_vrr_need_d(vrrIdx));
        }

        // if pos[countPos] > 0, then can be added
        std::size_t countPos = (vrrIdx + 3) % 6;
        if (p[countPos] > 0) {
            pairQue.push(p.hgp_vrr_need_e(vrrIdx));
        }
    }

    return std::vector<ijkPair>(pairSet.begin(),
                                pairSet.end());
}