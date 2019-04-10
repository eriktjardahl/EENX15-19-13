
#include "Arduino.h"
#include "robot.h"

char input = 'b';

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
    break;

  case 'd': // Nicka
    break;
  }
}
