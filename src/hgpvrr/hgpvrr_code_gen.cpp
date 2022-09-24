#include "ijk.hpp"
#include "pair.hpp"
#include "gen_utility.hpp"
#include <iostream>
#include <fstream>
#include <vector>
#include <set>
#include <utility>
#include <algorithm>



int main() {

    std::size_t e = 0, f = 0;
    std::cin >> e >> f;

    std::vector<ijkPair> pairVec;
    ijkPair tmp;
    while (std::cin >> tmp) {
        pairVec.push_back(tmp);
    }

    std::string codeFileName = "hgp_vrr_" + 
        std::to_string(e) + "_" +
        std::to_string(f) + "_.cpp";
    
    std::ofstream ofs(codeFileName);

    /****** print header include ******/
    ofs << "#include \"hgp_vrr.hpp\"" << std::endl;
    ofs << "#include \"boysfun.hpp\"" << std::endl;
    ofs << "#include <vector>" << std::endl;
    ofs << "#include <cmath>" << std::endl;
    ofs << std::endl;
    ofs << "namespace nhfInt {" << std::endl;
    ofs << std::endl;
    ofs << "using VecReal = std::vector<double>;" << std::endl;
    ofs << std::endl;

    /******       function name       ******/
    ofs << "void hgp_vrr_" << e << "_" << f << "_(" << std::endl;
    ofs << "    VecReal &" + array_name(e, f) + ", " << std::endl;
    ofs << "    double zetaAB, double kAB, "
           "double Px, double Py, double Pz," << std::endl;
    ofs << "    double PAx, double PAy, double PAz, " << std::endl;
    ofs << "    double zetaCD, double kCD, "
           "double Qx, double Qy, double Qz, " << std::endl;
    ofs << "    double QCx, double QCy, double QCz" << std::endl;
    ofs << ") { " << std::endl;
    

    /******     values for calculate    ******/
    ofs << "    double zetaSum   = zetaAB + zetaCD;" << std::endl;
    ofs << "    double invZeta   = 1.0 / zetaSum;" << std::endl;
    ofs << "    double invZetaAB = 1.0 / zetaAB;" << std::endl;
    ofs << "    double invZetaCD = 1.0 / zetaCD;" << std::endl;

    // PQ
    ofs << "    double PQx = Px - Qx;" << std::endl;
    ofs << "    double PQy = Py - Qy;" << std::endl;
    ofs << "    double PQz = Pz - Qz;" << std::endl;
    
    // W
    ofs << "    double Wx = (zetaAB * Px + zetaCD * Qx) * invZeta;" << std::endl;
    ofs << "    double Wy = (zetaAB * Py + zetaCD * Qy) * invZeta;" << std::endl;
    ofs << "    double Wz = (zetaAB * Pz + zetaCD * Qz) * invZeta;" << std::endl;

    // WP
    ofs << "    double WPx = Wx - Px;" << std::endl;
    ofs << "    double WPy = Wy - Py;" << std::endl;
    ofs << "    double WPz = Wz - Pz;" << std::endl;

    // WQ
    ofs << "    double WQx = Wx - Qx;" << std::endl;
    ofs << "    double WQy = Wy - Qy;" << std::endl;
    ofs << "    double WQz = Wz - Qz;" << std::endl;

    ofs << std::endl;

    // boysFun input T
    ofs << "    double len2PQ = PQx*PQx + PQy*PQy + PQz*PQz;" << std::endl;
    ofs << "    double T = zetaAB * zetaCD * invZeta * len2PQ;" << std::endl;
    ofs << "    double preBoysFunCoeff = std::sqrt(invZeta) * kAB * kCD;" << std::endl;
    ofs << std::endl;

    /******      get array information       ******/

    using RowCol = std::pair<std::size_t, std::size_t>;
    std::map<RowCol, std::size_t> info;
    for (const ijkPair &p : pairVec) {
        std::size_t na = p.a.sum();
        std::size_t nb = p.b.sum();

        if (info.find({na, nb}) == info.end()) {
            info[{na, nb}] = p.m;
        }
        else {
            std::size_t mMaxStored = info[{na, nb}];
            info[{na, nb}] = std::max(mMaxStored, p.m);
        }
    }

    struct ArrayInfo {
        std::size_t row;
        std::size_t col;
        std::size_t mMax;

        ArrayInfo() : row(0), col(0), mMax(0) {}
        ArrayInfo(std::size_t row, std::size_t col, std::size_t mMax)
        : row(row), col(col), mMax(mMax) {}
    };

    std::vector<ArrayInfo> arrInfoVec;
    for (const std::pair<RowCol, std::size_t> &i : info) {
        arrInfoVec.push_back(ArrayInfo(
            i.first.first,
            i.first.second,
            i.second
        ));
    }

    // used in sort array
    auto cmp1 = [](const ArrayInfo &ai1, const ArrayInfo &ai2) -> bool {
        std::size_t sum1 = ai1.row + ai1.col;
        std::size_t sum2 = ai2.row + ai2.col;
        if (sum1 != sum2) return sum1 < sum2;

        if (ai1.row != ai2.row)
            return ai1.row < ai2.row;
        
        return ai1.col < ai2.col;
    };

    std::sort(arrInfoVec.begin(), arrInfoVec.end(), cmp1);

    std::size_t maxArraySize = 0;
    for (const ArrayInfo &ai : arrInfoVec) {
        std::size_t na = ai.row;
        std::size_t nb = ai.col;
        std::size_t mMax = ai.mMax;
        std::size_t arraySize = array_size_multip(na, nb, mMax);
        maxArraySize = std::max(maxArraySize, arraySize);
    }

    std::size_t widthMaxArraySize = count_digit(maxArraySize);

    for (const ArrayInfo &ai : arrInfoVec) {
        std::size_t na = ai.row;
        std::size_t nb = ai.col;
        std::size_t mMax = ai.mMax;

        // this is input argument
        if (na == e && nb == f) {
            continue;
        }

        ofs << "    double "
            << array_define_multip(na, nb, mMax, widthMaxArraySize)
            << ";" << std::endl;
    }
    ofs << std::endl;

    /******             write [00]^{m}         ******/
    ArrayInfo a0b0m = arrInfoVec.front();
    assert(a0b0m.row == 0);
    assert(a0b0m.col == 0);

    std::size_t width_mMax = count_digit(a0b0m.mMax);

    for (std::size_t m = 0; m <= a0b0m.mMax; ++m) {
        ofs << "    a0b0[" + format_number(m, width_mMax) + "] = "
            << "preBoysFunCoeff * boysfun("
            << format_number(m, width_mMax) << ", T);" << std::endl; 
    }

    ofs << std::endl;


    /*************     generate       *************/

    // sort order: sumAll, na, nb, m, a, b
    auto cmp2 = [](const ijkPair &p1, const ijkPair &p2) -> bool {
        std::size_t p1aSum = p1.a.sum();
        std::size_t p1bSum = p1.b.sum();
        std::size_t p2aSum = p2.a.sum();
        std::size_t p2bSum = p2.b.sum();
        std::size_t nP1 = p1aSum+ p1bSum;
        std::size_t nP2 = p2aSum+ p2bSum;

        if (nP1 != nP2) return nP1 < nP2;
        if (p1aSum != p2aSum) return p1aSum < p2aSum;
        if (p1.m != p2.m) return p1.m < p2.m;
        if (p1.a != p2.a) return p1.a < p2.a;
        return p1.b < p2.b;
    };

    std::sort(pairVec.begin(), pairVec.end(), cmp2);

    std::set<ijkPair> hasCalcEle;

    std::vector<std::string> xyz = {"x", "y", "z"};

    std::vector<std::string> coeff_a = {"PAx", "PAy", "PAz", "QCx", "QCy", "QCz"};
    std::vector<std::string> coeff_b = {"WPx", "WPy", "WPz", "WQx", "WQy", "WQz"};
    std::vector<std::string> coeff_c = {"invZetaAB", "invZetaAB", "invZetaAB", 
                                        "invZetaCD", "invZetaCD", "invZetaCD"};
    std::vector<std::string> coeff_d = {"zetaCD", "zetaCD", "zetaCD",
                                        "zetaAB", "zetaAB", "zetaAB"};


    for (const ijkPair &p : pairVec) {
        if (p.a.is_zero() && p.b.is_zero()) {
            hasCalcEle.insert(p);
            continue;
        }

        for (std::size_t i = 0; i < 6; ++i) {

            if (p[i] == 0) continue;

            // check whether can be calculated
            if (p[i] > 0) {
                ijkPair needA = p.hgp_vrr_need_a(i);
                ijkPair needB = p.hgp_vrr_need_b(i);

                if (hasCalcEle.find(needA) == hasCalcEle.end()) continue;
                if (hasCalcEle.find(needB) == hasCalcEle.end()) continue;
            }

            if (p[i] > 1) {
                ijkPair needC = p.hgp_vrr_need_c(i);
                ijkPair needD = p.hgp_vrr_need_d(i);

                if (hasCalcEle.find(needC) == hasCalcEle.end()) continue;
                if (hasCalcEle.find(needD) == hasCalcEle.end()) continue;
            }

            std::size_t cPos = (i+3) % 6;
            if (p[i] > 0 && p[cPos] > 0) {
                ijkPair needE = p.hgp_vrr_need_e(i);
                if (hasCalcEle.find(needE) == hasCalcEle.end()) continue;
            }

            // if come here, can be calculate

            ofs << "    " << p.array_elem(widthMaxArraySize)
                << " = " << coeff_a[i] 
                << " * " << p.hgp_vrr_need_a(i).array_elem(widthMaxArraySize)
                << " + " << coeff_b[i] 
                << " * " << p.hgp_vrr_need_b(i).array_elem(widthMaxArraySize);

            if (p[i] > 1) {
                ofs << " + 0.5 * " << p[i] - 1 << " * " << coeff_c[i] << " * ("
                    << p.hgp_vrr_need_c(i).array_elem(widthMaxArraySize)
                    << " - " << coeff_d[i] << " * invZeta * " 
                    << p.hgp_vrr_need_d(i).array_elem(widthMaxArraySize)
                    << ")";
            }

            if (p[cPos] > 0) {
                ofs << " + 0.5 * " << p[cPos] << " * invZeta * "
                    << p.hgp_vrr_need_e(i).array_elem(widthMaxArraySize);
            }

            ofs << ";" << std::endl;

            hasCalcEle.insert(p);

            break;
        }

        // check calculated
        assert(hasCalcEle.find(p) != hasCalcEle.end());
    }

    

    /******       tail information      ******/
    ofs << "} // function (hgp_vrr_" << e << "_" << f << "_)" << std::endl;
    ofs << std::endl;
    ofs << "} // namespace (nhfInt)" << std::endl;
    ofs << std::endl;
    
    return 0;
}