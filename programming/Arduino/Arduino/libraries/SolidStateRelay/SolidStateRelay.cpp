#include <StringUtility.h>
#include <iterator>
#include <vector>

#include "SolidStateRelay.h"

void SolidStateRelay::turnOn()
{
  this->setState(HIGH);
}
void SolidStateRelay::turnOff()
{
  this->setState(LOW);
}
SolidStateRelay::SolidStateRelay(int pin)
{
	pinMode(pin, OUTPUT);
 	this->setIOPin(pin);
 	this->lastState=LOW;
}
SolidStateRelay::SolidStateRelay(int pin,bool state)
{
	pinMode(pin, OUTPUT);
 	 this->setIOPin(pin);
  	if(state)this->setState(HIGH);
  	else this->setState(LOW);
}
SolidStateRelay::SolidStateRelay()
{
	this->lastState=LOW;
}
/*void SolidStateRelay::loadObject(String obj)
{
	char charArray[255];
  	obj.toCharArray(charArray,255);
  	
  	int counter = 0;
  	String ioPinString;
  	while(charArray[counter] !=':')
  	{
  		ioPinString += charArray[counter];
  		counter++;
  	}
  	char charBuf[50];
    ioPinString.toCharArray(charBuf, 10);
  	this->id = atoi(charBuf);
  	free(charBuf);
  	
  	this->lastState = charArray[++counter] - '0';
}*/

int SolidStateRelay::getState()
{
  return this->lastState;
}
void SolidStateRelay::setState(int state)
{
	Serial.print("set State:  ");
	Serial.println(state);
	Serial.print("On pin:  ");
	Serial.println(this->getIOPin());
  	this->lastState = state;
  	digitalWrite(this->getIOPin(),state);
}
void SolidStateRelay::setIOPin(int pin)
{
	this->pin = pin;
}
int SolidStateRelay::getIOPin()
{
	return this->pin;
}

std::map<char*,char*> SolidStateRelay::save()
{
	std::map<char*,char*> params;
	params["id"] = StringUtility::itoa(this->getId());
	params["pin"] = StringUtility::itoa(this->pin);
	params["lastState"] = StringUtility::itoa(this->lastState);
	return params;
	//char* save = (char*)malloc(51);
	//Serial.println("SolidStateRelay save");
	//snprintf(save,50,"#%d:%d:%d;",this->getId(),this->pin,this->lastState);
	//return save;
}
IPersistable* SolidStateRelay::load(std::map<char*,char*,str_cmp> elems)
{
	SolidStateRelay *ssr = new SolidStateRelay(atoi(elems["pin"]),atoi(elems["lastState"]));
	ssr->setId(atoi(elems["id"]));
	//Serial.println(elems["id"]);
	//Serial.println(ssr->getId());
	return ssr;
}
  	
  	
  	
  	