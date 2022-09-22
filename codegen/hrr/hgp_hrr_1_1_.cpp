#include "hgp_hrr.hpp"
#include <vector>

namespace nhfInt {

using VecReal = std::vector<double>;

VecReal hgp_hrr_1_1_(const VecReal &hrrInp, double x, double y, double z) { 
    const double *a1b0 = hrrInp.data() + 0;
    const double *a2b0 = hrrInp.data() + 3;

    // intermediate arrays

    // resulted VecReal
    VecReal a1b1(9);

    a1b1[0] = a2b0[0] + z * a1b0[0];    // [(001)(001)] = [(002)(000)] + ABz * [(001)(000)]
    a1b1[1] = a2b0[1] + y * a1b0[0];    // [(001)(010)] = [(011)(000)] + ABy * [(001)(000)]
    a1b1[2] = a2b0[3] + x * a1b0[0];    // [(001)(100)] = [(101)(000)] + ABx * [(001)(000)]
    a1b1[3] = a2b0[1] + z * a1b0[1];    // [(010)(001)] = [(011)(000)] + ABz * [(010)(000)]
    a1b1[4] = a2b0[2] + y * a1b0[1];    // [(010)(010)] = [(020)(000)] + ABy * [(010)(000)]
    a1b1[5] = a2b0[4] + x * a1b0[1];    // [(010)(100)] = [(110)(000)] + ABx * [(010)(000)]
    a1b1[6] = a2b0[3] + z * a1b0[2];    // [(100)(001)] = [(101)(000)] + ABz * [(100)(000)]
    a1b1[7] = a2b0[4] + y * a1b0[2];    // [(100)(010)] = [(110)(000)] + ABy * [(100)(000)]
    a1b1[8] = a2b0[5] + x * a1b0[2];    // [(100)(100)] = [(200)(000)] + ABx * [(100)(000)]

    return a1b1;

}  // function (hgp_hrr_1_1_)

}  // namespace (nhfInt)

