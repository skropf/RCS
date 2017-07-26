#ifndef IPersistable_h
#define IPersistable_h

#include <iterator> 
#include <list>
#include <vector> 
#include <map>
#include <str_cmp.h>

#include <Arduino.h>

class IPersistable
{
  public:
  	virtual std::map<char*,char*> save()=0;
  	virtual IPersistable* load(std::map<char*,char*,str_cmp>)=0;
  	virtual int getId()=0;
  	virtual char* getClassName()=0;
};

#endif
