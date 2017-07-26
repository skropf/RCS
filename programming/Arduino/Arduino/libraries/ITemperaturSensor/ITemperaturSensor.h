#ifndef ITemperaturSensor_h
#define ITemperaturSensor_h


#include <Sensor.h>

class ITemperaturSensor : public Sensor
{
	public:
  	virtual double getTemperatureInCelsius()=0;
  	virtual void refresh(){};
  	
  	virtual std::map<char*,char*> save()=0;
  	virtual IPersistable* load(std::map<char*,char*,str_cmp>)=0;
  	virtual char* getClassName()=0;
  	virtual int getRawValue()=0;
};

#endif