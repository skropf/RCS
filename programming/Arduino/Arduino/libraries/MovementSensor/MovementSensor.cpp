#include <Ultrasonic.h>
#include <iterator>
#include <vector>
#include <StringUtility.h>
#include <Log.h>
#include "MovementSensor.h"



bool MovementSensor::checkForMovement()
{
	
	int current =ultrasonic->Ranging(CM);
	/*Serial.print("Standart:  ");
	Serial.println(standart);
	Serial.print("Tolerance:  ");
	Serial.println(tolerance);
	Serial.print("Current:  ");
	Serial.println(current);*/
	//if(current>130) digitalWrite(11,LOW);
	return ((!(standart-tolerance<=current&&standart+tolerance>=current)));
	
}
int MovementSensor::getRawValue()
{
	return ultrasonic->Ranging(CM);
}
void MovementSensor::setIOPins(int pingPin,int dataPin)
{
	this->pingPin = pingPin;
	this->dataPin = dataPin;
	this->ultrasonic = new Ultrasonic(pingPin,dataPin);
}

void MovementSensor::calibrate()
{
	standart=this->ultrasonic->Ranging(CM);
}

std::map<char*,char*> MovementSensor::save()
{
	std::map<char*,char*> map;
	map["id"] = StringUtility::itoa(this->getId());
	map["dataPin"] = StringUtility::itoa(this->dataPin);
	
	map["pingPin"] = StringUtility::itoa(this->pingPin);
	map["tolerance"] = StringUtility::itoa(this->tolerance);
	//char save[51];
	//snprintf(save,50,"#%d%d:%d:%d;",this->getId(),this->pingPin,this->dataPin,this->tolerance);
	//return save;
	return map;
}
IPersistable* MovementSensor::load(std::map<char*,char*,str_cmp> elems)
{
	//std::vector<char*> elems;
	//StringUtility::split(args,"#:;",elems);
	MovementSensor *movementSensor = new MovementSensor();
	Log::serial("pingPin:");
	Log::serial(elems["pingPin"]);
	Log::serial("dataPin:");
	Log::serial(elems["dataPin"]);
	movementSensor->setIOPins(atoi(elems["pingPin"]),atoi(elems["dataPin"]));
	movementSensor->setId(atoi(elems["id"]));
	movementSensor->setTolerance(50);//atoi(elems["tolerance"]));
	return movementSensor;
}
void MovementSensor::setTolerance(int t)
{
	if(t==0)t=50;
	this->tolerance = t;
}
MovementSensor::MovementSensor()
{
	this->setTolerance(10);
	this->calibrate();
}