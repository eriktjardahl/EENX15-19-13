#include "Arduino.h"
#include "robot.h"

//-------------------------------------Initiera alla motorer------------------------------------------------//

SoftwareSerial A116servoSerial = SoftwareSerial(rxPin15, txPin14);  //Höger arm, typ max pos armbåge = 300
SoftwareSerial A116servo2Serial = SoftwareSerial(rxPin17, txPin16); //Vänster arm
SoftwareSerial XL320servoSerial = SoftwareSerial(rxPin3, txPin4);   //Vänster hand
SoftwareSerial XL320servo2Serial = SoftwareSerial(rxPin6, txPin7);  //Höger hand, typ max pos finger 850
SoftwareSerial XL320servo3Serial = SoftwareSerial(rxPin8, txPin9);  //Nacke

XYZrobotServo elbowRight(A116servoSerial, 1);
XYZrobotServo shoulderRightPitch(A116servoSerial, 4);
//XYZrobotServo servo3(A116servoSerial,3);
XYZrobotServo shoulderRightRoll(A116servoSerial, 5);
XYZrobotServo elbowLeft(A116servo2Serial, 2);
XYZrobotServo shoulderLeftPitch(A116servo2Serial, 6);
XYZrobotServo shoulderLeftRoll(A116servo2Serial, 7);

// Declaration of init variables
int initPosHand;
int initPosArm;
int initPosSSP;

int initPosNeckPitch;
int initPosNeckYaw;
int initPosNeckRoll;

int initPosShoulderRoll;
int initPosShoulderPitch;

// Declaration of stop position variables
int stopPosArm;
int stopPosHand;

int stopPosNeckPitchDown;
int stopPosNeckPitchUp;
int stopPosNeckYaw;
int stopPosNeckRoll;

int stopPosShoulderRoll;
int stopPosShoulderPitch;

int posNeckPitchDiffInit;
int posNeckPitchDiffMove;
int posShoulderPitchDiff;
XL320 servoLeft;
/*
  Vänster hand alla öppna vid position 0. alla stängda vid 800 typ
  lillfinger .   ID:1
  ringfinger     ID:2
  långfinger    ID:3
  pekfinger     ID:4
  tummer        ID:5
 */

XL320 servoRight;
/*
  Höger hand alla öppna vid position 0. alla stängda vid 800 typ
  lillfinger .   ID:6
  ringfinger     ID:7
  långfinger    ID:8
  pekfinger     ID:9
  tummer        ID:10
 */

XL320 servoNeck;
/*
  Id 11-14 Nack rotationer. 
  Yaw tittar frammåt vid position 500
  Pitch vänster och höger tittar frammåt vid position 500
  Pich vänster mer än 500 går uppåt, mindre än 500 går neråt
  Pitch höger åker tvärtemot vänster
  Roll är rak vid position 520
 */

char lastCase;
//char LastCase = 'a';

char rgb[] = "rgbypcwo";

unsigned long revMillis;
unsigned long currentMillis;
int intervallTime;
int intervallTimeElbow;
int intervallTimeShoulder;

void internalTimer()
{
  revMillis = millis();
  currentMillis = millis();
  while (currentMillis - revMillis <= intervallTime)
  {
    currentMillis = millis();
  }
}

void stepFunc(XYZrobotServo A1_16_servo, int Start, int Stop, int Inc, int interval)
{
  if (Start < Stop)
  {
    for (int pos = Start; pos <= Stop; pos += Inc)
    {
      A1_16_servo.setPosition(pos, interval);
      internalTimer();
    }
  }
  else
  {
    for (int pos = Start; pos >= Stop; pos -= Inc)
    {
      A1_16_servo.setPosition(pos, interval);
      internalTimer();
    }
  }
}

