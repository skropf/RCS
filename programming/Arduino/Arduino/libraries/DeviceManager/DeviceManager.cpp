#include <Device.h>
#include <SPI.h>
#include "DeviceManager.h"
#include <SdFat.h>
#include <Log.h>
#include <iterator> 
#include <list> 
#include <map>
#include <SimpleDevice.h>
#include <IPersistable.h>
#include <UnifiedFactory.h>
#include <Device_Message.h>
#include <Global_MessageId.h>
#include <StringUtility.h>
#include <MemoryFree.h>
#include <str_cmp.h>
#include <memory>

SdFat card;

template<typename T, int size>
int GetArrayLength(T(&)[size]){return size;}

DeviceManager* DeviceManager::instance = 0;

DeviceManager* DeviceManager::getInstance()
{
  if(instance == 0) instance =  new DeviceManager();
  return instance;
}
void DeviceManager::addDevice(Device *d)
{
  	deviceMap[d->getId()] = d; 
}
void DeviceManager::addActor(Actor *d)
{
  	actorMap[d->getId()] = d; 
}
void DeviceManager::addSensor(Sensor *d)
{
  	sensorMap[d->getId()] = d; 
}
Device* DeviceManager::getDeviceById(int id)
{
	std::map<int, Device*>::iterator itxx;
  		for ( itxx=deviceMap.begin(); itxx != deviceMap.end(); itxx++ )
    	{
    		//Serial.println(itxx->first);
    		//Log::serial(itxx->second->getId());
    		if(id==itxx->first) return itxx->second;
    	}
  	return NULL;
}
Actor* DeviceManager::getActorById(int id)
{
	//Log::serial("Actors:");
	std::map<int, Actor*>::iterator itxx;
  		for ( itxx=actorMap.begin(); itxx != actorMap.end(); itxx++ )
    	{
    		//Serial.println(itxx->first);
    		//Log::serial(itxx->second->getId());
    		if(id==itxx->first) return itxx->second;
    	}
	//Serial.println(id);
	//Serial.println(actorMap[id]->getId());
  	return NULL;
}
Sensor* DeviceManager::getSensorById(int id)
{
	std::map<int, Sensor*>::iterator itxx;
  		for ( itxx=sensorMap.begin(); itxx != sensorMap.end(); itxx++ )
    	{
    		if(id==itxx->first) return itxx->second;
    	}

  	return NULL;
}
int DeviceManager::writeToSdCard()
{

  if (!card.init(SPI_HALF_SPEED, 4)) Log::serial("card.init failed!");
  
  // initialize a FAT volume
  if(-1==this->persist("Actors.mcp",&actorMap)) return -1;
  if(-1==this->persist("Sensors.mcp",&sensorMap)) return -1;
  if(-1==this->persist("Devices.mcp",&deviceMap)) return -1;
  return 1;
}
int DeviceManager::persist(char * fileName,void * ptr)
{
	std::map<int,IPersistable*,ltDev>* persistableMap = reinterpret_cast<std::map<int, IPersistable*,ltDev> *>(ptr);
	SdFile file;
if (!file.open(fileName, O_RDWR | O_CREAT | O_TRUNC)) {
    return -1;
  }
  std::map<int, IPersistable*>::iterator it;
  
  for ( it=persistableMap->begin() ; it != persistableMap->end(); it++ )
    {
    	char persistString[80]="";
    	std::map<char*,char*> params = it->second->save();
    	
    	std::map<char*, char*>::iterator itx;
		for ( itx=params.begin(); itx != params.end(); itx++ )
    	{
    		if(it != params.begin()) strcat(persistString,"|");
    		strcat(persistString,itx->first);
    		strcat(persistString,"=");
    		strcat(persistString,itx->second);
    	}
    	file.println(it->second->getClassName());
    	file.println(persistString);
    }
  	file.close();
  return 1;
}

