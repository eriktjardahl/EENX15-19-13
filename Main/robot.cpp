#include "Arduino.h"
#include "robot.h"
#include "servoFunctions.h"

//-------------------------------------Initiera alla motorer------------------------------------------------//

// Servo communication pins
SoftwareSerial A116servoSerial = SoftwareSerial(rxPin15, txPin14);  //Höger arm, typ max pos armbåge = 300
SoftwareSerial A116servo2Serial = SoftwareSerial(rxPin17, txPin16); //Vänster arm
SoftwareSerial XL320servoSerial = SoftwareSerial(rxPin3, txPin4);   //Vänster hand
SoftwareSerial XL320servo2Serial = SoftwareSerial(rxPin6, txPin7);  //Höger hand, typ max pos finger 850
SoftwareSerial XL320servo3Serial = SoftwareSerial(rxPin8, txPin9);  //Nacke

// Elbows
XYZrobotServo elbowRight(A116servoSerial, 1);
XYZrobotServo elbowLeft(A116servo2Serial, 2);

// Shoulders
XYZrobotServo shoulderRightPitch(A116servoSerial, 4);
XYZrobotServo shoulderRightRoll(A116servoSerial, 5);
XYZrobotServo shoulderLeftPitch(A116servo2Serial, 6);
XYZrobotServo shoulderLeftRoll(A116servo2Serial, 7);

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

// Declaration of init variables
int initPosHand;
int initPosArm;
int initPosSSP;
int initPosArmLeftDab;

const int initPosNeckPitch = 490;
const int initPosNeckYaw = 510;
const int initPosNeckRoll = 500;

int initPosShoulderRoll;
int initPosShoulderPitch;

// Declaration of stop position variables
int stopPosArm;
int stopPosHand;

int stopPosNeckPitchDown;
int stopPosNeckPitchUp;
int stopPosNeckYaw;
int stopPosNeckYawLeft;
int stopPosNeckYawRight;
int stopPosNeckRoll;

int stopPosShoulderRoll;
int stopPosShoulderPitch;

int posNeckPitchDiffInit;
int posNeckPitchDiffMove;
int posShoulderPitchDiff;

