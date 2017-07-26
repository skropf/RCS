#ifndef UnifiedFactory_h
#define UnifiedFactory_h
#include <iterator> 
#include <list> 
#include <vector>
#include <map>
#include <str_cmp.h>

class UnifiedFactory
{
	public:
    static UnifiedFactory * getInstance();
    IPersistable* generateClassFromName(char*,std::map<char*,char*,str_cmp>);
  private:
  	UnifiedFactory(){};
  	static UnifiedFactory *instance;
};
#endif