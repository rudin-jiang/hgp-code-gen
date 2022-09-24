#include "hgp_vrr.hpp"
#include "boysfun.hpp"
#include <vector>
#include <cmath>

namespace nhfInt {

using VecReal = std::vector<double>;

void hgp_vrr_4_0_(
    VecReal &a4b0, 
    double zetaAB, double kAB, double Px, double Py, double Pz,
    double PAx, double PAy, double PAz, 
    double zetaCD, double kCD, double Qx, double Qy, double Qz, 
    double QCx, double QCy, double QCz
) { 
    double zetaSum   = zetaAB + zetaCD;
    double invZeta   = 1.0 / zetaSum;
    double invZetaAB = 1.0 / zetaAB;
    double invZetaCD = 1.0 / zetaCD;
    double PQx = Px - Qx;
    double PQy = Py - Qy;
    double PQz = Pz - Qz;
    double Wx = (zetaAB * Px + zetaCD * Qx) * invZeta;
    double Wy = (zetaAB * Py + zetaCD * Qy) * invZeta;
    double Wz = (zetaAB * Pz + zetaCD * Qz) * invZeta;
    double WPx = Wx - Px;
    double WPy = Wy - Py;
    double WPz = Wz - Pz;
    double WQx = Wx - Qx;
    double WQy = Wy - Qy;
    double WQz = Wz - Qz;

    double len2PQ = PQx*PQx + PQy*PQy + PQz*PQz;
    double T = zetaAB * zetaCD * invZeta * len2PQ;
    double preBoysFunCoeff = std::sqrt(invZeta) * kAB * kCD;

    double a0b0[ 5];
    double a1b0[12];
    double a2b0[18];
    double a3b0[20];

    a0b0[0] = preBoysFunCoeff * boysfun(0, T);
    a0b0[1] = preBoysFunCoeff * boysfun(1, T);
    a0b0[2] = preBoysFunCoeff * boysfun(2, T);
    a0b0[3] = preBoysFunCoeff * boysfun(3, T);
    a0b0[4] = preBoysFunCoeff * boysfun(4, T);

    a1b0[ 0] = PAz * a0b0[ 0] + WPz * a0b0[ 1];
    a1b0[ 1] = PAy * a0b0[ 0] + WPy * a0b0[ 1];
    a1b0[ 2] = PAx * a0b0[ 0] + WPx * a0b0[ 1];
    a1b0[ 3] = PAz * a0b0[ 1] + WPz * a0b0[ 2];
    a1b0[ 4] = PAy * a0b0[ 1] + WPy * a0b0[ 2];
    a1b0[ 5] = PAx * a0b0[ 1] + WPx * a0b0[ 2];
    a1b0[ 6] = PAz * a0b0[ 2] + WPz * a0b0[ 3];
    a1b0[ 7] = PAy * a0b0[ 2] + WPy * a0b0[ 3];
    a1b0[ 8] = PAx * a0b0[ 2] + WPx * a0b0[ 3];
    a1b0[ 9] = PAz * a0b0[ 3] + WPz * a0b0[ 4];
    a1b0[10] = PAy * a0b0[ 3] + WPy * a0b0[ 4];
    a1b0[11] = PAx * a0b0[ 3] + WPx * a0b0[ 4];
    a2b0[ 0] = PAz * a1b0[ 0] + WPz * a1b0[ 3] + 0.5 * 1 * invZetaAB * (a0b0[ 0] - zetaCD * invZeta * a0b0[ 1]);
    a2b0[ 1] = PAy * a1b0[ 0] + WPy * a1b0[ 3];
    a2b0[ 2] = PAy * a1b0[ 1] + WPy * a1b0[ 4] + 0.5 * 1 * invZetaAB * (a0b0[ 0] - zetaCD * invZeta * a0b0[ 1]);
    a2b0[ 3] = PAx * a1b0[ 0] + WPx * a1b0[ 3];
    a2b0[ 5] = PAx * a1b0[ 2] + WPx * a1b0[ 5] + 0.5 * 1 * invZetaAB * (a0b0[ 0] - zetaCD * invZeta * a0b0[ 1]);
    a2b0[ 6] = PAz * a1b0[ 3] + WPz * a1b0[ 6] + 0.5 * 1 * invZetaAB * (a0b0[ 1] - zetaCD * invZeta * a0b0[ 2]);
    a2b0[ 7] = PAy * a1b0[ 3] + WPy * a1b0[ 6];
    a2b0[ 8] = PAy * a1b0[ 4] + WPy * a1b0[ 7] + 0.5 * 1 * invZetaAB * (a0b0[ 1] - zetaCD * invZeta * a0b0[ 2]);
    a2b0[ 9] = PAx * a1b0[ 3] + WPx * a1b0[ 6];
    a2b0[11] = PAx * a1b0[ 5] + WPx * a1b0[ 8] + 0.5 * 1 * invZetaAB * (a0b0[ 1] - zetaCD * invZeta * a0b0[ 2]);
    a2b0[12] = PAz * a1b0[ 6] + WPz * a1b0[ 9] + 0.5 * 1 * invZetaAB * (a0b0[ 2] - zetaCD * invZeta * a0b0[ 3]);
    a2b0[13] = PAy * a1b0[ 6] + WPy * a1b0[ 9];
    a2b0[14] = PAy * a1b0[ 7] + WPy * a1b0[10] + 0.5 * 1 * invZetaAB * (a0b0[ 2] - zetaCD * invZeta * a0b0[ 3]);
    a2b0[17] = PAx * a1b0[ 8] + WPx * a1b0[11] + 0.5 * 1 * invZetaAB * (a0b0[ 2] - zetaCD * invZeta * a0b0[ 3]);
    a3b0[ 0] = PAz * a2b0[ 0] + WPz * a2b0[ 6] + 0.5 * 2 * invZetaAB * (a1b0[ 0] - zetaCD * invZeta * a1b0[ 3]);
    a3b0[ 1] = PAy * a2b0[ 0] + WPy * a2b0[ 6];
    a3b0[ 2] = PAy * a2b0[ 1] + WPy * a2b0[ 7] + 0.5 * 1 * invZetaAB * (a1b0[ 0] - zetaCD * invZeta * a1b0[ 3]);
    a3b0[ 3] = PAy * a2b0[ 2] + WPy * a2b0[ 8] + 0.5 * 2 * invZetaAB * (a1b0[ 1] - zetaCD * invZeta * a1b0[ 4]);
    a3b0[ 7] = PAx * a2b0[ 3] + WPx * a2b0[ 9] + 0.5 * 1 * invZetaAB * (a1b0[ 0] - zetaCD * invZeta * a1b0[ 3]);
    a3b0[ 8] = PAy * a2b0[ 5] + WPy * a2b0[11];
    a3b0[ 9] = PAx * a2b0[ 5] + WPx * a2b0[11] + 0.5 * 2 * invZetaAB * (a1b0[ 2] - zetaCD * invZeta * a1b0[ 5]);
    a3b0[10] = PAz * a2b0[ 6] + WPz * a2b0[12] + 0.5 * 2 * invZetaAB * (a1b0[ 3] - zetaCD * invZeta * a1b0[ 6]);
    a3b0[11] = PAy * a2b0[ 6] + WPy * a2b0[12];
    a3b0[12] = PAy * a2b0[ 7] + WPy * a2b0[13] + 0.5 * 1 * invZetaAB * (a1b0[ 3] - zetaCD * invZeta * a1b0[ 6]);
    a3b0[13] = PAy * a2b0[ 8] + WPy * a2b0[14] + 0.5 * 2 * invZetaAB * (a1b0[ 4] - zetaCD * invZeta * a1b0[ 7]);
    a3b0[17] = PAz * a2b0[11] + WPz * a2b0[17];
    a3b0[18] = PAy * a2b0[11] + WPy * a2b0[17];
    a3b0[19] = PAx * a2b0[11] + WPx * a2b0[17] + 0.5 * 2 * invZetaAB * (a1b0[ 5] - zetaCD * invZeta * a1b0[ 8]);
    a4b0[ 0] = PAz * a3b0[ 0] + WPz * a3b0[10] + 0.5 * 3 * invZetaAB * (a2b0[ 0] - zetaCD * invZeta * a2b0[ 6]);
    a4b0[ 1] = PAy * a3b0[ 0] + WPy * a3b0[10];
    a4b0[ 2] = PAy * a3b0[ 1] + WPy * a3b0[11] + 0.5 * 1 * invZetaAB * (a2b0[ 0] - zetaCD * invZeta * a2b0[ 6]);
    a4b0[ 3] = PAy * a3b0[ 2] + WPy * a3b0[12] + 0.5 * 2 * invZetaAB * (a2b0[ 1] - zetaCD * invZeta * a2b0[ 7]);
    a4b0[ 4] = PAy * a3b0[ 3] + WPy * a3b0[13] + 0.5 * 3 * invZetaAB * (a2b0[ 2] - zetaCD * invZeta * a2b0[ 8]);
    a4b0[ 5] = PAx * a3b0[ 0] + WPx * a3b0[10];
    a4b0[ 6] = PAx * a3b0[ 1] + WPx * a3b0[11];
    a4b0[ 7] = PAx * a3b0[ 2] + WPx * a3b0[12];
    a4b0[ 8] = PAx * a3b0[ 3] + WPx * a3b0[13];
    a4b0[ 9] = PAz * a3b0[ 7] + WPz * a3b0[17] + 0.5 * 1 * invZetaAB * (a2b0[ 5] - zetaCD * invZeta * a2b0[11]);
    a4b0[10] = PAy * a3b0[ 7] + WPy * a3b0[17];
    a4b0[11] = PAy * a3b0[ 8] + WPy * a3b0[18] + 0.5 * 1 * invZetaAB * (a2b0[ 5] - zetaCD * invZeta * a2b0[11]);
    a4b0[12] = PAx * a3b0[ 7] + WPx * a3b0[17] + 0.5 * 2 * invZetaAB * (a2b0[ 3] - zetaCD * invZeta * a2b0[ 9]);
    a4b0[13] = PAy * a3b0[ 9] + WPy * a3b0[19];
    a4b0[14] = PAx * a3b0[ 9] + WPx * a3b0[19] + 0.5 * 3 * invZetaAB * (a2b0[ 5] - zetaCD * invZeta * a2b0[11]);
} // function (hgp_vrr_4_0_)

} // namespace (nhfInt)

