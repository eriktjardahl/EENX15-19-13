
#include "Arduino.h"
#include "robot.h"

<<<<<<< HEAD
//char input = 'e';
//char LastCase = 'e';
char lastCommand;
=======
char input='s';
char LastCase='e';
>>>>>>> parent of f6b50c2... update

void setup()
{
  // put your setup code here, to run once:
  jointArmLeft.SETUP();
  jointArmRight.SETUP();
  jointNeck.SETUP();
  Serial.begin(115200);

  /* switch (input)
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
    multiPart.dab();
    //jointArmLeft.dabPart1();
    //jointArmLeft.ShoulderRollPerp();
    //jointArmRight.dab();
    //jointArmRight.ShoulderRollPerp();
    //jointArmLeft.dabPart2();
    //jointNeck.dab();
    break;

  case 'f': // fuck
    jointArmRight.fack();
    //LastCase=input;
    break;

  case 'g': //test
<<<<<<< HEAD
    jointNeck.dab();
=======
    
>>>>>>> parent of f6b50c2... update
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
  } */
}

void loop()
{
  //input=communication.readSerial();
  // Read the serial data sent to the arduino and chose command based on var sent
  switch (Communication.readSerial())
  {
  case 'a': //Påse
    jointArmRight.close();
    jointArmRight.armMotionSSP();
    jointArmRight.paper();
    //lastCase = input;
    lastCommand = 'a';
    break;

  case 'b': //sax
    jointArmRight.close();
    jointArmRight.armMotionSSP();
    jointArmRight.scissor();
    //LastCase=input;
    lastCommand = 'b';
    break;

  case 'c': // sten
    jointArmRight.close();
    jointArmRight.armMotionSSP();
    jointArmRight.rock();
    lastCommand = 'c';
    break;

  case 'd': //ok
    jointArmRight.ok();
    lastCommand = 'd';
    break;

  case 'e': // DAB
    jointArmLeft.dabPart1();
    jointArmLeft.ShoulderRollPerp();
    jointArmRight.dab();
    jointArmRight.ShoulderRollPerp();
    //multiPart.dab();
    //jointArmLeft.dabPart2();
    //jointNeck.dab();
    lastCommand = 'e';
    break;

  case 'f': // fuck
    jointArmRight.fack();
    //LastCase=input;
    lastCommand = 'f';
    break;

  case 'g': //test
    jointNeck.dab();
    lastCommand = 'g';
    break;

  case 'o':
    jointArmRight.open();
    lastCommand = 'o';
    break;

  case 'p':
    jointArmRight.close();
    lastCommand = 'p';
    break;

  case 'r': //reset högerarm
    jointArmRight.RESET(lastCommand);
    break;

  case 's': //reset nacke
    jointNeck.RESET(lastCommand);
    break;

  case 't': //reset vänsterarm
    jointArmLeft.RESET(lastCommand);
    break;

  case 'R': // Full reset
    jointArmRight.RESET(lastCommand);
    jointNeck.RESET(lastCommand);
    jointArmLeft.RESET(lastCommand);
    break;

  default: // If unknown command or not a character print the following message
    Serial.println("Unknown command or wrong format!");
    break;
  }
  
  // Show what command was sent
  Communication.showNewData();
}
