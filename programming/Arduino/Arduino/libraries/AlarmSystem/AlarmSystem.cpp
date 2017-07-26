#include "AlarmSystem.h"
#include <SolidStateRelay.h>
#include <StringUtility.h>
#include <Result_Message.h>
#include <Connector.h>
#include <Connection.h>
#include <DeviceManager.h>
#include <WorkQueue.h>
#include <iterator> 
#include <list> 
#include <StringUtility.h>

SolidStateRelay* AlarmSystem::getSirene()
{
  return this->sirene;
}
void AlarmSystem::setSirene(SolidStateRelay* ssr)
{
  this->sirene=ssr;
}
MovementSensor* AlarmSystem::getRangeSensor()
{
  return this->rangeSensor;
}

char* AlarmSystem::callMethod(String methodName,std::vector<char*> params)
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
char* AlarmSystem::subscribe(std::vector<char*> args)
{
	destinations.push_back(Connector::getInstance()->getLastConnection());
	return "enabled";
}
bool AlarmSystem::doWork()
{
	if(time - 500 > millis())
	{
	bool hasChanged = this->rangeSensor->checkForMovement();
	
	if(hasChanged && destinations.size()>0)
	{
		Result_Message *msg = new Result_Message();
		msg->setReturnValue("ausgeloest");
		msg->setDeviceId(this->getId());
		std::vector<Connection>::iterator it;
		for ( it=destinations.begin() ; it != destinations.end(); it++ )
		{
			char* m = msg->getMessage();
			Connector::getInstance()->sendResult(m,*it);
			free(m);
		}
		this->sirene->turnOn();
		return false;
	}
	}
	else
	{
		time = millis();
	}
		return true;
}
char* AlarmSystem::turnOn(std::vector<char*> args)
{
	//this->rangeSensor->calibrate();
	//sirene->setState(0);
	//this->state = RUNNING;
	//WorkQueue::getInstance()->add(this);
	return "true";
}
char* AlarmSystem::turnOff(std::vector<char*> args)
{
	//WorkQueue::getInstance()->remove(this);
	//this->state=BREAK;
	return "true";
}
char* AlarmSystem::calibrateSensor(std::vector<char*> args)
{
	this->rangeSensor->calibrate();
	return "true";
}

char* AlarmSystem::unsubscribe(std::vector<char*> args)                                                   //abmelden
{
	std::vector<Connection>::iterator it;
		 for (it=destinations.begin(); it!=destinations.end(); it++)
		 {
		 	if(it->type==Connector::getInstance()->getLastConnection().type && it->type!=ETHERNET)
		 	{
		 		destinations.erase(it);
		 	}
		 	else
		 	{
		 		if(it->type==Connector::getInstance()->getLastConnection().type && it->type==ETHERNET)
		 		{
		 			if(it->ip[0] == Connector::getInstance()->getLastConnection().ip[0]&&
		 			it->ip[1] == Connector::getInstance()->getLastConnection().ip[1] &&
		 			it->ip[2] == Connector::getInstance()->getLastConnection().ip[2] &&
		 			it->ip[3] == Connector::getInstance()->getLastConnection().ip[3])
		 			{
		 				destinations.erase(it);
		 				return "disabled";
		 			}
		 		}
		 	}
		 }
}
char* AlarmSystem::setAlarmState(std::vector<char*> params)
{
	this->sirene->setState(atoi(params[0]));
	this->state=atoi(params[0]);
	return "true";
}

AlarmSystem::AlarmSystem()
{
	time=0;
	destinations = std::vector<Connection>();
	functionArray[0] = &AlarmSystem::subscribe;
	functionNames[0] = String("subscribe");
	
	functionArray[1] = &AlarmSystem::turnOn;
	functionNames[1] = String("turnOn");
	
	functionArray[2] = &AlarmSystem::turnOff;
	functionNames[2] = String("turnOff");
	
	/*functionArray[3] = &AlarmSystem::useSensor;
	functionNames[3] = String("useSensor");
	
	functionArray[4] = &AlarmSystem::getSensorList;
	functionNames[4] = String("getSensorList");
	
	functionArray[5] = &AlarmSystem::useActor;
	functionNames[5] = String("useActor");
	
	functionArray[6] = &AlarmSystem::getActorList;
	functionNames[6] = String("getActorList");*/
	
	functionArray[3] = &AlarmSystem::calibrateSensor;
	functionNames[3] = String("calibrate");
	
	functionArray[4] = &AlarmSystem::setAlarmState;
	functionNames[4] = String("setAlarm");
}
void AlarmSystem::setRangeSensor(MovementSensor* sensor)
{
	this->rangeSensor = sensor;
}

std::map<char*,char*> AlarmSystem::save()
{
	//char save[51];
	//snprintf(save,50,"#%d%d:%d;",this->getId(),this->sirene->getId(),this->rangeSensor->getId());
	//return save;
	return std::map<char*,char*>();
}
IPersistable* AlarmSystem::load(std::map<char*,char*,str_cmp> elems)
{
	//std::vector<char*> elems;
	//StringUtility::split(args,"#:;",elems);
	
	AlarmSystem *alarmSystem = new AlarmSystem();
	alarmSystem->setSirene((SolidStateRelay*)DeviceManager::getInstance()->getActorById(atoi(elems["sireneId"])));
	alarmSystem->setRangeSensor((MovementSensor*)DeviceManager::getInstance()->getSensorById(atoi(elems["rangeSensorId"])));
	alarmSystem->setId(atoi(elems["id"]));
	char* name = (char*) malloc(strlen(elems["name"])+10);
	strcpy(name,elems["name"]);
	alarmSystem->setName(name);
	return alarmSystem;
}
std::map<char*,char*> AlarmSystem::getProperties()
{
	std::map<char*,char*> props;
	if(this->sirene->getState()==HIGH)props["activated"]="true";
	if(this->sirene->getState()==LOW)props["activated"]="false";
	if(this->state==RUNNING) props["running"]="true";
	else props["running"] = "false";
	return props;
}
  	
  	
  	
  	