#include <IPersistable.h>
#include <StringUtility.h>
#include "PrecisionLightSensorPhidget.h"

int PrecisionLightSensorPhidget::getLuminosity()
{
	return (fmap(analogRead(this->pin), 0, 1023, 0.0, 5.0)*200.0);
}
int PrecisionLightSensorPhidget::getRawValue()
{
	return analogRead(this->pin);
}
std::map<char*,char*> PrecisionLightSensorPhidget::save()
{
	std::map<char*,char*> map;
	
	map["id"] = StringUtility::itoa(this->getId());
	map["pin"] = StringUtility::itoa(this->pin);
	return map;
}
IPersistable* PrecisionLightSensorPhidget::load(std::map<char*,char*,str_cmp> map)
{
	PrecisionLightSensorPhidget* p = new PrecisionLightSensorPhidget();
	p->setPin(atoi(map["pin"]));
	p->setId(atoi(map["id"]));
	return p;
}
int PrecisionLightSensorPhidget::getPin()
{
	return this->pin;
}
void PrecisionLightSensorPhidget::setPin(int pin)
{
	this->pin = pin;
	pinMode(this->pin, INPUT);
}
