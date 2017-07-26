// Ported to SdFat from the native Arduino SD library example by Bill Greiman
// On the Ethernet Shield, CS is pin 4. SdFat handles setting SS
const int chipSelect = 4;
/*
 SD card read/write
  
 This example shows how to read and write data to and from an SD card file 	
 The circuit:
 * SD card attached to SPI bus as follows:
 ** MOSI - pin 11
 ** MISO - pin 12
 ** CLK - pin 13
 ** CS - pin 4
 
 created   Nov 2010
 by David A. Mellis
 updated 2 Dec 2010
 by Tom Igoe
 modified by Bill Greiman 11 Apr 2011
 This example code is in the public domain.
 	 
 */
#include <SdFat.h>
SdFat sd;
SdFile myFile;

void setup() {
  Serial.begin(9600);

  // Initialize SdFat or print a detailed error message and halt
  // Use half speed like the native library.
  // change to SPI_FULL_SPEED for more performance.
  if (!sd.init(SPI_HALF_SPEED, chipSelect)) sd.initErrorHalt();

  // open the file for write at end like the Native SD library
  if (!myFile.open("sensors.mcp",  O_RDWR | O_CREAT)) {
    sd.errorHalt("opening test.txt for write failed");
  }
  // if the file opened okay, write to it:
  Serial.print("Writing to test.txt...");
  
  

  //insertDevices();
  //insertActors();
  insertSensors();
  
  
  
  myFile.close();
  
  Serial.println("done");
  
  if (!myFile.open("actors.mcp",  O_RDWR | O_CREAT)) {
    sd.errorHalt("opening test.txt for write failed");
  }
  // if the file opened okay, write to it:
  Serial.print("Writing to test.txt...");
  
  

  //insertDevices();
  insertActors();
  //insertSensors();
  
  
  
  myFile.close();
  
  Serial.println("done");
  
  if (!myFile.open("devices.mcp",  O_RDWR | O_CREAT)) {
    sd.errorHalt("opening test.txt for write failed");
  }
  // if the file opened okay, write to it:
  Serial.print("Writing to test.txt...");
  
  

  insertDevices();
  //insertActors();
  //insertSensors();
  
  
  
  myFile.close();
  
  Serial.println("done");
}

void insertDevices() {
  myFile.println("SensorDevice");
  myFile.println("name=Sensors|id=1|lightSensorId=50|tempSensorId=51");
  myFile.println("RollerBlind");
  myFile.println("brightness=-1|position=0|id=2|ssrUpId=101|ssrDownId=101|name=Rollerblind living room|lightSensorId=50");
  myFile.println("Light");
  myFile.println("condition=-1|ssrId=102|name=Light dinner room|id=3|lightSensorId=50");
  myFile.println("PowerOutlet");
  myFile.println("id=4|name=House electricity|ssrId=100");
  myFile.println("Fan");
  myFile.println("name=Air condition|ssrId=102|tempSensorId=51|condition=-1|id=6");
  myFile.println("Light");
  myFile.println("condition=-1|ssrId=102|name=Light dinner room|id=3|lightSensorId=50");
}

void insertActors() {
    myFile.println("SolidStateRelay");
    myFile.println("id=100|pin=22|lastState=0");
    myFile.println("SolidStateRelay");
    myFile.println("id=101|pin=12|lastState=0");
    myFile.println("SolidStateRelay");
    myFile.println("id=102|pin=30|lastState=0");
}

void insertSensors() {
    myFile.println("PrecisionLightSensorPhidget");
    myFile.println("pin=68|id=50");
    myFile.println("TemperaturSensorPhidget");
    myFile.println("pin=69|id=51");;
}
void loop() {
  // nothing happens after setup
}


