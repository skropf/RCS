#ifndef MCP_Message_h
#define MCP_Message_h

#include <iterator> 
#include <list> 
#include <vector>

class MCP_Message
{
  public:
  	enum MessageType
	{
		Device = 0,
  		Call = 1,
  		Result = 2,
  		Log = 3
	};
	MCP_Message();
	MCP_Message(const std::vector<char*>&);
    virtual void parse(const std::vector<char*>&);
    MCP_Message::MessageType getMessageType();
    char* getMessage();
    int getId();
    void setType(MCP_Message::MessageType);
  protected:
   char* message;
   int id;
   MCP_Message::MessageType type;
};

#endif