#include "Arduino.h"
#include "robot.h"

//char input = 'e';
//char LastCase = 'e';
//int a;
//char dataString[50];
char lastCommand;
char incoming;
boolean newData = false;
char input='s';
char LastCase='e';

void setup()
{
  // put your setup code here, to run once:
  jointArmLeft.SETUP();
  jointArmRight.SETUP();
  jointNeck.SETUP();
  jointArmRight.ShoulderRollPerp();
  Serial.begin(9600);
}

void loop()
{
  //input=communication.readSerial();
  // Read the serial data sent to the arduino and chose command based on var sent
  //readSerial();
  //if (newData)
  //{
  //selectCommand('g');
  //}
}

void selectCommand(char command)
{
  //Show what command was sent
  newData = false;
  switch (command)
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
    break;

  case 'g': //test
    jointArmRight.ShoulderRollPerp();
    break;

  case 'o':
    jointArmRight.open();
    break;

  case 'p':
    jointArmRight.close();
    break;

  case 'r': //reset högerarm
    //Serial.println(lastCommand);
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
    //Serial.println("Unknown command or wrong format!");
    break;
  }
  //Serial.println(command);
  lastCommand = command;
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
/*
void sendSerial()
{
  a = 0;
  dataString[50] = {0};
  // Increment a every loop
  a++;
  // Convert a value to hexadecimal
  sprintf(dataString, "%02X", a);
  // Send the data to the serial stream
  Serial.println(dataString);
  // Delay before this method exits and can be ran again
  //delay(1000);
}
*/