#include <StringUtility.h>
#include "TemperatureSensorPhidget.h"

double TemperatureSensorPhidget::getTemperatureInCelsius()
{
	double raw = analogRead(this->pin);
	//Serial.println(fmap(analogRead(this->pin), 0, 1023, 0.0, 5.0));
	//return ((((raw*0.977)/4)*0.2222)-61.1111); //0 - 1024 instead of 0 - 1000
	return (fmap(analogRead(this->pin), 0, 1023, 0.0, 5.0)*200.0*0.2222) - 61.111 -4.2;
}
std::map<char*,char*> TemperatureSensorPhidget::save()
{
	std::map<char*,char*> params;
	params["id"] = StringUtility::itoa(this->getId());
	params["pin"] = StringUtility::itoa(this->pin);
	return params;
}
IPersistable* TemperatureSensorPhidget::load(std::map<char*,char*,str_cmp> elems)
{
	TemperatureSensorPhidget* ph = new TemperatureSensorPhidget();
	ph->setPin(atoi(elems["pin"]));
	ph->setId(atoi(elems["id"]));
	return ph;
}
int TemperatureSensorPhidget::getRawValue()
{
	return analogRead(this->pin);
}
void TemperatureSensorPhidget::setPin(int pin)
{
	this->pin = pin;
	pinMode(this->pin, INPUT); 
}
int TemperatureSensorPhidget::getPin()
{
	return this->pin;
}