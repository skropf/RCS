#ifndef SolidStateRelay_h
#define SolidStateRelay_h


#include <Actor.h>


class SolidStateRelay: public Actor
{
  public:
  	void turnOn();
    void turnOff();
    SolidStateRelay(int);
    SolidStateRelay(int,bool);
    SolidStateRelay();
    
    virtual std::map<char*,char*> save();
  	virtual IPersistable* load(std::map<char*,char*,str_cmp>);
  	virtual char* getClassName(){return "SolidStateRelay";};
  	void setIOPin(int);
    int getIOPin();
  	void setState(int);
    int getState();
    protected:
    int lastState;
    private:
    int pin;
};

#endif