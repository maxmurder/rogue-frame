/*
* Simple logging utility script:
* Usage:
* const r_logging::ELogLevel loglevel = r_logging::DEBUG; //Set loglevel threshold
* R_LOG(r_logging::DEBUG) << "Message to output"; //Call the R_LOG() macro
*
* Alternatively you may call Log() directly
*/

#ifndef  R_LOGGING_H
#define R_LOGGING_H
#include <string>
#include <sstream>
#include <vector>

namespace  r_logging
{
    enum ELogLevel{ ERROR, WARNING, INFO, DEBUG };

    class Log 
    {
        public:      
        Log(ELogLevel level = ERROR); 
        // set << operator to allow atomic concatination ie std::cout
        template<typename T>
        Log & operator<<(T const & value)
        {
            ostream << value;
            return *this;
        }
        ~Log();

        protected:
        std::ostringstream ostream;
    };
}

    // Macro to allow precompiler to trim unneeded logging.
    // Calls to R_LOG with a level below the configured legLevel will be removed by the pre-compiler.
    // User must define a loglevel before calling the R_LOG macro
    extern r_logging::ELogLevel loglevel;
    #define R_LOG(level) \
    if (level > loglevel) ; \
    else r_logging::Log(level)

#endif 