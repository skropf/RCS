#include <WorkQueue.h>
#include <StringUtility.h>
#include <Log.h>
#include "Light.h"

char* Light::callMethod(String methodName,std::vector<char*> params)
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
std::map<char*,char*> Light::save()
{
	std::map<char*,char*> map;
	map["ssrId"] = StringUtility::itoa(this->ssr->getId());
	map["condition"] = StringUtility::itoa(this->condition);
	map["name"] = this->getName();
	map["id"] = StringUtility::itoa(this->getId());
	map["lightSensor"] = StringUtility::itoa(this->getLightSensor()->getId());
	return map;
}
IPersistable* Light::load(std::map<char*,char*,str_cmp> map)
{
	Light* l = new Light();
	l->setCondition(atoi(map["condition"]));
	l->setSSR((SolidStateRelay*)DeviceManager::getInstance()->getActorById(atoi(map["ssrId"])));
	char* buffer = (char*)malloc(strlen(map["name"])+2);
	strncpy(buffer,map["name"],strlen(map["name"])+1);
	l->setName(buffer);
	l->setId(atoi(map["id"]));
	l->setLightSensor((LightSensor*)DeviceManager::getInstance()->getSensorById(StringUtility::atoi(map["lightSensorId"])));

	return l;
}
char* Light::turnOn(std::vector<char*> params)
{
	ssr->turnOn();
	Log_Message *msg = new Log_Message();
				msg->setDeviceId(this->getId());
				char *text = "Light was turned on";
				//sprintf(text,"%s was turned on",this->getName());
				msg->setLogText(text);
				Log::verbose(msg);
				delete(msg);
	return "true";
}
char* Light::turnOff(std::vector<char*> params)
{
	ssr->turnOff();
	Log_Message *msg = new Log_Message();
	msg->setDeviceId(this->getId());
	char *text = "Light was turned off";
	//sprintf(text,"%s was turned on",this->getName());
	msg->setLogText(text);
	Log::verbose(msg);
	delete(msg);
	return "true";
}
char* Light::setBrightnessCondition(std::vector<char*> params)
{
	int cond = atoi(params[0]);
	setCondition(cond);
	return "true";
}
void Light::setCondition(int cond)
{
	this->condition = cond;
	if(cond!=-1)
		WorkQueue::getInstance()->add(this);
}
char* Light::getBrightnessCondition(std::vector<char*>)
{
	char buffer[20]="";
	sprintf(buffer,"%d",this->condition);
	return buffer;
}
char* Light::removeCondition(std::vector<char*>)
{
	this->condition = -1;
	WorkQueue::getInstance()->remove(this);
	return "Condition removed";
}
char* Light::getStatus(std::vector<char*>)  
{
	int state = this->ssr->getState();
	if(state == HIGH)
		return "on";
	return "off";
} 
SolidStateRelay* Light::getSSR()
{
	return this->ssr;
}
void Light::setSSR(SolidStateRelay* ssr)
{
	this->ssr = ssr;
}

LightSensor* Light::getLightSensor()
{
	return this->sensor;
}
void Light::setLightSensor(LightSensor* sensor)
{
	this->sensor = sensor;
}
bool Light::doWork()
{
	if(this->sensor->getLuminosity()<this->condition && this->ssr->getState()==LOW)
		{
			this->ssr->turnOn();
			Log_Message *msg = new Log_Message();
				msg->setDeviceId(this->getId());
				char *text = "ausgeloest";
				//sprintf(text,"%s was turned on",this->getName());
				msg->setLogText(text);
				Log::verbose(msg);
				delete(msg);
		}
	if(this->sensor->getLuminosity()>this->condition && this->ssr->getState()==HIGH)
		{
			this->ssr->turnOff();
			Log_Message *msg = new Log_Message();
				msg->setDeviceId(this->getId());
				char *text = "ausgeloest";
				//sprintf(text,"%s was turned on",this->getName());
				msg->setLogText(text);
				Log::verbose(msg);
				delete(msg);
		}
	return true;
}
Light::Light()
{
	condition=-1;
	functionArray[0] = &Light::turnOn;
	functionNames[0] = "turnOn";
	
	functionArray[1] = &Light::turnOff;
	functionNames[1] = "turnOff";
	
	functionArray[2] = &Light::setBrightnessCondition;
	functionNames[2] = "setBrightnessCondition";
	
	functionArray[3] = &Light::getBrightnessCondition;
	functionNames[3] = "getBrightnessCondition";
	
	functionArray[4] = &Light::removeCondition;
	functionNames[4] = "removeCondition";
	
	functionArray[5] = &Light::getStatus;
	functionNames[5] = "getStatus";
}
std::map<char*,char*> Light::getProperties()
{
	std::map<char*,char*> props;
	char* buffer=(char*)malloc(20);
	sprintf(buffer,"%d",condition);
	props["brightness"] = buffer;
	return props;
}