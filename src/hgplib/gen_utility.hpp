#pragma once

#include <string>
#include <cstddef>
#include <cassert>

/* 
 *   this set of function is used in 
 *   generating hgp hrr vrr code.
*/

// count digits of a number
std::size_t count_digit(std::size_t num);

// 0~9 -> 0~9   10 -> A   11 -> B   12 -> C ...
std::string encode_number(std::size_t num);

// output number with fixed width
std::string format_number(std::size_t num, std::size_t width);


// array size
std::size_t array_size_single(std::size_t a, std::size_t b);
std::size_t array_size_multip(std::size_t a, std::size_t b,
                                             std::size_t mMax);

// array name 
std::string array_name(std::size_t a, std::size_t b);

// array define
std::string array_define_single(std::size_t a, std::size_t b,
                                               std::size_t idxLen);
std::string array_define_multip(std::size_t a, std::size_t b,
                             std::size_t mMax, std::size_t idxLen);