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
XYZrobotServo shoulderRightRoll(A116servoSerial, 5);
XYZrobotServo elbowLeft(A116servo2Serial, 2);
XYZrobotServo shoulderLeftPitch(A116servo2Serial, 6);
XYZrobotServo shoulderLeftRoll(A116servo2Serial, 7);

//--------------------------------------Declaration of init variables---------------------------------------//

// Declaration of init variables
int initPosHand;
int initPosArm;
int initPosSSP;
int initPosArmLeftDab;

int initPosNeckPitch;
int initPosNeckYaw;
int initPosNeckRoll;

int initPosShoulderRoll;
int initPosShoulderPitch;

//----------------------------------Declaration of stop position variables-----------------------------------//

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

//-----------------------------------------------------------------------------------------------------------//

int posNeckPitchDiffInit;
int posNeckPitchDiffMove;
int posShoulderPitchDiff;

//---------------------------------Declaration of XL320 servo-motor objects----------------------------------//

XL320 servoLeft;
XL320 servoRight;
XL320 servoNeck;

//-----------------------------------------------------------------------------------------------------------//

char rgb[] = "rgbypcwo";

unsigned long revMillis;
unsigned long currentMillis;
int intervallTime;
int intervallTimeElbow;
int intervallTimeShoulder;

// Internal timer used to ensure the physical movement finishes before sending the next command
void internalTimer(int intervall)
{
  revMillis = millis(); // Set revMillis and currentMillis to the current value returned from the millis() function
  currentMillis = millis();
  /*
    Compare the value of currentMillis subtracted with revMillis and 
    continuse the loop as long as this value is LEQ than our input intervall
  */
  while (currentMillis - revMillis <= intervall)
  {
    currentMillis = millis(); // for each loop update the value of currentMillis with that from the millis() function
  }
}

// Function used to control an A1-16 servos motion from a start position to an end position
void stepFunc(XYZrobotServo A1_16_servo, int Start, int Stop, int Inc, int interval)
{
  // Check if the motion is meant to be a positive or negative rotation
  if (Start < Stop)
  {
    for (int pos = Start; pos <= Stop; pos += Inc)
    {
      // Tell the servo to move our input step amount for each microstep and wait for the motion to complete
      A1_16_servo.setPosition(pos, interval);
      internalTimer(interval);
    }
  }
  else
  {
    for (int pos = Start; pos >= Stop; pos -= Inc)
    {
      // Tell the servo to move our input step amount for each microstep and wait for the motion to complete
      A1_16_servo.setPosition(pos, interval);
      internalTimer(interval);
    }
  }
}

