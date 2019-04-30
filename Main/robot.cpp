#include "Arduino.h"
#include "robot.h"

//-------------------------------------Initiera alla motorer------------------------------------------------//

SoftwareSerial A116servoSerial = SoftwareSerial(rxPin1, txPin2);    //Höger arm, typ max pos armbåge = 300
SoftwareSerial A116servo2Serial = SoftwareSerial(rxPin10, txPin11); //Vänster arm
SoftwareSerial XL320servoSerial = SoftwareSerial(rxPin3, txPin4);   //Vänster hand
SoftwareSerial XL320servo2Serial = SoftwareSerial(rxPin6, txPin7);  //Höger hand, typ max pos finger 850
SoftwareSerial XL320servo3Serial = SoftwareSerial(rxPin8, txPin9);  //Nacke

XYZrobotServo elbowRight(A116servoSerial, 1);
XYZrobotServo shoulderRightPitch(A116servoSerial, 2);
//XYZrobotServo servo3(A116servoSerial,3);
XYZrobotServo shoulderRightYaw(A116servoSerial, 4);
XYZrobotServo elbowLeft(A116servo2Serial, 5);
XYZrobotServo shoulderLeftPitch(A116servo2Serial, 6);
XYZrobotServo shoulderLeftYaw(A116servo2Serial, 7);

// Declaration of init variables
int initPos;
int initPosArm;
int initPosJaw;
int initPosRoll;
int initPosPitch;

// Declaration of stop position variables
int stopPos;
int stopPosArm;

// Declaration of axis positions
int posYaw;
int posPitch;

XL320 servoLeft;
/*
  Vänster hand
  lillfinger .   ID:1
  ringfinger     ID:2
  långfinger    ID:3
  pekfinger     ID:4
  tummer        ID:5
 */

XL320 servoRight;
/*
  Höger hand
  lillfinger .   ID:6
  ringfinger     ID:7
  långfinger    ID:8
  pekfinger     ID:9
  tummer        ID:10
 */

XL320 servoNeck;
/*
 * Id 11-14 Nack rotationer. 
 */

boolean ran = false;
char lastCase = 'a';

char rgb[] = "rgbypcwo";

int intervall = 50000;

unsigned long timeMillis1;
  
unsigned long timeMillis2;
unsigned long timeMillis3;
unsigned long timeMillis4;
unsigned long timeMillis5;

//---------------------------------Communication--------------------------------------------------//
Communication::Communication()
{
}
void Communication::readSerial()

{
  int a = 0;
  char dataString[50] = {0};

  boolean newData = false;
  char incoming;
  // Send data only when you receive data:
  if (Serial.available() > 0)
  {
    // Read the incoming byte and write to our variable incoming
    incoming = Serial.read();
    // Flag newData as true to enable showNewData to run
    newData = true;
  }
}

void Communication::showNewData()
{
  int a = 0;
  char dataString[50] = {0};

  boolean newData = false;
  char incoming;
  // Only run if there is new data in the Serial stream.
  if (newData == true)
  {
    // Print current value sent from the raspberry pi
    Serial.print("This just in ... ");
    Serial.println(incoming);
    newData = false;
  }
}

void Communication::sendSerial()
{
  int a = 0;
  char dataString[50] = {0};

  boolean newData = false;
  char incoming;
  // Increment a every loop
  a++;
  // Convert a value to hexadecimal
  sprintf(dataString, "%02X", a);
  // Send the data to the serial stream
  Serial.println(dataString);
  // Delay before this method exits and can be ran again
  delay(1000);
}

unsigned long getMillis()
{
  return millis();
}

//---------------------------------Communication--------------------------------------------------//

//---------------------------------Arm_RIGHT-------------------------------------------------//

JointArmClassRight::JointArmClassRight()
{
}

void JointArmClassRight::SETUP()
{

  pinMode(rxPin6, INPUT);
  pinMode(txPin7, OUTPUT);
  pinMode(rxPin1, INPUT);
  pinMode(txPin2, OUTPUT);

  A116servo2Serial.begin(115200);  // höger arm
  XL320servo2Serial.begin(115200); // höger hand

  servoRight.begin(XL320servo2Serial);
  servoRight.setJointSpeed(littleFingerRight, 1023);
  servoRight.setJointSpeed(ringFingerRight, 1023);
  servoRight.setJointSpeed(middleFingerRight, 1023);
  servoRight.setJointSpeed(indexFingerRight, 1023);
  servoRight.setJointSpeed(thumbRight, 1023);
}

