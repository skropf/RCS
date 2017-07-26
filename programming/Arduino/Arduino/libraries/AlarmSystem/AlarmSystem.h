#ifndef AlarmSystem_h
#define AlarmSystem_h

#include <Loggable.h>
#include <MovementSensor.h>
#include <SolidStateRelay.h>
#include <iterator> 
#include <list> 
#include <vector>
#include <Log.h>
#include <Connection.h>
#include <MotionSensorPhidget.h>


#define ALARMED 2
#define RUNNING 1
#define BREAK 0

class AlarmSystem : public Device
{
  public:
  	AlarmSystem();
  	SolidStateRelay* getSirene();
  	void setSirene(SolidStateRelay*);
  	MovementSensor* getRangeSensor();
  	void setRangeSensor(MovementSensor*);
  	virtual char* callMethod(String,std::vector<char*>);
  	
    virtual std::map<char*,char*> save();
  	virtual IPersistable* load(std::map<char*,char*,str_cmp>);
  	virtual char* getClassName(){return "AlarmSystem";};
  	
  	char* subscribe(std::vector<char*>);
	char* turnOn(std::vector<char*>);
	char* turnOff(std::vector<char*>);
	char* calibrateSensor(std::vector<char*>);
	char* unsubscribe(std::vector<char*>);
	char* setAlarmState(std::vector<char*>);
	
	virtual std::map<char*,char*> getProperties();
	
	
  	virtual bool doWork();
  	
  private:
  	SolidStateRelay* sirene;
  	MovementSensor* rangeSensor;
  	MotionSensorPhidget* motionSensor;
  	std::vector<Connection> destinations;
  	
  	typedef char* (AlarmSystem::*pt2Member)(std::vector<char*>);
 	pt2Member functionArray[5];
 	String functionNames[5];
  	int state;
  	long time;
};

#endif