int DeviceManager::readFromSdCard()
{

  if (!card.init(SPI_HALF_SPEED, 4)) Log::serial("card.init failed!");
  
  if(-1==this->load("Actors.mcp",&actorMap)) return -1;
  //printActors();
  if(-1==this->load("Sensors.mcp",&sensorMap)) return -1;
  //printSensors();
  if(-1==this->load("Devices.mcp",&deviceMap)) return -1;
  return 1;
}

int DeviceManager::load(char * fileName, void*ptr)
{
	std::map<int,IPersistable*,ltDev>* persistableMap = static_cast<std::map<int, IPersistable*,ltDev> *>(ptr);
	SdFile file;
if (!file.open(fileName, O_READ)) {
    return -1;
  }
  char name[50]; 
  char line[120];
  /*if(strcmp(fileName,"Sensors.mcp")==0)
  {
  	file.fgets(line,sizeof(line));file.fgets(line,sizeof(line));
  }*/
  //int cnt = 0;
  //file.fgets(line,sizeof(line));file.fgets(line,sizeof(line));
	  while(file.fgets(name, sizeof(name)) > 0)
  {
  		file.fgets(line,sizeof(line));
  		Log::serial(name);
  		Log::serial(line);
  		
  		std::vector<char*> params;
  		
  		std::map<char*, char*,str_cmp> map;
  		
  		StringUtility::split(line,"=|\n",params);
  		
  		std::vector<char*>::iterator itx;
		for ( itx=params.begin(); itx != params.end(); itx++ )
    	{
    		
    		//char* first = (char*)malloc(20);
    		//char* second = (char*)malloc(20);
    		//strcpy(first,*itx);
    		//strcpy(second,*(++itx));
    		map[*itx] = *(++itx);
    		
    		//Log::serial("firstvalue:");
    		//Serial.println(first);
    		//Log::serial("secondvalue:");
    		
			//Log::serial(map[first]);
    		//Log::serial(second);
    	}
       	//params.clear();
    	
  		IPersistable* persist = UnifiedFactory::getInstance()->generateClassFromName(name,map);
  		if(persist==NULL)
  		{
  			Log::serial("persist is null");
  			return -1;
  		}
  		(*persistableMap).insert(std::pair <int, IPersistable*>(persist->getId(),persist)); 
  		//if(++cnt==2)
  		//break;
  }
  
  return 1;
}
void DeviceManager::printActors()
{
	Log::serial("Actors:");
		std::map<int, Actor*>::iterator itxx;
  		for ( itxx=actorMap.begin(); itxx != actorMap.end(); itxx++ )
    	{
    		Serial.println(itxx->first);
    		Serial.println(itxx->second->getId());
    	}
    	//free(&itxx);
}
void DeviceManager::printSensors()
{
	Log::serial("Sensors:");
	std::map<int, Sensor*>::iterator itxx;
  		for ( itxx=sensorMap.begin(); itxx != sensorMap.end(); itxx++ )
    	{
    		Serial.println(itxx->first);
    		Serial.println(itxx->second->getId());
    	}
    //free(&itxx);
}

	//#Msgid:Msgtype:DevId:DeviceType(string):DeviceName:currentStatus;
void DeviceManager::sendDevices()
{
	std::map<int, Device*>::iterator it;
	Device_Message *devMsg = new Device_Message();
	for ( it=deviceMap.begin(); it != deviceMap.end(); it++ )
    {
    	if(it->second!=NULL)
    	{
    		devMsg->setMsgId(Global_MessageId::getInstance()->getNextId());
    		devMsg->setDevId(it->second->getId());
    		Serial.println(it->second->getId());
    		devMsg->setDeviceType(it->second->getClassName());
    		Log::serial(it->second->getClassName());
    		devMsg->setDeviceName(it->second->getName());
    		Log::serial(it->second->getName());
    		std::map<char*,char*> map = it->second->getProperties();
    		devMsg->setCurrentProperties(&map);
    		//free(&map);
    		if(strlen(devMsg->getMessage())>3)Connector::getInstance()->sendResult(devMsg->getMessage());
    		delay(100);
    	}
    }
    delete(devMsg);
}