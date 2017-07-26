#ifndef MCP_MessageObserver_h
#define MCP_MessageObserver_h

#include <Connector.h>
#include <MCP_Interpreter.h>


class MCP_MessageObserver
{
  public:
	void subscribeListener();
	void unsubscribeListener();
	void observeEthernetMessages(bool);
	void observeSerialMessages(bool);
	void observeADKMessages(bool);
	void checkForMessages();

	static MCP_MessageObserver* getInstance();
  private:
  	MCP_MessageObserver();
  	static MCP_MessageObserver * instance;
  	bool observeSerial;
  	bool observeEthernet;
  	bool observeADK;
  	MCP_Interpreter *interpreter;
  	Connector *connector;
  	MCP_MessageListener *listener;
};

#endif