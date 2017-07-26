#ifndef TemperatureSensorPhidget_h
#define TemperatureSensorPhidget_h

#include <iterator> 
#include <list> 
#include <vector>
#include <ITemperaturSensor.h>
#include <IPersistable.h>

class TemperatureSensorPhidget : public ITemperaturSensor
{
  public:
    virtual double getTemperatureInCelsius();
  	virtual void refresh(){};
  	virtual std::map<char*,char*> save();
  	virtual IPersistable* load(std::map<char*,char*,str_cmp>);
  	virtual char* getClassName(){return "TemperaturSensorPhidget";};
  	virtual int getRawValue();
  	
  	void setPin(int pin);
  	int getPin();
 private:
  	int pin;
};

#endif