#ifndef Heater_h
#define Heater_h


#include <SolidStateRelay.h>
#include <StringUtility.h>
#include <Result_Message.h>
#include <Connector.h>
#include <Connection.h>
#include <DeviceManager.h>
#include <WorkQueue.h>
#include <ILightSensor.h>
#include <ITemperaturSensor.h>



class Heater : public Device
{
  public:
  virtual char* callMethod(String,std::vector<char*>);
  virtual std::map<char*,char*> save();
  virtual IPersistable* load(std::map<char*,char*,str_cmp>);
  virtual char* getClassName(){return "Heater";};
  virtual bool doWork();

  char* turnOn(std::vector<char*>);                         //einschalten
  char* turnOff(std::vector<char*>);                        //ausschalten
  char* getStatus(std::vector<char*>);        				//ob ein-/ausgeschalten
  char* setHumidityCondition(std::vector<char*>);              //Luftfeuchtigkeitsbedingung setzen
  char* removeCondition(std::vector<char*>);                                               //Bedingung löschen
  virtual std::map<char*,char*> getProperties();

  void setCondition(int condition);
  SolidStateRelay* getSSR();
  void setSSR(SolidStateRelay*);
  
  ITemperaturSensor* getTemperaturSensor();
  void setTemperaturSensor(ITemperaturSensor*);
  
  Heater();
  
  private:
  char* tempString;
  SolidStateRelay* ssr;
  ITemperaturSensor* tempSensor;
  int condition;
  bool conditionIsSet;
  typedef char* (Heater::*pt2Member)(std::vector<char*>);
  pt2Member functionArray[5];
  String functionNames[5];
};

#endif