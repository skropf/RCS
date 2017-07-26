#include "SimpleDevice.h"
#include <IPersistable.h>
#include <DeviceManager.h>
#include <PrecisionLightSensorPhidget.h>
#include <WorkQueue.h>
#include <TemperatureSensorPhidget.h>
#include <StringUtility.h>
#include <MotionSensorPhidget.h>

typedef char* (SimpleDevice::*pt2Member)(std::vector<char*>);

pt2Member functionArray[3] = {&SimpleDevice::getLuminosity,&SimpleDevice::getTemperature,&SimpleDevice::getMovementRaw};
String functionNames[3] =  	 {String("getBrightness"),String("getTemperature"),String("getMovement")};



char* SimpleDevice::getLuminosity(std::vector<char*> params)
{
	int lum = this->sensor->getLuminosity();
	//Serial.println(lum);
	//WorkQueue::getInstance()->add(this);
	if(brightness!=NULL)
		free(brightness);
	brightness = (char*) malloc(30);
	sprintf(brightness,"brightness=%d",lum);
	return brightness;
}
char* SimpleDevice::getLuminosity()
{
	int lum = this->sensor->getLuminosity();
	//Serial.println(lum);
	//WorkQueue::getInstance()->add(this);
	if(brightness!=NULL)
		free(brightness);
	brightness = (char*) malloc(30);
	sprintf(brightness,"%d",lum);
	return brightness;
}

SimpleDevice::SimpleDevice()
{
	this->temp=NULL;
	this->brightness=NULL;
	this->movement=NULL;
}
PrecisionLightSensorPhidget * SimpleDevice::getSensor()
{
	return this->sensor;
}

void SimpleDevice::setSensor(PrecisionLightSensorPhidget *sensor)
{
	this->sensor = sensor;
}
char* SimpleDevice::callMethod(String methodName,std::vector<char*> params)
{
	for(int i = 0;i<GetArrayLength(functionNames);i++)
	{
		if(functionNames[i] == methodName)
		{
			return (this->*functionArray[i])(params);
		}
	}
	return "Method not found";
}
std::map<char*,char*> SimpleDevice::save()
{
	std::map<char*,char*> map;
	
	map["name"]=this->getName();
	map["id"]=StringUtility::itoa(this->getId());
	map["lightSensorId"] = StringUtility::itoa(this->sensor->getId());
	map["tempSensorId"] = StringUtility::itoa(this->tempSensor->getId());
	//char save[51];
	//snprintf(save,50,"#%d;",this->getId(),this->sensor->getId());
	//return save;
	return map;
}
IPersistable* SimpleDevice::load(std::map<char*,char*,str_cmp> map)
{
	SimpleDevice* dev = new SimpleDevice();
	int len = strlen(map["name"]);
	char* buffer = (char*) malloc(len+2);
	strncpy(buffer,map["name"],len+1);
	dev->setName(buffer);
	dev->setId(StringUtility::atoi(map["id"]));
	dev->setSensor((PrecisionLightSensorPhidget*)DeviceManager::getInstance()->getSensorById(StringUtility::atoi(map["lightSensorId"])));
	dev->setTemperatureSensor((TemperatureSensorPhidget*)DeviceManager::getInstance()->getSensorById(StringUtility::atoi(map["tempSensorId"])));
	dev->setMovementSensor((MotionSensorPhidget*)DeviceManager::getInstance()->getSensorById(StringUtility::atoi(map["movementSensorId"])));
	return dev;
	//std::vector<char*> elems;
	//StringUtility::split(args,"#:;",elems);  502800
	//SimpleDevice *sd = new SimpleDevice();
	//sd->setSolidStateRelay((SolidStateRelay*)DeviceManager::getInstance()->getActorById(atoi(elems[1])));
	//sd->setId(atoi(elems[0]));
}
bool SimpleDevice::doWork()
{
	//int lum = this->sensor->getLuminosity();
	//Serial.println(lum);
	return false;
}
char* SimpleDevice::getTemperature(std::vector<char*> params)
{
	float t = (float)this->tempSensor->getTemperatureInCelsius();
	Serial.println(t);
	
	int d1 = t;            // Get the integer part (678).
	float f2 = t - d1;     // Get fractional part (678.0123 - 678 = 0.0123).
	int d2 = trunc(f2 * 100);   // Turn into integer (123).
	
	//WorkQueue::getInstance()->add(this);
	//char* t = (char*)malloc(20);
	if(temp!=NULL)
		free(temp);
	temp = (char*) malloc(30);
	sprintf(temp,"temperature=%d.%d", d1, d2);

	//snprintf(t,20,"%8.2f",temp);
	return temp;
}
char* SimpleDevice::getTemperature(void)
{
	double t = this->tempSensor->getTemperatureInCelsius();
	//Serial.println(temp);
	//WorkQueue::getInstance()->add(this);
	//char* t = (char*)malloc(20);
	int d1 = t;            // Get the integer part (678).
	float f2 = t - d1;     // Get fractional part (678.0123 - 678 = 0.0123).
	int d2 = trunc(f2 * 100);   // Turn into integer (123).

	if(temp!=NULL)
		free(temp);
	temp = (char*) malloc(30);
	sprintf(temp,"%d.%d", d1, d2);

	//snprintf(t,20,"%8.2f",temp);
	return temp;
}
char* SimpleDevice::getMovementRaw(std::vector<char*> params)
{
	int mov = this->movementSensor->getRawValue();
	Serial.println(mov);
	//WorkQueue::getInstance()->add(this);
	char* movement = (char*)malloc(20);
	sprintf(movement,"%d",mov);
	return movement;
}

TemperatureSensorPhidget* SimpleDevice::getTemperatureSensor()
{
	return this->tempSensor;
}

void SimpleDevice::setTemperatureSensor(TemperatureSensorPhidget *sensor)
{
	this->tempSensor = sensor;
}
void SimpleDevice::setMovementSensor(MotionSensorPhidget *sensor)
{
	this->movementSensor = sensor;
}
std::map<char*,char*> SimpleDevice::getProperties()
{
	std::map<char*,char*> props;
	if(temp!=NULL)
		free(temp);
	temp = (char*)malloc(20);
	sprintf(temp,"%s",this->getTemperature());
	props["temperature"] = temp;
	
	if(brightness!=NULL)
		free(brightness);
	brightness = (char*)malloc(20);
	sprintf(brightness,"%d",this->sensor->getLuminosity());
	props["brightness"] = brightness;
	
	return props;
	/*if(movement!=NULL)
		free(movement);
	movement = (char*)malloc(20);
	sprintf(movement,"%d",this->movementSensor->getRawValue());
	props["movement"] = movement;
	return props;*/
}