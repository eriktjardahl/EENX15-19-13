
#include "Arduino.h"
#include "robot.h"

char input = 'f';
//char LastCase;

void setup()
{
  // put your setup code here, to run once:
  jointArmLeft.SETUP();
  jointArmRight.SETUP();
  jointNeck.SETUP();
  Serial.begin(115200);

  switch (input)
  {
  case 'a': //Påse
    jointArmRight.close();
    jointArmRight.armMotionSSP();
    jointArmRight.paper();
    
    break;

  case 'b': //sax
    jointArmRight.close();
    jointArmRight.armMotionSSP();
    jointArmRight.scissor();

    break;

  case 'c': // sten
    jointArmRight.close();
    jointArmRight.armMotionSSP();
    jointArmRight.rock();
    break;

  case 'd': // test
    jointArmRight.ok();
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
    jointArmRight.RESET(/*LastCase*/);
    break;
  }
}

void loop()
{
}
