#ifndef Sensor_h
#define Sensor_h

#include <iterator> 
#include <list> 
#include <IPersistAble.h>
#include <str_cmp.h>

class Sensor : public IPersistable
{
  public:
  virtual int getId();
  void setId(int);
  char* getName();
  void setName(char*);
  virtual int getRawValue()=0;
  
  virtual std::map<char*,char*> save()=0;
  virtual IPersistable* load(std::map<char*,char*,str_cmp>)=0;
  virtual char* getClassName()=0;
  
  
  float fmap(float x, float in_min, float in_max, float out_min, float out_max);
  protected:
  int id;
  char* name;
};

#endif