void JointArmClassRight::armMotionSSP()
{
  int initPos = 0; // initsiera positioner
  int stopPos = 300;

  if (!ran)
  {
    shoulderRightPitch.setPosition(initPos, playtime + 100); //initierar axelpositionerna och sedan är de stela
    shoulderRightYaw.setPosition(initPos, playtime + 100);
    delay(playtime + 100);

    for (int i = 0; i < 4; i++)
    {
      if (i == 0 || i == 2)
      {
        for (int j = initPos; j <= stopPos; j++)
        {
          elbowRight.setPosition(j, playtime);
          delay(playtime);
        }
      }
      else if (i == 1 || i == 3)
      {
        for (int j = stopPos; j >= initPos; j--)
        {
          elbowRight.setPosition(j, playtime);
          delay(playtime);
        }
      }
    }
    ran = true;
  }
}

void JointArmClassRight::RESET()
{
  
  int initPosArm = 0;
  int initPosHand = 0;
  int maxPosHand = 800;

  if (!ran)
  {
    elbowRight.setPosition(initPosArm, playtime + 1000);
    shoulderRightPitch.setPosition(initPosArm, playtime + 1000);
    shoulderRightYaw.setPosition(initPosArm, playtime + 1000);
    switch (lastCase)
    {
    case 'a'://påse
      for (int i = initPosHand; i <= maxPosHand; i = i + 2)
    {
      servoRight.moveJoint(thumbRight, i);
      servoRight.LED(thumbRight, &rgb[random(0, 7)]);
      servoRight.moveJoint(indexFingerRight, i);
      servoRight.LED(indexFingerRight, &rgb[random(0, 7)]);
      servoRight.moveJoint(middleFingerRight, i);
      servoRight.LED(middleFingerRight, &rgb[random(0, 7)]);
      servoRight.moveJoint(ringFingerRight, i);
      servoRight.LED(ringFingerRight, &rgb[random(0, 7)]);
      servoRight.moveJoint(littleFingerRight, i);
      servoRight.LED(littleFingerRight, &rgb[random(0, 7)]);
    }
      break;

    case 'b'://sax
      for (int i = initPosHand; i <= maxPosHand; i = i + 2)
    {
      servoRight.moveJoint(indexFingerRight, i);
      servoRight.LED(indexFingerRight, &rgb[random(0, 7)]);
      servoRight.moveJoint(middleFingerRight, i);
      servoRight.LED(middleFingerRight, &rgb[random(0, 7)]);
    }
      break;

    case 'c'://sten 
  
        break;
    case 'd': //else
      for (int i = initPosHand; i <= maxPosHand; i = i + 2)
    {
      servoRight.moveJoint(thumbRight, i);
      servoRight.LED(thumbRight, &rgb[random(0, 7)]);
      servoRight.moveJoint(indexFingerRight, i);
      servoRight.LED(indexFingerRight, &rgb[random(0, 7)]);
      servoRight.moveJoint(middleFingerRight, i);
      servoRight.LED(middleFingerRight, &rgb[random(0, 7)]);
      servoRight.moveJoint(ringFingerRight, i);
      servoRight.LED(ringFingerRight, &rgb[random(0, 7)]);
      servoRight.moveJoint(littleFingerRight, i);
      servoRight.LED(littleFingerRight, &rgb[random(0, 7)]);
    }
      break;

       
    }

   

    
    ran = true;
  }
}

void JointArmClassRight::dab()
{
  initPos = 0;
  int endPosYawShoulder = 1023;
  int endPosPitchElbow = 1023;

  if (!ran)
  {
    for (int i = initPos, j = initPos; i <= endPosYawShoulder, j <= endPosPitchElbow; i++, j++)
    {
      elbowRight.setPosition(j, playtime);
      delay(playtime);
      shoulderRightYaw.setPosition(i, playtime);
      delay(playtime);
    }
    ran = true;
  }
}

