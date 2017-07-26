#ifndef Light_h
#define Light_h

#include <SolidStateRelay.h>
#include <StringUtility.h>
#include <Result_Message.h>
#include <Connector.h>
#include <Connection.h>
#include <DeviceManager.h>
#include <WorkQueue.h>
#include <ILightSensor.h>




class Light : public Device
{
  public:
  virtual char* callMethod(String,std::vector<char*>);
  virtual std::map<char*,char*> save();
  virtual IPersistable* load(std::map<char*,char*,str_cmp>);
  virtual char* getClassName(){return "Light";};
  virtual bool doWork();
  Light();

  void setCondition(int);
  char* turnOn(std::vector<char*>);                         //einschalten
  char* turnOff(std::vector<char*>);                        //ausschalten
  char* setBrightnessCondition(std::vector<char*>);  		//Helligkeitsbedingung setzen
  char* getBrightnessCondition(std::vector<char*>);			//Helligkeitsbedingung holen
  char* removeCondition(std::vector<char*>);       			//Bedingung löschen
  char* getStatus(std::vector<char*>);        				//ob ein-/ausgeschalten
  virtual std::map<char*,char*> getProperties();
  
  SolidStateRelay* getSSR();
  void setSSR(SolidStateRelay*);
  
  LightSensor* getLightSensor();
  void setLightSensor(LightSensor* sensor);
  private:
  SolidStateRelay* ssr;
  int condition;
  LightSensor* sensor;
  typedef char* (Light::*pt2Member)(std::vector<char*>);
  pt2Member functionArray[6];
  String functionNames[6];
};

#endif