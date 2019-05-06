#include "Arduino.h"
#include "robot.h"

//-------------------------------------Initiera alla motorer------------------------------------------------//

SoftwareSerial A116servoSerial = SoftwareSerial(rxPin1, txPin2);    //Höger arm, typ max pos armbåge = 300
SoftwareSerial A116servo2Serial = SoftwareSerial(rxPin10, txPin11); //Vänster arm
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

int stopPosNeckPitch;
int stopPosNeckYaw;
int stopPosNeckRoll;

int stopPosShoulderRoll;
int stopPosShoulderPitch;

int posNeckPitchDiff;
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
  Pitch höger åker tvärtemot alla andra
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

void stepFunc(int Start, int Stop, int Inc)
{
  if (Start < Stop)
  {
    for (int pos = Start; pos <= Stop; pos + Inc)
    {
    }
  }
  else
  {
    for (int pos = Start; pos >= Stop; pos - Inc)
    {
    }
  }
}

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

void JointArmClassRight::RESET(char LastCase)
{
  //Serial.println(LastCase);
  switch (LastCase)
  {
  case 'a': //påse färdig
    intervallTimeElbow = 10;
    initPosSSP = 300;
    initPosArm = 0;

    for (int pos = initPosSSP; pos >= initPosArm; pos -= 4) //Reset av armen
    {
      elbowRight.setPosition(pos, intervallTimeElbow);
      internalTimer();
    }
    break;

  case 'b': //sax färdig
    stopPosHand = 800;
    intervallTime = 10;
    intervallTimeElbow = 10;
    initPosHand = 0;
    initPosSSP = 300;
    initPosArm = 0;

    for (int pos = initPosSSP; pos >= initPosArm; pos -= 4) //reset av armen
    {
      elbowRight.setPosition(pos, intervallTime);
      internalTimer();
    }

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

    for (int pos = initPosSSP; pos >= initPosArm; pos -= 4) //Reset av armen
    {
      elbowRight.setPosition(pos, intervallTimeElbow);
      internalTimer();
    }

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
  case 'e': // dab, färdig
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
    stopPosArm = 330;
    intervallTimeElbow = 10;

    for (int pos = stopPosArm; pos >= initPosArm; pos -= 4)
    {
      elbowRight.setPosition(pos, intervallTimeElbow);
      internalTimer();
    }
    break;
  }
}

void JointArmClassRight::armMotionSSP() //färdig
{
  initPosArm = 0;
  stopPosArm = 500;
  initPosSSP = 300;
  intervallTimeElbow = 10;

  for (int j = 0; j <= 5; j++) //armMotionSSP
  {
    if (j == 0)
    {
      for (int pos = initPosArm; pos <= initPosSSP; pos += 4)
      {
        elbowRight.setPosition(pos, intervallTimeElbow);
        internalTimer();
      }
    }

    if (j == 1 || j == 3 || j == 5)
    {
      for (int pos = initPosSSP; pos <= stopPosArm; pos += 4)
      {
        elbowRight.setPosition(pos, intervallTimeElbow);
        internalTimer();
      }
    }
    if (j == 2 || j == 4)
    {
      for (int pos = stopPosArm; pos >= initPosSSP; pos -= 4)
      {
        elbowRight.setPosition(pos, intervallTimeElbow);
        internalTimer();
      }
    }
  }
}

void JointArmClassRight::dab() //färdig, LastCase = e
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
  stopPosArm = 500;
  intervallTimeElbow = 10;

  for (int pos = initPosArm; pos <= stopPosArm; pos += 4)
  {
    //Serial.println(pos);
    elbowRight.setPosition(pos, intervallTimeElbow);
    internalTimer();
  }
}

void JointArmClassRight::perpendicular() //skriven, ej testad. inte säker på att det är 90 grader, men typ.
{
  initPosArm = 0;
  stopPosArm = 330;
  intervallTimeElbow = 10;

  for (int pos = initPosArm; pos <= stopPosArm; pos += 4)
  {
    elbowRight.setPosition(pos, intervallTimeElbow);
    internalTimer();
  }
}

void JointArmClassRight::ShoulderPitchPerp() //färdig
{
  intervallTime = 10;
  intervallTimeElbow = 10;

  initPosShoulderPitch = 500;
  stopPosShoulderPitch = 800;

  shoulderRightPitch.setPosition(800, intervallTimeElbow);
  /*
  for (int pos = initPosShoulderPitch; pos <= stopPosShoulderPitch; pos += 10) //Gå ner så det bara är 8 varv kvar till initPosSSP
  {
    shoulderRightPitch.setPosition(pos, intervallTimeElbow);
    internalTimer();
  }
  */
}