//---------------------------------HandRight-------------------------------------------------//
void JointArmClassRight::rock() // char = c
{
  char lastCase = 'c';
  if (!ran)
  {
    int intervall1 = 100;

    for (int i = 0; i <= 900; i += 1)
    {
      timeMillis1 = 0;
      timeMillis2 = 0;
      timeMillis3 = 0;
      timeMillis4 = 0;
      timeMillis5 = 0;

      if ((unsigned long)(millis() > timeMillis1 + intervall1))
      {
        
        servoRight.moveJoint(6, i);
        servoRight.LED(6, &rgb[random(0, 7)]);
        timeMillis1 = millis();
      }

      if ((unsigned long)(millis() > timeMillis2 + intervall1))
      {
        timeMillis2 = millis();
        servoRight.moveJoint(7, i);
        servoRight.LED(7, &rgb[random(0, 7)]);
      }

      if ((unsigned long)(millis() > timeMillis3 + intervall1))
      {
        timeMillis3 = millis();

        servoRight.moveJoint(8, i);
        servoRight.LED(8, &rgb[random(0, 7)]);
      }
      if ((unsigned long)(millis() > timeMillis4 + intervall1))
      {
        timeMillis4 = millis();

        servoRight.moveJoint(9, i);
        servoRight.LED(9, &rgb[random(0, 7)]);
      }
      if ((unsigned long)(millis() > timeMillis5 + intervall1))
      {
        timeMillis5 = millis();

        servoRight.moveJoint(10, i);
        servoRight.LED(10, &rgb[random(0, 7)]);
      }
    }

    /*
    int initPosHand = 0;
    int maxPosHand = 800;

    for (int i = initPosHand; i <= maxPosHand; i = i + 1)
    {
      servoRight.moveJoint(thumbRight, i);
      servoRight.LED(thumbRight, &rgb[random(0, 7)]);
      servoRight.moveJoint(indexFingerRight, i);
      servoRight.LED(indexFingerRight, &rgb[random(0, 7)]);
      servoRight.moveJoint(middleFingerRight, i);
      servoRight.LED(middleFingerRight, &rgb[random(0, 7)]);
      servoRight.moveJoint(ringFingerRight, i);
      servoRight.LED(ringFingerRight, &rgb[random(0, 7)]);
      servoRight.moveJoint(littleFingerRight, i);
      servoRight.LED(littleFingerRight, &rgb[random(0, 7)]);
    }*/
    ran = true;
  }
}
void JointArmClassRight::scissor() //ändra,,, char = b
{

  char lastCase = 'b';
  initPos = 0;
  stopPos = 1023;
  initPosArm = 0;
  stopPosArm = 1023;

  for (int pos = initPos; pos < stopPos; pos += 10)
  {
    for (int i = littleFingerRight; i <= thumbRight; i++)
    {
      if (i == littleFingerLeft || i == ringFingerRight || i == thumbRight)

        servoRight.moveJoint(i, pos);
    }
  }
  for (int pos = initPosArm; pos <= stopPosArm; pos += 10)
  {
    elbowRight.setPosition(pos, playtime);
  }
}

void JointArmClassRight::paper() // char = a
{

  char lastCase = 'a';
  initPos = 0;
  int maxPos = 300;

  int initPosArm = 0;
  int initPosHand = 850;
  int stopPosArm = 300;
  int stopPosHand = 0;

  if (!ran)
  {
    for (int i = initPosHand; i >= stopPosHand; i--)
    {
      servoRight.moveJoint(thumbRight, i);
      servoRight.LED(thumbRight, &rgb[random(0, 7)]);
      servoRight.moveJoint(indexFingerRight, i);
      servoRight.LED(indexFingerRight, &rgb[random(0, 7)]);
      servoRight.moveJoint(middleFingerRight, i);
      servoRight.LED(middleFingerRight, &rgb[random(0, 7)]);
      servoRight.moveJoint(ringFingerRight, i);
      servoRight.LED(ringFingerRight, &rgb[random(0, 7)]);
      servoRight.moveJoint(littleFingerRight, i);
      servoRight.LED(littleFingerRight, &rgb[random(0, 7)]);
    }
  }
  ran = true;
}

