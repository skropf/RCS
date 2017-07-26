#include <Wire.h>
#define address 0x4F
#define baudrate 9600

void setup() {
  Wire.begin();
  Serial.begin(baudrate);
}

void loop(){
  Wire.beginTransmission(address);
  // send configuration 
  Wire.send(0xAC);
  Wire.send(B00001111); // 12 bit resolution, pol, oneshot
  Wire.endTransmission();
  delay(10);

  // begin convert
  Wire.beginTransmission(address);  
  Wire.send(0x51);
  Wire.endTransmission();  
  delay(10);

  // wait until converting is done
  byte conf = 0;
  while ( conf & B1000000 != B10000000 ) {
    delay( 100 );
    Wire.beginTransmission(address);  
    Wire.send(0xAC);  
    Wire.endTransmission();
    conf = Wire.receive();
  }

  // ask for the temerature  
  Wire.beginTransmission(address);  
  Wire.send(0xAA);  
  Wire.endTransmission();

  // request 2 bytes
  Wire.requestFrom(address, 2);
  // read first byte 

  int temp = Wire.receive();
  // read second byte
  int frac = Wire.receive();

  Serial.print(temp);
  Serial.print( "." );

  frac = 100 * (frac & 0xF0 )/ 256;
  if ( frac < 10 ) {
    Serial.print("0");
  }
  Serial.println( frac );

  delay(1000);
}
