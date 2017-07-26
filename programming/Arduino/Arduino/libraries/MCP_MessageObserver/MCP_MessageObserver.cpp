#include "MCP_MessageObserver.h"
#include <Connector.h>
#include <Log.h>

MCP_MessageObserver* MCP_MessageObserver::instance = 0;

MCP_MessageObserver::MCP_MessageObserver()
{
	Log::serial("aufruf");
	this->connector = Connector::getInstance();
	this->observeSerial=false;
	this->observeEthernet=false;
	connector->initSerial();
  	connector->initEthernetShield();
  	connector->initADK();
  	Log::serial("--------------");
  	interpreter = MCP_Interpreter::getInstance();
  	listener = new MCP_MessageListener();
  	Log::serial("---------------");
}
void MCP_MessageObserver::observeADKMessages(bool b)
{
	this->observeADK = b;
}
void MCP_MessageObserver::subscribeListener()
{
	this->connector->setMessageCallback(listener,&MCP_MessageListener::OnMCPMessageRecieved);
	Log::serial("subscribing");
}
void MCP_MessageObserver::unsubscribeListener()
{
	this->connector->setMessageCallback(NULL,NULL);
}
void MCP_MessageObserver::observeEthernetMessages(bool b)
{
	this->observeEthernet = b;
}
void MCP_MessageObserver::observeSerialMessages(bool b)
{
	this->observeSerial = b;
}
void MCP_MessageObserver::checkForMessages()
{
	if(this->observeSerial)
	{
		connector->checkforSerialMessages();
	}
	if(this->observeEthernet)
	{
		connector->checkforEthernetMessages();
	}
	if(this->observeADK)
	{
		connector->checkforADKMessages();
	}
}
MCP_MessageObserver* MCP_MessageObserver::getInstance()
{
  if(instance == 0) instance =  new MCP_MessageObserver();
  return instance;
}


