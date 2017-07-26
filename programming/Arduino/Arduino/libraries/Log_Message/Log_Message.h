#ifndef Log_Message_h
#define Log_Message_h

#include <MCP_Message.h>
#include <iterator> 
#include <vector> 

//#msgid:msgtype:devID:loglevel:logtext;
class Log_Message : public MCP_Message
{
  public:
  	Log_Message(const std::vector<char*>&);
  	Log_Message(){};
  	~Log_Message();
    virtual void parse(const std::vector<char*>&);
    char* getMessage();
    void setLogLevel(int);
    void setLogText(char*);
    void setDeviceId(int);
  private:
  	char* logText;
  	int devId;
  	int logLevel;
};

#endif