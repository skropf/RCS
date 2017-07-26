#include "MCP_Methods.h"
#include <SPI.h>
#include <Log.h>
#include <DeviceManager.h>
#include <SolidStateRelay.h>
#include <Led.h>
#include <SystemLogPreferences.h>

char* MCP_Methods::getDevices()
{
	DeviceManager::getInstance()->sendDevices();
	return "true";
}
char* MCP_Methods::logging(std::vector<char*> params)
{
	if(atoi(params[0])==0)
	{
		std::list<Connection>::iterator it;
		 for (it=SystemLogPreferences::getInstance()->getDestinations()->begin(); it!=SystemLogPreferences::getInstance()->getDestinations()->end(); it++)
		 {
		 	if(it->type==Connector::getInstance()->getLastConnection().type && it->type!=ETHERNET)
		 	{
		 		SystemLogPreferences::getInstance()->getDestinations()->erase(it);
		 	}
		 	else
		 	{
		 		if(it->type==Connector::getInstance()->getLastConnection().type && it->type==ETHERNET)
		 		{
		 			if(it->ip[0] == Connector::getInstance()->getLastConnection().ip[0]&&
		 			it->ip[1] == Connector::getInstance()->getLastConnection().ip[1] &&
		 			it->ip[2] == Connector::getInstance()->getLastConnection().ip[2] &&
		 			it->ip[3] == Connector::getInstance()->getLastConnection().ip[3])
		 			{
		 				SystemLogPreferences::getInstance()->getDestinations()->erase(it);
		 				return "disabled";
		 			}
		 		}
		 	}
		 }
	}
	else
	{
		SystemLogPreferences::getInstance()->getDestinations()->push_back(Connector::getInstance()->getLastConnection());
		return "enabled";
	}
	return "failed";
}
/*void MCP_Methods::turnOnLed(int deviceId)
{
	Log::serial(String("turn on led"));
	DeviceManager *deviceManager = DeviceManager::getInstance();
	Led *led = (Led*) deviceManager->getDeviceById(deviceId);
	led->turnOn();
}
void MCP_Methods::turnOnSSR(int deviceId)
{
	Log::serial(String("turning on SSR"));
	DeviceManager *deviceManager = DeviceManager::getInstance();
	SolidStateRelay *ssr = (SolidStateRelay*) deviceManager->getDeviceById(deviceId);
	ssr->turnOn();
}*/