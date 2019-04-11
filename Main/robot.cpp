#include "Arduino.h"
#include "robot.h"

//-------------------------------------Initiera alla motorer------------------------------------------------//

SoftwareSerial A116servoSerial = SoftwareSerial(rxPin1, txPin2);    //Höger arm
SoftwareSerial A116servo2Serial = SoftwareSerial(rxPin10, txPin11); //Väsnter arm
SoftwareSerial XL320servoSerial = SoftwareSerial(rxPin3, txPin4);   //Vänster hand
SoftwareSerial XL320servo2Serial = SoftwareSerial(rxPin6, txPin7);  //Höger hand
SoftwareSerial XL320servo3Serial = SoftwareSerial(rxPin8, txPin9);  //Nacke

XYZrobotServo elbowRight(A116servoSerial, 1);
XYZrobotServo shoulderRightPitch(A116servoSerial, 2);
//XYZrobotServo servo3(A116servoSerial,3);
XYZrobotServo shoulderRightYaw(A116servoSerial, 4);
XYZrobotServo elbowLeft(A116servo2Serial, 5);
XYZrobotServo shoulderLeftPitch(A116servo2Serial, 6);
XYZrobotServo shoulderLeftYaw(A116servo2Serial, 7);

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
}

void JointArmClassRight::armMotionSSP()
{
  int initPos = 0; // initsiera positioner
  int stopPos = 1023;
  int posYaw = 0;
  int posPitch = 0;
  
  shoulderRightPitch.setPosition(posPitch, playtime); //initierar axelpositionerna och sedan är de stela 
  shoulderRightYaw.setPosition(posYaw, playtime);

  
  for(int i = 0; i <= 2; i++)
  {
    for (int pos = initPos; pos <= stopPos; pos += 10)
    {
    elbowRight.setPosition(pos, playtime);
    }
    elbowRight.setPosition(initPos, playtime);
  }  
}

void JointArmClassRight::RESET()
{
  int initPos = 0;
  elbowRight.setPosition(initPos, playtime);
  shoulderRightPitch.setPosition(initPos, playtime);
  shoulderRightYaw.setPosition(initPos, playtime);
  for (int i = littleFingerRight; i <= thumbRight; i++)
  {
    servoRight.moveJoint(i, initPos);
  }
}

void JointArmClassRight::dab(){
  int initPos = 0;
  int endPosYawShoulder = 1023;
  int endPosPitchElbow =1023;

  for (int i = initPos, int j = initPos; i<=endPosRollShoulder, j<=endPosPitchElbow; i++, j++ ) {
    elbowRight.setPosition(j, playtime);
    shoulderRightYaw.setPosition(i,playtime);
  }

}

//---------------------------------HandRight-------------------------------------------------//
void JointArmClassRight::rock()
{

  int initPos = 0;
  int stopPos = 1023;
  int initPosArm = 0;
  int stopPosArm = 1023;

  for (int pos = initPos; pos < stopPos; pos += 15)
  {
    for (int i = littleFingerRight; i <= thumbRight; i++)
    {
      servoRight.moveJoint(i, pos);
    }
  }
  for (int pos = initPosArm; pos <= stopPosArm; pos += 10)
  {
    elbowRight.setPosition(pos, playtime);
   
  }
}
void JointArmClassRight::scissor()
{

  int initPos = 0;
  int stopPos = 1023;
  int initPosArm = 0;
  int stopPosArm = 1023;

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

void JointArmClassRight::paper()
{
  //int initPos=0;
  int pos=200;
  elbowRight.setPosition(pos,playtime);
  //elbowRight.setPosition(initPos,playtime);
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
}

void JointArmClassLeft::armMotionSSP()
{
  
  int initPos = 0; // initsiera positioner
  int stopPos = 1023;
  int posYaw = 0;
  int posPitch = 0;
  
  shoulderLeftPitch.setPosition(posPitch, playtime); //initierar axelpositionerna och sedan är de stela 
  shoulderLeftYaw.setPosition(posYaw, playtime);

  for(int i = 0; i <= 2; i++)
  {
    for (int pos = initPos; pos <= stopPos; pos += 10)
    {
    elbowLeft.setPosition(pos, playtime);
    }
    elbowLeft.setPosition(initPos, playtime);
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

void JointArmClassLeft::dab();{
  int initPos = 0;

  int endPosYawShoulder = 1023;

  for(int i = initPos; i <= endPosYawShoulder; i++)
  {
    jointArmLeft.setPosition(i,playtime);
  }
  

}
//---------------------------------HandLeft--------------------------------------------------//

void JointArmClassLeft::rock()
{
  int initPos = 0;
  int stopPos = 1023;
  int initPosArm = 0;
  int stopPosArm = 1023;

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
  int stopPos = 1023;
  int initPosArm = 0;
  int stopPosArm = 1023;

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
  int stopPosArm = 1023;
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
  int stopPos = 100;
  int i;

  for (i = initPos; i <= stopPos; i++)
  {
    servoNeck.moveJoint(neckPitch, i);
  }
}

void JointNeckClass::dab()
{

  int initPos = 0;
  int stopPos = 1000;
  int i;
  for (i = initPos; i <= stopPos; i++)
  {
    servoNeck.moveJoint(neckJaw, i);
    servoNeck.moveJoint(neckPitch, i);
  }
}

void JointNeckClass::RESET()
{
  int initPosJaw = 0;
  int initPosRoll = 0;
  int initPosPitch = 0;

  servoNeck.moveJoint(neckJaw, initPosJaw);
  servoNeck.moveJoint(neckRoll, initPosRoll);
  servoNeck.moveJoint(neckPitch, initPosPitch);
}

//-------------------------------------Skriv nackfunktioner över------------------------------------------------//

JointNeckClass jointNeck = JointNeckClass();