/*
void stepFuncXL320(XL320 servo, int servoNr1, int servoNr2, int initPos, int stopPos, int posDiff)
{
  if (initPos < stopPos)
  {
    for (int i = initPos, k = initPos + posDiff; i <= stopPos, k >= initPos - posDiff; i += 1, k -= 1)
    {
      servo.moveJoint(servoNr1, i);
      servo.moveJoint(servoNr2, k);
      internalTimer();
    }
  }
  else
  {
    for (int i = initPos, k = initPos - posDiff; i >= stopPos, k <= initPos; i -= 1, k += 1)
    {
      servo.moveJoint(servoNr1, i);
      servo.moveJoint(servoNr2, k);
      internalTimer();
    }
  }
}
*/

//---------------------------------Arm_RIGHT-------------------------------------------------//

JointArmClassRight::JointArmClassRight()
{
}

void JointArmClassRight::SETUP()
{

  pinMode(rxPin6, INPUT);
  pinMode(txPin7, OUTPUT);
  pinMode(rxPin15, INPUT);
  pinMode(txPin14, OUTPUT);

  A116servo2Serial.begin(115200);  // höger arm
  XL320servo2Serial.begin(115200); // höger hand

  servoRight.begin(XL320servo2Serial);
  servoRight.setJointSpeed(littleFingerRight, 1023);
  servoRight.setJointSpeed(ringFingerRight, 1023);
  servoRight.setJointSpeed(middleFingerRight, 1023);
  servoRight.setJointSpeed(indexFingerRight, 1023);
  servoRight.setJointSpeed(thumbRight, 1023);
}

