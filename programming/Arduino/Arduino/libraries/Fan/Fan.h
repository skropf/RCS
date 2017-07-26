#ifndef Fan_h
#define Fan_h


#include <SolidStateRelay.h>
#include <StringUtility.h>
#include <Result_Message.h>
#include <Connector.h>
#include <Connection.h>
#include <DeviceManager.h>
#include <WorkQueue.h>
#include <ILightSensor.h>
#include <ITemperaturSensor.h>




class Fan : public Device
{
  public:
  virtual char* callMethod(String,std::vector<char*>);
  virtual std::map<char*,char*> save();
  virtual IPersistable* load(std::map<char*,char*,str_cmp>);
  virtual char* getClassName(){return "Fan";};
  virtual std::map<char*,char*> getProperties();
  virtual bool doWork();

  char* turnOn(std::vector<char*>);                         //einschalten
  char* turnOff(std::vector<char*>);                        //ausschalten
  char* getStatus(std::vector<char*>);        				//ob ein-/ausgeschalten
  char* setTemperatureCondition(std::vector<char*>);              //Luftfeuchtigkeitsbedingung setzen
  char* removeCondition(std::vector<char*>);                                               //Bedingung löschen
  
  SolidStateRelay* getSSR();
  void setSSR(SolidStateRelay*);
  
  ITemperaturSensor* getTemperaturSensor();
  void setTemperaturSensor(ITemperaturSensor*);
  
  void setCondition(int cond);
  
  Fan();
  
  private:
  SolidStateRelay* ssr;
  ITemperaturSensor* tempSensor;
  int condition;
  bool isConditionEnabled;
  typedef char* (Fan::*pt2Member)(std::vector<char*>);
  pt2Member functionArray[5];
  String functionNames[5];
  long time;

};

#endif