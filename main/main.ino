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
    lastCommand = command;
    break;

  case 'b': //sax
    jointArmRight.close();
    jointArmRight.armMotionSSP();
    jointArmRight.scissor();
    lastCommand = command;
    break;

  case 'c': // sten
    jointArmRight.close();
    jointArmRight.armMotionSSP();
    jointArmRight.rock();
    lastCommand = command;
    break;

  case 'd': //ok
    jointArmRight.perpendicular();
    jointArmRight.ShoulderPitchPerp();
    jointArmRight.ok();
    lastCommand = command;
    break;

  case 'e': // DAB
    
    jointArmRight.dab();
    jointArmLeft.maxElbow();
    jointArmLeft.dabPart1();
    multiPart.dab();
    lastCommand = command;
    break;

  case 'f': // fuck
    jointArmRight.perpendicular();
    jointArmRight.ShoulderPitchPerp();
    jointArmRight.fack();
    jointNeck.neckYawLookRight();
    lastCommand = command;
    break;

  case 'g': //test
    jointArmLeft.test();
    break;

  case 'h':
    jointNeck.nod();
    lastCommand = command;
    break;

  case 'i': 
    jointNeck.shake();
    lastCommand = command;
    break;

  case 'k':
    jointNeck.neckPitchDown();
    lastCommand = command;
    break;  

  case 'l':
    jointNeck.wakeUp();
    break;

  case 'o':
    jointArmRight.open();
    jointArmLeft.open();
    lastCommand = command;
    break;

  case 'p':
    jointArmRight.close();
    jointArmLeft.close();
    lastCommand = command;
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
    lastCommand = command;
    break;

  case 'u':
    jointNeck.neckYawLookLeft();
    lastCommand = command;
    break;

  case 'v':
    jointNeck.neckYawLookRight();
    lastCommand = command;
    break;

  case 'w':
    jointNeck.neckRollTiltLeft();
    lastCommand = command;
   break;

  case 'x':
    jointNeck.neckRollTiltRight();
    lastCommand = command;
    break;

  case 'y':
    jointNeck.wakeDown();
    lastCommand = command;
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