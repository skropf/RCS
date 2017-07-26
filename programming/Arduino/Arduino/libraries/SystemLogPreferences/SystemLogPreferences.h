#ifndef SystemLogPreferences_h
#define SystemLogPreferences_h

#include <Connection.h>
#include <iterator> 
#include <Global_MessageId.h>
#include <list> 
#include <vector>


class SystemLogPreferences
{
  public:
    static SystemLogPreferences * getInstance();
    
    void setLevel(int level) { this->level = level; } 
	int getLevel() { return this->level; }
	void setDestinations(std::list<Connection> destination) { this->destination = destination; } 
	std::list<Connection> *getDestinations() { return &destination; }
	bool logToSd;
  private:
  	SystemLogPreferences();
  	int level;
	std::list<Connection> destination;
  	static SystemLogPreferences *instance;
};

#endif