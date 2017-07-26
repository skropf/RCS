#ifndef LogDisplay_h
#define LogDisplay_h

#include <SolidStateRelay.h>
#include <iterator> 
#include <list> 
#include <vector>
#include <IPersistable.h>
#include <PrecisionLightSensorPhidget.h>
#include <TemperatureSensorPhidget.h>
#include <MotionSensorPhidget.h>
#include <Log_Message.h>
#include <SimpleDevice.h>
#include <glcd.h>


class LogDisplay : public Device
{
	public:
  	virtual bool doWork();
  	virtual char* callMethod(String methodName,std::vector<char*> params){};
  	
  	virtual std::map<char*,char*> save(){return std::map<char*,char*>();};
  	virtual IPersistable* load(std::map<char*,char*,str_cmp>){return new LogDisplay();};
  	virtual char* getClassName(){ return "LogDisplay";};
  	
  	virtual std::map<char*,char*> getProperties(){return std::map<char*,char*>();};
  	static LogDisplay* getInstance();
  	void addLogMessage(Log_Message*);
  	private:
  	LogDisplay();
  	static LogDisplay *instance;
  	std::list<char*> logMsgList;
  	SimpleDevice* sensorDev;
  	long time;
  	gText textArea; 
};

#endif