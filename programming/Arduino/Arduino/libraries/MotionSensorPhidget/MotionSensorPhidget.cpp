#include <StringUtility.h>
#include "MotionSensorPhidget.h"


MotionSensorPhidget::MotionSensorPhidget()
{
	this->tolerance=30;
	this->standart=500;
}
bool MotionSensorPhidget::checkForMovement()
{
	int current = ((double)analogRead(this->pin))*0.977;
	return (!(standart-tolerance<current&&standart+tolerance>current));
}
std::map<char*,char*> MotionSensorPhidget::save()
{
	std::map<char*,char*> map;
	map["pin"] = StringUtility::itoa(this->pin);
	map["standart"] = StringUtility::itoa(this->standart);
	map["tolerance"] = StringUtility::itoa(this->tolerance);
	map["id"] = StringUtility::itoa(this->id);
	return map;
}
IPersistable* MotionSensorPhidget::load(std::map<char*,char*,str_cmp> map)
{
	MotionSensorPhidget *sensor = new MotionSensorPhidget();
	sensor->setPin(atoi(map["pin"]));
	sensor->setId(atoi(map["id"]));
	sensor->setTolerance(atoi(map["tolerance"]));
	sensor->setStandart(atoi(map["standart"]));
	return sensor;
}
void MotionSensorPhidget::setStandart(int standart)
{
	this->standart = standart;
}
int MotionSensorPhidget::getRawValue()
{
	return analogRead(this->pin);
}
void MotionSensorPhidget::setPin(int pin)
{
	this->pin = pin;
	pinMode(this->pin, INPUT);  
}
int MotionSensorPhidget::getPin()
{
	return this->pin;
}
void MotionSensorPhidget::setTolerance(int tolerance)
{
	this->tolerance = tolerance;
}
