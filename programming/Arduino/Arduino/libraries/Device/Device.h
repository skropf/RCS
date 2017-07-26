#ifndef Device_h
#define Device_h

#include <IO.h>
#include <iterator> 
#include <list>
#include <vector> 
#include <map>
#include <Sensor.h>
#include <Actor.h>
#include <IPersistable.h>
#include <str_cmp.h>



class Device: public IPersistable
{
  public:
  template<typename T, int size>
  int GetArrayLength(T(&)[size]){return size;}
  virtual int getId();
  void setId(int);
  void setName(char*);
  char* getName();
  virtual char* callMethod(String,std::vector<char*>) = 0;
  virtual bool doWork() =0;
  virtual std::map<char*,char*> save()=0;
  virtual IPersistable* load(std::map<char*,char*,str_cmp>)=0;
  virtual char* getClassName()=0;
  
  virtual std::map<char*,char*> getProperties()=0;
  
  protected:
  char* name;
  int deviceId;
  
};

#endif