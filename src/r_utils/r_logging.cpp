#include "r_logging.h"
#include "r_engine/r_time.h"
#include <iostream>

namespace r_logging
{
    static const char* ELogLevelStrings[] = { "ERROR", "WARNING", "INFO", "DEBUG" }; // human readable strings for ELogLevel values
    //returns human readable name for the ELogLevel values.
    const char* EtoString(ELogLevel enumVal)
    {
        return ELogLevelStrings[enumVal];
    }

    //Constructs the log prefix information
    Log::Log(ELogLevel level)
    {
        ostream << EtoString(level);
        ostream << " - " << r_time::system_time() << ": ";    
    }

    //Passes the output stream to std::cerr
    Log::~Log()
    {
        ostream << std::endl;
        std::cerr << ostream.str();
    }
}