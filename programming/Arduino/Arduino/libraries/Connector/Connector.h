#ifndef Connector_h
#define Connector_h

#include <Connection.h>
#include <ConnectionType.h>
#include <MCP_MessageListener.h>

class Connector
{
  public:
  	static Connector* getInstance();
    void setMessageCallback(MCP_MessageListener*,void (MCP_MessageListener::*pt2func)(char*));
    void checkforEthernetMessages();
    void checkforSerialMessages();
    void checkforADKMessages();
    void sendResult(String);
    void sendResult(String,Connection);
    void sendResult(char*);
    void sendResult(char*,Connection);
    void initSerial();
    void initADK();
    void initEthernetShield();
    Connection getLastConnection();
  private:
  	static Connector * instance;
  	byte* convertToByteArray(String);
  	void (MCP_MessageListener::*messageCallback)(char*);
    MCP_MessageListener *listener;
  	bool isValidMessage(String);
	Connector(){};
	void getConnection();
	Connection current;
};

#endif