char lastCase;
//char LastCase = 'a';
char rgb[] = "rgbypcwo";
int intervallTime;
int intervallTimeElbow;
int intervallTimeShoulder;

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

  switch (LastCase)
  {
  case 'a': //påse färdig
    intervallTimeElbow = 10;
    initPosSSP = 300;
    initPosArm = 0;
    move_A1_16(elbowRight, initPosSSP, initPosArm, 1, intervallTimeElbow);
    break;

  case 'b': //sax färdig
    stopPosHand = 800;
    intervallTime = 10;
    intervallTimeElbow = 10;
    initPosHand = 0;
    initPosSSP = 300;
    initPosArm = 0;
    move_A1_16(elbowRight, initPosSSP, initPosArm, 1, intervallTimeElbow);

    for (int i = stopPosHand; i >= initPosHand; i -= 100) //reset av handen
    {
      servoRight.moveJoint(thumbRight, i);
      servoRight.moveJoint(littleFingerRight, i);
      servoRight.moveJoint(ringFingerRight, i);
      servoRight.LED(thumbRight, &rgb[5]);
      servoRight.LED(littleFingerRight, &rgb[5]);
      servoRight.LED(ringFingerRight, &rgb[5]);
      internalTimer(intervallTime);
    }
    break;

  case 'c': //sten färdig
    stopPosHand = 800;
    intervallTime = 10;
    intervallTimeElbow = 10;
    initPosHand = 0;
    initPosSSP = 300;
    initPosArm = 0;
    move_A1_16(elbowRight, initPosSSP, initPosArm, 1, intervallTimeElbow);

    for (int i = stopPosHand; i >= initPosHand; i -= 100) //reset av handen
    {

      servoRight.moveJoint(middleFingerRight, i);
      servoRight.LED(middleFingerRight, &rgb[5]);

      servoRight.moveJoint(ringFingerRight, i);
      servoRight.LED(ringFingerRight, &rgb[5]);

      servoRight.moveJoint(littleFingerRight, i);
      servoRight.LED(littleFingerRight, &rgb[5]);

      servoRight.moveJoint(thumbRight, i);
      servoRight.LED(thumbRight, &rgb[5]);

      servoRight.moveJoint(indexFingerRight, i);
      servoRight.LED(indexFingerRight, &rgb[5]);
      internalTimer(intervallTime);
    }
    break;

  case 'd': //ok färdig
    initPosArm = 0;
    stopPosArm = 350;
    intervallTimeElbow = 50;

    initPosShoulderPitch = 500;
    stopPosShoulderPitch = 800;

    intervallTime = 10;

    move_A1_16(shoulderRightPitch, stopPosShoulderPitch, initPosShoulderPitch, 4, intervallTimeElbow);
    move_A1_16(elbowRight, stopPosArm, initPosArm, 4, intervallTimeElbow);

    stopPosHand = 800;
    initPosHand = 0;
    intervallTime = 10;

    for (int i = stopPosHand; i >= initPosHand; i -= 100) //knytnäven
    {
      servoRight.moveJoint(indexFingerRight, i);
      servoRight.LED(indexFingerRight, &rgb[5]);
      internalTimer(intervallTime);
    }
    break;
  case 'e': // dab,
    intervallTimeElbow = 20;
    initPosArm = 0;
    stopPosArm = 300;

    initPosShoulderPitch = 500;
    stopPosShoulderPitch = 650;

    initPosShoulderRoll = 500;
    stopPosShoulderRoll = 200;

    move_A1_16(shoulderRightRoll, stopPosShoulderRoll, initPosShoulderRoll, 4, intervallTimeElbow);
    move_A1_16(shoulderRightPitch, stopPosShoulderPitch, initPosShoulderPitch, 2, intervallTimeElbow);
    move_A1_16(elbowRight, stopPosArm, initPosArm, 4, intervallTimeElbow);

    break;
  case 'f': //fack färdig

    stopPosHand = 800;
    initPosHand = 0;
    intervallTime = 10;

    initPosArm = 0;
    stopPosArm = 350;
    intervallTimeElbow = 50;

    initPosShoulderPitch = 500;
    stopPosShoulderPitch = 800;

    move_A1_16(shoulderRightPitch, stopPosShoulderPitch, initPosShoulderPitch, 4, intervallTimeElbow);
    move_A1_16(elbowRight, stopPosArm, initPosArm, 4, intervallTimeElbow);

    for (int i = stopPosHand; i >= initPosHand; i -= 100) //knytnäven
    {

      servoRight.moveJoint(thumbRight, i);
      servoRight.LED(thumbRight, &rgb[5]);

      servoRight.moveJoint(indexFingerRight, i);
      servoRight.LED(indexFingerRight, &rgb[5]);

      servoRight.moveJoint(ringFingerRight, i);
      servoRight.LED(ringFingerRight, &rgb[5]);

      servoRight.moveJoint(littleFingerRight, i);
      servoRight.LED(littleFingerRight, &rgb[5]);
      internalTimer(intervallTime);
    }
    break;

  case 'g': //test
    initPosArm = 0;
    stopPosArm = 450;
    intervallTimeElbow = 50;

    initPosShoulderRoll = 500;
    stopPosShoulderRoll = 200;

    move_A1_16(shoulderRightRoll, stopPosShoulderRoll, initPosShoulderRoll, 1, intervallTimeElbow);
    move_A1_16(elbowRight, stopPosArm, initPosArm, 4, intervallTimeElbow);
    break;
  }
}

