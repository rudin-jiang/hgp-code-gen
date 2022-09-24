#include "hgp_vrr.hpp"
#include "boysfun.hpp"
#include <vector>
#include <cmath>

namespace nhfInt {

using VecReal = std::vector<double>;

void hgp_vrr_3_1_(
    VecReal &a3b1, 
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
    double a0b1[12];
    double a1b0[12];
    double a1b1[27];
    double a2b0[18];
    double a2b1[36];
    double a3b0[20];

    a0b0[0] = preBoysFunCoeff * boysfun(0, T);
    a0b0[1] = preBoysFunCoeff * boysfun(1, T);
    a0b0[2] = preBoysFunCoeff * boysfun(2, T);
    a0b0[3] = preBoysFunCoeff * boysfun(3, T);
    a0b0[4] = preBoysFunCoeff * boysfun(4, T);

    a0b1[ 0] = QCz * a0b0[ 0] + WQz * a0b0[ 1];
    a0b1[ 1] = QCy * a0b0[ 0] + WQy * a0b0[ 1];
    a0b1[ 2] = QCx * a0b0[ 0] + WQx * a0b0[ 1];
    a0b1[ 3] = QCz * a0b0[ 1] + WQz * a0b0[ 2];
    a0b1[ 4] = QCy * a0b0[ 1] + WQy * a0b0[ 2];
    a0b1[ 5] = QCx * a0b0[ 1] + WQx * a0b0[ 2];
    a0b1[ 6] = QCz * a0b0[ 2] + WQz * a0b0[ 3];
    a0b1[ 7] = QCy * a0b0[ 2] + WQy * a0b0[ 3];
    a0b1[ 8] = QCx * a0b0[ 2] + WQx * a0b0[ 3];
    a0b1[ 9] = QCz * a0b0[ 3] + WQz * a0b0[ 4];
    a0b1[11] = QCx * a0b0[ 3] + WQx * a0b0[ 4];
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
    a1b1[ 1] = PAz * a0b1[ 1] + WPz * a0b1[ 4];
    a1b1[ 2] = PAz * a0b1[ 2] + WPz * a0b1[ 5];
    a1b1[ 3] = PAy * a0b1[ 0] + WPy * a0b1[ 3];
    a1b1[ 5] = PAy * a0b1[ 2] + WPy * a0b1[ 5];
    a1b1[10] = PAz * a0b1[ 4] + WPz * a0b1[ 7];
    a1b1[11] = PAz * a0b1[ 5] + WPz * a0b1[ 8];
    a1b1[12] = PAy * a0b1[ 3] + WPy * a0b1[ 6];
    a1b1[14] = PAy * a0b1[ 5] + WPy * a0b1[ 8];
    a1b1[16] = PAx * a0b1[ 4] + WPx * a0b1[ 7];
    a1b1[19] = QCy * a1b0[ 6] + WQy * a1b0[ 9];
    a1b1[20] = PAz * a0b1[ 8] + WPz * a0b1[11];
    a1b1[21] = PAy * a0b1[ 6] + WPy * a0b1[ 9];
    a1b1[23] = PAy * a0b1[ 8] + WPy * a0b1[11];
    a1b1[25] = QCy * a1b0[ 8] + WQy * a1b0[11];
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
    a2b0[12] = PAz * a1b0[ 6] + WPz * a1b0[ 9] + 0.5 * 1 * invZetaAB * (a0b0[ 2] - zetaCD * invZeta * a0b0[ 3]);
    a2b0[14] = PAy * a1b0[ 7] + WPy * a1b0[10] + 0.5 * 1 * invZetaAB * (a0b0[ 2] - zetaCD * invZeta * a0b0[ 3]);
    a2b0[15] = PAx * a1b0[ 6] + WPx * a1b0[ 9];
    a2b0[16] = PAx * a1b0[ 7] + WPx * a1b0[10];
    a2b0[17] = PAx * a1b0[ 8] + WPx * a1b0[11] + 0.5 * 1 * invZetaAB * (a0b0[ 2] - zetaCD * invZeta * a0b0[ 3]);
    a2b1[ 1] = PAz * a1b1[ 1] + WPz * a1b1[10] + 0.5 * 1 * invZetaAB * (a0b1[ 1] - zetaCD * invZeta * a0b1[ 4]);
    a2b1[ 2] = PAz * a1b1[ 2] + WPz * a1b1[11] + 0.5 * 1 * invZetaAB * (a0b1[ 2] - zetaCD * invZeta * a0b1[ 5]);
    a2b1[ 5] = PAy * a1b1[ 2] + WPy * a1b1[11];
    a2b1[ 6] = PAy * a1b1[ 3] + WPy * a1b1[12] + 0.5 * 1 * invZetaAB * (a0b1[ 0] - zetaCD * invZeta * a0b1[ 3]);
    a2b1[ 7] = QCy * a2b0[ 2] + WQy * a2b0[ 8] + 0.5 * 2 * invZeta * a1b0[ 4];
    a2b1[ 8] = PAy * a1b1[ 5] + WPy * a1b1[14] + 0.5 * 1 * invZetaAB * (a0b1[ 2] - zetaCD * invZeta * a0b1[ 5]);
    a2b1[10] = PAx * a1b1[ 1] + WPx * a1b1[10];
    a2b1[16] = QCy * a2b0[ 5] + WQy * a2b0[11];
    a2b1[17] = QCx * a2b0[ 5] + WQx * a2b0[11] + 0.5 * 2 * invZeta * a1b0[ 5];
    a2b1[19] = PAz * a1b1[10] + WPz * a1b1[19] + 0.5 * 1 * invZetaAB * (a0b1[ 4] - zetaCD * invZeta * a0b1[ 7]);
    a2b1[20] = PAz * a1b1[11] + WPz * a1b1[20] + 0.5 * 1 * invZetaAB * (a0b1[ 5] - zetaCD * invZeta * a0b1[ 8]);
    a2b1[23] = PAy * a1b1[11] + WPy * a1b1[20];
    a2b1[24] = PAy * a1b1[12] + WPy * a1b1[21] + 0.5 * 1 * invZetaAB * (a0b1[ 3] - zetaCD * invZeta * a0b1[ 6]);
    a2b1[25] = QCy * a2b0[ 8] + WQy * a2b0[14] + 0.5 * 2 * invZeta * a1b0[ 7];
    a2b1[26] = PAy * a1b1[14] + WPy * a1b1[23] + 0.5 * 1 * invZetaAB * (a0b1[ 5] - zetaCD * invZeta * a0b1[ 8]);
    a2b1[28] = PAx * a1b1[10] + WPx * a1b1[19];
    a2b1[34] = PAx * a1b1[16] + WPx * a1b1[25] + 0.5 * 1 * invZetaAB * (a0b1[ 4] - zetaCD * invZeta * a0b1[ 7]);
    a2b1[35] = QCx * a2b0[11] + WQx * a2b0[17] + 0.5 * 2 * invZeta * a1b0[ 8];
    a3b0[ 0] = PAz * a2b0[ 0] + WPz * a2b0[ 6] + 0.5 * 2 * invZetaAB * (a1b0[ 0] - zetaCD * invZeta * a1b0[ 3]);
    a3b0[ 1] = PAy * a2b0[ 0] + WPy * a2b0[ 6];
    a3b0[ 3] = PAy * a2b0[ 2] + WPy * a2b0[ 8] + 0.5 * 2 * invZetaAB * (a1b0[ 1] - zetaCD * invZeta * a1b0[ 4]);
    a3b0[ 4] = PAx * a2b0[ 0] + WPx * a2b0[ 6];
    a3b0[ 5] = PAx * a2b0[ 1] + WPx * a2b0[ 7];
    a3b0[ 6] = PAx * a2b0[ 2] + WPx * a2b0[ 8];
    a3b0[ 7] = PAx * a2b0[ 3] + WPx * a2b0[ 9] + 0.5 * 1 * invZetaAB * (a1b0[ 0] - zetaCD * invZeta * a1b0[ 3]);
    a3b0[ 8] = PAx * a2b0[ 4] + WPx * a2b0[10] + 0.5 * 1 * invZetaAB * (a1b0[ 1] - zetaCD * invZeta * a1b0[ 4]);
    a3b0[ 9] = PAx * a2b0[ 5] + WPx * a2b0[11] + 0.5 * 2 * invZetaAB * (a1b0[ 2] - zetaCD * invZeta * a1b0[ 5]);
    a3b0[10] = PAz * a2b0[ 6] + WPz * a2b0[12] + 0.5 * 2 * invZetaAB * (a1b0[ 3] - zetaCD * invZeta * a1b0[ 6]);
    a3b0[11] = PAy * a2b0[ 6] + WPy * a2b0[12];
    a3b0[13] = PAy * a2b0[ 8] + WPy * a2b0[14] + 0.5 * 2 * invZetaAB * (a1b0[ 4] - zetaCD * invZeta * a1b0[ 7]);
    a3b0[14] = PAx * a2b0[ 6] + WPx * a2b0[12];
    a3b0[15] = PAy * a2b0[ 9] + WPy * a2b0[15];
    a3b0[16] = PAx * a2b0[ 8] + WPx * a2b0[14];
    a3b0[17] = PAx * a2b0[ 9] + WPx * a2b0[15] + 0.5 * 1 * invZetaAB * (a1b0[ 3] - zetaCD * invZeta * a1b0[ 6]);
    a3b0[18] = PAx * a2b0[10] + WPx * a2b0[16] + 0.5 * 1 * invZetaAB * (a1b0[ 4] - zetaCD * invZeta * a1b0[ 7]);
    a3b0[19] = PAx * a2b0[11] + WPx * a2b0[17] + 0.5 * 2 * invZetaAB * (a1b0[ 5] - zetaCD * invZeta * a1b0[ 8]);
    a3b1[ 0] = QCz * a3b0[ 0] + WQz * a3b0[10] + 0.5 * 3 * invZeta * a2b0[ 6];
    a3b1[ 1] = PAz * a2b1[ 1] + WPz * a2b1[19] + 0.5 * 2 * invZetaAB * (a1b1[ 1] - zetaCD * invZeta * a1b1[10]);
    a3b1[ 2] = PAz * a2b1[ 2] + WPz * a2b1[20] + 0.5 * 2 * invZetaAB * (a1b1[ 2] - zetaCD * invZeta * a1b1[11]);
    a3b1[ 3] = QCz * a3b0[ 1] + WQz * a3b0[11] + 0.5 * 2 * invZeta * a2b0[ 7];
    a3b1[ 4] = PAy * a2b1[ 1] + WPy * a2b1[19] + 0.5 * 1 * invZeta * a2b0[ 6];
    a3b1[ 5] = PAy * a2b1[ 2] + WPy * a2b1[20];
    a3b1[ 6] = PAz * a2b1[ 6] + WPz * a2b1[24] + 0.5 * 1 * invZeta * a2b0[ 8];
    a3b1[ 7] = PAz * a2b1[ 7] + WPz * a2b1[25];
    a3b1[ 8] = PAy * a2b1[ 5] + WPy * a2b1[23] + 0.5 * 1 * invZetaAB * (a1b1[ 2] - zetaCD * invZeta * a1b1[11]);
    a3b1[ 9] = PAy * a2b1[ 6] + WPy * a2b1[24] + 0.5 * 2 * invZetaAB * (a1b1[ 3] - zetaCD * invZeta * a1b1[12]);
    a3b1[10] = QCy * a3b0[ 3] + WQy * a3b0[13] + 0.5 * 3 * invZeta * a2b0[ 8];
    a3b1[11] = PAy * a2b1[ 8] + WPy * a2b1[26] + 0.5 * 2 * invZetaAB * (a1b1[ 5] - zetaCD * invZeta * a1b1[14]);
    a3b1[12] = QCz * a3b0[ 4] + WQz * a3b0[14] + 0.5 * 2 * invZeta * a2b0[ 9];
    a3b1[13] = PAx * a2b1[ 1] + WPx * a2b1[19];
    a3b1[14] = PAx * a2b1[ 2] + WPx * a2b1[20] + 0.5 * 1 * invZeta * a2b0[ 6];
    a3b1[15] = QCz * a3b0[ 5] + WQz * a3b0[15] + 0.5 * 1 * invZeta * a2b0[10];
    a3b1[16] = PAy * a2b1[10] + WPy * a2b1[28] + 0.5 * 1 * invZeta * a2b0[ 9];
    a3b1[17] = PAx * a2b1[ 5] + WPx * a2b1[23] + 0.5 * 1 * invZeta * a2b0[ 7];
    a3b1[18] = PAx * a2b1[ 6] + WPx * a2b1[24];
    a3b1[19] = PAx * a2b1[ 7] + WPx * a2b1[25];
    a3b1[20] = PAx * a2b1[ 8] + WPx * a2b1[26] + 0.5 * 1 * invZeta * a2b0[ 8];
    a3b1[21] = QCz * a3b0[ 7] + WQz * a3b0[17] + 0.5 * 1 * invZeta * a2b0[11];
    a3b1[22] = PAx * a2b1[10] + WPx * a2b1[28] + 0.5 * 1 * invZetaAB * (a1b1[ 1] - zetaCD * invZeta * a1b1[10]);
    a3b1[23] = PAz * a2b1[17] + WPz * a2b1[35];
    a3b1[24] = QCz * a3b0[ 8] + WQz * a3b0[18];
    a3b1[25] = PAy * a2b1[16] + WPy * a2b1[34] + 0.5 * 1 * invZeta * a2b0[11];
    a3b1[26] = PAy * a2b1[17] + WPy * a2b1[35];
    a3b1[27] = QCz * a3b0[ 9] + WQz * a3b0[19];
    a3b1[28] = QCy * a3b0[ 9] + WQy * a3b0[19];
    a3b1[29] = QCx * a3b0[ 9] + WQx * a3b0[19] + 0.5 * 3 * invZeta * a2b0[11];
} // function (hgp_vrr_3_1_)

} // namespace (nhfInt)

