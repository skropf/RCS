#ifndef SimpleDevice_h
#define SimpleDevice_h

#include <SolidStateRelay.h>
#include <iterator> 
#include <list> 
#include <vector>
#include <IPersistable.h>
#include <PrecisionLightSensorPhidget.h>
#include <TemperatureSensorPhidget.h>
#include <MotionSensorPhidget.h>


class SimpleDevice : public Device
{
	public:
  	char* getLuminosity(std::vector<char*>);
  	char* getLuminosity();
  	char* getTemperature(std::vector<char*>);
  	char* getTemperature();
  	char* getMovementRaw(std::vector<char*>);
  	void setSensor(PrecisionLightSensorPhidget *sensor);
  	PrecisionLightSensorPhidget * getSensor();
  	
  	void setTemperatureSensor(TemperatureSensorPhidget *sensor);
  	TemperatureSensorPhidget * getTemperatureSensor();
  	
  	void setMovementSensor(MotionSensorPhidget *sensor);
  	
  	virtual bool doWork();
  	virtual char* callMethod(String methodName,std::vector<char*> params);
  	
  	virtual std::map<char*,char*> save();
  	virtual IPersistable* load(std::map<char*,char*,str_cmp>);
  	virtual char* getClassName(){ return "SensorDevice";};
  	
  	virtual std::map<char*,char*> getProperties();
  	SimpleDevice();
  	private:
  	char* temp;
  	char* brightness;
  	char* movement;
  	PrecisionLightSensorPhidget* sensor;
  	TemperatureSensorPhidget* tempSensor;
  	MotionSensorPhidget* movementSensor;
};

#endif