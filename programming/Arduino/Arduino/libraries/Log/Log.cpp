#include <SPI.h>
#include <SystemLogPreferences.h>
#include <SdFat.h>
#include <Log_Message.h>
#include <Connector.h>
#include <Connection.h>
#include <iterator> 
#include <list> 
#include <LogDisplay.h>
#include "Log.h"

#define LOG_FILENAME "log.mcp"

void Log::verbose(Log_Message * msg)
{
	Log::log(msg,LOG_VERBOSE);
}
void Log::debug(Log_Message * msg)
{
	Log::log(msg,LOG_DEBUG);
}
void Log::error(Log_Message * msg)
{
	Log::log(msg,LOG_ERROR);
}
void Log::log(Log_Message* msg,int level)
{
	msg->setLogLevel(level);
	if(SystemLogPreferences::getInstance()->getLevel()>=level)
	{
		if(SystemLogPreferences::getInstance()->logToSd)
		{
			SdFat card;
			SdFile file;
			if (!card.init(SPI_HALF_SPEED, 4)) Log::serial("card.init failed!");
			if (!file.open(LOG_FILENAME, O_RDWR | O_CREAT | O_APPEND)) return;
			char* msgString = msg->getMessage();
			file.println(msgString);
			free(msgString);
			file.close();
		}
		std::list<Connection>::iterator it;
		 for (it=SystemLogPreferences::getInstance()->getDestinations()->begin(); it!=SystemLogPreferences::getInstance()->getDestinations()->end(); it++)
		 {
		 	Log::serial("item in list");
		 	char* msgString = msg->getMessage();
		 	Log::serial(msgString);
			Connector::getInstance()->sendResult(msgString,*it);
			free(msgString);
		 }
		 Log::serial("after");
		 
		 LogDisplay::getInstance()->addLogMessage(msg);
	}
}
void Log::serial(String arg)
{
  	char charBuf[20];
    arg.toCharArray(charBuf, 20);
	Serial.println(charBuf);
	Serial.flush();
}
void Log::serial(char* arg)
{
	Serial.println(arg);
	Serial.flush();
}