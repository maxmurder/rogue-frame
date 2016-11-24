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
    Log::Log(ELogLevel level, std::vector<IOutputPolicy*> policyList)
    {
        if(policyList.size() == 0)
        {
            auto pol = new DefaultPolicy();
            AddOutput(pol);
        }else{
            outputPolicies.swap(policyList);
        }
        ostream << EtoString(level);
        ostream << " - " << r_time::system_time() << ": ";    
    }

    //Passes the output stream to std::cerr
    Log::~Log()
    {
        ostream << std::endl;
        for(auto out : outputPolicies)
        {
            out->write(ostream.str());
        }
    }

    void Log::AddOutput(IOutputPolicy* policy)
    {
        outputPolicies.emplace_back(policy);
    }

    void DefaultPolicy::write(const std::string& msg)
    {
        std::cerr << msg;
    }
}