void JointArmClassRight::RESET(char LastCase)
{
  //Serial.println(LastCase);
  switch (LastCase)
  {
  case 'a': //påse färdig
    intervallTimeElbow = 10;
    initPosSSP = 300;
    initPosArm = 0;
    stepFunc(elbowRight, initPosSSP, initPosArm, 1, intervallTimeElbow);

    break;

  case 'b': //sax färdig
    stopPosHand = 800;
    intervallTime = 10;
    intervallTimeElbow = 10;
    initPosHand = 0;
    initPosSSP = 300;
    initPosArm = 0;

    stepFunc(elbowRight, initPosSSP, initPosArm, 1, intervallTimeElbow);

    for (int i = stopPosHand; i >= initPosHand; i -= 100) //reset av handen
    {
      servoRight.moveJoint(thumbRight, i);
      servoRight.LED(thumbRight, &rgb[5]);
      internalTimer();

      servoRight.moveJoint(littleFingerRight, i);
      servoRight.LED(littleFingerRight, &rgb[5]);
      internalTimer();

      servoRight.moveJoint(ringFingerRight, i);
      servoRight.LED(ringFingerRight, &rgb[5]);
      internalTimer();
    }
    break;

  case 'c': //sten färdig
    stopPosHand = 800;
    intervallTime = 10;
    intervallTimeElbow = 10;
    initPosHand = 0;
    initPosSSP = 300;
    initPosArm = 0;

    stepFunc(elbowRight, initPosSSP, initPosArm, 1, intervallTimeElbow);

    for (int i = stopPosHand; i >= initPosHand; i -= 100) //reset av handen
    {

      servoRight.moveJoint(middleFingerRight, i);
      servoRight.LED(middleFingerRight, &rgb[5]);
      internalTimer();

      servoRight.moveJoint(ringFingerRight, i);
      servoRight.LED(ringFingerRight, &rgb[5]);
      internalTimer();

      servoRight.moveJoint(littleFingerRight, i);
      servoRight.LED(littleFingerRight, &rgb[5]);
      internalTimer();

      servoRight.moveJoint(thumbRight, i);
      servoRight.LED(thumbRight, &rgb[5]);
      internalTimer();

      servoRight.moveJoint(indexFingerRight, i);
      servoRight.LED(indexFingerRight, &rgb[5]);
      internalTimer();
    }
    break;

  case 'd': //ok färdig

    initPosArm = 0;
    stopPosArm = 330;
    intervallTimeElbow = 50;

    initPosShoulderPitch = 500;
    stopPosShoulderPitch = 800;

    stepFunc(shoulderRightPitch, stopPosShoulderPitch, initPosShoulderPitch, 4, intervallTimeElbow);

    stepFunc(elbowRight, stopPosArm, initPosArm, 4, intervallTimeElbow);

    stopPosHand = 800;
    initPosHand = 0;
    intervallTime = 10;

    for (int i = stopPosHand; i >= initPosHand; i -= 100) //knytnäven
    {
      servoRight.moveJoint(indexFingerRight, i);
      servoRight.LED(indexFingerRight, &rgb[5]);
      internalTimer();
    }
    break;
  case 'e': // dab,
    intervallTime = 10;
    intervallTimeElbow = 10;

    initPosArm = 0;
    stopPosArm = 400;

    initPosShoulderPitch = 500;
    stopPosShoulderPitch = 700;

    initPosShoulderRoll = 800;
    stopPosShoulderRoll = 500;

    for (int k = stopPosShoulderRoll; k <= initPosShoulderRoll; k += 5)
    {
      shoulderRightRoll.setPosition(k, intervallTimeElbow);
      internalTimer();
    }

    for (int pos = stopPosArm, k = stopPosShoulderPitch; pos >= initPosArm, k >= initPosShoulderPitch; pos -= 4, k -= 2) //Gå ner så det bara är 8 varv kvar till initPosSSP
    {
      elbowRight.setPosition(pos, intervallTimeElbow);
      internalTimer();

      shoulderRightPitch.setPosition(k, intervallTimeElbow);
      internalTimer();
    }
    break;
  case 'f': //fack färdig

    stopPosHand = 800;
    initPosHand = 0;
    intervallTime = 10;

    initPosArm = 0;
    stopPosArm = 330;
    intervallTimeElbow = 50;

    initPosShoulderPitch = 500;
    stopPosShoulderPitch = 800;

    stepFunc(shoulderRightPitch, stopPosShoulderPitch, initPosShoulderPitch, 4, intervallTimeElbow);

    stepFunc(elbowRight, stopPosArm, initPosArm, 4, intervallTimeElbow);

    for (int i = stopPosHand; i >= initPosHand; i -= 100) //knytnäven
    {

      servoRight.moveJoint(thumbRight, i);
      servoRight.LED(thumbRight, &rgb[5]);
      internalTimer();

      servoRight.moveJoint(indexFingerRight, i);
      servoRight.LED(indexFingerRight, &rgb[5]);
      internalTimer();

      servoRight.moveJoint(ringFingerRight, i);
      servoRight.LED(ringFingerRight, &rgb[5]);
      internalTimer();

      servoRight.moveJoint(littleFingerRight, i);
      servoRight.LED(littleFingerRight, &rgb[5]);
      internalTimer();
    }
    break;

  case 'g': //test
    initPosArm = 0;
    stopPosArm = 450;
    intervallTimeElbow = 50;

    initPosShoulderRoll = 500;
    stopPosShoulderRoll = 200;

    stepFunc(shoulderRightRoll, stopPosShoulderRoll, initPosShoulderRoll, 1, intervallTimeElbow);

    stepFunc(elbowRight, stopPosArm, initPosArm, 4, intervallTimeElbow);

    break;
  }
}

void JointArmClassRight::armMotionSSP() //färdig
{
  initPosArm = 0;
  stopPosArm = 500;
  initPosSSP = 300;
  intervallTimeElbow = 10;

  stepFunc(elbowRight, initPosArm, stopPosArm, 4, intervallTimeElbow);

  stepFunc(elbowRight, stopPosArm, initPosSSP, 4, intervallTimeElbow);

  stepFunc(elbowRight, initPosSSP, stopPosArm, 4, intervallTimeElbow);

  stepFunc(elbowRight, stopPosArm, initPosSSP, 4, intervallTimeElbow);

  stepFunc(elbowRight, initPosSSP, stopPosArm, 4, intervallTimeElbow);

  //}
  //}
}

