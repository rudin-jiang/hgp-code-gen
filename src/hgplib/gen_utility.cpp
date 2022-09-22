#include "gen_utility.hpp"

std::size_t count_digit(std::size_t num) {
    if (num == 0) return 1;
    std::size_t n = 0;
    while (num) ++n, num/=10;
    return n;
}

std::string encode_number(std::size_t num) {
    if (num < 10)   return std::to_string(num);
    int n = static_cast<int>(num - 10);
    return std::string(1, 'A' + n);
}

std::string format_number(std::size_t num, std::size_t width) {
    std::size_t numWidth = count_digit(num);
    assert(numWidth <= width);
    return std::string(width - numWidth, ' ')
            + std::to_string(num);
}


std::size_t array_size_single(std::size_t a, std::size_t b) {
    std::size_t nbsA = (a + 1) * (a + 2) / 2;
    std::size_t nbsB = (b + 1) * (b + 2) / 2;
    return nbsA * nbsB;
}

std::size_t array_size_multip(std::size_t a, std::size_t b,
                                             std::size_t mMax) {
    return (mMax + 1) * array_size_single(a, b);
}

std::string array_name(std::size_t a, std::size_t b) {
    return "a" + encode_number(a) + "b" + encode_number(b);
}

std::string array_define_single(std::size_t a, std::size_t b,
                                               std::size_t idxLen) {
    return array_name(a,b) + 
           "[" + format_number(array_size_single(a,b), idxLen) + "]";
}

std::string array_define_multip(std::size_t a, std::size_t b,
                             std::size_t mMax, std::size_t idxLen) {
    return array_name(a,b) + "[" + 
           format_number(array_size_multip(a, b, mMax), idxLen)
           + "]";
}