void JointArmClassRight::armMotionSSP() //färdig
{
  initPosArm = 0;
  stopPosArm = 500;
  initPosSSP = 300;
  intervallTimeElbow = 10;

  move_A1_16(elbowRight, initPosArm, stopPosArm, 4, intervallTimeElbow);
  move_A1_16(elbowRight, stopPosArm, initPosSSP, 4, intervallTimeElbow);
  move_A1_16(elbowRight, initPosSSP, stopPosArm, 4, intervallTimeElbow);
  move_A1_16(elbowRight, stopPosArm, initPosSSP, 4, intervallTimeElbow);
  move_A1_16(elbowRight, initPosSSP, stopPosArm, 4, intervallTimeElbow);
}

void JointArmClassRight::dab() //LastCase = e
{
  intervallTimeElbow = 10;
  initPosArm = 0;
  stopPosArm = 400;

  initPosShoulderPitch = 500;
  stopPosShoulderPitch = 650;

  move_A1_16(elbowRight, initPosArm, stopPosArm, 4, intervallTimeElbow);
  move_A1_16(shoulderRightPitch, initPosShoulderPitch, stopPosShoulderPitch, 2, intervallTimeElbow);
  /*
  for (int pos = initPosArm, k = initPosShoulderPitch; pos <= stopPosArm, k <= stopPosShoulderPitch; pos += 4, k += 2)
  {
    elbowRight.setPosition(pos, intervallTimeElbow);
    internalTimer();

    shoulderRightPitch.setPosition(k, intervallTimeElbow);
    internalTimer();
  }
  */
}

void JointArmClassRight::maxElbow() //färdig
{
  initPosArm = 0;
  stopPosArm = 600;
  intervallTime = 10;

  move_A1_16(elbowRight, initPosArm, stopPosArm, 4, intervallTime);
}

void JointArmClassRight::perpendicular() //färdig.
{
  initPosArm = 0;
  stopPosArm = 350;
  intervallTimeElbow = 10;

  move_A1_16(elbowRight, initPosArm, stopPosArm, 4, intervallTimeElbow);
}

void JointArmClassRight::ShoulderPitchPerp() //färdig
{
  intervallTimeElbow = 10;
  initPosShoulderPitch = 500;
  stopPosShoulderPitch = 850;

  move_A1_16(shoulderRightPitch, initPosShoulderPitch, stopPosShoulderPitch, 5, intervallTimeElbow);
}

void JointArmClassRight::ShoulderRollPerp() //färdig
{
  intervallTime = 10;

  initPosShoulderRoll = 500;
  stopPosShoulderRoll = 300;

  move_A1_16(shoulderRightRoll, initPosShoulderRoll, stopPosShoulderRoll, 4, intervallTime);
}
//---------------------------------HandRight-------------------------------------------------//
void JointArmClassRight::rock() // lastCase = c färdig
{

  intervallTimeElbow = 10;
  stopPosArm = 500;
  initPosSSP = 300;

  move_A1_16(elbowRight, stopPosArm, initPosSSP, 4, intervallTimeElbow);
}
void JointArmClassRight::scissor() //lastCase = b färdig
{
  stopPosHand = 800;
  initPosHand = 0;

  intervallTimeElbow = 10;
  stopPosArm = 500;
  initPosSSP = 300;
  intervallTime = 10;

  move_A1_16(elbowRight, stopPosArm, initPosSSP + 32, 4, intervallTimeElbow); //gå ner så det är 8 varv kvar.

  for (int k = stopPosHand, pos = initPosSSP + 32; k >= initPosHand, pos >= initPosSSP; k -= 100, pos -= 4) //När det är 8 varv kvar så börjar handen röra på sig
  {
    elbowRight.setPosition(pos, intervallTimeElbow);
    internalTimer(intervallTimeElbow);
    servoRight.moveJoint(indexFingerRight, k);
    servoRight.moveJoint(middleFingerRight, k);
    internalTimer(intervallTime);
  }
}

