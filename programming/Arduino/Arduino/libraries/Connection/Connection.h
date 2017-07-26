#ifndef Connection_h
#define Connection_h
#define COM 0
#define ETHERNET 1
#define ADK 2

#include <Arduino.h>
#include <ConnectionType.h>

struct Connection {
  			byte type; 
  			byte* ip;
  		};

#endif