// Function used to control an XL-320 servos motion from a start position to an end position
void stepFuncXL320(XL320 servo, int joint, int initPos, int stopPos, int Inc)
{
  if (initPos < stopPos)
  {
    // Tell the servo to move our input step amount for each microstep and wait for the motion to complete
    for (int i = initPos; i <= stopPos; i += Inc)
    {
      servo.moveJoint(joint, i);
      internalTimer(10);
    }
  }
  else
  {
    // Tell the servo to move our input step amount for each microstep and wait for the motion to complete
    for (int i = initPos; i >= stopPos; i -= Inc)
    {
      servo.moveJoint(joint, i);
      internalTimer(10);
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
  pinMode(rxPin15, INPUT);
  pinMode(txPin14, OUTPUT);

  // Set the baud-rate of the arm and finger servos
  A116servo2Serial.begin(115200);  // Right arm
  XL320servo2Serial.begin(115200); // Right hand

  // Set the speed of each finger servo
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
  case 'a': // påse färdig
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
      internalTimer(intervallTime);

      servoRight.moveJoint(littleFingerRight, i);
      servoRight.LED(littleFingerRight, &rgb[5]);
      internalTimer(intervallTime);

      servoRight.moveJoint(ringFingerRight, i);
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

    stepFunc(elbowRight, initPosSSP, initPosArm, 1, intervallTimeElbow);

    for (int i = stopPosHand; i >= initPosHand; i -= 100) //reset av handen
    {
      servoRight.moveJoint(middleFingerRight, i);
      servoRight.LED(middleFingerRight, &rgb[5]);
      internalTimer(intervallTime);

      servoRight.moveJoint(ringFingerRight, i);
      servoRight.LED(ringFingerRight, &rgb[5]);
      internalTimer(intervallTime);

      servoRight.moveJoint(littleFingerRight, i);
      servoRight.LED(littleFingerRight, &rgb[5]);
      internalTimer(intervallTime);

      servoRight.moveJoint(thumbRight, i);
      servoRight.LED(thumbRight, &rgb[5]);
      internalTimer(intervallTime);

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

    stepFunc(shoulderRightPitch, stopPosShoulderPitch, initPosShoulderPitch, 4, intervallTimeElbow);
    stepFunc(elbowRight, stopPosArm, initPosArm, 4, intervallTimeElbow);

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
    stopPosArm = 400;
    initPosShoulderPitch = 500;
    stopPosShoulderPitch = 600;
    initPosShoulderRoll = 500;
    stopPosShoulderRoll = 300;

    stepFunc(shoulderRightRoll, stopPosShoulderRoll, initPosShoulderRoll, 4, intervallTimeElbow);
    stepFunc(shoulderRightPitch, stopPosShoulderPitch, initPosShoulderPitch, 2, intervallTimeElbow);
    stepFunc(elbowRight, stopPosArm, initPosArm, 4, intervallTimeElbow);
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

    stepFunc(shoulderRightPitch, stopPosShoulderPitch, initPosShoulderPitch, 4, intervallTimeElbow);
    stepFunc(elbowRight, stopPosArm, initPosArm, 4, intervallTimeElbow);

    for (int i = stopPosHand; i >= initPosHand; i -= 100) //knytnäven
    {
      servoRight.moveJoint(thumbRight, i);
      servoRight.LED(thumbRight, &rgb[5]);
      internalTimer(intervallTime);

      servoRight.moveJoint(indexFingerRight, i);
      servoRight.LED(indexFingerRight, &rgb[5]);
      internalTimer(intervallTime);

      servoRight.moveJoint(ringFingerRight, i);
      servoRight.LED(ringFingerRight, &rgb[5]);
      internalTimer(intervallTime);

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
}

void JointArmClassRight::dab() //LastCase = e
{
  intervallTimeElbow = 10;
  initPosArm = 0;
  stopPosArm = 400;
  intervallTime = 10;
  initPosShoulderRoll = 500;
  stopPosShoulderRoll = 300;
  initPosShoulderPitch = 500;
  stopPosShoulderPitch = 600;

  stepFunc(elbowRight, initPosArm, stopPosArm, 4, intervallTimeElbow);
  stepFunc(shoulderRightPitch, initPosShoulderPitch, stopPosShoulderPitch, 2, intervallTimeElbow);
  stepFunc(shoulderRightRoll, initPosShoulderRoll, stopPosShoulderRoll, 4, intervallTime);
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
  stopPosArm = 350;
  intervallTimeElbow = 10;

  stepFunc(elbowRight, initPosArm, stopPosArm, 4, intervallTimeElbow);
}

void JointArmClassRight::ShoulderPitchPerp() //färdig
{
  intervallTimeElbow = 10;
  initPosShoulderPitch = 500;
  stopPosShoulderPitch = 850;

  stepFunc(shoulderRightPitch, initPosShoulderPitch, stopPosShoulderPitch, 5, intervallTimeElbow);
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
  intervallTime = 10;

  stepFunc(elbowRight, stopPosArm, initPosSSP + 64, 4, intervallTimeElbow); //gå ner så det är 8 varv kvar.

  for (int k = stopPosHand, pos = initPosSSP + 64; k >= initPosHand, pos >= initPosSSP; k -= 50, pos -= 4) //När det är 8 varv kvar så börjar handen röra på sig
  {
    elbowRight.setPosition(pos, intervallTimeElbow);
    internalTimer(intervallTime);

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

  stepFunc(elbowRight, stopPosArm, initPosSSP + 64, 4, intervallTimeElbow); //gå ner så det är 8 varv kvar.

  for (int i = stopPosHand, pos = initPosSSP + 64; i >= initPosHand, pos >= initPosSSP; i -= 50, pos -= 4) //när det bara är 8 loopar kvar börjar handen röra på sig
  {
    elbowRight.setPosition(pos, intervallTimeElbow);
    internalTimer(intervallTimeElbow);

    servoRight.moveJoint(middleFingerRight, i);
    internalTimer(intervallTime);

    servoRight.moveJoint(ringFingerRight, i);
    internalTimer(intervallTime);

    servoRight.moveJoint(littleFingerRight, i);
    internalTimer(intervallTime);

    servoRight.moveJoint(thumbRight, i);
    internalTimer(intervallTime);

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
  stopPosHand = 750;
  intervallTime = 10;
  initPosHand = 0;

  servoRight.LED(middleFingerRight, &rgb[2]);

  for (int i = stopPosHand; i >= initPosHand; i -= 100)
  {
    servoRight.moveJoint(middleFingerRight, i);
    servoRight.moveJoint(ringFingerRight, i);
    servoRight.moveJoint(littleFingerRight, i);
    servoRight.moveJoint(thumbRight, i);
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
  stopPosHand = 750;
  intervallTime = 10;
  initPosHand = 0;

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

void JointArmClassRight::test()
{
  stopPosHand = 750;
  intervallTime = 10;
  initPosHand = 0;

  servoRight.moveJoint(thumbRight, stopPosHand);
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
    stopPosShoulderRoll = 950;
    initPosArm = 0;
    stopPosArm = 450;

    stepFunc(shoulderLeftPitch, 499, 500, 1, intervallTimeElbow);
    maxElbow();
    stepFunc(shoulderLeftRoll, stopPosShoulderRoll, initPosShoulderRoll, 4, intervallTimeElbow);
    stepFunc(elbowLeft, stopPosArm, initPosArm, 4, intervallTimeElbow);
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
  initPosShoulderRoll = 500;
  stopPosShoulderRoll = 950;

  stepFunc(shoulderLeftRoll, initPosShoulderRoll, stopPosShoulderRoll, 4, intervallTimeElbow);
}

void JointArmClassLeft::dabPart2()
{
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
  stopPosShoulderRoll = 850;

  stepFunc(shoulderLeftRoll, initPosShoulderRoll, stopPosShoulderRoll, 4, intervallTimeElbow);
}

//---------------------------------HandLeft--------------------------------------------------//

void JointArmClassLeft::open() //skriven, ej testad. LastCase = o.
{
  stopPosHand = 750;
  intervallTime = 10;
  initPosHand = 0;

  // Vad gör denna loopen? Repeterar samma uppgift 5ggr
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
  stopPosHand = 750;
  intervallTime = 10;
  initPosHand = 0;

  for (int i = initPosHand; i <= stopPosHand; i += 100)
  {
    servoLeft.moveJoint(middleFingerLeft, i);
    servoLeft.moveJoint(ringFingerLeft, i);
    servoLeft.moveJoint(littleFingerLeft, i);
    servoLeft.moveJoint(thumbLeft, i);
    servoLeft.moveJoint(indexFingerLeft, i);
    internalTimer(intervallTime);
  }
}

void JointArmClassLeft::test()
{
  stopPosHand = 750;
  intervallTime = 10;
  initPosHand = 0;

  servoLeft.moveJoint(4, 750);
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

  initPosNeckRoll = 500;
  initPosNeckPitch = 500;
  initPosNeckYaw = 519;
  stopPosNeckRoll = 520;
  stopPosNeckYaw = 520;
  stopPosNeckPitchUp = 600;
  stopPosNeckPitchDown = 400;
  posNeckPitchDiffMove = stopPosNeckPitchUp - stopPosNeckPitchDown;
  posNeckPitchDiffInit = stopPosNeckPitchUp - initPosNeckPitch;
  intervallTime = 10;

  stepFuncXL320(servoNeck, neckRoll, initPosNeckRoll, stopPosNeckRoll, 1);
  stepFuncXL320(servoNeck, neckYaw, initPosNeckYaw, stopPosNeckYaw, 1);
}

void JointNeckClass::test() //för att hitta rätt id. för yaw bör den vara över 10
{
  for (int i = 10; i <= 11; i++)
    servoNeck.moveJoint(i, random(499, 500));
}

void JointNeckClass::RESET(char LastCase)
{

  switch (LastCase)
  {

  case 'h': //nicka, färdig
            /*
    stopPosNeckPitchUp = 600;
    stopPosNeckPitchDown = 400;
    initPosNeckPitch = 500;
    posNeckPitchDiffMove = stopPosNeckPitchUp - stopPosNeckPitchDown;
    posNeckPitchDiffInit = stopPosNeckPitchUp - initPosNeckPitch;
    intervallTime=10;

    //Titta frammåt från att titta uppåt
    for (int i = stopPosNeckPitchDown, k = stopPosNeckPitchDown + posNeckPitchDiffMove; i <= initPosNeckPitch, k >= initPosNeckPitch; i++, k--)
    {
      servoNeck.moveJoint(neckPitchLeft, k);
      servoNeck.moveJoint(neckPitchRight, i);
      internalTimer(intervallTime);
    }
    */
    break;

  case 'i': //skaka på huvudet färdig
    /*
    initPosNeckYaw = 520;
    stopPosNeckYawLeft = 700;
    stopPosNeckYawRight = 300;

    stepFuncXL320(servoNeck, neckYaw, stopPosNeckYawLeft, initPosNeckYaw, 1);
    */
    break;

  case 'g':
    initPosNeckYaw = 500;
    stopPosNeckYaw = 200;
    
    stepFuncXL320(servoNeck, neckYaw, stopPosNeckYaw, initPosNeckYaw, 1);
    break;

  case 'f': //fuck färdig
    initPosNeckYaw = 500;
    stopPosNeckYaw = 200;

    stepFuncXL320(servoNeck, neckYaw, stopPosNeckYaw, initPosNeckYaw, 1);
    break;

  case 'e': //dab färdig
    initPosNeckPitch = 500;
    initPosNeckYaw = 520;
    stopPosNeckPitchUp = 600;
    stopPosNeckPitchDown = 400;
    stopPosNeckYaw = 350;
    posNeckPitchDiffMove = stopPosNeckPitchUp - stopPosNeckPitchDown;
    posNeckPitchDiffInit = stopPosNeckPitchUp - initPosNeckPitch;
    intervallTime = 10;

    // frammåt från neråt tittande
    for (int i = stopPosNeckPitchUp, k = stopPosNeckPitchDown; i >= initPosNeckPitch, k <= initPosNeckPitch; i--, k++)
    {
      servoNeck.moveJoint(neckPitchLeft, k);
      servoNeck.moveJoint(neckPitchRight, i);
      internalTimer(intervallTime);
    }

    stepFuncXL320(servoNeck, neckYaw, stopPosNeckYaw, initPosNeckYaw, 1);
    break;

  case 'k': //titta frammåt från neråt färdig
    wakeUp();
    break;

  case 't': //titta frammåt från uppåt färdig
    stopPosNeckPitchUp = 600;
    stopPosNeckPitchDown = 400;
    initPosNeckPitch = 500;
    posNeckPitchDiffMove = stopPosNeckPitchUp - stopPosNeckPitchDown;
    posNeckPitchDiffInit = stopPosNeckPitchUp - initPosNeckPitch;
    intervallTime = 10;

    //Frammåt från titta uppåt
    for (int i = stopPosNeckPitchUp, k = stopPosNeckPitchDown; i >= initPosNeckPitch, k <= initPosNeckPitch; i--, k++)
    {
      servoNeck.moveJoint(neckPitchLeft, i);
      servoNeck.moveJoint(neckPitchRight, k);
      internalTimer(intervallTime);
    }
    break;

  case 'u': //titta från vänster till frammåt färdig
    initPosNeckYaw = 500;
    stopPosNeckYaw = 800;

    stepFuncXL320(servoNeck, neckYaw, stopPosNeckYaw, initPosNeckYaw, 1);
    break;

  case 'v': //titta från höger till frammåt färdig
    initPosNeckYaw = 500;
    stopPosNeckYaw = 200;

    stepFuncXL320(servoNeck, neckYaw, stopPosNeckYaw, initPosNeckYaw, 1);
    break;

  case 'w': //titta fråmmåt från vänster roll färdig
    initPosNeckRoll = 520;
    stopPosNeckRoll = 450;

    stepFuncXL320(servoNeck, neckRoll, stopPosNeckRoll, initPosNeckRoll, 1);
    break;

  case 'x': //titta frammåt från höger roll färdig
    initPosNeckRoll = 520;
    stopPosNeckRoll = 690;

    stepFuncXL320(servoNeck, neckRoll, stopPosNeckRoll, initPosNeckRoll, 1);
    break;
  }
}

void JointNeckClass::nod() //färdig
{
  stopPosNeckPitchUp = 580;
  stopPosNeckPitchDown = 420;
  initPosNeckPitch = 500;
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

  //Uppåt
  for (int i = stopPosNeckPitchDown, k = stopPosNeckPitchDown + posNeckPitchDiffMove; i <= stopPosNeckPitchUp, k >= stopPosNeckPitchDown; i++, k--)
  {
    servoNeck.moveJoint(neckPitchLeft, i);
    servoNeck.moveJoint(neckPitchRight, k);
    internalTimer(intervallTime);
  }

  //Neråt
  for (int i = stopPosNeckPitchDown, k = stopPosNeckPitchDown + posNeckPitchDiffMove; i <= stopPosNeckPitchUp, k >= stopPosNeckPitchDown; i++, k--)
  {
    servoNeck.moveJoint(neckPitchLeft, k);
    servoNeck.moveJoint(neckPitchRight, i);
    internalTimer(intervallTime);
  }

  //Uppåt
  for (int i = stopPosNeckPitchDown, k = stopPosNeckPitchDown + posNeckPitchDiffMove; i <= stopPosNeckPitchUp, k >= stopPosNeckPitchDown; i++, k--)
  {
    servoNeck.moveJoint(neckPitchLeft, i);
    servoNeck.moveJoint(neckPitchRight, k);
    internalTimer(intervallTime);
  }

  //Titta frammåt från att titta uppåt
  for (int i = stopPosNeckPitchDown, k = stopPosNeckPitchDown + posNeckPitchDiffMove; i <= initPosNeckPitch, k >= initPosNeckPitch; i++, k--)
  {
    servoNeck.moveJoint(neckPitchLeft, k);
    servoNeck.moveJoint(neckPitchRight, i);
    internalTimer(intervallTime);
  }
}

void JointNeckClass::neckPitchDown() //färdig
{
  stopPosNeckPitchUp = 600;
  stopPosNeckPitchDown = 400;
  initPosNeckPitch = 500;
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
  stopPosNeckPitchUp = 600;
  stopPosNeckPitchDown = 400;
  initPosNeckPitch = 500;
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
  initPosNeckYaw = 500;
  stopPosNeckYaw = 800;

  stepFuncXL320(servoNeck, neckYaw, initPosNeckYaw, stopPosNeckYaw, 2);
}

void JointNeckClass::neckYawLookRight() //färdig
{
  initPosNeckYaw = 500;
  stopPosNeckYaw = 200;

  stepFuncXL320(servoNeck, neckYaw, initPosNeckYaw, stopPosNeckYaw, 2);
}

void JointNeckClass::shake() //färdig
{
  initPosNeckYaw = 520;
  stopPosNeckYawLeft = 700;
  stopPosNeckYawRight = 300;

  stepFuncXL320(servoNeck, neckYaw, initPosNeckYaw, stopPosNeckYawLeft, 1);
  stepFuncXL320(servoNeck, neckYaw, stopPosNeckYawLeft, stopPosNeckYawRight, 1);
  stepFuncXL320(servoNeck, neckYaw, stopPosNeckYawRight, stopPosNeckYawLeft, 1);
  stepFuncXL320(servoNeck, neckYaw, stopPosNeckYawLeft, initPosNeckYaw, 1);
}

void JointNeckClass::neckRollTiltLeft() //färdig
{
  initPosNeckRoll = 520;
  stopPosNeckRoll = 450;

  stepFuncXL320(servoNeck, neckRoll, initPosNeckRoll, stopPosNeckRoll, 1);
}

void JointNeckClass::neckRollTiltRight() //färdig
{
  initPosNeckRoll = 520;
  stopPosNeckRoll = 690;

  stepFuncXL320(servoNeck, neckRoll, initPosNeckRoll, stopPosNeckRoll, 1);
}

void JointNeckClass::wakeUp()
{
  stopPosNeckPitchUp = 600;
  stopPosNeckPitchDown = 400;
  initPosNeckPitch = 520;
  posNeckPitchDiffMove = stopPosNeckPitchUp - stopPosNeckPitchDown;
  posNeckPitchDiffInit = stopPosNeckPitchUp - initPosNeckPitch;
  intervallTime = 10;

  // neråt från frammåt tittande
  for (int i = stopPosNeckPitchUp, k = stopPosNeckPitchDown; i >= initPosNeckPitch, k <= initPosNeckPitch; i--, k++)
  {
    servoNeck.moveJoint(neckPitchLeft, k);
    servoNeck.moveJoint(neckPitchRight, i);
    internalTimer(intervallTime);
  }
}

void JointNeckClass::wakeDown()
{
  stopPosNeckPitchUp = 600;
  stopPosNeckPitchDown = 400;
  initPosNeckPitch = 500;
  posNeckPitchDiffMove = stopPosNeckPitchUp - stopPosNeckPitchDown;
  posNeckPitchDiffInit = stopPosNeckPitchUp - initPosNeckPitch;
  intervallTime = 10;

  //Frammåt från titta uppåt
  for (int i = stopPosNeckPitchUp, k = stopPosNeckPitchDown; i >= initPosNeckPitch, k <= initPosNeckPitch; i--, k++)
  {
    servoNeck.moveJoint(neckPitchLeft, i);
    servoNeck.moveJoint(neckPitchRight, k);
    internalTimer(intervallTime);
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

void MultiPartClass::dab()
{
  initPosArm = 0;
  initPosArmLeftDab = 400;
  intervallTimeElbow = 10;
  initPosNeckPitch = 500;
  initPosNeckYaw = 520;
  stopPosArm = 450;
  stopPosNeckPitchUp = 600;
  stopPosNeckPitchDown = 400;
  stopPosNeckYaw = 350;
  posNeckPitchDiffMove = stopPosNeckPitchUp - stopPosNeckPitchDown;
  posNeckPitchDiffInit = stopPosNeckPitchUp - initPosNeckPitch;
  intervallTime = 10;

  stepFunc(shoulderLeftPitch, 500, 499, 1, intervallTimeElbow);
  stepFunc(elbowLeft, stopPosArm, initPosArmLeftDab, 4, intervallTimeElbow);

  // neråt från frammåt tittande
  for (int i = initPosNeckPitch, k = initPosNeckPitch, j = initPosNeckYaw, l = initPosArmLeftDab; i <= stopPosNeckPitchUp, k >= stopPosNeckPitchDown, j >= stopPosNeckYaw, l >= initPosArm; i += 2, k -= 2, j -= 3, l -= 8)
  {
    servoNeck.moveJoint(neckPitchLeft, k);
    servoNeck.moveJoint(neckPitchRight, i);
    servoNeck.moveJoint(neckYaw, j);
    internalTimer(intervallTime);

    elbowLeft.setPosition(l, intervallTimeElbow);
    internalTimer(intervallTimeElbow);
  }
}

//----------------------------------------------------------------------------------------------------------------
MultiPartClass multiPart = MultiPartClass();