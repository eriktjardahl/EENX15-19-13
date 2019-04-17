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
int initPosHand;
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

int moveIntervall;
unsigned long revMillis;
unsigned long currentMillis;
int intervallTime;

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

  if (!ran)
  {
    

    ran = true;
  }
}

void JointArmClassRight::RESET()
{

  int initPosArm = 0;
  int maxPosHand = 800;

  if (!ran)
  {
    elbowRight.setPosition(initPosArm, playtime + 1000);
    shoulderRightPitch.setPosition(initPosArm, playtime + 1000);
    shoulderRightYaw.setPosition(initPosArm, playtime + 1000);
    switch (lastCase)
    {
    case 'a': //påse färdig
      moveIntervall = 800;
      revMillis = 0;
      currentMillis = millis();
      intervallTime = 10;
      initPosHand = 0;

      for (int i = initPosHand; i < moveIntervall; i += 100)
      {

        servoRight.moveJoint(middleFingerRight, i);
        servoRight.LED(middleFingerRight, &rgb[1]);

        revMillis = millis();
        currentMillis = millis();
        while (currentMillis - revMillis <= intervallTime)
        {
          currentMillis = millis();
        }
        servoRight.moveJoint(ringFingerRight, i);
        servoRight.LED(ringFingerRight, &rgb[1]);

        revMillis = millis();
        currentMillis = millis();
        while (currentMillis - revMillis <= intervallTime)
        {
          currentMillis = millis();
        }
        servoRight.moveJoint(littleFingerRight, i);
        servoRight.LED(littleFingerRight, &rgb[1]);

        revMillis = millis();
        currentMillis = millis();
        while (currentMillis - revMillis <= intervallTime)
        {
          currentMillis = millis();
        }
        servoRight.moveJoint(thumbRight, i);
        servoRight.LED(thumbRight, &rgb[1]);

        revMillis = millis();
        currentMillis = millis();
        while (currentMillis - revMillis <= intervallTime)
        {
          currentMillis = millis();
        }

        servoRight.moveJoint(indexFingerRight, i);
        servoRight.LED(indexFingerRight, &rgb[1]);

        revMillis = millis();
        currentMillis = millis();
        while (currentMillis - revMillis <= intervallTime)
        {
          currentMillis = millis();
        }
      }

      break;

    case 'b': //sax färdig
      moveIntervall = 800;
      revMillis = 0;
      currentMillis = millis();
      intervallTime = 10;
      initPosHand = 0;

      for (int i = initPosHand; i < moveIntervall; i += 100)
      {

        servoRight.moveJoint(indexFingerRight, i);
        servoRight.LED(indexFingerRight, &rgb[1]);

        revMillis = millis();
        currentMillis = millis();
        while (currentMillis - revMillis <= intervallTime)
        {
          currentMillis = millis();
        }

        servoRight.moveJoint(middleFingerRight, i);
        servoRight.LED(middleFingerRight, &rgb[1]);

        revMillis = millis();
        currentMillis = millis();
        while (currentMillis - revMillis <= intervallTime)
        {
          currentMillis = millis();
        }
      }

      break;

    case 'c': //sten

      break;
    case 'd': //else

      break;
    }

    ran = true;
  }
}

void JointArmClassRight::dab()
{

  if (!ran)
  {

    ran = true;
  }
}

//---------------------------------HandRight-------------------------------------------------//
void JointArmClassRight::rock() // lastCase = c
{
  char lastCase = 'c';
}
void JointArmClassRight::scissor() //lastCase = b färdig
{

  if (!ran)
  {
    moveIntervall = 0;
    revMillis = 0;
    currentMillis = millis();
    intervallTime = 10;
    initPosHand = 800;

    for (int i = initPosHand; i > moveIntervall; i -= 100)
    {

      servoRight.moveJoint(indexFingerRight, i);
      servoRight.LED(indexFingerRight, &rgb[1]);

      revMillis = millis();
      currentMillis = millis();
      while (currentMillis - revMillis <= intervallTime)
      {
        currentMillis = millis();
      }

      servoRight.moveJoint(middleFingerRight, i);
      servoRight.LED(middleFingerRight, &rgb[1]);

      revMillis = millis();
      currentMillis = millis();
      while (currentMillis - revMillis <= intervallTime)
      {
        currentMillis = millis();
      }
    }
    char lastCase = 'b';
    ran = true;
  }
}

void JointArmClassRight::paper() // lastCase = a
{

  if (!ran)
  {

    ran = true;
  }
}

void JointArmClassRight::ok()
{

  if (!ran)
  {

    ran = true;
  }
}

void JointArmClassRight::open() //färdig lastCase = o
{

  lastCase = 'o';

  if (!ran)
  {
    moveIntervall = 0;
    revMillis = 0;
    currentMillis = millis();
    intervallTime = 10;
    initPosHand = 800;

    for (int i = initPosHand; i > moveIntervall; i -= 100)
    {

      servoRight.moveJoint(middleFingerRight, i);
      servoRight.LED(middleFingerRight, &rgb[1]);

      revMillis = millis();
      currentMillis = millis();
      while (currentMillis - revMillis <= intervallTime)
      {
        currentMillis = millis();
      }
      servoRight.moveJoint(ringFingerRight, i);
      servoRight.LED(ringFingerRight, &rgb[1]);

      revMillis = millis();
      currentMillis = millis();
      while (currentMillis - revMillis <= intervallTime)
      {
        currentMillis = millis();
      }
      servoRight.moveJoint(littleFingerRight, i);
      servoRight.LED(littleFingerRight, &rgb[1]);

      revMillis = millis();
      currentMillis = millis();
      while (currentMillis - revMillis <= intervallTime)
      {
        currentMillis = millis();
      }
      servoRight.moveJoint(thumbRight, i);
      servoRight.LED(thumbRight, &rgb[1]);

      revMillis = millis();
      currentMillis = millis();
      while (currentMillis - revMillis <= intervallTime)
      {
        currentMillis = millis();
      }

      servoRight.moveJoint(indexFingerRight, i);
      servoRight.LED(indexFingerRight, &rgb[1]);

      revMillis = millis();
      currentMillis = millis();
      while (currentMillis - revMillis <= intervallTime)
      {
        currentMillis = millis();
      }
    }
    ran = true;
  }
}

