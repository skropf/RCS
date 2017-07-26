#include <SPI.h>
#include "Result_Message.h"
#include <Global_MessageId.h>
#include <Log.h>
#include <stdio.h>

Result_Message::Result_Message(char* msg)
{
  this->returnValue = msg;
  //this->parse(msg);
}
Result_Message::Result_Message()
{
	this->type = Result;
}

void Result_Message::setReturnValue(char* param)
{
	this->returnValue = param;
}
void Result_Message::parse(String arg)
{
}
//#MsgId:MsgType:Type:Result
char* Result_Message::getMessage()
{
	char *buffer=(char*)malloc(80);
	snprintf (buffer,79, "#%d:2:%d:%s;",Global_MessageId::getInstance()->getNextId(),this->deviceId,this->returnValue);
	return buffer;
	/*String msg = String("#");
	Log::serial(msg);
	msg += Global_MessageId::getInstance()->getNextId();
	Log::serial(msg);
	msg += ":";
	Log::serial(msg);
	msg += this->type;
	Log::serial(msg);
	msg += ":";
	Log::serial(msg);
	msg += this->returnValue;
	Log::serial(msg);
	msg += "\n";
	Log::serial(msg);
	return msg;*/
}
void Result_Message::setDeviceId(int id)
{
	this->deviceId = id;
}
int Result_Message::getDeviceId()
{
	return this->deviceId;
}