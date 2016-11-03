#ifndef  R_LOGGING_H
#define R_LOGGING_H
#include <string>
#include <sstream>

namespace  r_logging
{
    enum LogLevel{ ERROR, WARNING, INFO, DEBUG };

    class Log 
    {
        public:
        static LogLevel& ReportLevel();            
        Log(LogLevel level = ERROR);
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

    extern LogLevel loglevel;

//    #define LOG(level) \
    if (level > loglevel) ;\
    else log(level)
}

#endif 