void JointArmClassRight::dab() //LastCase = e
{
  intervallTime = 10;
  intervallTimeElbow = 10;
  initPosArm = 0;
  stopPosArm = 400;

  initPosShoulderPitch = 500;
  stopPosShoulderPitch = 700;

  for (int pos = initPosArm, k = initPosShoulderPitch; pos <= stopPosArm, k <= stopPosShoulderPitch; pos += 4, k += 2) //Gå ner så det bara är 8 varv kvar till initPosSSP
  {
    elbowRight.setPosition(pos, intervallTimeElbow);
    internalTimer();

    shoulderRightPitch.setPosition(k, intervallTimeElbow);
    internalTimer();
  }
}

void JointArmClassRight::maxElbow() //färdig
{
  initPosArm = 0;
  stopPosArm = 450;
  intervallTime = 10;

  stepFunc(elbowRight, initPosArm, stopPosArm, 4, intervallTime);
}

void JointArmClassRight::perpendicular() //färdig.
{
  initPosArm = 0;
  stopPosArm = 330;
  intervallTimeElbow = 10;

  stepFunc(elbowRight, initPosArm, stopPosArm, 4, intervallTimeElbow);
}

void JointArmClassRight::ShoulderPitchPerp() //färdig
{
  intervallTimeElbow = 20;
  initPosShoulderPitch = 500;
  stopPosShoulderPitch = 850;

  stepFunc(shoulderRightPitch, initPosShoulderPitch, stopPosShoulderPitch, 4, intervallTimeElbow);
}

void JointArmClassRight::ShoulderRollPerp() //färdig
{
  intervallTime = 10;

  initPosShoulderRoll = 500;
  stopPosShoulderRoll = 200;

  stepFunc(shoulderRightRoll, initPosShoulderRoll, stopPosShoulderRoll, 4, intervallTime);
}
//---------------------------------HandRight-------------------------------------------------//
void JointArmClassRight::rock() // lastCase = c färdig
{

  intervallTimeElbow = 10;
  stopPosArm = 500;
  initPosSSP = 300;

  stepFunc(elbowRight, stopPosArm, initPosSSP, 4, intervallTimeElbow);
}
void JointArmClassRight::scissor() //lastCase = b färdig
{
  stopPosHand = 800;
  initPosHand = 0;

  intervallTimeElbow = 10;
  stopPosArm = 500;
  initPosSSP = 300;

  stepFunc(elbowRight, stopPosArm, initPosSSP + 32, 4, intervallTimeElbow); //gå ner så det är 8 varv kvar.

  for (int k = stopPosHand, pos = initPosSSP + 32; k >= initPosHand, pos >= initPosSSP; k -= 100, pos -= 4) //När det är 8 varv kvar så börjar handen röra på sig
  {
    elbowRight.setPosition(pos, intervallTimeElbow);
    internalTimer();

    servoRight.moveJoint(indexFingerRight, k);
    servoRight.LED(indexFingerRight, &rgb[1]);
    internalTimer();

    servoRight.moveJoint(middleFingerRight, k);
    servoRight.LED(middleFingerRight, &rgb[1]);
    internalTimer();
  }
}

void JointArmClassRight::paper() // lastCase = a färdig
{
  stopPosHand = 800;
  initPosHand = 0;

  intervallTimeElbow = 10;
  stopPosArm = 500;
  initPosSSP = 300;

  stepFunc(elbowRight, stopPosArm, initPosSSP + 32, 4, intervallTimeElbow); //gå ner så det är 8 varv kvar.

  for (int i = stopPosHand, pos = initPosSSP + 32; i >= initPosHand, pos >= initPosSSP; i -= 100, pos -= 4) //när det bara är 8 loopar kvar börjar handen röra på sig
  {
    elbowRight.setPosition(pos, intervallTimeElbow);
    internalTimer();

    servoRight.moveJoint(middleFingerRight, i);
    servoRight.LED(middleFingerRight, &rgb[1]);
    internalTimer();

    servoRight.moveJoint(ringFingerRight, i);
    servoRight.LED(ringFingerRight, &rgb[1]);
    internalTimer();

    servoRight.moveJoint(littleFingerRight, i);
    servoRight.LED(littleFingerRight, &rgb[1]);
    internalTimer();

    servoRight.moveJoint(thumbRight, i);
    servoRight.LED(thumbRight, &rgb[1]);
    internalTimer();

    servoRight.moveJoint(indexFingerRight, i);
    servoRight.LED(indexFingerRight, &rgb[1]);
    internalTimer();
  }
}

