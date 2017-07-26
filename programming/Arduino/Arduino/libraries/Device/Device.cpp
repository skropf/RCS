#include "Device.h"

int Device::getId()
 {
  	return this->deviceId;
}
 void Device::setId(int id)
  {
  	this->deviceId = id;
}
void Device::setName(char* name)
{
  	this->name=name;
}
char* Device::getName()
  {
  	return this->name;
}