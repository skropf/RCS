#include <WorkQueue.h>
#include <StringUtility.h>
#include <DeviceManager.h>
#include <Log.h>
#include "Rolladen.h"

char* Rolladen::callMethod(String methodName,std::vector<char*> params)
{
	for(int i = 0;i<GetArrayLength(functionNames);i++)
	{
		if(functionNames[i] == methodName)
		{
			return (this->*functionArray[i])(params);
		}
	}
	return "Method Not Found";
}
bool Rolladen::doWork()
{
	Serial.println(this->lastPosition);
	Serial.println(this->lastState);
	if(state==STOPPED)
	{
		lastPosition = position;
		return false;
	}
	if(state==BEGIN)
	{
		
		this->startTime = millis();
		int dif = lastPosition-position;
		if(dif<0)dif=dif*-1;
		this->estimatedTime = duration/1000 * dif;
		if(lastPosition<position)
		{
			if(this->lastState==LAST_STATE_DOWN)
			{
				this->ssrUp->turnOn();
				delay(500);
				this->ssrUp->turnOff();
				delay(500);
				this->ssrUp->turnOn();
				delay(500);
				this->ssrUp->turnOff();
				delay(500);
			}
			if(this->lastState==LAST_STATE_UP)
			{
				this->ssrUp->turnOn();
				delay(500);
				
			}
			this->lastState=LAST_STATE_DOWN;
		}
		if(lastPosition>position)
		{
			if(this->lastState==LAST_STATE_DOWN)
			{
				this->ssrUp->turnOn();
				delay(500);
			}
			if(this->lastState==LAST_STATE_UP)
			{
				this->ssrUp->turnOn();
				delay(500);
				this->ssrUp->turnOff();
				delay(500);
				this->ssrUp->turnOn();
				delay(500);
				this->ssrUp->turnOff();
				delay(500);
			}
			this->lastState=LAST_STATE_UP;
		}
		
		this->state=RUNNING;
		return true;
	}
	if(state==RUNNING)
	{
		if(startTime+estimatedTime<millis())
		{
			this->ssrUp->turnOn();
				delay(500);
				this->ssrUp->turnOff();
				delay(500);
			this->state=STOPPED;
		}
		return true;
	}
	if(state==CONDITION)
	{
		int brightness = this->light->getLuminosity();
		
		if(brightness<condition)
		{
			position = 500;
			this->state=BEGIN;
		}
		if(brightness>condition)
		{
			position = 0;
			this->state=BEGIN;
		}
		return true;
	}
	return false;
}
std::map<char*,char*> Rolladen::save()
{
 	std::map<char*,char*> map;
 	map["brightness"] = StringUtility::itoa(condition);
 	map["id"] = StringUtility::itoa(this->getId());
 	map["position"] = StringUtility::itoa(this->lastPosition);
 	map["ssrUpId"] = StringUtility::itoa(this->ssrUp->getId());
 	map["ssrDownId"] = StringUtility::itoa(this->ssrDown->getId());
 	map["name"] = this->getName();
 	map["lightSensorId"] = StringUtility::itoa(this->getLightSensor()->getId());
 	return map;
}
IPersistable* Rolladen::load(std::map<char*,char*,str_cmp> map)
{
	Rolladen* rolladen = new Rolladen(StringUtility::atoi(map["position"]));
	rolladen->setCondition(StringUtility::atoi(map["brightness"]));
	rolladen->setId(StringUtility::atoi(map["id"]));
	rolladen->setSSRUp((SolidStateRelay*)DeviceManager::getInstance()->getActorById(StringUtility::atoi(map["ssrUpId"])));
	rolladen->setSSRDown((SolidStateRelay*)DeviceManager::getInstance()->getActorById(StringUtility::atoi(map["ssrDownId"])));
	char* buffer = (char*) malloc(30);
	strcpy(buffer,map["name"]);
	rolladen->setName(buffer);
	rolladen->setLightSensor((LightSensor*)DeviceManager::getInstance()->getSensorById(StringUtility::atoi(map["lightSensorId"])));
	return rolladen;
}
std::map<char*,char*> Rolladen::getProperties()
{
 	std::map<char*,char*> props;
 	if(conditionString!=NULL)
 		free(conditionString);
 	conditionString=(char*)malloc(30);
 	sprintf(conditionString,"%d",condition);
 	props["brightness"] = conditionString;
 	
 	if(lastPositionString!=NULL)
 		free(lastPositionString);
 	lastPositionString= (char*)malloc(30);
 	sprintf(lastPositionString,"%d",lastPosition);
 	props["position"] = lastPositionString;
 	return props;
}  	
void Rolladen::setCondition(int cond)
{
	this->condition = cond;
	if(condition!=-1)
	{
		this->state=CONDITION;
		WorkQueue::getInstance()->add(this);
	}
}
char* Rolladen::setPosition(std::vector<char*> args)                               //Position setzen
{
	this->position = atoi(args[0]);
	Serial.println(position);
	this->state = BEGIN;
	WorkQueue::getInstance()->add(this);
	return "true";
}
char* Rolladen::getPosition(std::vector<char*>)                                                   //Position holen
{
	char buffer[20];
	sprintf(buffer,"%d",this->position);
	return buffer;
}
char* Rolladen::setBrightnessCondition(std::vector<char*> args)  //Helligkeitsbedingung setzen
{
	this->condition = atoi(args[0]);
	this->state = CONDITION;
	WorkQueue::getInstance()->add(this);
	return "true";
}
char* Rolladen::getBrightnessCondition(std::vector<char*> args)                                //Helligkeitsbedingung holen
{
	char buffer[30]="";
	sprintf(buffer,"%d",this->condition);
	return buffer;
}
char* Rolladen::removeCondition(std::vector<char*>)                                               //Bedingung lÃ¶schen
{
	this->state = CONDITION;
	return "Condition removed";
}
LightSensor* Rolladen::getLightSensor()
{
	return this->light;
}
void Rolladen::setLightSensor(LightSensor* light)
{
	this->light = light;
}
/*
	char* setPosition(std::vector<char*>);                               //Position setzen
	char* getPosition(std::vector<char*>);                                                   //Position holen
	char* setBrightnessCondition(std::vector<char*>);  //Helligkeitsbedingung setzen
	char* getBrightnessCondition(std::vector<char*>);                                //Helligkeitsbedingung holen
	char* removeCondition(std::vector<char*>);                                               //Bedingung lÃ¶schen
*/
Rolladen::Rolladen(int last)
{
	this->lastPosition = last;
	this->conditionString=NULL;
	this->lastPositionString=NULL;
	this->duration = 25000; //default
	this->condition = -1;
	this->lastState=LAST_STATE_DOWN;
	
	functionArray[0] = &Rolladen::setPosition;
	functionNames[0] = "setPosition";
	
	functionArray[1] = &Rolladen::getPosition;
	functionNames[1] = "getPosition";
	
	functionArray[2] = &Rolladen::setBrightnessCondition;
	functionNames[2] = "setBrightnessCondition";
	
	functionArray[3] = &Rolladen::getBrightnessCondition;
	functionNames[3] = "getBrightnessCondition";
	
	functionArray[4] = &Rolladen::removeCondition;
	functionNames[4] = "removeCondition";
}
SolidStateRelay* Rolladen::getSSRUp()
{
  return this->ssrUp;
}
void Rolladen::setSSRUp(SolidStateRelay* ssr)
{
  this->ssrUp=ssr;
}
SolidStateRelay* Rolladen::getSSRDown()
{
  return this->ssrDown;
}
void Rolladen::setSSRDown(SolidStateRelay* ssr)
{
  this->ssrDown=ssr;
}