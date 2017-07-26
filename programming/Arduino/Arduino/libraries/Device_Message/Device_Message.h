#ifndef Call_Message_h
#define Call_Message_h

#include <MCP_Message.h>
#include <iterator> 
#include <vector> 
#include <map>

class Device_Message : public MCP_Message
{
  public:
    //#Msgid:Msgtype:DevId:DeviceType(string):DeviceName:currentStatus;
    //currentStatus example = currentStatus=64,Brightness=324;
    //AlarmSystem currentStatus = on,sensorList=a,b,c,activeSensorList=a,b
  	Device_Message(const std::vector<char*>&);
  	Device_Message();
  	~Device_Message();
    virtual void parse(const std::vector<char*>&);
    char* getMessage();
    
    
    void setDevId(int devId) { this->devId = devId; } 
	int getDevId() { return this->devId; }
	void setMsgId(int msgId) { this->msgId = msgId; } 
	int getMsgId() { return this->msgId; }
	void setDeviceType(char* deviceType) { this->deviceType = deviceType; } 
	char* getDeviceType() { return this->deviceType; }
	void setDeviceName(char* deviceName) { this->deviceName = deviceName; } 
	char* getDeviceName() { return this->deviceName; }
	void setCurrentProperties(std::map<char*,char*>* currentProperties) { this->currentProperties = currentProperties; } 
	std::map<char*,char*>* getCurrentProperties() { return this->currentProperties; }

  private:
  	int devId;
  	int msgId;
  	char* deviceType;
  	char* deviceName;
  	std::map<char*,char*> *currentProperties;
};

#endif