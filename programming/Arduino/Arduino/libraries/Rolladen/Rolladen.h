#ifndef Rolladen_h
#define Rolladen_h

#define BEGIN 0
#define STOPPED -1
#define RUNNING 1
#define CONDITION 2

#include <IO.h>
#include <iterator> 
#include <list>
#include <vector> 
#include <map>
#include <Sensor.h>
#include <Actor.h>
#include <IPersistable.h>
#include <ILightSensor.h>
#include <SolidStateRelay.h>

#define LAST_STATE_UP 1
#define LAST_STATE_DOWN 0

class Rolladen : public Device
{
	public:
    virtual char* callMethod(String,std::vector<char*>);
  	virtual bool doWork();
  	virtual std::map<char*,char*> save();
  	virtual IPersistable* load(std::map<char*,char*,str_cmp>);
  	virtual char* getClassName(){return "RollerBlind";};
  	virtual std::map<char*,char*> getProperties();
  	
  	char* setPosition(std::vector<char*>);                               //Position setzen
	char* getPosition(std::vector<char*>);                                                   //Position holen
	char* setBrightnessCondition(std::vector<char*>);  //Helligkeitsbedingung setzen
	char* getBrightnessCondition(std::vector<char*>);                                //Helligkeitsbedingung holen
	char* removeCondition(std::vector<char*>);                                               //Bedingung lÃ¶schen
	//char* getBrightness(std::
	
	void setCondition(int cond);
	
	void setLightSensor(LightSensor*);
	LightSensor* getLightSensor();
	SolidStateRelay* getSSRUp();
	void setSSRUp(SolidStateRelay* ssr);
	
	SolidStateRelay* getSSRDown();
	void setSSRDown(SolidStateRelay* ssr);
	
	Rolladen(int lastPos = 0);
	
	private:
	char* conditionString;
	char* lastPositionString;
	typedef char* (Rolladen::*pt2Member)(std::vector<char*>);
 	pt2Member functionArray[5];
 	String functionNames[5];
 	int position;
 	int lastPosition;
 	int lastState;
 	LightSensor* light;
 	SolidStateRelay* ssrUp;
 	SolidStateRelay* ssrDown;
 	long startTime;
 	long duration;
 	int state;
 	int condition;
 	long estimatedTime;
};

#endif