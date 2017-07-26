#include <SPI.h>
#include <Wire.h>
#include "C_ControlTemperatureSensor.h"

IPersistable* C_ControlTemperatureSensor::load(std::map<char*,char*>)
{
	return NULL;
}
std::map<char*,char*> C_ControlTemperatureSensor::save()
{
	return std::map<char*,char*>();
}
int C_ControlTemperatureSensor::getRawValue()
{
	return this->rawValue;
}
double C_ControlTemperatureSensor::getTemperatureInCelsius()
{
	return this->lastTemperature;
}
void C_ControlTemperatureSensor::initTransmission(int address)
{
	/*Wire.beginTransmission(address);
  	// send configuration 
  	Wire.send(0xAC);
  	Wire.send(B00001111); // 12 bit resolution, pol, oneshot
  	Wire.endTransmission();*/
}
void C_ControlTemperatureSensor::refresh()
{
	/*if(!converting)
	{
	// begin convert
  		Wire.beginTransmission(address);  
  		Wire.send(0x51);
  		Wire.endTransmission();
  		converting=true;
  		return;
	}
	if(converting)
	{
		if ( conf & B1000000 != B10000000 ) 
		{
    		Wire.beginTransmission(address);  
    		Wire.send(0xAC);  
    		Wire.endTransmission();
    		conf = Wire.receive();
		}
		else
		{
			// ask for the temerature  
  			Wire.beginTransmission(address);  
  			Wire.send(0xAA);  
  			Wire.endTransmission();

  			// request 2 bytes
  			Wire.requestFrom(address, 2);
  			// read first byte 

  			int temp = Wire.receive();
  			// read second byte
  			int frac = Wire.receive();
  			
  			this->rawValue=temp;
  			this->lastTemperature = 100.0 * (frac & 0xF0 )/ 256.0;
  			
  			converting=false;
		}
  }*/
}