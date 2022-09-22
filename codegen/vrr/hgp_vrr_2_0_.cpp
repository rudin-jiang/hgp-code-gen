#include "hgp_vrr.hpp"
#include "boysfun.hpp"
#include <vector>
#include <cmath>

namespace nhfInt {

using VecReal = std::vector<double>;

void hgp_vrr_2_0_(
    VecReal &a2b0, 
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

    double a0b0[3];
    double a1b0[6];

    a0b0[0] = preBoysFunCoeff * boysfun(0, T);
    a0b0[1] = preBoysFunCoeff * boysfun(1, T);
    a0b0[2] = preBoysFunCoeff * boysfun(2, T);

    a1b0[0] = PAz * a0b0[0] + WPz * a0b0[1];
    a1b0[1] = PAy * a0b0[0] + WPy * a0b0[1];
    a1b0[2] = PAx * a0b0[0] + WPx * a0b0[1];
    a1b0[3] = PAz * a0b0[1] + WPz * a0b0[2];
    a1b0[4] = PAy * a0b0[1] + WPy * a0b0[2];
    a1b0[5] = PAx * a0b0[1] + WPx * a0b0[2];
    a2b0[0] = PAz * a1b0[0] + WPz * a1b0[3] + 0.5 * 1 * invZetaAB * (a0b0[0] - zetaCD * invZeta * a0b0[1]);
    a2b0[1] = PAy * a1b0[0] + WPy * a1b0[3];
    a2b0[1] = PAz * a1b0[1] + WPz * a1b0[4];
    a2b0[2] = PAy * a1b0[1] + WPy * a1b0[4] + 0.5 * 1 * invZetaAB * (a0b0[0] - zetaCD * invZeta * a0b0[1]);
    a2b0[3] = PAx * a1b0[0] + WPx * a1b0[3];
    a2b0[3] = PAz * a1b0[2] + WPz * a1b0[5];
    a2b0[4] = PAx * a1b0[1] + WPx * a1b0[4];
    a2b0[4] = PAy * a1b0[2] + WPy * a1b0[5];
    a2b0[5] = PAx * a1b0[2] + WPx * a1b0[5] + 0.5 * 1 * invZetaAB * (a0b0[0] - zetaCD * invZeta * a0b0[1]);
} // function (hgp_vrr_2_0_)

} // namespace (nhfInt)