void JointArmClassRight::paper() // lastCase = a färdig
{
  stopPosHand = 800;
  initPosHand = 0;

  intervallTimeElbow = 10;
  stopPosArm = 500;
  initPosSSP = 300;

  intervallTime = 10;

  move_A1_16(elbowRight, stopPosArm, initPosSSP + 32, 4, intervallTimeElbow); //gå ner så det är 8 varv kvar.

  for (int i = stopPosHand, pos = initPosSSP + 32; i >= initPosHand, pos >= initPosSSP; i -= 100, pos -= 4) //när det bara är 8 loopar kvar börjar handen röra på sig
  {
    elbowRight.setPosition(pos, intervallTimeElbow);
    internalTimer(intervallTimeElbow);

    servoRight.moveJoint(middleFingerRight, i);
    servoRight.moveJoint(ringFingerRight, i);
    servoRight.moveJoint(littleFingerRight, i);
    servoRight.moveJoint(thumbRight, i);
    servoRight.moveJoint(indexFingerRight, i);
    internalTimer(intervallTime);
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
    internalTimer(intervallTime);
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
    servoRight.moveJoint(ringFingerRight, i);
    servoRight.moveJoint(littleFingerRight, i);
    servoRight.moveJoint(thumbRight, -i);
    servoRight.moveJoint(indexFingerRight, i);
    internalTimer(intervallTime);
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
    servoRight.moveJoint(indexFingerRight, i);
    servoRight.moveJoint(ringFingerRight, i);
    servoRight.moveJoint(littleFingerRight, i);
    internalTimer(intervallTime);
  }
}

void JointArmClassRight::close() //färdig lastCase = p
{
  initPosHand = 0;
  stopPosHand = 900;
  intervallTime = 10;

  for (int i = initPosHand; i <= stopPosHand; i += 100)
  {
    servoRight.moveJoint(middleFingerRight, i);
    servoRight.moveJoint(ringFingerRight, i);
    servoRight.moveJoint(littleFingerRight, i);
    servoRight.moveJoint(thumbRight, i);
    servoRight.moveJoint(indexFingerRight, i);
    internalTimer(intervallTime);
  }
}

//-------------------------------------Skriv armfunktioner över------------------------------------------------//

JointArmClassRight jointArmRight = JointArmClassRight();

//---------------------------------Arm_Left--------------------------------------------------//

JointArmClassLeft::JointArmClassLeft()
{
}

void JointArmClassLeft::SETUP() //färdig
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
    intervallTimeElbow = 20;
    initPosShoulderRoll = 500;
    initPosArm = 0;
    stopPosShoulderRoll = 850;
    stopPosArm = 400;

    move_A1_16(shoulderLeftPitch, 499, 500, 1, intervallTimeElbow);
    maxElbow();
    move_A1_16(shoulderLeftRoll, stopPosShoulderRoll, initPosShoulderRoll, 4, intervallTimeElbow);
    move_A1_16(elbowLeft, stopPosArm, initPosArm, 4, intervallTimeElbow);

    break;
  case 'g': //
    intervallTimeElbow = 50;
    initPosArm = 0;
    stopPosArm = 450;

    move_A1_16(elbowLeft, stopPosArm, initPosArm, 4, intervallTimeElbow);
    break;
  }
}

void JointArmClassLeft::dabPart1()
{
}

void JointArmClassLeft::dabPart2()
{
}

void JointArmClassLeft::maxElbow() //färdig
{
  initPosArm = 0;
  stopPosArm = 450;
  intervallTimeElbow = 10;

  move_A1_16(elbowLeft, initPosArm, stopPosArm, 4, intervallTimeElbow);
}

void JointArmClassLeft::perpendicular() //färdig
{
  initPosArm = 0;
  stopPosArm = 330;
  intervallTimeElbow = 10;

  move_A1_16(elbowLeft, initPosArm, stopPosArm, 4, intervallTimeElbow);
}

void JointArmClassLeft::ShoulderPitchPerp() //färdig
{
  intervallTime = 10;
  intervallTimeElbow = 10;
  initPosShoulderPitch = 500;
  stopPosShoulderPitch = 200;

  move_A1_16(shoulderLeftPitch, initPosShoulderPitch, stopPosShoulderPitch, 4, intervallTimeElbow);
}

