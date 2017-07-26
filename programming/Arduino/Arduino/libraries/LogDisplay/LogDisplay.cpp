#include <Log_Message.h>
#include <glcd.h>
#include <bitmaps/allBitmaps.h>       // all images in the bitmap dir 
// include the Fonts
#include <fonts/allFonts.h>
#include <WorkQueue.h>
#include <DeviceManager.h>
#include "LogDisplay.h"

LogDisplay* LogDisplay::instance = 0;


LogDisplay::LogDisplay()
{
	// Initialize the GLCD 
  GLCD.Init();

 // Select the font for the default text area
  GLCD.SelectFont(System5x7);
  WorkQueue::getInstance()->add(this);
  sensorDev = (SimpleDevice*)DeviceManager::getInstance()->getDeviceById(1);
  time = millis();
  textArea.DefineArea(0, GLCD.CenterY, GLCD.Right, GLCD.Bottom, SCROLL_UP); 
  textArea.SelectFont(System5x7, BLACK);
}
bool LogDisplay::doWork()
{
	if(time < millis() - 2000)
	{
  		textArea.CursorTo(0,0);
		std::list<char*>::iterator it;
		GLCD.CursorTo(0, 0);
		for ( it=logMsgList.begin() ; it != logMsgList.end(); it++ )
		{
			textArea.println(*it);
		}
		char* lum = sensorDev->getLuminosity();
  		char* temp = sensorDev->getTemperature();
 		char firstline[100];
  		sprintf(firstline,"Temp: %s °C\nLum: %s", temp,lum);  
  		GLCD.CursorTo(0, 0);
  		GLCD.println(firstline);
  		time = millis();
	}
	return true;
}
LogDisplay* LogDisplay::getInstance()
{
	if(instance==0)
		instance = new LogDisplay();
	return instance;
}
void LogDisplay::addLogMessage(Log_Message* msg)
{
	if(this->logMsgList.size()>2)
	{
		free(*this->logMsgList.begin());
		this->logMsgList.pop_front();
	}
	this->logMsgList.push_back(msg->getMessage());
}