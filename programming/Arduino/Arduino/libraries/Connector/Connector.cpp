#include <SPI.h>

#include <EthernetClient.h>
#include <Ethernet.h>
#include <EthernetServer.h>

#include <Max3421e.h>
#include <Usb.h>
#include <AndroidAccessory.h>

#define SERIAL_RETRIES 100
#define ETHERNET_RETRIES 1000
#define SERIAL 1
#define ETHERNET 2

#include <Log.h>
#include <iterator> 
#include <list> 
#include <vector> 
#include <StringUtility.h>
#include <Connection.h>
#include "Connector.h"
#include <MemoryFree.h>
#include <stdio.h>
#include <string.h>
#include <MCP_MessageListener.h>



// Enter a MAC address and IP address for your controller below.
// The IP address will be dependent on your local network:
byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
byte ip[] = { 192,168,1, 2 };
byte ipdest[] = { 192,168,1, 1 };

// Initialize the Ethernet server library
// with the IP address and port you want to use 
// (port 80 is default for HTTP):
EthernetServer server(13316);


AndroidAccessory acc("Google, Inc.",
		     "DemoKit",
		     "DemoKit Arduino Board",
		     "1.0",
		     "http://www.android.com",
		     "0000000012345678");


Connector* Connector::instance = 0;

Connector* Connector::getInstance()
{
  if(instance == 0) instance =  (Connector*)malloc(sizeof(Connector));
  return instance;
}


void Connector::initSerial()
{ 
  	Serial.begin(115200);
}
void Connector::initEthernetShield()
{
	this->current.ip= (byte*)malloc(sizeof(uint8_t)*4);
	Ethernet.begin(mac, ip);
  	server.begin();  
}
void Connector::initADK()
{
	acc.powerOn();
}
void Connector::checkforADKMessages()
{
	char mcpMessage[50]="";
	if (acc.isConnected()) {
		int len = acc.read(mcpMessage, sizeof(mcpMessage), 1);
		if (len > 0) {
			Log::serial(mcpMessage);
			this->current.type=ADK;
			(listener->*messageCallback)(mcpMessage);
		}
	}
}
void Connector::setMessageCallback(MCP_MessageListener *listener,void (MCP_MessageListener::*pt2func)(char*))
{
	messageCallback = pt2func;
	this->listener = listener;
}
void Connector::checkforEthernetMessages()
{
	
	EthernetClient client = server.available();
	if (!client) return;
	//Serial.println("ethernet not null");
	char mcpMessage[50]="";
	int counter = 0;
	char c=' ';
  	while(c!=';')
  	{
  		if(client.available() > 0)
  		{
  			c = client.read();
  			int len = strlen(mcpMessage);
        	mcpMessage[len] = c;
        	mcpMessage[len+1] = '\0';
  		}
  		else
  			counter++;
  		if(counter == ETHERNET_RETRIES)	
  		{
  			return;
  		}
  	}
  	//if(!this->isValidMessage(mcpMessage)) return;
  	current.type=ETHERNET;
  	Log::serial(mcpMessage);
	free(this->current.ip);
  	this->current.ip= (byte*)malloc(sizeof(uint8_t)*4);
	client.getRemoteIP(this->current.ip);
  	client.stop();
  	(listener->*messageCallback)(mcpMessage);
}



void Connector::checkforSerialMessages()
{
  char mcpMessage[40]="";
  int counter = 0;
  char c=' ';
  while(c!=';')
  {
  	if(Serial.available() > 0)
  	{
  		delay(5);
  		c = (char)Serial.read();
  		int len = strlen(mcpMessage);
        mcpMessage[len] = c;
        mcpMessage[len+1] = '\0';
  	}
  	else
  		counter++;
  	if(counter == SERIAL_RETRIES)	
  	{
  		return;
  	}
  }
  //if(!this->isValidMessage(mcpMessage)) return;
  this->current.type=COM;
  Log::serial(mcpMessage);
  (listener->*messageCallback)(mcpMessage);
}
void Connector::sendResult(char* erg)
{
	this->sendResult(erg,current);
}
void Connector::getConnection()
{
	switch(current.type)
	{
  		case ETHERNET:
				//uint8_t* ip = client->getIp();
				//free(this->current.ip);
				this->current.ip= (byte*)malloc(sizeof(uint8_t)*4);
				
				//memcpy(this->current.ip,ip,sizeof(uint8_t)*4);
  			break;
  	}
}

Connection Connector::getLastConnection()
{
	return current;
}

void Connector::sendResult(char* erg,Connection con)
{
  	if(con.type==COM)
  	{
  		Serial.println(erg);
  		Serial.flush();
  	}
  	else
  	{
  		if(con.type==ADK)
  		{
  			Log::serial(erg);
  			strcat(erg,"\n");
  			acc.write(erg,strlen(erg));
  			//Serial.println(erg);
  			//Serial.flush();
  		}
  		else
  		{
  			//client->stop();
  			//delete(client);
  			EthernetClient client;
  			client.connect(con.ip,13316);
  			Log::serial(erg);
  			if(client)
  			{
  					delay(20);
  					client.println(erg);
  					client.flush();
  					client.stop();
  			}
	  	}
  	}
}

/*byte* Connector::convertToByteArray(String ip)
{
	Serial.print(ip);
  	byte *array = (byte *) malloc(4*sizeof(byte));
  	
  	char splitChar = '.';
  	String current = "";
  	int counter = 0;
  	
  	for (int i = 0; i < ip.length(); i++) {
		if(ip.charAt(i) == splitChar)
		{			
			char charBuf;
			//current.toCharArray(charBuf, 4);
  			int part = current.charAt(0);//(int)charBuf;
  			array[counter] = (byte)part;
  			counter++;
			current = String("");
		}
		else
		{
			current += String(ip.charAt(i));
		}
	}
	array[4] = current.charAt(0);
  	return array;
}*/
/*
<?mcp version="1.0"?>
 <methodCall>
   <methodName>getTemperature</methodName>
 </methodCall>
*/
//very basic! validation check
bool Connector::isValidMessage(String msg)
{
	return true;
	/*return msg.startsWith("<?mcp")&&msg.indexOf("<methodCall>")!=-1
	&& msg.indexOf("<methodName>")!=-1 && msg.indexOf("</methodCall>")!=-1
	&& msg.indexOf("</methodName>")!=-1;*/
}