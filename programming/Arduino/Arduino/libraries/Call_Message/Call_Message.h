#ifndef Call_Message_h
#define Call_Message_h

#include <MCP_Message.h>
#include <iterator> 
#include <vector> 

class Call_Message : public MCP_Message
{
  public:
  	Call_Message(const std::vector<char*>&);
    virtual void parse(const std::vector<char*>&);
    String getMessage();
    void setMethodName(char*);
    void setParams(std::vector<char*>);
    char* getMethodName();
    std::vector<char*> getParams();
    int getDevId();
  private:
  	std::vector<char*> params;
  	char* methodName;
  	int devId;
};

#endif