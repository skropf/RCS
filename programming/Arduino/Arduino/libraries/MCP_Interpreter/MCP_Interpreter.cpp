
#include <SPI.h>

#include <MCP_Methods.h>

#include <MCP_Message.h>
#include <Result_Message.h>
#include <Call_Message.h>
#include <Log.h>
#include <Device.h>
#include <DeviceManager.h>
#include <iterator> 
#include <list> 
#include <vector>
#include <StringUtility.h>
#include <MemoryFree.h>
#include <memory>
#include <Global_MessageId.h>

#include "MCP_Interpreter.h"

MCP_Interpreter* MCP_Interpreter::instance = 0;

MCP_Interpreter* MCP_Interpreter::getInstance()
{
  if(instance == 0) instance =  new MCP_Interpreter();
  return instance;
}


char* MCP_Interpreter::interprete(char* mcpMessage)
{
	std::vector<char*> elems;
	StringUtility::split(mcpMessage,":#;()",elems);
	
	Log::serial("Elems:");
	Log::serial(elems[0]);
	Log::serial(elems[1]);
	Log::serial(elems[2]);
	Log::serial(elems[3]);
	
	Global_MessageId::getInstance()->setId(atoi(elems[0]));
	
	char t = elems[1][0];
	MCP_Message::MessageType type = (MCP_Message::MessageType) (t - '0');
	
	Log::serial(elems[1]);
	if(type == MCP_Message::Call)
	{
		return this->handleCallMessage(elems);
	}
	return "MessageType not right";
}
char* MCP_Interpreter::handleCallMessage(const std::vector<char*> &elems)
{
	Call_Message callmsg(elems);
	
    Serial.println(callmsg.getMethodName());
  
  	Serial.print(freeMemory());
  	Serial.println("   Memory free");
	if(callmsg.getDevId()>0) // Device ID gegeben
	{
		Device *dev = DeviceManager::getInstance()->getDeviceById(callmsg.getDevId());
		if(dev==NULL)return "Device not configured";
		
		
		char* erg = NULL;
		erg = dev->callMethod(callmsg.getMethodName(),callmsg.getParams());
		
  		
		//if(erg==-1) return -1;
		if(erg==NULL|strcmp(erg,"")==0)erg = "Method call failed";
		std::auto_ptr<Result_Message> result(new Result_Message());
		result->setReturnValue(erg);
		result->setDeviceId(dev->getId());
		
		return result->getMessage();
	}
	else
	{
		char* erg =NULL;
		if(strcmp(callmsg.getMethodName(),"getDevices")==0)
			erg= MCP_Methods::getDevices();
		if(strcmp(callmsg.getMethodName(),"logging")==0)
		{
			erg= MCP_Methods::logging(callmsg.getParams());
		}
		if(erg==NULL) erg = "Method not found";
		std::auto_ptr<Result_Message> result(new Result_Message());
		result->setReturnValue(erg);
		result->setDeviceId(0);
		
		return result->getMessage();
	}
}

/*String MCP_Interpreter::getMethodName(String xmlMessage)
{
	String xmlString = String(xmlMessage);
	int begin = xmlString.indexOf("<methodName>");
	//length of <methodname>
  	begin += 12;
  	int end = xmlString.indexOf("</methodName>");
  	return xmlString.substring(begin,end);
	//return "getTemperature";
};*/