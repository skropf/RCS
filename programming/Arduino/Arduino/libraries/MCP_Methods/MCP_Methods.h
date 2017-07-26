#ifndef MCP_Methods_h
#define MCP_Methods_h


#include <iterator> 
#include <list> 
#include <vector>

class MCP_Methods
{
  public:
    static char* getDevices();
    static char* logging(std::vector<char*> params);
};

#endif