void JointArmClassRight::ok()
{
  initPos = 850;
  stopPos = 0;

  if (!ran)
  {
    for (int i = initPos; i >= stopPos; i--)
    {
      servoRight.moveJoint(thumbRight, i);
      servoRight.LED(thumbRight, &rgb[random(0, 7)]);
      servoRight.moveJoint(middleFingerRight, i);
      servoRight.LED(middleFingerRight, &rgb[random(0, 7)]);
      servoRight.moveJoint(ringFingerRight, i);
      servoRight.LED(ringFingerRight, &rgb[random(0, 7)]);
      servoRight.moveJoint(littleFingerRight, i);
      servoRight.LED(littleFingerRight, &rgb[random(0, 7)]);
    }
    ran = true;
  }
}

void JointArmClassRight::open()
{
  int initPosHand = 800;
  int stopPosHand = 0;

  if (!ran)
  {
    for (int i = initPosHand; i >= stopPosHand; i = i - 1)
    {
      servoRight.moveJoint(thumbRight, i);
      servoRight.LED(thumbRight, &rgb[random(0, 7)]);
      servoRight.moveJoint(indexFingerRight, i);
      servoRight.LED(indexFingerRight, &rgb[random(0, 7)]);
      servoRight.moveJoint(middleFingerRight, i);
      servoRight.LED(middleFingerRight, &rgb[random(0, 7)]);
      servoRight.moveJoint(ringFingerRight, i);
      servoRight.LED(ringFingerRight, &rgb[random(0, 7)]);
      servoRight.moveJoint(littleFingerRight, i);
      servoRight.LED(littleFingerRight, &rgb[random(0, 7)]);
    }
    ran = true;
  }
}

void JointArmClassRight::fack()
{
  /*
  int initPos = 800;
  int stopPos = 0;

  previousMillis = 0;
  currentMillis = getMillis();

  if (!ran)
  {
    if ((unsigned long)(currentMillis - previousMillis) >= intervall)
    {
      for (int i = initPos; i >= stopPos; i--)
      {
        servoRight.moveJoint(middleFingerRight, i);
        servoRight.LED(middleFingerRight, &rgb[random(0, 7)]);
      }
    }
    previousMillis = currentMillis;

    //ran = true;
  }
  */
}
//-------------------------------------Skriv armfunktioner över------------------------------------------------//

JointArmClassRight jointArmRight = JointArmClassRight();

//---------------------------------Arm_Left--------------------------------------------------//

JointArmClassLeft::JointArmClassLeft()
{
}

void JointArmClassLeft::SETUP()
{
  pinMode(rxPin10, INPUT);
  pinMode(txPin11, OUTPUT);
  pinMode(rxPin3, INPUT);
  pinMode(txPin4, OUTPUT);

  A116servoSerial.begin(115200);  //vänster arm
  XL320servoSerial.begin(115200); //vänster hand

  servoLeft.begin(XL320servoSerial);
  servoLeft.setJointSpeed(littleFingerLeft, 1023);
  servoLeft.setJointSpeed(ringFingerLeft, 1023);
  servoLeft.setJointSpeed(middleFingerLeft, 1023);
  servoLeft.setJointSpeed(indexFingerLeft, 1023);
  servoLeft.setJointSpeed(thumbLeft, 1023);
}

void JointArmClassLeft::armMotionSSP()
{
int initPos = 0; // initsiera positioner
  int stopPos = 300;

  if (!ran)
  {
    shoulderLeftPitch.setPosition(initPos, playtime + 100); //initierar axelpositionerna och sedan är de stela
    shoulderLeftYaw.setPosition(initPos, playtime + 100);
    delay(playtime + 100);

    for (int i = 0; i < 4; i++)
    {
      if (i == 0 || i == 2)
      {
        for (int j = initPos; j <= stopPos; j++)
        {
          elbowLeft.setPosition(j, playtime);
          delay(playtime);
        }
      }
      else if (i == 1 || i == 3)
      {
        for (int j = stopPos; j >= initPos; j--)
        {
          elbowLeft.setPosition(j, playtime);
          delay(playtime);
        }
      }
    }
    ran = true;
  }
}

