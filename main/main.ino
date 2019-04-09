
#include "Arduino.h"
#include "robot.h"

char input = 'a';

void setup()
{
  // put your setup code here, to run once:
  jointArmLeft.SETUP();
  jointArmRight.SETUP();
  jointNeck.SETUP();
  jointArmRight.rock();
}

void loop()
{

  switch (input)
  {
  case 'a': //Sten sax påse
    jointArmRight.rock();
    break;

  case 'b': //Vinka
    break;

  case 'c': // High-Five
    break;

  case 'd': // Nicka
    break;
  }
}