void JointArmClassRight::ShoulderRollPerp() //färdig
{
  intervallTime = 10;
  intervallTimeElbow = 100;

  initPosShoulderRoll = 500;
  stopPosShoulderRoll = 200;
  shoulderRightRoll.setPosition(200, intervallTimeElbow);
  /*
  for (int k = initPosShoulderRoll; k >= stopPosShoulderRoll; k -= 5)
  {
    shoulderRightRoll.setPosition(200, intervallTimeElbow);
    internalTimer();
  }
  */
}
//---------------------------------HandRight-------------------------------------------------//
void JointArmClassRight::rock() // lastCase = c färdig
{

  intervallTimeElbow = 10;
  stopPosArm = 500;
  initPosSSP = 300;

  for (int pos = stopPosArm; pos >= initPosSSP; pos -= 4) //Gå ner hela vägen utan att röra handen eftersom den redan är en näve
  {
    elbowRight.setPosition(pos, intervallTimeElbow);
    internalTimer();
  }
}
void JointArmClassRight::scissor() //lastCase = b färdig
{
  stopPosHand = 800;
  initPosHand = 0;

  intervallTimeElbow = 10;
  stopPosArm = 500;
  initPosSSP = 300;

  for (int pos = stopPosArm; pos >= initPosSSP + 32; pos -= 4) //Gå ner så det bara är 8 varv kvar till initPosSSP
  {
    elbowRight.setPosition(pos, intervallTimeElbow);
    internalTimer();
  }

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

  for (int pos = stopPosArm; pos >= initPosSSP + 32; pos -= 4) //Gå ner så det bara är 8 varv kvar till initPosSSP
  {
    elbowRight.setPosition(pos, intervallTimeElbow);
    internalTimer();
  }
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
  case 'p': //

    break;
  }
}

void JointArmClassLeft::dabPart1() //skriven ,ej testad
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

void JointArmClassLeft::ShoulderRollPerp()
{
  intervallTime = 10;

  intervallTimeElbow = 10;

  initPosShoulderRoll = 800;
  stopPosShoulderRoll = 500;

  for (int k = initPosShoulderRoll; k >= stopPosShoulderRoll; k -= 5)
  {
    shoulderLeftRoll.setPosition(k, intervallTimeElbow);
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

void JointArmClassLeft::maxElbow()
{
  initPosArm = 0;
  stopPosArm = 400;

  revMillis = 0;
  currentMillis = millis();
  intervallTimeElbow = 10;

  for (int pos = initPosArm; pos <= stopPosArm; pos += 4)
  {
    elbowLeft.setPosition(pos, intervallTimeElbow);
    internalTimer();
  }
}
//---------------------------------HandLeft--------------------------------------------------//

void JointArmClassLeft::open() //skriven, ej testad. LastCase = o.
{
  stopPosHand = 800;
  revMillis = 0;
  currentMillis = millis();
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
  revMillis = 0;
  currentMillis = millis();
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
    initPosNeckYaw = 500;
    stopPosNeckYaw = 350;
    initPosNeckPitch = 500;
    stopPosNeckPitch = 600;
    posNeckPitchDiff = stopPosNeckPitch - initPosNeckPitch;

    intervallTime = 10;
    servoNeck.LED(neckPitchRight, &rgb[3]);
    servoNeck.LED(neckPitchLeft, &rgb[3]);
    servoNeck.LED(neckYaw, &rgb[3]);

    for (int i = stopPosNeckPitch, k = initPosNeckPitch - posNeckPitchDiff; i >= initPosNeckPitch, k <= initPosNeckPitch; i -= 1, k += 1)
    {

      servoNeck.moveJoint(neckPitchRight, i);
      internalTimer();

      servoNeck.moveJoint(neckPitchLeft, k);
      internalTimer();
    }

    for (int i = stopPosNeckYaw; i <= initPosNeckYaw; i += 1)
    {
      servoNeck.moveJoint(neckYaw, i);

      internalTimer();
    }
    break;
    

}
}

void JointNeckClass::nod() //färdig
{
  initPosNeckPitch = 500;
  stopPosNeckPitch = 650;
  posNeckPitchDiff = stopPosNeckPitch - initPosNeckPitch;
 
  intervallTime = 10;

  servoNeck.LED(neckPitchRight, &rgb[4]);
  servoNeck.LED(neckPitchLeft, &rgb[4]);

  for (int i = 0; i <= 3; i++)
  {
    if (i == 0 || i == 2)
    {
      for (int i = initPosNeckPitch, k = initPosNeckPitch; i <= stopPosNeckPitch, k >= initPosNeckPitch - posNeckPitchDiff; i += 1, k -= 1)
      {
        servoNeck.moveJoint(neckPitchRight, i);
        internalTimer();

        servoNeck.moveJoint(neckPitchLeft, k);
        internalTimer();
      }
    }
    else if (i == 1 || i == 3)
    {
      for (int i = stopPosNeckPitch, k = initPosNeckPitch - posNeckPitchDiff; i >= initPosNeckPitch, k <= initPosNeckPitch; i -= 1, k += 1)
      {
        servoNeck.moveJoint(neckPitchRight, i);
        internalTimer();

        servoNeck.moveJoint(neckPitchLeft, k);
        internalTimer();
      }
    }
  }
}

void JointNeckClass::dab() // färdig
{
  initPosNeckYaw = 520;
  stopPosNeckYaw = 300;
  initPosNeckPitch = 500;
  stopPosNeckPitch = 600;
  posNeckPitchDiff = stopPosNeckPitch - initPosNeckPitch;

  revMillis = 0;
  currentMillis = millis();
  intervallTime = 10;
  for (int i = initPosNeckPitch, k = initPosNeckPitch; i <= stopPosNeckPitch, k >= initPosNeckPitch - posNeckPitchDiff; i += 1, k -= 1)
  {
    servoNeck.moveJoint(neckPitchRight, i);
    internalTimer();

    servoNeck.moveJoint(neckPitchLeft, k);
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

