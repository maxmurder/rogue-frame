#include "r_logging.h"
#include "r_engine/r_time.h"
namespace r_logging
{
    #define Log(level) \
    if (level > Log::ReportingLevel()) ; \
    else Log().Get(level)
    std::ostringstream& Log::Get(LogLevel level)
    {
        ostream << "- " << r_time::system_time();
        ostream << " " << level << ": ";
        ostream << std::string( level > DEBUG ? 0 : level - DEBUG, '\t');
        messageLevel = level;
        return ostream;
    }
    Log::~Log()
    {
        //OutputPolicy::Output(ostream.str());
        ostream << std::endl;
        fprintf(stderr, "%s", ostream.str().c_str());
        fflush(stderr);
    }

    LogLevel& Log::ReportLevel()
    {
        return messageLevel;
    }
/*
    inline FILE*& Output_File::Stream()
    {
        static FILE* stream = stderr;
        return stream;
    }

    inline void Output_File::Output(const std::string& msg)
    {
        FILE* stream = Stream();
        if (!stream)
            return;
        fprintf(stream, "%s", msg.c_str());
        fflush(stream);
    }
    */
}