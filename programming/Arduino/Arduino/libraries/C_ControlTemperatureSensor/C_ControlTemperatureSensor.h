#ifndef C_ControlTemperatureSensor_h
#define C_ControlTemperatureSensor_h


#include <ITemperaturSensor.h>
#include <IPersistable.h>
#include <Sensor.h>


class C_ControlTemperatureSensor : public ITemperaturSensor
{
	public:
  		virtual std::map<char*,char*> save();
  		virtual IPersistable* load(std::map<char*,char*>);
  		virtual char* getClassName(){return "C_ControlTemperaturSensor";};
  		virtual int getRawValue();
  		virtual double getTemperatureInCelsius()=0;
  		void initTransmission(int adress);
  		virtual void refresh();
  	private:
  		int address;
  		double lastTemperature;
  		bool converting;
  		byte conf;
  		byte rawValue;
};

#endif