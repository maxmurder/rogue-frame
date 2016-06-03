#ifndef R_UTILS_H
#define R_UTILS_H
#include <vector>
#include <string>
#include <array>

namespace r_utils
{
    std::string UnicodeToHexString(std::vector<uint16_t> symbols, std::string delimeter = ",");
    std::vector<uint16_t> HexStringToUnicode( char* data, std::string delimeter = ",");
};

#endif
