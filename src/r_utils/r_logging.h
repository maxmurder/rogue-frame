#ifndef  R_LOGGING_H
#define R_LOGGING_H
#include <string>
#include <sstream>

namespace  r_logging
{
    enum LogLevel{ ERROR, WARNING, INFO, DEBUG };

   // static void OutputPolicy(const std::string& msg);
    static LogLevel messageLevel;
    class Log 
    {
        private:
        Log(const Log&);
        Log& operator = (const Log&);
        //#define Log(level) \
        if (level > Log::ReportingLevel()) ; \
        else Log().Get(level)

        public:
        static LogLevel& ReportLevel();            
        Log();
        ~Log();
        std::ostringstream& Get(LogLevel level = INFO);

        protected:
            std::ostringstream ostream;
    };
/*
    class Output_File 
    {
        public:
        static FILE*& Stream();
        static void Output(const std::string& msg);
    };

    typedef Log<Output_File> FileLog;
    #define FILE_LOG(level) \
    if (level < FileLog::ReportLevel() || !Output_File::Stream()) ; \
    else FileLog().Get(messageLevel);
*/
}

#endif 