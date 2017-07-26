#include <MCP_Interpreter.h>
#include <Connector.h>
#include "MCP_MessageListener.h"
#include <Log.h>	
	
void MCP_MessageListener::OnMCPMessageRecieved(char* msg)
{
	Log::serial("onMCPMessageRecieved");
	char* result = MCP_Interpreter::getInstance()->interprete(msg); 
  	Connector::getInstance()->sendResult(result); 
  	free(result);
}