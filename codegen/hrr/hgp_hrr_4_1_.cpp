#include "hgp_hrr.hpp"
#include <vector>

namespace nhfInt {

using VecReal = std::vector<double>;

VecReal hgp_hrr_4_1_(const VecReal &hrrInp, double x, double y, double z) { 
    const double *a4b0 = hrrInp.data() +  0;
    const double *a5b0 = hrrInp.data() + 15;

    // intermediate arrays

    // resulted VecReal
    VecReal a4b1(45);

    a4b1[ 0] = a5b0[ 0] + z * a4b0[ 0];    // [(004)(001)] = [(005)(000)] + ABz * [(004)(000)]
    a4b1[ 1] = a5b0[ 1] + y * a4b0[ 0];    // [(004)(010)] = [(014)(000)] + ABy * [(004)(000)]
    a4b1[ 2] = a5b0[ 6] + x * a4b0[ 0];    // [(004)(100)] = [(104)(000)] + ABx * [(004)(000)]
    a4b1[ 3] = a5b0[ 1] + z * a4b0[ 1];    // [(013)(001)] = [(014)(000)] + ABz * [(013)(000)]
    a4b1[ 4] = a5b0[ 2] + y * a4b0[ 1];    // [(013)(010)] = [(023)(000)] + ABy * [(013)(000)]
    a4b1[ 5] = a5b0[ 7] + x * a4b0[ 1];    // [(013)(100)] = [(113)(000)] + ABx * [(013)(000)]
    a4b1[ 6] = a5b0[ 2] + z * a4b0[ 2];    // [(022)(001)] = [(023)(000)] + ABz * [(022)(000)]
    a4b1[ 7] = a5b0[ 3] + y * a4b0[ 2];    // [(022)(010)] = [(032)(000)] + ABy * [(022)(000)]
    a4b1[ 8] = a5b0[ 8] + x * a4b0[ 2];    // [(022)(100)] = [(122)(000)] + ABx * [(022)(000)]
    a4b1[ 9] = a5b0[ 3] + z * a4b0[ 3];    // [(031)(001)] = [(032)(000)] + ABz * [(031)(000)]
    a4b1[10] = a5b0[ 4] + y * a4b0[ 3];    // [(031)(010)] = [(041)(000)] + ABy * [(031)(000)]
    a4b1[11] = a5b0[ 9] + x * a4b0[ 3];    // [(031)(100)] = [(131)(000)] + ABx * [(031)(000)]
    a4b1[12] = a5b0[ 4] + z * a4b0[ 4];    // [(040)(001)] = [(041)(000)] + ABz * [(040)(000)]
    a4b1[13] = a5b0[ 5] + y * a4b0[ 4];    // [(040)(010)] = [(050)(000)] + ABy * [(040)(000)]
    a4b1[14] = a5b0[10] + x * a4b0[ 4];    // [(040)(100)] = [(140)(000)] + ABx * [(040)(000)]
    a4b1[15] = a5b0[ 6] + z * a4b0[ 5];    // [(103)(001)] = [(104)(000)] + ABz * [(103)(000)]
    a4b1[16] = a5b0[ 7] + y * a4b0[ 5];    // [(103)(010)] = [(113)(000)] + ABy * [(103)(000)]
    a4b1[17] = a5b0[11] + x * a4b0[ 5];    // [(103)(100)] = [(203)(000)] + ABx * [(103)(000)]
    a4b1[18] = a5b0[ 7] + z * a4b0[ 6];    // [(112)(001)] = [(113)(000)] + ABz * [(112)(000)]
    a4b1[19] = a5b0[ 8] + y * a4b0[ 6];    // [(112)(010)] = [(122)(000)] + ABy * [(112)(000)]
    a4b1[20] = a5b0[12] + x * a4b0[ 6];    // [(112)(100)] = [(212)(000)] + ABx * [(112)(000)]
    a4b1[21] = a5b0[ 8] + z * a4b0[ 7];    // [(121)(001)] = [(122)(000)] + ABz * [(121)(000)]
    a4b1[22] = a5b0[ 9] + y * a4b0[ 7];    // [(121)(010)] = [(131)(000)] + ABy * [(121)(000)]
    a4b1[23] = a5b0[13] + x * a4b0[ 7];    // [(121)(100)] = [(221)(000)] + ABx * [(121)(000)]
    a4b1[24] = a5b0[ 9] + z * a4b0[ 8];    // [(130)(001)] = [(131)(000)] + ABz * [(130)(000)]
    a4b1[25] = a5b0[10] + y * a4b0[ 8];    // [(130)(010)] = [(140)(000)] + ABy * [(130)(000)]
    a4b1[26] = a5b0[14] + x * a4b0[ 8];    // [(130)(100)] = [(230)(000)] + ABx * [(130)(000)]
    a4b1[27] = a5b0[11] + z * a4b0[ 9];    // [(202)(001)] = [(203)(000)] + ABz * [(202)(000)]
    a4b1[28] = a5b0[12] + y * a4b0[ 9];    // [(202)(010)] = [(212)(000)] + ABy * [(202)(000)]
    a4b1[29] = a5b0[15] + x * a4b0[ 9];    // [(202)(100)] = [(302)(000)] + ABx * [(202)(000)]
    a4b1[30] = a5b0[12] + z * a4b0[10];    // [(211)(001)] = [(212)(000)] + ABz * [(211)(000)]
    a4b1[31] = a5b0[13] + y * a4b0[10];    // [(211)(010)] = [(221)(000)] + ABy * [(211)(000)]
    a4b1[32] = a5b0[16] + x * a4b0[10];    // [(211)(100)] = [(311)(000)] + ABx * [(211)(000)]
    a4b1[33] = a5b0[13] + z * a4b0[11];    // [(220)(001)] = [(221)(000)] + ABz * [(220)(000)]
    a4b1[34] = a5b0[14] + y * a4b0[11];    // [(220)(010)] = [(230)(000)] + ABy * [(220)(000)]
    a4b1[35] = a5b0[17] + x * a4b0[11];    // [(220)(100)] = [(320)(000)] + ABx * [(220)(000)]
    a4b1[36] = a5b0[15] + z * a4b0[12];    // [(301)(001)] = [(302)(000)] + ABz * [(301)(000)]
    a4b1[37] = a5b0[16] + y * a4b0[12];    // [(301)(010)] = [(311)(000)] + ABy * [(301)(000)]
    a4b1[38] = a5b0[18] + x * a4b0[12];    // [(301)(100)] = [(401)(000)] + ABx * [(301)(000)]
    a4b1[39] = a5b0[16] + z * a4b0[13];    // [(310)(001)] = [(311)(000)] + ABz * [(310)(000)]
    a4b1[40] = a5b0[17] + y * a4b0[13];    // [(310)(010)] = [(320)(000)] + ABy * [(310)(000)]
    a4b1[41] = a5b0[19] + x * a4b0[13];    // [(310)(100)] = [(410)(000)] + ABx * [(310)(000)]
    a4b1[42] = a5b0[18] + z * a4b0[14];    // [(400)(001)] = [(401)(000)] + ABz * [(400)(000)]
    a4b1[43] = a5b0[19] + y * a4b0[14];    // [(400)(010)] = [(410)(000)] + ABy * [(400)(000)]
    a4b1[44] = a5b0[20] + x * a4b0[14];    // [(400)(100)] = [(500)(000)] + ABx * [(400)(000)]

    return a4b1;

}  // function (hgp_hrr_4_1_)

}  // namespace (nhfInt)

