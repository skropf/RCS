#ifndef MotionSensorPhidget_h
#define MotionSensorPhidget_h

#include <iterator> 
#include <list> 
#include <ITemperaturSensor.h>
#include <Sensor.h>

class MotionSensorPhidget : public Sensor
{
  public:
  	virtual bool checkForMovement();
  	virtual std::map<char*,char*> save();
  	virtual IPersistable* load(std::map<char*,char*,str_cmp>);
  	virtual char* getClassName(){return "MotionSensorPhidget";};
  	virtual int getRawValue();
  	void setTolerance(int);
  	MotionSensorPhidget();
  	void setPin(int pin);
  	int getPin();
  	void setStandart(int);
 private:
  	int pin;
  	int standart;
  	int tolerance;
};

#endif