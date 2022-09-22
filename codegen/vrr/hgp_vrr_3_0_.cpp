#include "hgp_vrr.hpp"
#include "boysfun.hpp"
#include <vector>
#include <cmath>

namespace nhfInt {

using VecReal = std::vector<double>;

void hgp_vrr_3_0_(
    VecReal &a3b0, 
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

    double a0b0[ 4];
    double a1b0[ 9];
    double a2b0[12];

    a0b0[0] = preBoysFunCoeff * boysfun(0, T);
    a0b0[1] = preBoysFunCoeff * boysfun(1, T);
    a0b0[2] = preBoysFunCoeff * boysfun(2, T);
    a0b0[3] = preBoysFunCoeff * boysfun(3, T);

    a1b0[ 0] = PAz * a0b0[ 0] + WPz * a0b0[ 1];
    a1b0[ 1] = PAy * a0b0[ 0] + WPy * a0b0[ 1];
    a1b0[ 2] = PAx * a0b0[ 0] + WPx * a0b0[ 1];
    a1b0[ 3] = PAz * a0b0[ 1] + WPz * a0b0[ 2];
    a1b0[ 4] = PAy * a0b0[ 1] + WPy * a0b0[ 2];
    a1b0[ 5] = PAx * a0b0[ 1] + WPx * a0b0[ 2];
    a1b0[ 6] = PAz * a0b0[ 2] + WPz * a0b0[ 3];
    a1b0[ 7] = PAy * a0b0[ 2] + WPy * a0b0[ 3];
    a1b0[ 8] = PAx * a0b0[ 2] + WPx * a0b0[ 3];
    a2b0[ 0] = PAz * a1b0[ 0] + WPz * a1b0[ 3] + 0.5 * 1 * invZetaAB * (a0b0[ 0] - zetaCD * invZeta * a0b0[ 1]);
    a2b0[ 2] = PAy * a1b0[ 1] + WPy * a1b0[ 4] + 0.5 * 1 * invZetaAB * (a0b0[ 0] - zetaCD * invZeta * a0b0[ 1]);
    a2b0[ 4] = PAx * a1b0[ 1] + WPx * a1b0[ 4];
    a2b0[ 4] = PAy * a1b0[ 2] + WPy * a1b0[ 5];
    a2b0[ 5] = PAx * a1b0[ 2] + WPx * a1b0[ 5] + 0.5 * 1 * invZetaAB * (a0b0[ 0] - zetaCD * invZeta * a0b0[ 1]);
    a2b0[ 6] = PAz * a1b0[ 3] + WPz * a1b0[ 6] + 0.5 * 1 * invZetaAB * (a0b0[ 1] - zetaCD * invZeta * a0b0[ 2]);
    a2b0[ 8] = PAy * a1b0[ 4] + WPy * a1b0[ 7] + 0.5 * 1 * invZetaAB * (a0b0[ 1] - zetaCD * invZeta * a0b0[ 2]);
    a2b0[10] = PAx * a1b0[ 4] + WPx * a1b0[ 7];
    a2b0[10] = PAy * a1b0[ 5] + WPy * a1b0[ 8];
    a2b0[11] = PAx * a1b0[ 5] + WPx * a1b0[ 8] + 0.5 * 1 * invZetaAB * (a0b0[ 1] - zetaCD * invZeta * a0b0[ 2]);
    a3b0[ 0] = PAz * a2b0[ 0] + WPz * a2b0[ 6] + 0.5 * 2 * invZetaAB * (a1b0[ 0] - zetaCD * invZeta * a1b0[ 3]);
    a3b0[ 1] = PAy * a2b0[ 0] + WPy * a2b0[ 6];
    a3b0[ 2] = PAz * a2b0[ 2] + WPz * a2b0[ 8];
    a3b0[ 3] = PAy * a2b0[ 2] + WPy * a2b0[ 8] + 0.5 * 2 * invZetaAB * (a1b0[ 1] - zetaCD * invZeta * a1b0[ 4]);
    a3b0[ 4] = PAx * a2b0[ 0] + WPx * a2b0[ 6];
    a3b0[ 5] = PAz * a2b0[ 4] + WPz * a2b0[10];
    a3b0[ 6] = PAx * a2b0[ 2] + WPx * a2b0[ 8];
    a3b0[ 6] = PAy * a2b0[ 4] + WPy * a2b0[10] + 0.5 * 1 * invZetaAB * (a1b0[ 2] - zetaCD * invZeta * a1b0[ 5]);
    a3b0[ 7] = PAz * a2b0[ 5] + WPz * a2b0[11];
    a3b0[ 8] = PAx * a2b0[ 4] + WPx * a2b0[10] + 0.5 * 1 * invZetaAB * (a1b0[ 1] - zetaCD * invZeta * a1b0[ 4]);
    a3b0[ 8] = PAy * a2b0[ 5] + WPy * a2b0[11];
    a3b0[ 9] = PAx * a2b0[ 5] + WPx * a2b0[11] + 0.5 * 2 * invZetaAB * (a1b0[ 2] - zetaCD * invZeta * a1b0[ 5]);
} // function (hgp_vrr_3_0_)

} // namespace (nhfInt)

