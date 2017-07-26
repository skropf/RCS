#ifndef DeviceManager_h
#define DeviceManager_h

#include <Device.h>
#include <Sensor.h>
#include <Actor.h>
#include <iterator> 
#include <list> 
#include <map>
#include <Connector.h>
#include <str_cmp.h>


class DeviceManager
{
  public:
    static DeviceManager * getInstance();
    void addDevice(Device*);
    void addSensor(Sensor*);
    void addActor(Actor*);
    Sensor* getSensorById(int id);
    Actor* getActorById(int id);
    Device* getDeviceById(int id);
    int writeToSdCard();
    int readFromSdCard();
    void sendDevices();
    
  private:
  	static DeviceManager *instance;
  	struct ltDev
	{
  		bool operator()(int s1, int s2)
  		{
    		if (s1 == s2)
    			return 0;
    		if (s1 > s2)
    			return 1;
    		else
    			return -1;
  		}
	};
  	std::map<int, Device*> deviceMap;
  	std::map<int, Sensor*> sensorMap;
  	std::map<int, Actor*> actorMap;
  	
	int persist(char *,void *);
	int load(char *, void*);
	void reinitClassArray();
	void printActors();
	void printSensors();
  protected:
  	DeviceManager() {};
};

#endif