void JointArmClassLeft::RESET()
{
  int initPosArm = 0;
  int initPosHand = 0;
  int maxPosHand = 800;

  if (!ran)
  {
    elbowRight.setPosition(initPosArm, playtime + 1000);
    shoulderRightPitch.setPosition(initPosArm, playtime + 1000);
    shoulderRightYaw.setPosition(initPosArm, playtime + 1000);
    switch (lastCase)
    {
    case 'a'://påse
      for (int i = initPosHand; i <= maxPosHand; i = i + 2)
    {
      servoRight.moveJoint(thumbRight, i);
      servoRight.LED(thumbRight, &rgb[random(0, 7)]);
      servoRight.moveJoint(indexFingerRight, i);
      servoRight.LED(indexFingerRight, &rgb[random(0, 7)]);
      servoRight.moveJoint(middleFingerRight, i);
      servoRight.LED(middleFingerRight, &rgb[random(0, 7)]);
      servoRight.moveJoint(ringFingerRight, i);
      servoRight.LED(ringFingerRight, &rgb[random(0, 7)]);
      servoRight.moveJoint(littleFingerRight, i);
      servoRight.LED(littleFingerRight, &rgb[random(0, 7)]);
    }
      break;

    case 'b'://sax
      for (int i = initPosHand; i <= maxPosHand; i = i + 2)
    {
      servoRight.moveJoint(indexFingerRight, i);
      servoRight.LED(indexFingerRight, &rgb[random(0, 7)]);
      servoRight.moveJoint(middleFingerRight, i);
      servoRight.LED(middleFingerRight, &rgb[random(0, 7)]);
    }
      break;

    case 'c'://sten 
  
        break;
    case 'd': //else
      for (int i = initPosHand; i <= maxPosHand; i = i + 2)
    {
      servoLeft.moveJoint(thumbLeft, i);
      servoLeft.LED(thumbLeft, &rgb[random(0, 7)]);
      servoLeft.moveJoint(indexFingerLeft, i);
      servoLeft.LED(indexFingerLeft, &rgb[random(0, 7)]);
      servoLeft.moveJoint(middleFingerLeft, i);
      servoLeft.LED(middleFingerLeft, &rgb[random(0, 7)]);
      servoLeft.moveJoint(ringFingerLeft, i);
      servoLeft.LED(ringFingerLeft, &rgb[random(0, 7)]);
      servoLeft.moveJoint(littleFingerLeft, i);
      servoLeft.LED(littleFingerLeft, &rgb[random(0, 7)]);
    }
      break;

       
    }

   

    
    ran = true;
  }
}

void JointArmClassLeft::dab()
{
  initPos = 0;
  int endPosYawShoulder = 1023;
  int endPosPitchElbow = 1023;

  if (!ran)
  {
    for (int i = initPos, j = initPos; i <= endPosYawShoulder, j <= endPosPitchElbow; i++, j++)
    {
      elbowLeft.setPosition(j, playtime);
      delay(playtime);
      shoulderLeftYaw.setPosition(i, playtime);
      delay(playtime);
    }
    ran = true;
  }
}
//---------------------------------HandLeft--------------------------------------------------//

