#include "SystemLogPreferences.h"

SystemLogPreferences* SystemLogPreferences::instance=0;

SystemLogPreferences::SystemLogPreferences()
{
	this->logToSd=false;
	this->level = 0;
	this->logToSd = true;
}
SystemLogPreferences* SystemLogPreferences::getInstance()
{
	if(instance==0) instance = new SystemLogPreferences();
  return instance;
}