#ifndef Actor_h
#define Actor_h

#include <Device.h>
#include <iterator> 
#include <list> 
#include <IPersistable.h>
#include <str_cmp.h>

class Actor : public IPersistable
{
  public:
  virtual int getId();
  void setId(int);
  char* getName();
  void setName(char*);
  
  virtual std::map<char*,char*> save()=0;
  virtual IPersistable* load(std::map<char*,char*,str_cmp>)=0;
  virtual char* getClassName()=0;
  	
  	
  protected:
  int id;
  char* name;
};

#endif