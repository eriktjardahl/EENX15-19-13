
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
  Serial.begin(115200);
}

void loop()
{
  switch (input)
  {
  case 'a': //Påse
    jointArmRight.open();
    
    break;

  case 'b': //Reset
    jointArmLeft.test();
    break;

  case 'c': // Ok
    jointArmRight.ok();
    break;

  case 'd': // sten
    jointArmRight.armMotionSSP();
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
