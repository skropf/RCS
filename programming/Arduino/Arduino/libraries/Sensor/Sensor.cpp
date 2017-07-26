#include "Sensor.h"

void Sensor::setId(int id)
{
	this->id =id;
}
int Sensor::getId()
{
	return this->id;
}
void Sensor::setName(char* name)
{
	this->name =name;
}
char* Sensor::getName()
{
	return this->name;
}
float Sensor::fmap(float x, float in_min, float in_max, float out_min, float out_max)
{
 return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}