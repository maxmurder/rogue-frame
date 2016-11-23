/*
* Simple logging utility script:
* Usage:
* const r_logging::ELogLevel loglevel = r_logging::DEBUG; //Set loglevel threshold.
* R_LOG(r_logging::DEBUG) << "Message to output"; //Call the R_LOG() and construct the message.
* NOTE: You must define a loglevel before calling the R_LOG macro. Superfluous calls to R_LOG will be omitted by the pre-compiler.
*
* Alternatively you may call Log() directly.
* Usage:
* r_logging::Log(r_logging::DEBUG) << "Message to output";
* NOTE: Calling Log directly removes the requirement to define a loglevel. Direct calls to Log() will always be executed.
*/

#ifndef  R_LOGGING_H
#define R_LOGGING_H
#include <string>
#include <sstream>
#include <vector>

namespace  r_logging
{
    enum ELogLevel{ ERROR, WARNING, INFO, DEBUG }; // Enum of possible LogLevels
    
    class IOutputPolicy 
    {
        public:
            virtual void write(const std::string& msg) = 0;
    };

    class Log 
    {
        public:      
        Log(ELogLevel level = ERROR); 
        // << operator to allow atomic concatination ie std::cout
        template<typename T>
        Log & operator<<(T const & value)
        {
            ostream << value;
            return *this;
        }
        ~Log();

        void AddOutput(IOutputPolicy* policy);

        protected:
        std::ostringstream ostream;
        std::vector<IOutputPolicy*> outputPolicies;
    };

    class DefaultPolicy : public IOutputPolicy
    {
        void write(const std::string& msg);
    };
}


    // preprocessor define for logging level threshold.
    #ifndef R_LOG_LEVEL
    #define R_LOG_LEVEL r_logging::ERROR
    #endif // !LOG_LEVEL

    // Macro to allow precompiler to trim unneeded logging.
    // Calls to R_LOG with a level below the configured legLevel will be removed by the pre-compiler.
    #define R_LOG(level) \
    if (level > R_LOG_LEVEL) ; \
    else r_logging::Log(level)

#endif 