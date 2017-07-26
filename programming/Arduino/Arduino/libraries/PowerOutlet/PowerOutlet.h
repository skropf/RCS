#ifndef PowerOutlet_h
#define PowerOutlet_h


#include <SolidStateRelay.h>
#include <StringUtility.h>
#include <Result_Message.h>
#include <Connector.h>
#include <Connection.h>
#include <DeviceManager.h>
#include <WorkQueue.h>
#include <ILightSensor.h>




class PowerOutlet : public Device
{
  public:
  virtual char* callMethod(String,std::vector<char*>);
  virtual std::map<char*,char*> save();
  virtual IPersistable* load(std::map<char*,char*,str_cmp>);
  virtual char* getClassName(){return "PowerOutlet";};
  virtual bool doWork(){};
  PowerOutlet();

  char* turnOn(std::vector<char*>);                         //einschalten
  char* turnOff(std::vector<char*>);                        //ausschalten
  
  SolidStateRelay* getSSR();
  void setSSR(SolidStateRelay*);
  virtual std::map<char*,char*> getProperties();
  
  private:
  typedef char* (PowerOutlet::*pt2Member)(std::vector<char*>);
  pt2Member functionArray[2];
  String functionNames[2];
  SolidStateRelay* ssr;
};

#endif