void JointArmClassRight::ok() // färdig lastCase = d
{
  stopPosHand = 800;
  initPosHand = 0;
  initPosArm = 0;
  stopPosArm = 300;

  intervallTime = 10;

  for (int i = initPosHand; i <= stopPosHand; i += 100) //knytnäven
  {
    servoRight.moveJoint(indexFingerRight, i);
    servoRight.LED(indexFingerRight, &rgb[1]);
    internalTimer();
  }
}

void JointArmClassRight::open() //färdig lastCase = o
{
  stopPosHand = 800;

  intervallTime = 10;
  initPosHand = 0;

  servoRight.LED(middleFingerRight, &rgb[2]);

  for (int i = stopPosHand; i >= initPosHand; i -= 100)
  {
    servoRight.moveJoint(middleFingerRight, i);
    servoRight.LED(middleFingerRight, &rgb[1]);
    internalTimer();

    servoRight.moveJoint(ringFingerRight, i);
    servoRight.LED(ringFingerRight, &rgb[1]);
    internalTimer();

    servoRight.moveJoint(littleFingerRight, i);
    servoRight.LED(littleFingerRight, &rgb[1]);
    internalTimer();

    servoRight.moveJoint(thumbRight, i);
    servoRight.LED(thumbRight, &rgb[1]);
    internalTimer();

    servoRight.moveJoint(indexFingerRight, i);
    servoRight.LED(indexFingerRight, &rgb[1]);
    internalTimer();
  }
}

void JointArmClassRight::fack() //färdig lastCase = f
{

  stopPosHand = 800;
  initPosHand = 0;

  intervallTime = 10;

  for (int i = initPosHand; i <= stopPosHand; i += 100) //knytnäven
  {
    servoRight.moveJoint(thumbRight, i);
    servoRight.LED(thumbRight, &rgb[1]);
    internalTimer();

    servoRight.moveJoint(indexFingerRight, i);
    servoRight.LED(indexFingerRight, &rgb[1]);
    internalTimer();

    servoRight.moveJoint(ringFingerRight, i);
    servoRight.LED(ringFingerRight, &rgb[1]);
    internalTimer();

    servoRight.moveJoint(littleFingerRight, i);
    servoRight.LED(littleFingerRight, &rgb[1]);
    internalTimer();
  }
}

