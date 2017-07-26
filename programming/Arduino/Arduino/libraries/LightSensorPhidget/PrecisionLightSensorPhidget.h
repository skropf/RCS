#ifndef PrecisionLightSensorPhidget_h
#define PrecisionLightSensorPhidget_h
#include <ILightSensor.h>

class PrecisionLightSensorPhidget : public LightSensor
{
  public:
    virtual int getLuminosity();
    virtual int getRawValue();
  	virtual std::map<char*,char*> save();
  	virtual IPersistable* load(std::map<char*,char*,str_cmp>);
  	virtual char* getClassName(){return "PrecisionLightSensorPhidget";};
  	void setPin(int pin);
  	int getPin();
  	private:
  	int pin;
  	
};

#endif