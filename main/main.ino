
#include "Arduino.h"
#include "robot.h"

char input = 'd';
//char lastCase ='a';

void setup()
{
  // put your setup code here, to run once:
  jointArmLeft.SETUP();
  jointArmRight.SETUP();
  jointNeck.SETUP();
}

void loop()
{
  switch (input)
  {
  case 'a': //Påse
    jointArmRight.open();
    
    break;

  case 'b': //Reset
    jointArmLeft.RESET();
    break;

  case 'c': // Ok
    jointArmRight.ok();
    break;

  case 'd': // sten
    
    jointArmLeft.scissor();
    break;

  case 'e': // DAB
    jointNeck.dab();
    jointArmLeft.dab();
    jointArmRight.dab();
    break;

  case 'f': // fuck
    jointArmRight.fack();
    break;
  }
}
