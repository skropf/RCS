#ifndef Result_Message_h
#define Result_Message_h

#include <MCP_Message.h>

class Result_Message : public MCP_Message
{
  public:
  	Result_Message(char*);
  	Result_Message();
    char* getMessage();
    void setReturnValue(char*);
    char* getReturnValue();
    void setDeviceId(int);
    int getDeviceId();
    virtual void parse(String);
  private:
  	char* returnValue;
  	int deviceId;
};

#endif