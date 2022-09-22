#include <iostream>
#include <fstream>
#include <string>
#include <cstddef>
#include <set>
#include <utility>
#include <algorithm>
#include "pair.hpp"
#include "gen_utility.hpp"

std::vector<std::string> xyz = {"x", "y", "z"};

// check whether the path is legal
bool check_path(
    const std::vector<ijkPair> &pairVec,
    std::size_t a, std::size_t b
);


int main() {

    std::size_t a = 0;
    std::size_t b = 0;
    std::vector<ijkPair> pairVec;

    // read in path
    std::cin >> a >> b;
    ijkPair tmp;
    while (std::cin >> tmp) {
        pairVec.push_back(tmp);
    }

    // check whether path is legal
    if (!check_path(pairVec, a, b)) {
        std::cerr << "path error!" << std::endl;
        return -1;
    }

    // code filename
    std::string codeFileName = 
    "hgp_hrr_" + std::to_string(a) + 
    "_" + std::to_string(b) + "_.cpp";

    // recreate code file
    std::ofstream ofs(codeFileName);

    // header file
    ofs << "#include \"hgp_hrr.hpp\"" << std::endl;
    ofs << "#include <vector>" << std::endl;
    ofs << std::endl;

    ofs << "namespace nhfInt {" << std::endl;
    ofs << std::endl;
    ofs << "using VecReal = std::vector<double>;" << std::endl;
    ofs << std::endl;

    // function name
    ofs << "VecReal hgp_hrr_" << a << "_" << b 
        << "_(const VecReal &hrrInp, "
           "double x, double y, double z) { " << std::endl;

    if (b == 0) {
        ofs << "    VecReal " << array_name(a,b)
            << "(hrrInp);" << std::endl;

        ofs << "    return " << array_name(a,b) << ";" << std::endl;
        ofs << std::endl;
        ofs << "}  // function (hgp_hrr_" << a << "_" << b << "_)" << std::endl;
        ofs << std::endl;
        ofs << "}  // namespace (nhfInt)" << std::endl;
        ofs << std::endl;

        ofs.close();

        return 0;
          
    }
    


    /*****************   parse input data   *****************/
    std::size_t maxAddNum = 0;
    for (std::size_t ia = a; ia < a+b; ++ia) {
        maxAddNum += (ia + 1) * (ia + 2) / 2;
    }
    std:size_t widthMaxAddNum = count_digit(maxAddNum);

    std::size_t axb0Num = 0;  // count number of integral
    for (std::size_t ia = a; ia <= a + b; ++ia) {
        ofs << "    const double *" << array_name(ia, 0) << " = hrrInp.data() + " 
            << format_number(axb0Num, widthMaxAddNum) << ";" << std::endl;
        axb0Num += (ia + 1) * (ia + 2) / 2;
    }
    ofs << std::endl;



    /******    define arrays for recurrence relation    ******/

    using ArrayInfo = std::pair<std::size_t, std::size_t>;
    
    std::set<ArrayInfo> midArraySet;
    for (const ijkPair &p : pairVec) {
        std::size_t aSum = p.a.sum();
        std::size_t bSum = p.b.sum();

        // input data and result data
        if (bSum == 0 || (aSum == a && bSum == b)) {
            continue;
        }

        midArraySet.insert({aSum, bSum});
    }

    // store into vector for sort
    std::vector<ArrayInfo> midArrayVec(
        midArraySet.begin(), midArraySet.end()
    );

    // sort as constructive order
    std::sort(midArrayVec.begin(), midArrayVec.end(),
        [](const ArrayInfo &pa, const ArrayInfo &pb) {
            if (pa.second != pb.second) return pa.second < pb.second;
            return pa.first < pb.first;
        }
    );

    // find max array size for format code
    std::size_t maxArraySize = 0;
    for (const ArrayInfo &ai : midArrayVec) {
        std::size_t arraySize = array_size_single(ai.first, ai.second);
        maxArraySize = std::max(maxArraySize, arraySize);
    }

    // digit numbers of maxArraySize
    std::size_t widthMaxArraySize = count_digit(maxArraySize);

    // output arrays
    ofs <<"    // intermediate arrays" << std::endl;
    for (const ArrayInfo &pr : midArrayVec) {
        ofs << "    double "
            << array_define_single(pr.first, pr.second, widthMaxArraySize)
            << ";" << std::endl;
    }
    ofs << std::endl;



    /************    define resulted VecReal    ************/
    ofs << "    // resulted VecReal" << std::endl;
    ofs << "    VecReal "
        << array_name(a,b)
        <<"(" << array_size_single(a, b) << ")"
        << ";" << std::endl;
    ofs << std::endl;



    /******  use the recursive relationship to recurs  ******/

    // choose element need calculate
    std::vector<ijkPair> calcEleVec;
    for (const ijkPair &p : pairVec) {
        if (p.b.sum() == 0) {
            continue;
        }

        calcEleVec.push_back(p);
    }

    // compare order: bSum, aSum, a, b
    auto cmp = [](const ijkPair &p1, const ijkPair &p2) -> bool {
        std::size_t p1aSum = p1.a.sum();
        std::size_t p1bSum = p1.b.sum();
        std::size_t p2aSum = p2.a.sum();
        std::size_t p2bSum = p2.b.sum();

        if (p1bSum != p2bSum) return p1bSum < p2bSum;
        if (p1aSum != p2aSum) return p1aSum < p2aSum;
        if (p1.a != p2.a) return p1.a < p2.a;
        return p1.b < p2.b;
    };

    std::sort(calcEleVec.begin(), calcEleVec.end(), cmp);

    // elements already calculated
    std::set<ijkPair> hasCalcEle;
    for (std::size_t e = a; e <= a+b; ++e) {
        std::vector<ijkPair> e0f0 = generate_pair(e, 0);
        for (const ijkPair &p : e0f0) {
            hasCalcEle.insert(p);
        }
    }

    // calculate max number of digit
    std::size_t maxSize = std::max({
        array_size_single(a+b, 0),
        array_size_single(  a, b),
        maxArraySize
    });

    assert(maxSize > 0);
    std::size_t maxIdx = maxSize - 1;
    std::size_t widthMaxIdx = count_digit(maxIdx);

    for (const ijkPair &p : calcEleVec) {
        for (std::size_t i = 0; i < 3; ++i) {
            if (p.b[i] == 0) {
                continue;
            }

            ijkPair needA = p.hgp_hrr_need_a(i);
            ijkPair needB = p.hgp_hrr_need_b(i);

            bool canCalculate = (hasCalcEle.find(needA) != hasCalcEle.end()
                              && hasCalcEle.find(needA) != hasCalcEle.end());

            if (canCalculate) {

                ofs << "    "
                    << p.array_elem(widthMaxIdx)
                    << " = "
                    << needA.array_elem(widthMaxIdx)
                    << " + "
                    << xyz[i]
                    << " * "
                    << needB.array_elem(widthMaxIdx)
                    << ";";
                
                // output comment
                ofs << "    // "
                    << p.to_comment()
                    << " = "
                    << needA.to_comment()
                    << " + "
                    << "AB" + xyz[i]
                    << " * "
                    << needB.to_comment()
                    <<std::endl;

                hasCalcEle.insert(p);
                break;
            }
        }

        // check whether p has build
        assert(hasCalcEle.find(p) != hasCalcEle.end());
    }
    ofs << std::endl;

    ofs << "    return " << array_name(a,b) << ";" << std::endl;
    ofs << std::endl;
    ofs << "}  // function (hgp_hrr_" << a << "_" << b << "_)" << std::endl;
    ofs << std::endl;
    ofs << "}  // namespace (nhfInt)" << std::endl;
    ofs << std::endl;

    ofs.close();

    return 0;
}


bool check_path(
    const std::vector<ijkPair> &pairVec,
    std::size_t a, std::size_t b
) {
    for (const ijkPair &p : pairVec) {
        if (p.m != 0) return false;
    }
    return true;
}