void JointArmClassRight::fack()
{
  lastCase = 'f';
  if (!ran)
  {

    ran = true;
  }
}

void JointArmClassRight::close() //färdig lastCase = p
{

  if (!ran)
  {
    moveIntervall = 800;
    revMillis = 0;
    currentMillis = millis();
    intervallTime = 10;
    initPosHand = 0;

    for (int i = initPosHand; i < moveIntervall; i += 100)
    {

      servoRight.moveJoint(middleFingerRight, i);
      servoRight.LED(middleFingerRight, &rgb[1]);

      revMillis = millis();
      currentMillis = millis();
      while (currentMillis - revMillis <= intervallTime)
      {
        currentMillis = millis();
      }
      servoRight.moveJoint(ringFingerRight, i);
      servoRight.LED(ringFingerRight, &rgb[1]);

      revMillis = millis();
      currentMillis = millis();
      while (currentMillis - revMillis <= intervallTime)
      {
        currentMillis = millis();
      }
      servoRight.moveJoint(littleFingerRight, i);
      servoRight.LED(littleFingerRight, &rgb[1]);

      revMillis = millis();
      currentMillis = millis();
      while (currentMillis - revMillis <= intervallTime)
      {
        currentMillis = millis();
      }
      servoRight.moveJoint(thumbRight, i);
      servoRight.LED(thumbRight, &rgb[1]);

      revMillis = millis();
      currentMillis = millis();
      while (currentMillis - revMillis <= intervallTime)
      {
        currentMillis = millis();
      }

      servoRight.moveJoint(indexFingerRight, i);
      servoRight.LED(indexFingerRight, &rgb[1]);

      revMillis = millis();
      currentMillis = millis();
      while (currentMillis - revMillis <= intervallTime)
      {
        currentMillis = millis();
      }
    }
    ran = true;
  }
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

  initPosHand = 0; // initsiera positioner
  stopPos = 1023;
  posYaw = 0;
  posPitch = 0;

  shoulderLeftPitch.setPosition(posPitch, playtime); //initierar axelpositionerna och sedan är de stela
  shoulderLeftYaw.setPosition(posYaw, playtime);

  for (int i = 0; i <= 2; i++)
  {
    for (int pos = initPosHand; pos <= stopPos; pos += 10)
    {
      elbowLeft.setPosition(pos, playtime);
    }
    elbowLeft.setPosition(initPosHand, playtime);
  }
}

void JointArmClassLeft::RESET()
{
  int initPos = 0;

  elbowLeft.setPosition(initPos, playtime);
  shoulderLeftPitch.setPosition(initPos, playtime);
  shoulderLeftYaw.setPosition(initPos, playtime);

  for (int i = littleFingerLeft; i < thumbLeft + 1; i++)
  {
    servoLeft.moveJoint(i, initPos);
  }
}

void JointArmClassLeft::dab()
{
  int initPos = 0;

  int endPosYawShoulder = 1023;

  for (int i = initPos; i <= endPosYawShoulder; i++)
  {
    shoulderLeftYaw.setPosition(i, playtime);
  }
}
//---------------------------------HandLeft--------------------------------------------------//

void JointArmClassLeft::rock()
{
  int initPos = 0;
  stopPos = 1023;
  initPosArm = 0;
  stopPosArm = 1023;

  for (int pos = initPos; pos <= stopPos; pos += 10)
  {
    for (int i = littleFingerLeft; i <= thumbLeft; i++)
    {
      servoLeft.moveJoint(i, pos);
    }
  }
  for (int pos = initPosArm; pos <= stopPosArm; pos += 10)
  {
    elbowRight.setPosition(pos, playtime);
  }
}
void JointArmClassLeft::scissor()
{
  int initPos = 0;
  stopPos = 1023;
  initPosArm = 0;
  stopPosArm = 1023;

  for (int pos = initPos; pos <= stopPos; pos += 10)
  {
    for (int i = littleFingerLeft; i <= thumbLeft; i++)
    {
      if (i == littleFingerLeft || i == ringFingerLeft || i == thumbLeft)
        servoLeft.moveJoint(i, pos);
    }
  }
  for (int pos = initPosArm; pos <= stopPosArm; pos += 10)
  {
    elbowRight.setPosition(pos, playtime);
  }
}

void JointArmClassLeft::paper()
{
  int initPosArm = 0;
  stopPosArm = 1023;
  for (int pos = initPosArm; pos <= stopPosArm; pos += 10)
  {
    elbowRight.setPosition(pos, playtime);
  }
}

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

  int initPos = 0;
  stopPos = 100;

  for (int i = initPos; i <= stopPos; i++)
  {
    servoNeck.moveJoint(neckPitch, i);
  }
}

void JointNeckClass::dab()
{

  int initPos = 0;
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
