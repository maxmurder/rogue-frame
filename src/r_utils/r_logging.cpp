#include "r_logging.h"
#include "r_engine/r_time.h"
#include <iostream>

namespace r_logging
{
    Log::Log(LogLevel level)
    {
        ostream << level;
        ostream << " - " << r_time::system_time();
        ostream << " " << level << ": ";
        ostream << std::string( level > DEBUG ? 0 : level - DEBUG, '\t');
    }

    Log::~Log()
    {
        ostream << std::endl;
        std::cerr << ostream.str();
    }
}