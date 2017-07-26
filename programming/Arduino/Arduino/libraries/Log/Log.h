#ifndef Log_h
#define Log_h

#define LOG_VERBOSE 0 
#define LOG_DEBUG 1
#define LOG_ERROR 2

#include <Arduino.h>
#include <Log_Message.h>

class Log
{
  public:
    static void verbose(Log_Message *);
    static void error(Log_Message *);
    static void debug(Log_Message *);
    static void serial(String);
    static void serial(char*);
  	static void log(Log_Message*,int);
  	static std::vector<Log_Message*> logMessages;
};

#endif