void JointArmClassRight::close() //färdig lastCase = p
{
  stopPosHand = 900;

  intervallTime = 10;
  initPosHand = 0;

  for (int i = initPosHand; i <= stopPosHand; i += 100)
  {
    servoRight.moveJoint(middleFingerRight, i);
    servoRight.LED(middleFingerRight, &rgb[1]);
    internalTimer();

    servoRight.moveJoint(ringFingerRight, i);
    servoRight.LED(ringFingerRight, &rgb[1]);
    internalTimer();

    servoRight.moveJoint(littleFingerRight, i);
    servoRight.LED(littleFingerRight, &rgb[1]);
    internalTimer();

    servoRight.moveJoint(thumbRight, i);
    servoRight.LED(thumbRight, &rgb[1]);
    internalTimer();

    servoRight.moveJoint(indexFingerRight, i);
    servoRight.LED(indexFingerRight, &rgb[1]);
    internalTimer();
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
  pinMode(rxPin17, INPUT);
  pinMode(txPin16, OUTPUT);
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

void JointArmClassLeft::RESET(char LastCase)
{
  switch (LastCase)
  {
  case 'e': //
    jointArmLeft.dabPart1();

    initPosShoulderRoll = 800;
    stopPosShoulderRoll = 500;

    for (int k = stopPosShoulderRoll; k <= initPosShoulderRoll; k += 5)
    {
      shoulderLeftRoll.setPosition(k, intervallTimeElbow);

      internalTimer();
    }

    jointArmLeft.dabPart2();

    break;
  case 'g': //
    initPosArm = 0;
    stopPosArm = 450;
    intervallTimeElbow = 50;

    stepFunc(elbowLeft, stopPosArm, initPosArm, 4, intervallTimeElbow);
    break;
  }
}

void JointArmClassLeft::dabPart1()
{

  intervallTime = 10;

  intervallTimeElbow = 10;
  initPosArm = 0;
  stopPosArm = 400;

  initPosShoulderPitch = 500;
  stopPosShoulderPitch = 700;

  for (int pos = initPosArm, k = initPosShoulderPitch; pos <= stopPosArm, k <= stopPosShoulderPitch; pos += 4, k += 2) //Gå ner så det bara är 8 varv kvar till initPosSSP
  {
    elbowLeft.setPosition(pos, intervallTimeElbow);
    internalTimer();

    shoulderLeftPitch.setPosition(k, intervallTimeElbow);
    internalTimer();
  }
}

void JointArmClassLeft::dabPart2()
{

  intervallTimeElbow = 10;
  initPosArm = 0;
  stopPosArm = 400;

  initPosShoulderPitch = 500;
  stopPosShoulderPitch = 700;
  for (int k = initPosShoulderPitch - posShoulderPitchDiff; k <= initPosShoulderPitch; k += 2) //Gå ner så det bara är 8 varv kvar till initPosSSP
  {
    shoulderLeftPitch.setPosition(k, intervallTimeElbow);
    internalTimer();
  }

  for (int pos = stopPosArm; pos >= initPosArm; pos -= 4)
  {
    elbowLeft.setPosition(pos, intervallTimeElbow);
    internalTimer();
  }
}

void JointArmClassLeft::maxElbow() //färdig
{
  initPosArm = 0;
  stopPosArm = 450;
  intervallTimeElbow = 10;

  stepFunc(elbowLeft, initPosArm, stopPosArm, 4, intervallTimeElbow);
}

void JointArmClassLeft::perpendicular() //färdig
{
  initPosArm = 0;
  stopPosArm = 330;
  intervallTimeElbow = 10;

  stepFunc(elbowLeft, initPosArm, stopPosArm, 4, intervallTimeElbow);
}

void JointArmClassLeft::ShoulderPitchPerp() //färdig
{
  intervallTime = 10;
  intervallTimeElbow = 10;
  initPosShoulderPitch = 500;
  stopPosShoulderPitch = 200;

  stepFunc(shoulderLeftPitch, initPosShoulderPitch, stopPosShoulderPitch, 4, intervallTimeElbow);
}

void JointArmClassLeft::ShoulderRollPerp() //färdig
{
  intervallTime = 10;
  intervallTimeElbow = 10;

  initPosShoulderRoll = 500;
  stopPosShoulderRoll = 800;

  stepFunc(shoulderLeftRoll, initPosShoulderRoll, stopPosShoulderRoll, 4, intervallTimeElbow);
}

//---------------------------------HandLeft--------------------------------------------------//

void JointArmClassLeft::open() //skriven, ej testad. LastCase = o.
{
  stopPosHand = 800;

  intervallTime = 10;
  initPosHand = 0;

  // Vad gör denna loopen? Repeterar samma uppgift 5ggr
  for (int i = stopPosHand; i >= initPosHand; i -= 100)
  {
    servoLeft.moveJoint(middleFingerLeft, i);
    servoLeft.LED(middleFingerLeft, &rgb[1]);
    internalTimer();

    servoLeft.moveJoint(ringFingerLeft, i);
    servoLeft.LED(ringFingerRight, &rgb[1]);
    internalTimer();

    servoLeft.moveJoint(littleFingerLeft, i);
    servoLeft.LED(littleFingerLeft, &rgb[1]);
    internalTimer();

    servoLeft.moveJoint(thumbLeft, i);
    servoLeft.LED(thumbLeft, &rgb[1]);
    internalTimer();

    servoLeft.moveJoint(indexFingerLeft, i);
    servoLeft.LED(indexFingerLeft, &rgb[1]);
    internalTimer();
  }
}

void JointArmClassLeft::close() //skriven, ej testad. lastCase = p.
{
  stopPosHand = 800;

  intervallTime = 10;
  initPosHand = 0;

  for (int i = initPosHand; i <= stopPosHand; i += 100)
  {
    servoLeft.moveJoint(middleFingerLeft, i);
    servoLeft.LED(middleFingerLeft, &rgb[1]);
    internalTimer();

    servoLeft.moveJoint(ringFingerLeft, i);
    servoLeft.LED(ringFingerLeft, &rgb[1]);
    internalTimer();

    servoLeft.moveJoint(littleFingerLeft, i);
    servoLeft.LED(littleFingerLeft, &rgb[1]);
    internalTimer();

    servoLeft.moveJoint(thumbLeft, i);
    servoLeft.LED(thumbLeft, &rgb[1]);
    internalTimer();

    servoLeft.moveJoint(indexFingerRight, i);
    servoLeft.LED(indexFingerRight, &rgb[1]);
    internalTimer();
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

void JointNeckClass::RESET(char LastCase)
{
  
  switch (LastCase)
  {
  case 'x': //

    break;
  case 'e': //färdig
    
    break;
  }
}

void JointNeckClass::nod() 
{
  stopPosNeckPitchUp = 600;
  stopPosNeckPitchDown = 400;
  initPosNeckPitch = 500;
  posNeckPitchDiffMove = stopPosNeckPitchUp - stopPosNeckPitchDown;


  //Neråt
  
  for(int i= stopPosNeckPitchDown, k=stopPosNeckPitchDown+ posNeckPitchDiffMove;i<=stopPosNeckPitchUp, k>= stopPosNeckPitchDown;i++, k--)
  {
    servoNeck.moveJoint(neckPitchLeft, i);
    servoNeck.moveJoint(neckPitchRight, k);
    internalTimer();
  }
  
  //Uppåt
  for(int i= stopPosNeckPitchDown, k=stopPosNeckPitchDown+ posNeckPitchDiffMove;i<=stopPosNeckPitchUp, k>= stopPosNeckPitchDown;i++, k--)
  {
    servoNeck.moveJoint(neckPitchLeft, k);
    servoNeck.moveJoint(neckPitchRight, i);
    internalTimer();
  }
  //Neråt
  for(int i= stopPosNeckPitchDown, k=stopPosNeckPitchDown+ posNeckPitchDiffMove;i<=stopPosNeckPitchUp, k>= stopPosNeckPitchDown;i++, k--)
  {
    servoNeck.moveJoint(neckPitchLeft, i);
    servoNeck.moveJoint(neckPitchRight, k);
    internalTimer();
  }
  //Uppåt
  for(int i= stopPosNeckPitchDown, k=stopPosNeckPitchDown+ posNeckPitchDiffMove;i<=stopPosNeckPitchUp, k>= stopPosNeckPitchDown;i++, k--)
  {
    servoNeck.moveJoint(neckPitchLeft, k);
    servoNeck.moveJoint(neckPitchRight, i);
    internalTimer();
  }



  
  
  
}



//-------------------------------------Skriv nackfunktioner över------------------------------------------------//

JointNeckClass jointNeck = JointNeckClass();

//-------------------------------------Multi parts ------------------------------------------------//

MultiPartClass::MultiPartClass()
{
}

void MultiPartClass::RESET(char LastCase)
{
}

//----------------------------------------------------------------------------------------------------------------
MultiPartClass multiPart = MultiPartClass();
