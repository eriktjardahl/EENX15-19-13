
#include "Arduino.h"
#include "robot.h"

char input = 'd';

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
    jointArmRight.RESET();
    break;

  case 'c': // Ok
    jointArmRight.ok();
    break;

  case 'd': // Nicka
    jointArmRight.rock();
    break;

  case 'e': // DAB
    jointNeck.dab();
    jointArmLeft.dab();
    jointArmRight.dab();
    break;
  }
}
