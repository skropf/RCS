#include <SimpleDevice.h>
#include <IPersistable.h>
#include <AlarmSystem.h>
#include "UnifiedFactory.h"
#include <PowerOutlet.h>
#include <Heater.h>
#include <TemperatureSensorPhidget.h>
#include <Light.h>
#include <str_cmp.h>
#include <MotionSensorPhidget.h>
#include <Rolladen.h>
#include <MemoryFree.h>
#include <Fan.h>
#include <MovementSensor.h>

template<typename T, int size>
int GetArrayLength(T(&)[size]){return size;}

IPersistable* persistableClassArray[9] = 
{
	new SimpleDevice(),
	new SolidStateRelay(),
	new PowerOutlet(),
	new Heater(),
	new TemperatureSensorPhidget(),
	new PrecisionLightSensorPhidget(), 
	new Light(),
	new Rolladen(), 
	new Fan()};

IPersistable* UnifiedFactory::generateClassFromName(char* className,std::map<char*,char*,str_cmp> params)
{
	//Log::serial("UNIFIEDFACTORY");
	//Log::serial("CLASSNAME = ");
	//Log::serial(className);
	Serial.print("UNIFIEDFACTORY freeMemory()=");
  	Serial.println(freeMemory());
	IPersistable* obj=NULL;
  for(int i = 0;i<GetArrayLength(persistableClassArray);i++)
	{
		if(strncmp(persistableClassArray[i]->getClassName(),className,strlen(persistableClassArray[i]->getClassName()))==0)
		{
  			obj = (IPersistable *)persistableClassArray[i]->load(params);
			break;
		}
	}
	return obj;
}
UnifiedFactory* UnifiedFactory::instance = 0;

UnifiedFactory* UnifiedFactory::getInstance()
{
  if(instance==0) instance = new UnifiedFactory();
  return instance;
}