
#include "Arduino.h"
#include "robot.h"


void setup() {
  // put your setup code here, to run once:
  jointArm.SETUP();
  jointNeck.SETUP();
}

void loop() {
  
switch (input_signal) {
      case 'a':  //Sten sax påse
      break;
      
      case 'b':   //Vinka  
      break;
      
      case 'c':    // High-Five
      break;
      
      case 'd': // Nicka
      break;
  }     

}
