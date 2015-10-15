#ifndef R_UTILS_H
#define R_UTILS_H
#include <vector>
#include <string>
#include <array>

class r_utils
{
    public:
        static std::string UnicodeToHexString(std::vector<uint16_t> symbols, std::string delimeter = ",");
        static std::vector<uint16_t> HexStringToUnicode( char* data, std::string delimeter = ",");
};

#endif
