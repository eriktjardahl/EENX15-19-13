
#include "Arduino.h"
#include "robot.h"

char input = 'a';

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
  case 'a': //Sten sax påse
    jointArmRight.paper();
    break;

  case 'b': //Vinka
    jointArmRight.RESET();
    break;

  case 'c': // High-Five
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