void JointArmClassLeft::rock()
{
  boolean ran = false; 
  char lastCase = 'c';
  if (!ran)
  {
    int intervall1 = 100;

    for (int i = 0; i <= 900; i += 1)
    {
      timeMillis1 = 0;
      timeMillis2 = 0;
      timeMillis3 = 0;
      timeMillis4 = 0;
      timeMillis5 = 0;

      if ((unsigned long)(millis() > timeMillis1 + intervall1))
      {
        
        servoLeft.moveJoint(4, i);
        servoLeft.LED(4, &rgb[random(0, 7)]);
        timeMillis1 = millis();
      }

      if ((unsigned long)(millis() > timeMillis2 + intervall1))
      {
        timeMillis2 = millis();
        servoLeft.moveJoint(2, i);
        servoLeft.LED(2, &rgb[random(0, 7)]);
      }

      if ((unsigned long)(millis() > timeMillis3 + intervall1))
      {
        timeMillis3 = millis();

        servoLeft.moveJoint(3, i);
        servoLeft.LED(3, &rgb[random(0, 7)]);
      }
      if ((unsigned long)(millis() > timeMillis4 + intervall1))
      {
        timeMillis4 = millis();

        servoLeft.moveJoint(3, i);
        servoLeft.LED(3, &rgb[random(0, 7)]);
      }
      if ((unsigned long)(millis() > timeMillis5 + intervall1))
      {
        timeMillis5 = millis();

        servoLeft.moveJoint(3, i);
        servoLeft.LED(3, &rgb[random(0, 7)]);
      }
    }

    /*
    int initPosHand = 0;
    int maxPosHand = 800;

    for (int i = initPosHand; i <= maxPosHand; i = i + 1)
    {
      servoRight.moveJoint(thumbRight, i);
      servoRight.LED(thumbRight, &rgb[random(0, 7)]);
      servoRight.moveJoint(indexFingerRight, i);
      servoRight.LED(indexFingerRight, &rgb[random(0, 7)]);
      servoRight.moveJoint(middleFingerRight, i);
      servoRight.LED(middleFingerRight, &rgb[random(0, 7)]);
      servoRight.moveJoint(ringFingerRight, i);
      servoRight.LED(ringFingerRight, &rgb[random(0, 7)]);
      servoRight.moveJoint(littleFingerRight, i);
      servoRight.LED(littleFingerRight, &rgb[random(0, 7)]);
    }*/
    ran = true;
  }
}
void JointArmClassLeft::scissor()
{
   
  if(!ran)
  {
  
  

  for(int i = 0 ; i < 200000; i++)
  {
        servoLeft.LED(4, &rgb[1]);
        servoLeft.moveJoint(4, i%2047);
  }
  ran = true; 
  } 
  
}

void JointArmClassLeft::paper()
{
  
  char lastCase = 'a';
  initPos = 0;
  int maxPos = 300;

  int initPosArm = 0;
  int initPosHand = 850;
  int stopPosArm = 300;
  int stopPosHand = 0;

  if (!ran)
  {
    for (int i = initPosHand; i >= stopPosHand; i--)
    {
      servoLeft.moveJoint(thumbLeft, i);
      servoLeft.LED(thumbLeft, &rgb[1]);
      servoLeft.moveJoint(indexFingerLeft, i);
      servoLeft.LED(indexFingerLeft, &rgb[1]);
      servoLeft.moveJoint(middleFingerLeft, i);
      servoLeft.LED(middleFingerLeft, &rgb[1]);
      servoLeft.moveJoint(ringFingerLeft, i);
      servoLeft.LED(ringFingerLeft, &rgb[1]);
      servoLeft.moveJoint(littleFingerLeft, i);
      servoLeft.LED(littleFingerLeft, &rgb[1]);
    }
  }
  ran = true;
}

/*
void JointArmClassLeft::test()
{

  for (int i = 0; i < 1023; i++)
  {
    elbowLeft.setPosition(i, playtime);
    Serial.println(elbowLeft.readStatus().position);
  }
  uint16_t blob = elbowLeft.readStatus().position;

  Serial.println(blob);
}
*/

//-------------------------------------Skriv armfunktioner över------------------------------------------------//

JointArmClassLeft jointArmLeft = JointArmClassLeft();

//-------------------------------------Neck------------------------------------------------//

JointNeckClass::JointNeckClass()
{
}

void JointNeckClass::SETUP()
{
  pinMode(rxPin8, INPUT);
  pinMode(txPin9, OUTPUT);

  XL320servo3Serial.begin(115200);
  servoNeck.begin(XL320servo3Serial);
}

void JointNeckClass::nod()
{

  initPos = 0;
  stopPos = 100;

  for (int i = initPos; i <= stopPos; i++)
  {
    servoNeck.moveJoint(neckPitch, i);
  }
}

void JointNeckClass::dab()
{

  initPos = 0;
  stopPos = 1000;

  for (int i = initPos; i <= stopPos; i++)
  {
    servoNeck.moveJoint(neckJaw, i);
    servoNeck.moveJoint(neckPitch, i);
  }
}

void JointNeckClass::RESET()
{
  initPosJaw = 0;
  initPosRoll = 0;
  initPosPitch = 0;

  servoNeck.moveJoint(neckJaw, initPosJaw);
  servoNeck.moveJoint(neckRoll, initPosRoll);
  servoNeck.moveJoint(neckPitch, initPosPitch);
}

//-------------------------------------Skriv nackfunktioner över------------------------------------------------//

JointNeckClass jointNeck = JointNeckClass();
