#ifndef LightSensor_h
#define LightSensor_h


#include <Sensor.h>

class LightSensor : public Sensor
{
  public:
    virtual int getLuminosity()=0;
    
    virtual int getRawValue()=0;
  
  	virtual std::map<char*,char*> save()=0;
  	virtual IPersistable* load(std::map<char*,char*,str_cmp>)=0;
  	virtual char* getClassName()=0;
};

#endif