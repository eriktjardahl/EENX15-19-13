#include "Arduino.h"
#include "robot.h"

char lastCommand;
char incoming;
boolean newData = false;

void setup()
{
  // put your setup code here, to run once:
  jointArmLeft.SETUP();
  jointArmRight.SETUP();
  jointNeck.SETUP();
  Serial.begin(9600);
}

void loop()
{
  // Read the serial data sent to the arduino and chose command based on var sent
  readSerial();
  if (newData)
  {
    selectCommand(incoming);
  }
}

void selectCommand(char command)
{
  //Show what command was sent
  showNewData();
  switch (command)
  {
  case 'a': //Påse
    jointArmRight.close();
    jointArmRight.armMotionSSP();
    jointArmRight.paper();
    lastCommand='a';
    break;

  case 'b': //sax
    jointArmRight.close();
    jointArmRight.armMotionSSP();
    jointArmRight.scissor();
    lastCommand='b';
    break;

  case 'c': // sten
    jointArmRight.close();
    jointArmRight.armMotionSSP();
    jointArmRight.rock();
    lastCommand='c';
    break;

  case 'd': //ok
    jointArmRight.perpendicular();
    jointArmRight.ShoulderPitchPerp();
    jointArmRight.ok();
    lastCommand='d';
    break;

  case 'e': // DAB
    
    jointArmRight.dab();
    jointArmLeft.maxElbow();
    jointArmLeft.dabPart1();
    multiPart.dab();
    lastCommand='e';
    break;

  case 'f': // fuck

    jointArmRight.perpendicular();
    jointArmRight.ShoulderPitchPerp();
    jointArmRight.fack();
    jointNeck.neckYawLookRight();
    lastCommand='f';
    break;

  case 'g': //test
    jointArmLeft.test();
    break;

  case 'h':
    jointNeck.nod();
    lastCommand='h';
    break;

  case 'i': 
    jointNeck.shake();
    lastCommand='i';
    break;

  case 'k':
    jointNeck.neckPitchDown();
    lastCommand = 'k';
    break;  

  case 'l':
    jointNeck.wakeUp();
    break;

  case 'o':
    jointArmRight.open();
    jointArmLeft.open();
    lastCommand='o';
    break;

  case 'p':
    jointArmRight.close();
    jointArmLeft.close();
    lastCommand='p';
    break;

  case 'q': //reset vänsterarm
    jointArmLeft.RESET(lastCommand);
    break;

  case 'r': //reset högerarm
    jointArmRight.RESET(lastCommand);
    break;

  case 's': //reset nacke
    
    jointNeck.RESET(lastCommand);
    break;

  case 't': //titta uppåt
    jointNeck.neckPitchUp();
    lastCommand='t';
    break;

  case 'u':
    jointNeck.neckYawLookLeft();
    lastCommand='u';
    break;

  case 'v':
    jointNeck.neckYawLookRight();
    lastCommand='v';
    break;

  case 'w':
    jointNeck.neckRollTiltLeft();
    lastCommand='w';
   break;

  case 'x':
    jointNeck.neckRollTiltRight();
    lastCommand='x';
    break;

  case 'y':
    jointNeck.wakeDown();
    lastCommand='y';
    break;

  case 'R': // Full reset
    jointArmRight.RESET(lastCommand);
    jointArmLeft.RESET(lastCommand);
    jointNeck.RESET(lastCommand);
    break;

  default: // If unknown command or not a character print the following message
    //Serial.println("Unknown command or wrong format!");
    break;
  }
  //lastCommand = command;
}

char readSerial()
{
  // Send data only when you receive data:
  while (Serial.available() > 0)
  {
    // Read the incoming byte and write to our variable incoming
    incoming = Serial.read();
    // Flag newData as true to enable showNewData to run
    newData = true;
  }
  return incoming;
}

void showNewData()
{
  // Only run if there is new data in the Serial stream.
  if (newData == true)
  {
    // Print current value sent from the raspberry pi
    //Serial.print("This just in ... ");
    Serial.println(incoming);
    newData = false;
  }
  delay(10);
}