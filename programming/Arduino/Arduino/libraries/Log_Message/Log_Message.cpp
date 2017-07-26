#include <SPI.h>
#include <MCP_Message.h>

#include "Log_Message.h"
#include <Log.h>
#include <iterator> 
#include <vector>
#include <StringUtility.h>
#include <MCP_Message.h>
#include <Log.h>
#include <iterator> 
#include <Global_MessageId.h>
#include <list> 
#include <vector>
Log_Message::Log_Message(const std::vector<char*>& elements)
{
	this->parse(elements);
}

//#msgid:msgtype:devID:loglevel:logtext;
void Log_Message::parse(const std::vector<char*>& elems)
{
	MCP_Message::parse(elems);
	this->setLogLevel(atoi(elems[3]));
	this->setDeviceId(atoi(elems[2]));
	this->setLogText(elems[4]);
}
void Log_Message::setLogLevel(int level)
{
	this->logLevel = level;
}
void Log_Message::setLogText(char* logText)
{
	this->logText = logText;
}
void Log_Message::setDeviceId(int devId)
{
	this->devId = devId;
}
//#msgid:msgtype:devID:loglevel:logtext;
char* Log_Message::getMessage()
{
	Log::serial("elements");
	Serial.println(this->devId);
	Serial.println(this->logLevel);
	Log::serial(this->logText);
	char *buffer=(char*)malloc(80);
	snprintf (buffer,79, "#%d:3:%d:%d:%s;",Global_MessageId::getInstance()->getNextId(),this->devId,this->logLevel,this->logText);
	return buffer;
}
Log_Message::~Log_Message()
{
}