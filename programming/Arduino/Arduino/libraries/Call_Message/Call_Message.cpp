#include <SPI.h>
#include <MCP_Message.h>

#include "Call_Message.h"
#include <Log.h>
#include <iterator> 
#include <vector>
#include <StringUtility.h>
#include <MCP_Message.h>
#include <Log.h>
#include <iterator> 
#include <list> 
#include <vector>
Call_Message::Call_Message(const std::vector<char*>& elements)
{
	this->params = std::vector<char*>();
	this->parse(elements);
}
int Call_Message::getDevId()
{
	return this->devId;
}

//#MsgId:MsgType:DeviceID:Methodname:params;
//#5:1:1:join;
void Call_Message::parse(const std::vector<char*>& elems)
{
	MCP_Message::parse(elems);
	
	this->setMethodName(elems[3]);
	/*Log::serial("MethodName:");
	Log::serial(elems[3]);
	Log::serial("DevId:");
	Log::serial(elems[2]);*/
	this->devId = atoi(elems[2]);
	
	int counter=0;
	std::vector<char*>::const_iterator it;
	for ( it=elems.begin() ; it != elems.end(); it++ )
	{
		if(counter>3) params.push_back(const_cast<char *>(*it));
		counter++;
	}
	
	/*int counter = MCP_Message::parse(msg);
	String method = String("");
  	char charArray[255];
  	msg.toCharArray(charArray,255);
  	
	Log::serial(String("Counter = ") + counter);
  	
  	while(charArray[counter] !=':')
  	{
  		method += charArray[counter];
  		counter++;
  	}
  	counter++;
  	this->setMethodName(method);
  	
  	int size = 1;
  	String param = String("");
  	while(charArray[counter] !=';')
  	{
  		while(charArray[counter] !=':' && charArray[counter] !=';')
  		{
  			param += charArray[counter];
  			counter++;
  		}
  		
  		if(charArray[counter]!=';')
  				counter++;
  				
  		this->params.push_back(param);
  		Log::serial("Parameter:" + param);
  		
  		//TODO: mehr als einen Parameter 
  		//this->params[size-1] = param;
  		//realloc(this->params,++size * sizeof(String));
  		param = String("");
  	}
  	
  	return ++counter;*/
}
char* Call_Message::getMethodName()
{
  return this->methodName;
}
void Call_Message::setMethodName(char* name)
{
  this->methodName = name;
}
std::vector<char*> Call_Message::getParams()
{
  return this->params;
}
void Call_Message::setParams(std::vector<char*> parameter)
{
  this->params = parameter;
}
