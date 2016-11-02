#ifndef  R_LOGGING_H
#define R_LOGGING_H
#include <string>
#include <sstream>

namespace  r_logging
{
    enum LogLevel{ ERROR, WARNING, INFO, DEBUG };

    static void OutputPolicy(const std::string& msg);

    template <typename OutputPolicy>
    class Log 
    {
        public:
            static LogLevel& ReportLevel();
            std::ostringstream& Get(LogLevel level = INFO);
            Log();
            virtual ~Log();
        protected:
            std::ostringstream ostream;
        private:
            Log(const Log&);
            Log& operator = (const Log&);
            LogLevel messageLevel;
    };

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
}

#endif 