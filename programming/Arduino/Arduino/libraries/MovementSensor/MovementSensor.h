#ifndef MovementSensor_h
#define MovementSensor_h


#include <Sensor.h>
#include <IPersistable.h>
#include <Ultrasonic.h>

class MovementSensor: public Sensor
{
	public:
  		bool checkForMovement();
  		void setIOPins(int,int);
  		void calibrate();
  		void setTolerance(int);
  		MovementSensor();
  		
  		virtual std::map<char*,char*> save();
  		virtual IPersistable* load(std::map<char*,char*,str_cmp>);
  		virtual char* getClassName(){return "MovementSensor";};
  		virtual int getRawValue();
  	
  	private:
  		int pingPin;
  		int dataPin;
  		bool isRunning;
  		Ultrasonic *ultrasonic;
  		int standart;
  		int tolerance;
};

#endif