void JointArmClassLeft::ShoulderRollPerp() //färdig
{
  intervallTime = 10;
  intervallTimeElbow = 10;

  initPosShoulderRoll = 500;
  stopPosShoulderRoll = 900;

  move_A1_16(shoulderLeftRoll, initPosShoulderRoll, stopPosShoulderRoll, 4, intervallTimeElbow);
}

//---------------------------------HandLeft--------------------------------------------------//

void JointArmClassLeft::open() //skriven, ej testad. LastCase = o.
{
  stopPosHand = 800;
  intervallTime = 10;
  initPosHand = 0;

  for (int i = stopPosHand; i >= initPosHand; i -= 100)
  {
    servoLeft.moveJoint(middleFingerLeft, i);
    servoLeft.moveJoint(ringFingerLeft, i);
    servoLeft.moveJoint(littleFingerLeft, i);
    servoLeft.moveJoint(thumbLeft, i);
    servoLeft.moveJoint(indexFingerLeft, i);
    internalTimer(intervallTime);
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
    servoLeft.moveJoint(ringFingerLeft, i);
    servoLeft.moveJoint(littleFingerLeft, i);
    servoLeft.moveJoint(thumbLeft, i);
    servoLeft.moveJoint(indexFingerRight, i);
    internalTimer(intervallTime);
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

  // Roll
  stopPosNeckRoll = 520;
  move_XL_320(servoNeck, neckRoll, initPosNeckRoll, stopPosNeckRoll, 5, 10);

  // Yaw
  stopPosNeckYaw = 500;
  move_XL_320(servoNeck, neckYaw, initPosNeckYaw, stopPosNeckYaw, 5, 10);

  // Pitch: frammåt från neråt tittande
  stopPosNeckPitchUp = initPosNeckPitch + 50;
  stopPosNeckPitchDown = initPosNeckPitch - 50;
  intervallTime = 30;
  MOVE_NECK_PITCH(servoNeck, neckPitchRight, neckPitchLeft, stopPosNeckPitchUp, stopPosNeckPitchDown, initPosNeckPitch, initPosNeckPitch, intervallTime);
}

void JointNeckClass::RESET(char LastCase)
{

  switch (LastCase)
  {
  case 'h': //nicka, färdig
    stopPosNeckPitchUp = initPosNeckPitch + 100;
    stopPosNeckPitchDown = initPosNeckPitch - 100;
    posNeckPitchDiffMove = stopPosNeckPitchUp - stopPosNeckPitchDown;
    posNeckPitchDiffInit = stopPosNeckPitchUp - initPosNeckPitch;
    intervallTime = 10;

    //Titta frammåt från att titta uppåt
    MOVE_NECK_PITCH(servoNeck, neckPitchRight, neckPitchLeft, stopPosNeckPitchUp, stopPosNeckPitchDown, initPosNeckPitch, initPosNeckPitch, intervallTime);
    break;

  case 'i': //skaka på huvudet färdig
    stopPosNeckYawLeft = initPosNeckYaw + 200;
    stopPosNeckYawRight = initPosNeckYaw - 200;
    move_XL_320(servoNeck, neckYaw, stopPosNeckYawLeft, initPosNeckYaw, 1, 10);
    break;

  case 'g': // Detta är hur man gör "OR" i switch-case satser
  case 'f':
    stopPosNeckYaw = 200;
    move_XL_320(servoNeck, neckYaw, stopPosNeckYaw, initPosNeckYaw, 1, 10);
    break;

  case 'e': //dab
    stopPosNeckPitchUp = initPosNeckPitch + 100;
    stopPosNeckPitchDown = initPosNeckPitch - 100;
    posNeckPitchDiffMove = stopPosNeckPitchUp - stopPosNeckPitchDown;
    posNeckPitchDiffInit = stopPosNeckPitchUp - initPosNeckPitch;

    stopPosNeckYaw = 400;
    intervallTime = 10;

    // frammåt från neråt tittande
    MOVE_NECK_PITCH(servoNeck, neckPitchRight, neckPitchLeft, stopPosNeckPitchUp, stopPosNeckPitchDown, initPosNeckPitch, initPosNeckPitch, intervallTime);
    move_XL_320(servoNeck, neckYaw, stopPosNeckYaw, initPosNeckYaw, 1, 10);
    break;
  }
}

void JointNeckClass::nod() //färdig
{
  stopPosNeckPitchUp = initPosNeckPitch + 40;
  stopPosNeckPitchDown = initPosNeckPitch - 80;
  posNeckPitchDiffMove = stopPosNeckPitchUp - stopPosNeckPitchDown;
  posNeckPitchDiffInit = stopPosNeckPitchUp - initPosNeckPitch;
  intervallTime = 5;

  // Från start till att titta ner
  MOVE_NECK_PITCH(servoNeck, neckPitchRight, neckPitchLeft, initPosNeckPitch, initPosNeckPitch, stopPosNeckPitchUp, stopPosNeckPitchDown, intervallTime);
  // Uppåt
  MOVE_NECK_PITCH(servoNeck, neckPitchLeft, neckPitchRight, stopPosNeckPitchDown, stopPosNeckPitchUp, stopPosNeckPitchUp, stopPosNeckPitchDown, intervallTime);
  // Neråt
  MOVE_NECK_PITCH(servoNeck, neckPitchRight, neckPitchLeft, stopPosNeckPitchDown, stopPosNeckPitchUp, stopPosNeckPitchUp, stopPosNeckPitchDown, intervallTime);
   // Uppåt
  MOVE_NECK_PITCH(servoNeck, neckPitchLeft, neckPitchRight, stopPosNeckPitchDown, stopPosNeckPitchUp, stopPosNeckPitchUp, stopPosNeckPitchDown, intervallTime);
}

void JointNeckClass::neckPitchDown() //färdig
{
  stopPosNeckPitchUp = initPosNeckPitch + 100;
  stopPosNeckPitchDown = initPosNeckPitch - 100;
  posNeckPitchDiffMove = stopPosNeckPitchUp - stopPosNeckPitchDown;
  posNeckPitchDiffInit = stopPosNeckPitchUp - initPosNeckPitch;

  intervallTime = 10;

  // neråt från frammåt tittande

  for (int i = initPosNeckPitch, k = initPosNeckPitch; i <= stopPosNeckPitchUp, k >= stopPosNeckPitchDown; i++, k--)
  {
    servoNeck.moveJoint(neckPitchLeft, k);
    servoNeck.moveJoint(neckPitchRight, i);
    internalTimer(intervallTime);
  }
}

void JointNeckClass::neckPitchUp() //färdig
{
  stopPosNeckPitchUp = initPosNeckPitch + 100;
  stopPosNeckPitchDown = initPosNeckPitch - 100;
  posNeckPitchDiffMove = stopPosNeckPitchUp - stopPosNeckPitchDown;
  posNeckPitchDiffInit = stopPosNeckPitchUp - initPosNeckPitch;

  intervallTime = 10;

  //Uppåt från titta frammåt
  for (int i = initPosNeckPitch, k = initPosNeckPitch; i <= stopPosNeckPitchUp, k >= stopPosNeckPitchDown; i++, k--)
  {
    servoNeck.moveJoint(neckPitchLeft, i);
    servoNeck.moveJoint(neckPitchRight, k);
    internalTimer(intervallTime);
  }
}

void JointNeckClass::neckYawLookLeft() //färdig
{
  stopPosNeckYaw = 800;
  move_XL_320(servoNeck, neckYaw, initPosNeckYaw, stopPosNeckYaw, 1, 10);
}

void JointNeckClass::neckYawLookRight() //färdig
{
  stopPosNeckYaw = 200;
  move_XL_320(servoNeck, neckYaw, initPosNeckYaw, stopPosNeckYaw, 1, 10);
}

void JointNeckClass::shake() //färdig
{
  intervallTime = 2;
  stopPosNeckYawLeft = initPosNeckYaw + 70;
  stopPosNeckYawRight = initPosNeckYaw - 70;

  move_XL_320(servoNeck, neckYaw, initPosNeckYaw, stopPosNeckYawLeft, 1, intervallTime);
  move_XL_320(servoNeck, neckYaw, stopPosNeckYawLeft, stopPosNeckYawRight, 1, intervallTime);
  move_XL_320(servoNeck, neckYaw, stopPosNeckYawRight, stopPosNeckYawLeft, 1, intervallTime);
  move_XL_320(servoNeck, neckYaw, stopPosNeckYawLeft, initPosNeckYaw, 1, intervallTime);
}

void JointNeckClass::neckRollTiltLeft() //färdig
{
  stopPosNeckRoll = 200;
  move_XL_320(servoNeck, neckRoll, initPosNeckRoll, stopPosNeckRoll, 1, 10);
}

void JointNeckClass::neckRollTiltRight() //färdig
{
  stopPosNeckRoll = 800;
  move_XL_320(servoNeck, neckRoll, initPosNeckRoll, stopPosNeckRoll, 1, 10);
}

void JointNeckClass::wakeUp()
{
  stopPosNeckPitchUp = initPosNeckPitch + 100;
  stopPosNeckPitchDown = initPosNeckPitch - 100;
  intervallTime = 10;

  // frammåt från neråt tittande
  MOVE_NECK_PITCH(servoNeck, neckPitchLeft, neckPitchRight, stopPosNeckPitchUp, stopPosNeckPitchDown, initPosNeckPitch, initPosNeckPitch, intervallTime);
}

//-------------------------------------Skriv nackfunktioner över------------------------------------------------//

JointNeckClass jointNeck = JointNeckClass();

//-------------------------------------Multi parts ------------------------------------------------//

MultiPartClass::MultiPartClass()
{
}

void MultiPartClass::RESET(char LastCase)
{ /*
  switch (LastCase)
  {
  case 


    break;
  
  default:
    break;
  }*/
}

void MultiPartClass::dab()
{
  initPosArm = 0;
  stopPosArm = 600;
  initPosArmLeftDab = 400;
  intervallTimeElbow = 10;

  stopPosNeckPitchUp = initPosNeckPitch + 100;
  stopPosNeckPitchDown = initPosNeckPitch - 100;
  posNeckPitchDiffMove = stopPosNeckPitchUp - stopPosNeckPitchDown;
  posNeckPitchDiffInit = stopPosNeckPitchUp - initPosNeckPitch;
  stopPosNeckYaw = initPosNeckYaw - 100;
  intervallTime = 10;

  move_A1_16(shoulderLeftPitch, 500, 499, 1, intervallTimeElbow);
  move_A1_16(elbowLeft, stopPosArm, initPosArmLeftDab, 4, intervallTimeElbow);

  // neråt från frammåt tittande
  for (int i = initPosNeckPitch, k = initPosNeckPitch, j = initPosNeckYaw, l = initPosArmLeftDab; i <= stopPosNeckPitchUp, k >= stopPosNeckPitchDown, j >= stopPosNeckYaw, l >= initPosArm; i += 2, k -= 2, j -= 2, l -= 8)
  {
    elbowLeft.setPosition(l, intervallTimeElbow);
    internalTimer(intervallTimeElbow);
    servoNeck.moveJoint(neckPitchLeft, k);
    servoNeck.moveJoint(neckPitchRight, i);
    servoNeck.moveJoint(neckYaw, j);
    internalTimer(intervallTime);
  }
}

//----------------------------------------------------------------------------------------------------------------
MultiPartClass multiPart = MultiPartClass();
