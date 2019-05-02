
#include "Arduino.h"
#include "robot.h"

char input='e';
char LastCase='e';

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
    //lastCase = input;
    break;

  case 'b': //sax
    jointArmRight.close();
    jointArmRight.armMotionSSP();
    jointArmRight.scissor();
    //LastCase=input;
    break;

  case 'c': // sten
    jointArmRight.close();
    jointArmRight.armMotionSSP();
    jointArmRight.rock();
    break;

  case 'd': //ok
    jointArmRight.ok();
    break;

  case 'e': // DAB
    jointNeck.dab();
    //jointArmLeft.dab();
    //jointArmLeft.ShoulderRollPerp();
    //jointArmRight.dab();
    //jointArmRight.ShoulderRollPerp();
    
    break;

  case 'f': // fuck
    jointArmRight.fack();
    //LastCase=input;
    break;

  case 'g': //test
    jointArmRight.dab();
    jointArmRight.ShoulderRollPerp();
    break;

  case 'o':
    jointArmRight.open();
    break;

  case 'p':
    jointArmRight.close();
    break;

  case 'r': //reset högerarm
    jointArmRight.RESET(LastCase);
    break;

  case 's': //reset nacke
    jointNeck.RESET(LastCase);
    break;

  case 't':
    jointArmLeft.RESET(LastCase);
    break;
  }
  
  
}

void loop()
{
  //input=communication.readSerial();
}
