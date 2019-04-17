
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
    jointArmRight.paper();
    
    break;

  case 'b': //sax
    jointArmRight.scissor();
    break;

  case 'c': // sten
    jointArmRight.rock();
    break;

  case 'd': // test
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

  case 'o':
    jointArmRight.open();
  break;

  case 'p':
    jointArmRight.close();
  break;

  case 'r': //reset
    jointArmRight.RESET();
    break;

  }
}
