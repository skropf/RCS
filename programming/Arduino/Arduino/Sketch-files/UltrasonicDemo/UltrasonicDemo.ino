#include "Ultrasonic.h"
#include <SPI.h>
#include <Connector.h>
#include <SdFat.h>
#include <Client.h>
#include <Ethernet.h>
#include <Server.h>
#include <Udp.h>
#include <Max3421e.h>
#include <Usb.h>
#include <AndroidAccessory.h>


#include <IPersistable.h>
#include <SimpleDevice.h>
#include <Global_MessageId.h>
#include <MCP_Message.h>
#include <Connector.h>
#include <MCP_Interpreter.h>
#include <MCP_Methods.h>
#include <Call_Message.h>
#include <Result_Message.h>

#include <Log.h>
#include <Loggable.h>
#include <IO.h>
#include <IOActor.h>
#include <IOSensor.h>
#include <Led.h>
#include <Device.h>
#include <DeviceManager.h>
#include <iterator> 
#include <list> 
#include <map>
#include <SolidStateRelay.h>
#include <new.cpp>
#include <IOSensor.h>
#include <Sensor.h>
#include <Actor.h>
#include <IOActor.h>
#include <avr/io.h>
#include <UnifiedFactory.h>
#include <StringUtility.h>
#include <AlarmSystem.h>
#include <MovementSensor.h>
#include <Connection.h>
#include <ConnectionType.h>
#include <MemoryFree.h>


int toleranz=5;
int standart;
Connector* connector;
Connection* connections;
int connectionCounter=0;
int isRunning = 0;
Ultrasonic ultrasonic(48,49);
SolidStateRelay solidStateRelay(8);

void callback(String msg)
{
   int counter=0;
   String methodName="";
   for(int i=0;i<msg.length();i++)
   {
       if(msg.charAt(i) == ':')
      {
         counter++;
      } 
      if(counter==3)
      {
        if(msg.charAt(i)!=':'&&msg.charAt(i)!=';')
          methodName+=msg.charAt(i);
      }
   }
   Serial.println(methodName);
   Serial.flush();
   
   if(methodName==String("subscribe"))
   {
       connections[connectionCounter] = connector->getLastConnection();
       connectionCounter++;
       Serial.println("AlarmSystem subscribed"); 
   }
    if(methodName==String("unsubscribe"))
   {
       free(connections);
       connections = (Connection*) malloc(5*sizeof(Connection));
       connectionCounter=0;
       Serial.println("AlarmSystem unsubscribed"); 
   }
   if(methodName==String("turnOn"))
   {
       isRunning=1;
       Serial.println("Start");
   }
    if(methodName==String("turnOff"))
   {
       isRunning=0;
       Serial.println("Stop");
   }
    if(methodName==String("getDevices"))
   {
       Serial.println("getDevices");
       connector->sendResult(String("#5:0:1:ALARMSYSTEM:Alarm System Arduino;"));
   }
   if(methodName==String("calibrate"))
   {
     Serial.println("calibrate");
     standart = ultrasonic.Ranging(CM);
   }
   connector->sendResult("#1:2:-1:OK;");
}
void setup() {
    connector = Connector::getInstance();
    Serial.begin(115200);
    standart = ultrasonic.Ranging(CM);
    connector->setMessageCallback(&callback);
    connector->initEthernetShield();
    Log::serial("setup done");
    connections =(Connection*) malloc(5*sizeof(Connection));
}
void loop()
{
  connector->checkforSerialMessages();
  connector->checkforEthernetMessages();
  if(isRunning==0)return;
  int current =ultrasonic.Ranging(CM);
  delay(500);
  
  Serial.print("freeMemory()=");
  Serial.println(freeMemory());
  
  Log::serial(current);
  if(!(standart-toleranz<current&&standart+toleranz>current))
  {
      for(int i=0;i<connectionCounter;i++)
      {
          Log::serial("ausgeloest");
          connector->sendResult("#5:2:1:AlarmSystem called",connections[i]);
          isRunning=0;
      }
  }
}




