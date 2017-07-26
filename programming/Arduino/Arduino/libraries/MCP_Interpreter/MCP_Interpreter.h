#ifndef MCP_Interpreter_h
#define MCP_Interpreter_h
#include <iterator> 
#include <list> 
#include <vector>

class MCP_Interpreter
{
  public:
    char* interprete(char*);
    static MCP_Interpreter* getInstance();
  private:
  	static MCP_Interpreter* instance;
  	MCP_Interpreter(){};
  	char* handleCallMessage(const std::vector<char*>& msg);
};

#endif