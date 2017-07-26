#include <SolidStateRelay.h>
#include <IPersistable.h>
#include <Log.h>
#include "PowerOutlet.h"

template<typename T, int size>
int GetArrayLength(T(&)[size]){return size;}

char* PowerOutlet::callMethod(String methodName,std::vector<char*> params)
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
std::map<char*,char*> PowerOutlet::save()
{
	std::map<char*,char*> params;
	//char* buffer = (char*)malloc(50);
	//sprintf(buffer,"#%d:%s:%d;",this->getId(),this->getName(),this->getSSR()->getId());
	//return buffer;
	params["id"] = StringUtility::itoa(this->getId());
	params["name"] = this->getName();
	params["ssrId"] = StringUtility::itoa(this->getSSR()->getId());
	return params;
}
IPersistable* PowerOutlet::load(std::map<char*,char*,str_cmp> params)
{
	PowerOutlet* po = new PowerOutlet();
	po->setId(atoi(params["id"]));
	char* buffer = (char*) malloc(30);
	strcpy(buffer,params["name"]);
	po->setName(buffer);
	po->setSSR((SolidStateRelay*)DeviceManager::getInstance()->getActorById(atoi(params["ssrId"])));
	if(DeviceManager::getInstance()->getActorById(atoi(params["ssrId"]))==NULL)
		Log::serial("actor is null");
	return po;
}
char* PowerOutlet::turnOn(std::vector<char*>)                         //einschalten
{
	Log_Message *msg = new Log_Message();
	msg->setDeviceId(this->getId());
	char errorText[50] = "";
	sprintf(errorText,"Light dinner room was turned on");
	msg->setLogText(errorText);
	Log::verbose(msg);
	delete(msg);
	
	SolidStateRelay* s1 = (SolidStateRelay*)DeviceManager::getInstance()->getActorById(101);
	SolidStateRelay* s2 = (SolidStateRelay*)DeviceManager::getInstance()->getActorById(102);
	SolidStateRelay* s3 = (SolidStateRelay*)DeviceManager::getInstance()->getActorById(103);
	s1->turnOn();
	s2->turnOn();
	s3->turnOn();
	
	this->ssr->turnOn();
	return "true";
}
char* PowerOutlet::turnOff(std::vector<char*>)                        //ausschalten
{
	Log_Message *msg = new Log_Message();
	msg->setDeviceId(this->getId());
	char errorText[50] = "";
	sprintf(errorText,"Light dinner room was turned off");
	msg->setLogText(errorText);
	Log::verbose(msg);
	delete(msg);

	this->ssr->turnOff();
	SolidStateRelay* s1 = (SolidStateRelay*)DeviceManager::getInstance()->getActorById(101);
	SolidStateRelay* s2 = (SolidStateRelay*)DeviceManager::getInstance()->getActorById(102);
	SolidStateRelay* s3 = (SolidStateRelay*)DeviceManager::getInstance()->getActorById(103);
	s1->turnOff();
	s2->turnOff();
	s3->turnOff();
	return "true";
}
PowerOutlet::PowerOutlet()
{
	functionArray[0] = &PowerOutlet::turnOn;
	functionNames[0] = "turnOn";
	
	functionArray[1] = &PowerOutlet::turnOff;
	functionNames[1] = "turnOff";
}
std::map<char*,char*> PowerOutlet::getProperties()
{
	std::map<char*,char*> props;
	int state = this->ssr->getState();
	if(state == HIGH)
		props["state"]= "on";
	else props["state"] = "off";
	return props;
}
  
SolidStateRelay* PowerOutlet::getSSR()
{
	return this->ssr;
}
void PowerOutlet::setSSR(SolidStateRelay* ssr)
{
	this->ssr = ssr;
}
