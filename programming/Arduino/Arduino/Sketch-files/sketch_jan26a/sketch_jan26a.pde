/*  PS2Keyboard library example
  
  PS2Keyboard now requries both pins specified for begin()

  keyboard.begin(data_pin, irq_pin);
  
  Valid irq pins:
     Arduino:      2, 3
     Arduino Mega: 2, 3, 18, 19, 20, 21
     Teensy 1.0:   0, 1, 2, 3, 4, 6, 7, 16
     Teensy 2.0:   5, 6, 7, 8
     Teensy++ 1.0: 0, 1, 2, 3, 18, 19, 36, 37
     Teensy++ 2.0: 0, 1, 2, 3, 18, 19, 36, 37
     Sanguino:     2, 10, 11
  
  for more information you can read the original wiki in arduino.cc
  at http://www.arduino.cc/playground/Main/PS2Keyboard
  or http://www.pjrc.com/teensy/td_libs_PS2Keyboard.html
  
  Like the Original library and example this is under LGPL license.
  
  Modified by Cuninganreset@gmail.com on 2010-03-22
  Modified by Paul Stoffregen <paul@pjrc.com> June 2010
*/
   
#include <PS2Keyboard.h>
#include <SdFat.h>

const int DataPin = 3;
const int IRQpin =  2;


SdFat card;
SdFile file;
PS2Keyboard keyboard;

void setup() {
  delay(1000);
  keyboard.begin(DataPin, IRQpin);
  Serial.begin(9600);
  Serial.println("Keyboard Test:");
 
  if (!card.init(SPI_HALF_SPEED, 4)) Serial.println("failed");

  // open the file for write at end like the Native SD library
  if (!file.open("log.txt", O_RDWR | O_CREAT | O_AT_END)) {
    Serial.println("opening log.txt for write failed");
  }
  // if the file opened okay, write to it:
 file.println("-----------------------------");
}

void loop() {
  if (keyboard.available()) {
    
    // read the next key
    char c = keyboard.read();
    
    // check for some of the special keys
    if (c == PS2_ENTER) {
      file.println();
    } else if (c == PS2_TAB) {
      file.print("[Tab]");
    } else if (c == PS2_ESC) {
      file.print("[ESC]");
    } else if (c == PS2_PAGEDOWN) {
      file.print("[PgDn]");
    } else if (c == PS2_PAGEUP) {
      file.print("[PgUp]");
    } else if (c == PS2_LEFTARROW) {
      file.print("[Left]");
    } else if (c == PS2_RIGHTARROW) {
      file.print("[Right]");
    } else if (c == PS2_UPARROW) {
      file.print("[Up]");
    } else if (c == PS2_DOWNARROW) {
      file.print("[Down]");
    } else if (c == PS2_DELETE) {
      file.print("[Del]");
    } else {
      
      // otherwise, just print all normal characters
      file.print(c);
      Serial.print(c);
    }
    
     file.close();
     file.open("log.txt", O_RDWR | O_CREAT | O_AT_END);
  }
}
