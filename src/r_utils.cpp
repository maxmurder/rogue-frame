#include "r_utils.h"
#include <iostream>
#include <iomanip>
#include <sstream>
#include <vector>
#include <stdlib.h>

using namespace std;

std::string r_utils::UnicodeToHexString( std::vector<uint16_t> symbols, std::string delimeter )
{
    stringstream ls; 
    int i = 0;
    for ( auto &s : symbols )
    {
        if (i == 0)
        {   
            ls << "0x" << std::uppercase << std::setfill('0') << std::setw(4) << std::hex << s; 
        }else 
        {
            ls << delimeter << "0x" << std::uppercase << std::setfill('0') << std::setw(4) << std::hex << s; 
        }
        i++;
    }
    return ls.str();
}

std::vector<uint16_t> r_utils::HexStringToUnicode( char* data, std::string delimeter )
{
    vector<uint16_t> symbols;
    string str = data;
    string token;
    stringstream stream;
    size_t pos = 0;
    //loop thru string and find delimeters
    while ( ( pos = str.find(delimeter) ) != std::string::npos )
    {
        token = str.substr(0,pos); // get the substring up to delimeter
        symbols.push_back( (uint16_t)strtol( token.c_str(), NULL, 0) ); //convert hex to int and push to vector
        str.erase(0, pos + delimeter.length()); // pop the hex from the string
    }
    symbols.push_back((uint16_t)strtol( str.c_str(), NULL, 0)); //put final value into the list
    return symbols;  
}
