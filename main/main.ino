
#include "Arduino.h"
#include "robot.h"


void setup() {
  // put your setup code here, to run once:
  jointArmLeft.SETUP();
  jointArmRight.SETUP();
  jointNeck.SETUP();
}

void loop() {

  jointArmRight.MOVE();

  jointNeck.dab();
    
  /*
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
  */  

}
