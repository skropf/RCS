#include <SolidStateRelay.h>
#include <IPersistable.h>
#include <Log.h>
#include <WorkQueue.h>
#include "Fan.h"


char* Fan::callMethod(String methodName,std::vector<char*> params)
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
std::map<char*,char*> Fan::save()
{
	/*char* buffer = (char*) malloc(20);
	sprintf(buffer,"#%d:%d:%d;",this->ssr->getId(),this->tempSensor->getId(),this->condition);
	return buffer;*/
	std::map<char*,char*> map;
	map["ssrId"] = StringUtility::itoa(this->ssr->getId());
	map["id"] = StringUtility::itoa(this->getId());
	map["tempSensorId"] = StringUtility::itoa(this->tempSensor->getId());
	map["condition"] = StringUtility::itoa(this->condition);
	map["name"] = this->getName();
	return map;
}
IPersistable* Fan::load(std::map<char*,char*,str_cmp> elems)
{
	Fan* fan = new Fan();
	char* buffer = (char*) malloc(30);
	strcpy(buffer,elems["name"]);
	fan->setName(buffer);
	fan->setSSR((SolidStateRelay*)DeviceManager::getInstance()->getActorById(atoi(elems["ssrId"])));

	fan->setTemperaturSensor((ITemperaturSensor*)DeviceManager::getInstance()->getSensorById(StringUtility::atoi(elems["tempSensorId"])));
	if(DeviceManager::getInstance()->getSensorById(StringUtility::atoi(elems["tempSensorId"]))==NULL)
	{
		Log::serial("Sensor is null");
		Serial.println(elems["tempSensorId"]);
	}
	//std::vector<char*> param;
	//param.push_back(elems["condition"]);
	fan->setCondition(atoi(elems["condition"]));
	//delete(&param);
	fan->setId(atoi(elems["id"]));
	return fan;

}

std::map<char*,char*> Fan::getProperties()
{
	std::map<char*,char*> props;
	int state = this->ssr->getState();
	if(state == HIGH)
		props["state"]= "on";
	else props["state"] = "off";
	
	char* tempString = (char*)malloc(20);
	sprintf(tempString,"%d",21);
	props["temperature"] = tempString;
	return props;
}

void Fan::setCondition(int cond)
{
	this->condition = cond;
}
char* Fan::turnOn(std::vector<char*>)                         //einschalten
{
	this->ssr->turnOn();
	Log_Message *msg = new Log_Message();
				msg->setDeviceId(this->getId());
				char *text = "Air conditioner was turned on";
				//sprintf(text,"%s was turned on",this->getName());
				msg->setLogText(text);
				Log::verbose(msg);
				delete(msg);
	return "true";
}
char* Fan::turnOff(std::vector<char*>)                        //ausschalten
{
	this->ssr->turnOff();
	Log_Message *msg = new Log_Message();
				msg->setDeviceId(this->getId());
				char *text = "Air conditioner was turned on";
				//sprintf(text,"%s was turned on",this->getName());
				msg->setLogText(text);
				Log::verbose(msg);
				delete(msg);
	return "true";
}
char* Fan::getStatus(std::vector<char*>)        				//ob ein-/ausgeschalten
{
	int state = this->ssr->getState();
	if(state == HIGH)
		return "on";
	return "off";
}
  
SolidStateRelay* Fan::getSSR()
{
	return this->ssr;
}
void Fan::setSSR(SolidStateRelay* ssr)
{
	this->ssr = ssr;
}
bool Fan::doWork()
{
	if(!isConditionEnabled)
		return false;
	if(time + 1000< millis())
	{
		double temp = this->tempSensor->getTemperatureInCelsius();
		Serial.println(temp);
		if(temp>condition&& this->ssr->getState()!=HIGH)
		{
			Log::serial("eingeschaltet");
			this->ssr->turnOn();
		}
		else
		{
			if(this->ssr->getState()!=LOW)
			{
				Log::serial("ausgeschaltet");
				this->ssr->turnOff();
			}
		}
		time = millis();
	}
	return true;
}
Fan::Fan()
{
	this->time=0;
	this->condition=-1;
	functionArray[0] = &Fan::turnOn;
	functionNames[0] = "turnOn";
	
	functionArray[1] = &Fan::turnOff;
	functionNames[1] = "turnOff";
	
	functionArray[2] = &Fan::setTemperatureCondition;
	functionNames[2] = "setTemperatureCondition";
	
	functionArray[3] = &Fan::removeCondition;
	functionNames[3] = "removeCondition";
	
	functionArray[4] = &Fan::getStatus;
	functionNames[4] = "getStatus";
}
char* Fan::removeCondition(std::vector<char*> params)
{
	this->isConditionEnabled = false;
	return "true";
}
char* Fan::setTemperatureCondition(std::vector<char*> params)
{
	this->condition = atoi(params[0]);
	this->isConditionEnabled = true;
	WorkQueue::getInstance()->add(this);
	return "true";
}
ITemperaturSensor* Fan::getTemperaturSensor()
{
	return this->tempSensor;
}
void Fan::setTemperaturSensor(ITemperaturSensor* temp)
{
	this->tempSensor = temp;
}