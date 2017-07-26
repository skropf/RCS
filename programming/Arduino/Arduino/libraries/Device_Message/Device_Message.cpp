#include <SPI.h>
#include <MCP_Message.h>

#include "Device_Message.h"
#include <Log.h>
#include <iterator> 
#include <vector>
#include <StringUtility.h>
#include <MCP_Message.h>
#include <Log.h>
#include <iterator> 
#include <list> 
#include <vector>



Device_Message::Device_Message(const std::vector<char*>& args)
{
	this->parse(args);
}
Device_Message::Device_Message()
{
}
void Device_Message::parse(const std::vector<char*>& args)
{
	//#Msgid:Msgtype:DevId:DeviceType(string):DeviceName:currentStatus;
	this->msgId = atoi(args[0]);
	this->devId = atoi(args[2]);
	this->deviceType = args[3];
	this->deviceName = args[4];
	//this->currentStatus = args[5];
}
char* Device_Message::getMessage()
{
	char buffer[200];
	sprintf(buffer,"#%d:0:%d:%s:%s:",this->msgId,this->devId,this->deviceType,this->deviceName);
	
	std::map<char*, char*>::iterator it;
	for ( it=currentProperties->begin(); it != currentProperties->end(); it++ )
    {
    	if(it != currentProperties->begin()) strcat(buffer,"|");
    	strcat(buffer,it->first);
    	strcat(buffer,"=");
    	strcat(buffer,it->second);
    }
	strcat(buffer,";");
	return buffer;
}
Device_Message::~Device_Message()
{
	/*std::map<char*, char*>::iterator it;
	for ( it=currentProperties.begin(); it != currentProperties.end(); it++ )
    {
    	currentProperties.erase(it);
    }*/
}
