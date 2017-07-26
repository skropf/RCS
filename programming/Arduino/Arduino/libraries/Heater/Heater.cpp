#include <IPersistable.h>
#include <ITemperaturSensor.h>
#include <SolidStateRelay.h>
#include <iterator> 
#include <list> 
#include <Log.h>
#include <Log_Message.h>
#include <vector>
#include "Heater.h"

char* Heater::callMethod(String methodName,std::vector<char*> params)
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
std::map<char*,char*> Heater::save()
{
	std::map<char*,char*> map;
	map["ssrId"] = StringUtility::itoa(this->ssr->getId());
	map["id"] = StringUtility::itoa(this->getId());
	map["tempSensorId"] = StringUtility::itoa(this->tempSensor->getId());
	map["condition"] = StringUtility::itoa(this->condition);
	map["name"] = this->getName();
	return map;
	//char* buffer = (char*) malloc(20);
	//sprintf(buffer,"#%d:%d:%d;",this->ssr->getId(),this->tempSensor->getId(),this->condition);
	//return buffer;
}
IPersistable* Heater::load(std::map<char*,char*,str_cmp> elems)
{
	Heater* heater = new Heater();
	char* buffer = (char*) malloc(30);
	strcpy(buffer,elems["name"]);
	heater->setName(buffer);
	heater->setSSR((SolidStateRelay*)DeviceManager::getInstance()->getActorById(atoi(elems["ssrId"])));

	heater->setTemperaturSensor((ITemperaturSensor*)DeviceManager::getInstance()->getSensorById(StringUtility::atoi(elems["tempSensorId"])));
	if(DeviceManager::getInstance()->getSensorById(StringUtility::atoi(elems["tempSensorId"]))==NULL)
	{
		Log::serial("Sensor is null");
		Serial.println(elems["tempSensorId"]);
	}
	//std::vector<char*> param;
	//param.push_back(elems["condition"]);
	heater->setCondition(atoi(elems["condition"]));
	//delete(&param);
	heater->setId(atoi(elems["id"]));
	return heater;
}
void Heater::setCondition(int cond)
{
	this->condition = cond;
	if(cond!=-1)
	{
		this->conditionIsSet = true;
		WorkQueue::getInstance()->add(this);
	}
}
bool Heater::doWork()
{
	int temp = this->tempSensor->getTemperatureInCelsius();
	if(!conditionIsSet)return false;
	if(this->ssr->getState()==LOW && this->tempSensor->getTemperatureInCelsius()>condition)
		this->ssr->turnOn();
	return true;
}

char* Heater::turnOn(std::vector<char*>)                         //einschalten
{
	this->ssr->turnOn();
	
	Log_Message *msg = new Log_Message();
	msg->setDeviceId(this->getId());
	msg->setLogText("Heater was turned on");
	Log::serial("LOG");
	Log::verbose(msg);
	delete(msg);
	return "true";
}
char* Heater::turnOff(std::vector<char*>)                        //ausschalten
{
	Log_Message *msg = new Log_Message();
	msg->setDeviceId(this->getId());
	msg->setLogText("Heater was turned off");
	Log::serial("LOG");
	Log::verbose(msg);
	delete(msg);
	
	this->ssr->turnOff();
	return "true";
}
char* Heater::getStatus(std::vector<char*>)        				//ob ein-/ausgeschalten
{
	int state = this->ssr->getState();
	if(state == HIGH)
		return "on";
	return "off";
}
char* Heater::setHumidityCondition(std::vector<char*> args)              //Luftfeuchtigkeitsbedingung setzen
{
	int humidity = atoi(args[0]);
	this->condition = humidity;
	if(humidity!=-1)
	{
		this->conditionIsSet = true;
		WorkQueue::getInstance()->add(this);
	}
	return "true";
}
char* Heater::removeCondition(std::vector<char*>)                                              //Bedingung löschen
{
	this->conditionIsSet = true;
	return "true";
}
  
SolidStateRelay* Heater::getSSR()
{
	return this->ssr;
}
void Heater::setSSR(SolidStateRelay* ssr)
{
	this->ssr = ssr;
}
ITemperaturSensor* Heater::getTemperaturSensor()
{
	return this->tempSensor;
}
void Heater::setTemperaturSensor(ITemperaturSensor* sensor)
{
	this->tempSensor = sensor;
}
std::map<char*,char*> Heater::getProperties()
{
	std::map<char*,char*> props;
	int state = this->ssr->getState();
	if(state == HIGH)
		props["state"]= "on";
	else props["state"] = "off";
	
	if(tempString!=NULL)
		free(tempString);
	tempString = (char*)malloc(5);
	sprintf(tempString,"%d",this->tempSensor->getTemperatureInCelsius());
	props["temperature"] = tempString;
	return props;
}

//temperature,status(on/off)

Heater::Heater()
{
	this->tempString=NULL;
	this->condition = -1;
	this->conditionIsSet =false;
	functionArray[0] = &Heater::turnOn;
	functionNames[0] = "turnOn";
	
	functionArray[1] = &Heater::turnOff;
	functionNames[1] = "turnOff";
	
	functionArray[2] = &Heater::setHumidityCondition;
	functionNames[2] = "setHumidityCondition";
	
	functionArray[3] = &Heater::removeCondition;
	functionNames[3] = "removeCondition";
	
	functionArray[4] = &Heater::getStatus;
	functionNames[4] = "getStatus";
}