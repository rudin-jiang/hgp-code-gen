#include "hgp_vrr.hpp"
#include "boysfun.hpp"
#include <vector>
#include <cmath>

namespace nhfInt {

using VecReal = std::vector<double>;

void hgp_vrr_2_1_(
    VecReal &a2b1, 
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
    double a0b1[ 9];
    double a1b0[ 9];
    double a1b1[18];
    double a2b0[12];

    a0b0[0] = preBoysFunCoeff * boysfun(0, T);
    a0b0[1] = preBoysFunCoeff * boysfun(1, T);
    a0b0[2] = preBoysFunCoeff * boysfun(2, T);
    a0b0[3] = preBoysFunCoeff * boysfun(3, T);

    a0b1[ 2] = QCx * a0b0[ 0] + WQx * a0b0[ 1];
    a0b1[ 5] = QCx * a0b0[ 1] + WQx * a0b0[ 2];
    a0b1[ 8] = QCx * a0b0[ 2] + WQx * a0b0[ 3];
    a1b0[ 0] = PAz * a0b0[ 0] + WPz * a0b0[ 1];
    a1b0[ 1] = PAy * a0b0[ 0] + WPy * a0b0[ 1];
    a1b0[ 2] = PAx * a0b0[ 0] + WPx * a0b0[ 1];
    a1b0[ 3] = PAz * a0b0[ 1] + WPz * a0b0[ 2];
    a1b0[ 4] = PAy * a0b0[ 1] + WPy * a0b0[ 2];
    a1b0[ 5] = PAx * a0b0[ 1] + WPx * a0b0[ 2];
    a1b0[ 6] = PAz * a0b0[ 2] + WPz * a0b0[ 3];
    a1b0[ 7] = PAy * a0b0[ 2] + WPy * a0b0[ 3];
    a1b0[ 8] = PAx * a0b0[ 2] + WPx * a0b0[ 3];
    a1b1[ 2] = PAz * a0b1[ 2] + WPz * a0b1[ 5];
    a1b1[ 3] = QCz * a1b0[ 1] + WQz * a1b0[ 4];
    a1b1[ 5] = PAy * a0b1[ 2] + WPy * a0b1[ 5];
    a1b1[11] = PAz * a0b1[ 5] + WPz * a0b1[ 8];
    a1b1[12] = QCz * a1b0[ 4] + WQz * a1b0[ 7];
    a1b1[14] = PAy * a0b1[ 5] + WPy * a0b1[ 8];
    a2b0[ 0] = PAz * a1b0[ 0] + WPz * a1b0[ 3] + 0.5 * 1 * invZetaAB * (a0b0[ 0] - zetaCD * invZeta * a0b0[ 1]);
    a2b0[ 1] = PAy * a1b0[ 0] + WPy * a1b0[ 3];
    a2b0[ 2] = PAy * a1b0[ 1] + WPy * a1b0[ 4] + 0.5 * 1 * invZetaAB * (a0b0[ 0] - zetaCD * invZeta * a0b0[ 1]);
    a2b0[ 3] = PAx * a1b0[ 0] + WPx * a1b0[ 3];
    a2b0[ 4] = PAx * a1b0[ 1] + WPx * a1b0[ 4];
    a2b0[ 5] = PAx * a1b0[ 2] + WPx * a1b0[ 5] + 0.5 * 1 * invZetaAB * (a0b0[ 0] - zetaCD * invZeta * a0b0[ 1]);
    a2b0[ 6] = PAz * a1b0[ 3] + WPz * a1b0[ 6] + 0.5 * 1 * invZetaAB * (a0b0[ 1] - zetaCD * invZeta * a0b0[ 2]);
    a2b0[ 7] = PAy * a1b0[ 3] + WPy * a1b0[ 6];
    a2b0[ 8] = PAy * a1b0[ 4] + WPy * a1b0[ 7] + 0.5 * 1 * invZetaAB * (a0b0[ 1] - zetaCD * invZeta * a0b0[ 2]);
    a2b0[ 9] = PAx * a1b0[ 3] + WPx * a1b0[ 6];
    a2b0[10] = PAx * a1b0[ 4] + WPx * a1b0[ 7];
    a2b0[11] = PAx * a1b0[ 5] + WPx * a1b0[ 8] + 0.5 * 1 * invZetaAB * (a0b0[ 1] - zetaCD * invZeta * a0b0[ 2]);
    a2b1[ 0] = QCz * a2b0[ 0] + WQz * a2b0[ 6] + 0.5 * 2 * invZeta * a1b0[ 3];
    a2b1[ 1] = QCy * a2b0[ 0] + WQy * a2b0[ 6];
    a2b1[ 2] = PAz * a1b1[ 2] + WPz * a1b1[11] + 0.5 * 1 * invZetaAB * (a0b1[ 2] - zetaCD * invZeta * a0b1[ 5]);
    a2b1[ 3] = PAz * a1b1[ 3] + WPz * a1b1[12] + 0.5 * 1 * invZeta * a1b0[ 4];
    a2b1[ 4] = QCy * a2b0[ 1] + WQy * a2b0[ 7] + 0.5 * 1 * invZeta * a1b0[ 3];
    a2b1[ 5] = PAy * a1b1[ 2] + WPy * a1b1[11];
    a2b1[ 6] = QCz * a2b0[ 2] + WQz * a2b0[ 8];
    a2b1[ 7] = QCy * a2b0[ 2] + WQy * a2b0[ 8] + 0.5 * 2 * invZeta * a1b0[ 4];
    a2b1[ 8] = PAy * a1b1[ 5] + WPy * a1b1[14] + 0.5 * 1 * invZetaAB * (a0b1[ 2] - zetaCD * invZeta * a0b1[ 5]);
    a2b1[ 9] = QCz * a2b0[ 3] + WQz * a2b0[ 9] + 0.5 * 1 * invZeta * a1b0[ 5];
    a2b1[10] = QCy * a2b0[ 3] + WQy * a2b0[ 9];
    a2b1[11] = PAx * a1b1[ 2] + WPx * a1b1[11] + 0.5 * 1 * invZeta * a1b0[ 3];
    a2b1[12] = PAx * a1b1[ 3] + WPx * a1b1[12];
    a2b1[13] = QCy * a2b0[ 4] + WQy * a2b0[10] + 0.5 * 1 * invZeta * a1b0[ 5];
    a2b1[14] = PAx * a1b1[ 5] + WPx * a1b1[14] + 0.5 * 1 * invZeta * a1b0[ 4];
    a2b1[15] = QCz * a2b0[ 5] + WQz * a2b0[11];
    a2b1[16] = QCy * a2b0[ 5] + WQy * a2b0[11];
    a2b1[17] = QCx * a2b0[ 5] + WQx * a2b0[11] + 0.5 * 2 * invZeta * a1b0[ 5];
} // function (hgp_vrr_2_1_)

} // namespace (nhfInt)

