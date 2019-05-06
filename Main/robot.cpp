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

boolean ran = false;
char lastCase;
//char LastCase = 'a';

char rgb[] = "rgbypcwo";

unsigned long revMillis;
unsigned long currentMillis;
int intervallTime;
int intervallTimeElbow;
int intervallTimeShoulder;

void revCurMillis()
{
  revMillis = millis();
  currentMillis = millis();
  while (currentMillis - revMillis <= intervallTime)
  {
    currentMillis = millis();
  }
}

//---------------------------------Communication--------------------------------------------------//
Communication::Communication()
{
}
char Communication::readSerial()
{
  boolean newData = false;
  char incoming;
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

void JointArmClassRight::RESET(char LastCase)
{
  Serial.println(LastCase);

  //if (!ran)
  //{
  switch (LastCase)
  {
  case 'a': //påse färdig

    revMillis = 0;
    currentMillis = millis();

    intervallTimeElbow = 10;

    initPosSSP = 300;
    initPosArm = 0;

    for (int pos = initPosSSP; pos >= initPosArm; pos -= 4) //Reset av armen
    {

      elbowRight.setPosition(pos, intervallTimeElbow);

      revCurMillis();
    }
    ran = true;
    break;

  case 'b': //sax färdig
    stopPosHand = 800;
    revMillis = 0;
    currentMillis = millis();
    intervallTime = 10;
    intervallTimeElbow = 10;
    initPosHand = 0;
    initPosSSP = 300;
    initPosArm = 0;

    for (int pos = initPosSSP; pos >= initPosArm; pos -= 4) //reset av armen
    {

      elbowRight.setPosition(pos, intervallTime);

      revCurMillis();
    }

    for (int i = stopPosHand; i >= initPosHand; i -= 100) //reset av handen
    {
      servoRight.moveJoint(thumbRight, i);
      servoRight.LED(thumbRight, &rgb[5]);
      revCurMillis();

      servoRight.moveJoint(littleFingerRight, i);
      servoRight.LED(littleFingerRight, &rgb[5]);
      revCurMillis();

      servoRight.moveJoint(ringFingerRight, i);
      servoRight.LED(ringFingerRight, &rgb[5]);
      revCurMillis();
    }
    ran = true;
    break;

  case 'c': //sten färdig
    stopPosHand = 800;
    revMillis = 0;
    currentMillis = millis();
    intervallTime = 10;
    intervallTimeElbow = 10;
    initPosHand = 0;
    initPosSSP = 300;
    initPosArm = 0;

    for (int pos = initPosSSP; pos >= initPosArm; pos -= 4) //Reset av armen
    {
      elbowRight.setPosition(pos, intervallTimeElbow);
      revCurMillis();
    }

    for (int i = stopPosHand; i >= initPosHand; i -= 100) //reset av handen
    {

      servoRight.moveJoint(middleFingerRight, i);
      servoRight.LED(middleFingerRight, &rgb[5]);
      revCurMillis();

      servoRight.moveJoint(ringFingerRight, i);
      servoRight.LED(ringFingerRight, &rgb[5]);
      revCurMillis();

      servoRight.moveJoint(littleFingerRight, i);
      servoRight.LED(littleFingerRight, &rgb[5]);
      revCurMillis();

      servoRight.moveJoint(thumbRight, i);
      servoRight.LED(thumbRight, &rgb[5]);
      revCurMillis();

      servoRight.moveJoint(indexFingerRight, i);
      servoRight.LED(indexFingerRight, &rgb[5]);
      revCurMillis();
    }
    //ran = true;
    break;

  case 'd': //ok färdig
            //if (!ran)
            //{
    stopPosHand = 800;
    initPosHand = 0;
    revMillis = 0;
    currentMillis = millis();
    intervallTime = 10;

    for (int i = stopPosHand; i >= initPosHand; i -= 100) //knytnäven
    {
      servoRight.moveJoint(indexFingerRight, i);
      servoRight.LED(indexFingerRight, &rgb[5]);
      revCurMillis();
    }

    //ran = true;
    //}
    break;
  case 'e': // dab, färdig
    revMillis = 0;
    currentMillis = millis();
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
      revCurMillis();
    }

    for (int pos = stopPosArm, k = stopPosShoulderPitch; pos >= initPosArm, k >= initPosShoulderPitch; pos -= 4, k -= 2) //Gå ner så det bara är 8 varv kvar till initPosSSP
    {
      elbowRight.setPosition(pos, intervallTimeElbow);
      revCurMillis();

      shoulderRightPitch.setPosition(k, intervallTimeElbow);
      revCurMillis();
    }
    break;
  case 'f': //fack färdig

    stopPosHand = 800;
    initPosHand = 0;
    revMillis = 0;
    currentMillis = millis();
    intervallTime = 10;

    for (int i = stopPosHand; i >= initPosHand; i -= 100) //knytnäven
    {

      servoRight.moveJoint(thumbRight, i);
      servoRight.LED(thumbRight, &rgb[5]);
      revCurMillis();

      servoRight.moveJoint(indexFingerRight, i);
      servoRight.LED(indexFingerRight, &rgb[5]);
      revCurMillis();

      servoRight.moveJoint(ringFingerRight, i);
      servoRight.LED(ringFingerRight, &rgb[5]);
      revCurMillis();

      servoRight.moveJoint(littleFingerRight, i);
      servoRight.LED(littleFingerRight, &rgb[5]);
      revCurMillis();
    }
    ran = true;
    break;

  case 'g': //test
    initPosArm = 0;
    stopPosArm = 330;

    revMillis = 0;
    currentMillis = millis();
    intervallTimeElbow = 10;

    for (int pos = stopPosArm; pos >= initPosArm; pos -= 4)
    {
      elbowRight.setPosition(pos, intervallTimeElbow);
      revCurMillis();
    }
    break;
  }
  //}
}

void JointArmClassRight::armMotionSSP() //färdig
{

  initPosArm = 0;
  stopPosArm = 500;
  initPosSSP = 300;

  revMillis = 0;
  currentMillis = millis();
  intervallTimeElbow = 10;

  //if (!ran)
  //{
  for (int j = 0; j <= 5; j++) //armMotionSSP
  {

    if (j == 0)
    {
      for (int pos = initPosArm; pos <= initPosSSP; pos += 4)
      {
        elbowRight.setPosition(pos, intervallTimeElbow);
        revCurMillis();
      }
    }

    if (j == 1 || j == 3 || j == 5)
    {

      for (int pos = initPosSSP; pos <= stopPosArm; pos += 4)
      {
        elbowRight.setPosition(pos, intervallTimeElbow);
        revCurMillis();
      }
    }

    if (j == 2 || j == 4)
    {

      for (int pos = stopPosArm; pos >= initPosSSP; pos -= 4)
      {
        elbowRight.setPosition(pos, intervallTimeElbow);
        revCurMillis();
      }
    }
  }

  ran = true;
  //}
}

void JointArmClassRight::dab() //färdig, LastCase = e
{
  revMillis = 0;
  currentMillis = millis();
  intervallTime = 10;

  intervallTimeElbow = 10;
  initPosArm = 0;
  stopPosArm = 400;

  initPosShoulderPitch = 500;
  stopPosShoulderPitch = 700;

  for (int pos = initPosArm, k = initPosShoulderPitch; pos <= stopPosArm, k <= stopPosShoulderPitch; pos += 4, k += 2) //Gå ner så det bara är 8 varv kvar till initPosSSP
  {
    elbowRight.setPosition(pos, intervallTimeElbow);
    revCurMillis();

    shoulderRightPitch.setPosition(k, intervallTimeElbow);
    revCurMillis();
  }
}

void JointArmClassRight::maxElbow() //färdig
{
  initPosArm = 0;
  stopPosArm = 500;

  revMillis = 0;
  currentMillis = millis();
  intervallTimeElbow = 10;

  for (int pos = initPosArm; pos <= stopPosArm; pos += 4)
  {
    elbowRight.setPosition(pos, intervallTimeElbow);
    revCurMillis();
  }
}

void JointArmClassRight::perpendicular() //skriven, ej testad. inte säker på att det är 90 grader, men typ.
{
  initPosArm = 0;
  stopPosArm = 330;

  revMillis = 0;
  currentMillis = millis();
  intervallTimeElbow = 10;

  for (int pos = initPosArm; pos <= stopPosArm; pos += 4)
  {
    elbowRight.setPosition(pos, intervallTimeElbow);
    revCurMillis();
  }
}

void JointArmClassRight::ShoulderPitchPerp() //färdig
{
  revMillis = 0;
  currentMillis = millis();
  intervallTime = 10;

  intervallTimeElbow = 10;

  initPosShoulderPitch = 500;
  stopPosShoulderPitch = 800;

  for (int pos = initPosShoulderPitch; pos <= stopPosShoulderPitch; pos += 10) //Gå ner så det bara är 8 varv kvar till initPosSSP
  {
    shoulderRightPitch.setPosition(pos, intervallTimeElbow);
    revCurMillis();
  }
}

void JointArmClassRight::ShoulderRollPerp() //färdig
{
  revMillis = 0;
  currentMillis = millis();
  intervallTime = 10;

  intervallTimeElbow = 10;

  initPosShoulderRoll = 800;
  stopPosShoulderRoll = 500;

  for (int k = initPosShoulderRoll; k >= stopPosShoulderRoll; k -= 5)
  {
    shoulderRightRoll.setPosition(k, intervallTimeElbow);
    revCurMillis();
  }
}
//---------------------------------HandRight-------------------------------------------------//
void JointArmClassRight::rock() // lastCase = c färdig
{
  lastCase = 'c';
  //if (!ran)
  //{
  revMillis = 0;
  currentMillis = millis();

  intervallTimeElbow = 10;
  stopPosArm = 500;
  initPosSSP = 300;

  for (int pos = stopPosArm; pos >= initPosSSP; pos -= 4) //Gå ner hela vägen utan att röra handen eftersom den redan är en näve
  {
    elbowRight.setPosition(pos, intervallTimeElbow);
    revCurMillis();
  }

  ran = true;
  //}
}
void JointArmClassRight::scissor() //lastCase = b färdig
{
  lastCase = 'b';
  //if (!ran)
  //{

  stopPosHand = 800;
  initPosHand = 0;
  revMillis = 0;
  currentMillis = millis();
  intervallTime = 10;

  intervallTimeElbow = 10;
  stopPosArm = 500;
  initPosSSP = 300;

  for (int pos = stopPosArm; pos >= initPosSSP + 32; pos -= 4) //Gå ner så det bara är 8 varv kvar till initPosSSP
  {
    elbowRight.setPosition(pos, intervallTimeElbow);
    revCurMillis();
  }

  for (int k = stopPosHand, pos = initPosSSP + 32; k >= initPosHand, pos >= initPosSSP; k -= 100, pos -= 4) //När det är 8 varv kvar så börjar handen röra på sig
  {

    elbowRight.setPosition(pos, intervallTimeElbow);
    revCurMillis();

    servoRight.moveJoint(indexFingerRight, k);
    servoRight.LED(indexFingerRight, &rgb[1]);
    revCurMillis();

    servoRight.moveJoint(middleFingerRight, k);
    servoRight.LED(middleFingerRight, &rgb[1]);
    revCurMillis();
  }

  ran = true;
  //}
}

void JointArmClassRight::paper() // lastCase = a färdig
{
  lastCase = 'a';
  //if (!ran)
  //{
  stopPosHand = 800;
  initPosHand = 0;

  revMillis = 0;
  currentMillis = millis();
  intervallTime = 10;

  intervallTimeElbow = 10;
  stopPosArm = 500;
  initPosSSP = 300;

  for (int pos = stopPosArm; pos >= initPosSSP + 32; pos -= 4) //Gå ner så det bara är 8 varv kvar till initPosSSP
  {
    elbowRight.setPosition(pos, intervallTimeElbow);
    revCurMillis();
  }
  for (int i = stopPosHand, pos = initPosSSP + 32; i >= initPosHand, pos >= initPosSSP; i -= 100, pos -= 4) //när det bara är 8 loopar kvar börjar handen röra på sig
  {
    elbowRight.setPosition(pos, intervallTimeElbow);
    revCurMillis();

    servoRight.moveJoint(middleFingerRight, i);
    servoRight.LED(middleFingerRight, &rgb[1]);
    revCurMillis();

    servoRight.moveJoint(ringFingerRight, i);
    servoRight.LED(ringFingerRight, &rgb[1]);
    revCurMillis();

    servoRight.moveJoint(littleFingerRight, i);
    servoRight.LED(littleFingerRight, &rgb[1]);
    revCurMillis();

    servoRight.moveJoint(thumbRight, i);
    servoRight.LED(thumbRight, &rgb[1]);
    revCurMillis();

    servoRight.moveJoint(indexFingerRight, i);
    servoRight.LED(indexFingerRight, &rgb[1]);
    revCurMillis();
  }

  ran = true;
  //}
}

void JointArmClassRight::ok() // färdig lastCase = d
{
  lastCase = 'd';
  if (!ran)
  {
    stopPosHand = 800;
    initPosHand = 0;
    revMillis = 0;
    currentMillis = millis();
    intervallTime = 10;

    for (int i = initPosHand; i <= stopPosHand; i += 100) //knytnäven
    {
      servoRight.moveJoint(indexFingerRight, i);
      servoRight.LED(indexFingerRight, &rgb[1]);
      revCurMillis();
    }
    ran = true;
  }
}

void JointArmClassRight::open() //färdig lastCase = o
{
  lastCase = 'o';

  if (!ran)
  {
    stopPosHand = 800;
    revMillis = 0;
    currentMillis = millis();
    intervallTime = 10;
    initPosHand = 0;

    for (int i = stopPosHand; i >= initPosHand; i -= 100)
    {
      servoRight.moveJoint(middleFingerRight, i);
      servoRight.LED(middleFingerRight, &rgb[1]);
      revCurMillis();

      servoRight.moveJoint(ringFingerRight, i);
      servoRight.LED(ringFingerRight, &rgb[1]);
      revCurMillis();
      
      servoRight.moveJoint(littleFingerRight, i);
      servoRight.LED(littleFingerRight, &rgb[1]);
      revCurMillis();

      servoRight.moveJoint(thumbRight, i);
      servoRight.LED(thumbRight, &rgb[1]);
      revCurMillis();

      servoRight.moveJoint(indexFingerRight, i);
      servoRight.LED(indexFingerRight, &rgb[1]);
      revCurMillis();
    }
    ran = true;
  }
}

void JointArmClassRight::fack() //färdig lastCase = f
{
  lastCase = 'f';
  if (!ran)
  {
    stopPosHand = 800;
    initPosHand = 0;
    revMillis = 0;
    currentMillis = millis();
    intervallTime = 10;

    for (int i = initPosHand; i <= stopPosHand; i += 100) //knytnäven
    {
      servoRight.moveJoint(thumbRight, i);
      servoRight.LED(thumbRight, &rgb[1]);
      revCurMillis();

      servoRight.moveJoint(indexFingerRight, i);
      servoRight.LED(indexFingerRight, &rgb[1]);
      revCurMillis();

      servoRight.moveJoint(ringFingerRight, i);
      servoRight.LED(ringFingerRight, &rgb[1]);
      revCurMillis();

      servoRight.moveJoint(littleFingerRight, i);
      servoRight.LED(littleFingerRight, &rgb[1]);
      revCurMillis();
    }
    ran = true;
  }
}

void JointArmClassRight::close() //färdig lastCase = p
{
  lastCase = 'p';
  //if (!ran)
  //{
  stopPosHand = 800;
  revMillis = 0;
  currentMillis = millis();
  intervallTime = 10;
  initPosHand = 0;

  for (int i = initPosHand; i <= stopPosHand; i += 100)
  {
    servoRight.moveJoint(middleFingerRight, i);
    servoRight.LED(middleFingerRight, &rgb[1]);
    revCurMillis();

    servoRight.moveJoint(ringFingerRight, i);
    servoRight.LED(ringFingerRight, &rgb[1]);
    revCurMillis();

    servoRight.moveJoint(littleFingerRight, i);
    servoRight.LED(littleFingerRight, &rgb[1]);
    revCurMillis();

    servoRight.moveJoint(thumbRight, i);
    servoRight.LED(thumbRight, &rgb[1]);
    revCurMillis();

    servoRight.moveJoint(indexFingerRight, i);
    servoRight.LED(indexFingerRight, &rgb[1]);
    revCurMillis();
  }
  //ran = true;
  //}
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
<<<<<<< HEAD
      shoulderLeftRoll.setPosition(k, intervallTimeElbow);
      revCurMillis();
=======

      shoulderRightRoll.setPosition(k, intervallTimeElbow);

      revMillis = millis();
      currentMillis = millis();
      while (currentMillis - revMillis <= intervallTimeElbow)
      {
        currentMillis = millis();
      }
>>>>>>> parent of f6b50c2... update
    }

    jointArmLeft.dabPart2();

    break;
  case 'p': //

    break;
  }
}

void JointArmClassLeft::dabPart1() //skriven ,ej testad
{
  revMillis = 0;
  currentMillis = millis();
  intervallTime = 10;

  intervallTimeElbow = 10;
  initPosArm = 0;
  stopPosArm = 400;

  initPosShoulderPitch = 500;
  stopPosShoulderPitch = 700;

  for (int pos = initPosArm, k = initPosShoulderPitch; pos <= stopPosArm, k <= stopPosShoulderPitch; pos += 4, k += 2) //Gå ner så det bara är 8 varv kvar till initPosSSP
  {
    elbowLeft.setPosition(pos, intervallTimeElbow);
    revCurMillis();

    shoulderLeftPitch.setPosition(k, intervallTimeElbow);
    revCurMillis();
  }
}

void JointArmClassLeft::ShoulderRollPerp()
{
  revMillis = 0;
  currentMillis = millis();
  intervallTime = 10;

  intervallTimeElbow = 10;

  initPosShoulderRoll = 800;
  stopPosShoulderRoll = 500;

  for (int k = initPosShoulderRoll; k >= stopPosShoulderRoll; k -= 5)
  {
    shoulderLeftRoll.setPosition(k, intervallTimeElbow);
    revCurMillis();
  }
}

void JointArmClassLeft::dabPart2()
{
  revMillis = 0;
  currentMillis = millis();
  intervallTime = 10;

  intervallTimeElbow = 10;
  initPosArm = 0;
  stopPosArm = 400;

  initPosShoulderPitch = 500;
  stopPosShoulderPitch = 700;

<<<<<<< HEAD
  for (int k = initPosShoulderPitch - posShoulderPitchDiff; k <= initPosShoulderPitch; k += 2) //Gå ner så det bara är 8 varv kvar till initPosSSP
  {
    shoulderLeftPitch.setPosition(k, intervallTimeElbow);
    revCurMillis();
  }

  for (int pos = stopPosArm; pos >= initPosArm; pos -= 4)
  {
    elbowLeft.setPosition(pos, intervallTimeElbow);
    revCurMillis();
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
    revCurMillis();
=======
  for (int pos = stopPosArm, k = stopPosShoulderPitch; pos >= initPosArm, k >= initPosShoulderPitch; pos -= 4, k -= 2) 
  {
    elbowLeft.setPosition(pos, intervallTimeElbow);

    revMillis = millis();
    currentMillis = millis();
    while (currentMillis - revMillis <= intervallTimeElbow)
    {
      currentMillis = millis();
    }

    shoulderLeftPitch.setPosition(k, intervallTimeElbow);

    revMillis = millis();
    currentMillis = millis();
    while (currentMillis - revMillis <= intervallTimeElbow)
    {
      currentMillis = millis();
    }
>>>>>>> parent of f6b50c2... update
  }
  
}
//---------------------------------HandLeft--------------------------------------------------//

<<<<<<< HEAD
=======
void JointArmClassLeft::rock()
{
}
void JointArmClassLeft::scissor()
{
}

void JointArmClassLeft::paper()
{
}

>>>>>>> parent of f6b50c2... update
void JointArmClassLeft::open() //skriven, ej testad. LastCase = o.
{

  lastCase = 'o';

  if (!ran)
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
      revCurMillis();

      servoLeft.moveJoint(ringFingerLeft, i);
      servoLeft.LED(ringFingerRight, &rgb[1]);
      revCurMillis();

      servoLeft.moveJoint(littleFingerLeft, i);
      servoLeft.LED(littleFingerLeft, &rgb[1]);
      revCurMillis();

      servoLeft.moveJoint(thumbLeft, i);
      servoLeft.LED(thumbLeft, &rgb[1]);
      revCurMillis();

      servoLeft.moveJoint(indexFingerLeft, i);
      servoLeft.LED(indexFingerLeft, &rgb[1]);
      revCurMillis();
    }
    ran = true;
  }
}

void JointArmClassLeft::close() //skriven, ej testad. lastCase = p.
{
  lastCase = 'p';
  stopPosHand = 800;
  revMillis = 0;
  currentMillis = millis();
  intervallTime = 10;
  initPosHand = 0;

  for (int i = initPosHand; i <= stopPosHand; i += 100)
  {
    servoLeft.moveJoint(middleFingerLeft, i);
    servoLeft.LED(middleFingerLeft, &rgb[1]);
    revCurMillis();

    servoLeft.moveJoint(ringFingerLeft, i);
    servoLeft.LED(ringFingerLeft, &rgb[1]);
    revCurMillis();

    servoLeft.moveJoint(littleFingerLeft, i);
    servoLeft.LED(littleFingerLeft, &rgb[1]);
    revCurMillis();

    servoLeft.moveJoint(thumbLeft, i);
    servoLeft.LED(thumbLeft, &rgb[1]);
    revCurMillis();

    servoLeft.moveJoint(indexFingerRight, i);
    servoLeft.LED(indexFingerRight, &rgb[1]);
    revCurMillis();
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
    revMillis = 0;
    currentMillis = millis();
      intervallTime = 10;
      servoNeck.LED(neckPitchRight, &rgb[3]);
      servoNeck.LED(neckPitchLeft, &rgb[3]);
      servoNeck.LED(neckYaw, &rgb[3]);

<<<<<<< HEAD
    for (int i = stopPosNeckPitch, k = initPosNeckPitch - posNeckPitchDiff; i >= initPosNeckPitch, k <= initPosNeckPitch; i -= 1, k += 1)
    {
=======
      for (int i = stopPosNeckPitch, k = initPosNeckPitch - posNeckPitchDiff; i >= initPosNeckPitch, k <= initPosNeckPitch; i -= 1, k += 1)
      {

>>>>>>> parent of f6b50c2... update
      servoNeck.moveJoint(neckPitchRight, i);
      revCurMillis();

      servoNeck.moveJoint(neckPitchLeft, k);
<<<<<<< HEAD
      revCurMillis();
    }
=======

      revMillis = millis();
      currentMillis = millis();
      while (currentMillis - revMillis <= intervallTime)
      {
        currentMillis = millis();
      }
      }
>>>>>>> parent of f6b50c2... update

      for (int i = stopPosNeckYaw; i <= initPosNeckYaw; i += 1)
      {
      servoNeck.moveJoint(neckYaw, i);
<<<<<<< HEAD
      revCurMillis();
    }
=======

      revMillis = millis();
      currentMillis = millis();
      while (currentMillis - revMillis <= intervallTime)
      {
        currentMillis = millis();
      }
      }
>>>>>>> parent of f6b50c2... update

  break;
  }
}

void JointNeckClass::nod() //färdig
{
  initPosNeckPitch = 500;
  stopPosNeckPitch = 650;
  posNeckPitchDiff = stopPosNeckPitch - initPosNeckPitch;
  revMillis = 0;
  currentMillis = millis();
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
        revCurMillis();

        servoNeck.moveJoint(neckPitchLeft, k);
        revCurMillis();
      }
    }
    else if (i == 1 || i == 3)
    {
      for (int i = stopPosNeckPitch, k = initPosNeckPitch - posNeckPitchDiff; i >= initPosNeckPitch, k <= initPosNeckPitch; i -= 1, k += 1)
      {
        servoNeck.moveJoint(neckPitchRight, i);
        revCurMillis();

        servoNeck.moveJoint(neckPitchLeft, k);
        revCurMillis();
      }
    }
  }
}

void JointNeckClass::dab() // färdig
{
<<<<<<< HEAD
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
    revCurMillis();

    servoNeck.moveJoint(neckPitchLeft, k);
    revCurMillis();
  }
=======
  initPosNeckYaw = 500;
    stopPosNeckYaw = 350;
    initPosNeckPitch = 500;
    stopPosNeckPitch = 600;
    posNeckPitchDiff = stopPosNeckPitch - initPosNeckPitch;

    revMillis = 0;
    currentMillis = millis();
    intervallTime = 10;
    servoNeck.LED(neckPitchRight, &rgb[2]);
    servoNeck.LED(neckPitchLeft, &rgb[2]);
    servoNeck.LED(neckYaw, &rgb[2]);

    for (int i = initPosNeckPitch, k = initPosNeckPitch; i <= stopPosNeckPitch, k >= initPosNeckPitch - posNeckPitchDiff; i += 1, k -= 1)
    {

      servoNeck.moveJoint(neckPitchRight, i);
      revMillis = millis();
      currentMillis = millis();
      while (currentMillis - revMillis <= intervallTime)
      {
        currentMillis = millis();
      }

      servoNeck.moveJoint(neckPitchLeft, k);

      revMillis = millis();
      currentMillis = millis();
      while (currentMillis - revMillis <= intervallTime)
      {
        currentMillis = millis();
      }
    }
>>>>>>> parent of f6b50c2... update

    for (int i = initPosNeckYaw; i >= stopPosNeckYaw; i -= 1)
    {
    servoNeck.moveJoint(neckYaw, i);
<<<<<<< HEAD
    revCurMillis();
  }
=======

    revMillis = millis();
    currentMillis = millis();
    while (currentMillis - revMillis <= intervallTime)
    {
      currentMillis = millis();
    }
    }
  
>>>>>>> parent of f6b50c2... update
}

//-------------------------------------Skriv nackfunktioner över------------------------------------------------//

JointNeckClass jointNeck = JointNeckClass();

//-------------------------------------Multi parts ------------------------------------------------//

MultiPartClass::MultiPartClass()
{
}

void MultiPartClass::RESET(char LastCase)
{
  switch (LastCase)
  {
  case 'e':
    //Nacke 
      initPosNeckYaw = 500;
      stopPosNeckYaw = 350;
      initPosNeckPitch = 500;
      stopPosNeckPitch = 600;
      posNeckPitchDiff = stopPosNeckPitch - initPosNeckPitch;
      revMillis = 0;
      currentMillis = millis();
      intervallTime = 10;
      servoNeck.LED(neckPitchRight, &rgb[3]);
      servoNeck.LED(neckPitchLeft, &rgb[3]);
      servoNeck.LED(neckYaw, &rgb[3]);

      for (int i = stopPosNeckPitch, k = initPosNeckPitch - posNeckPitchDiff; i >= initPosNeckPitch, k <= initPosNeckPitch; i -= 1, k += 1)
      {

      servoNeck.moveJoint(neckPitchRight, i);

      revMillis = millis();
      currentMillis = millis();
      while (currentMillis - revMillis <= intervallTime)
      {
        currentMillis = millis();
      }

      servoNeck.moveJoint(neckPitchLeft, k);

      revMillis = millis();
      currentMillis = millis();
      while (currentMillis - revMillis <= intervallTime)
      {
        currentMillis = millis();
      }
      }

      for (int i = stopPosNeckYaw; i <= initPosNeckYaw; i += 1)
      {
      servoNeck.moveJoint(neckYaw, i);

      revMillis = millis();
      currentMillis = millis();
      while (currentMillis - revMillis <= intervallTime)
      {
        currentMillis = millis();
      }
      }

    //Höger arm
      revMillis = 0;
      currentMillis = millis();
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

      revMillis = millis();
      currentMillis = millis();
      while (currentMillis - revMillis <= intervallTimeElbow)
      {
        currentMillis = millis();
      }
      }

      for (int pos = stopPosArm, k = stopPosShoulderPitch; pos >= initPosArm, k >= initPosShoulderPitch; pos -= 4, k -= 2) //Gå ner så det bara är 8 varv kvar till initPosSSP
      {
      elbowRight.setPosition(pos, intervallTimeElbow);

      revMillis = millis();
      currentMillis = millis();
      while (currentMillis - revMillis <= intervallTimeElbow)
      {
        currentMillis = millis();
      }

      shoulderRightPitch.setPosition(k, intervallTimeElbow);

      revMillis = millis();
      currentMillis = millis();
      while (currentMillis - revMillis <= intervallTimeElbow)
      {
        currentMillis = millis();
      }
      }


    //Vänster arm
    
    break;

  }

}

void MultiPartClass::dab()
{

  //Höger arm dab
    revMillis = 0;
    currentMillis = millis();
    intervallTime = 10;

    intervallTimeElbow = 10;
    initPosArm = 0;
    stopPosArm = 400;

    initPosShoulderPitch = 500;
    stopPosShoulderPitch = 700;

    for (int pos = initPosArm, k = initPosShoulderPitch; pos <= stopPosArm, k <= stopPosShoulderPitch; pos += 4, k += 2) //Gå ner så det bara är 8 varv kvar till initPosSSP
    {
    elbowRight.setPosition(pos, intervallTimeElbow);

<<<<<<< HEAD
  for (int k = initPosShoulderPitch - posShoulderPitchDiff, i = initPosNeckPitch, j = initPosNeckPitch; k <= initPosShoulderPitch, i <= stopPosNeckPitch, j >= initPosNeckPitch - posNeckPitchDiff; k += 2, i += 1, j -= 1) //Gå ner så det bara är 8 varv kvar till initPosSSP
  {
    shoulderLeftPitch.setPosition(k, intervallTimeElbow);
    revCurMillis();

    servoNeck.moveJoint(neckPitchRight, i);
    revCurMillis();

    servoNeck.moveJoint(neckPitchLeft, j);
    revCurMillis();
  }

  for (int pos = stopPosArm, i = initPosNeckYaw; pos >= initPosArm, i >= stopPosNeckYaw; pos -= 1, i -= 1)
  {
=======
    revMillis = millis();
    currentMillis = millis();
    while (currentMillis - revMillis <= intervallTimeElbow)
    {
      currentMillis = millis();
    }

    shoulderRightPitch.setPosition(k, intervallTimeElbow);

    revMillis = millis();
    currentMillis = millis();
    while (currentMillis - revMillis <= intervallTimeElbow)
    {
      currentMillis = millis();
    }
    }

  //Höger arm ShoulderRollPerp

    revMillis = 0;
    currentMillis = millis();
    intervallTime = 10;

    intervallTimeElbow = 10;

    initPosShoulderRoll = 800;
    stopPosShoulderRoll = 500;

    for (int k = initPosShoulderRoll; k >= stopPosShoulderRoll; k -= 5)
    {

    shoulderRightRoll.setPosition(k, intervallTimeElbow);

    revMillis = millis();
    currentMillis = millis();
    while (currentMillis - revMillis <= intervallTimeElbow)
    {
      currentMillis = millis();
    }
    }

  //Vänster arm dabPart1
    revMillis = 0;
    currentMillis = millis();
    intervallTime = 10;

    intervallTimeElbow = 10;
    initPosArm = 0;
    stopPosArm = 400;

    initPosShoulderPitch = 500;
    stopPosShoulderPitch = 700;

    for (int pos = initPosArm, k = initPosShoulderPitch; pos <= stopPosArm, k <= stopPosShoulderPitch; pos += 4, k += 2) //Gå ner så det bara är 8 varv kvar till initPosSSP
    {
    elbowLeft.setPosition(pos, intervallTimeElbow);

    revMillis = millis();
    currentMillis = millis();
    while (currentMillis - revMillis <= intervallTimeElbow)
    {
      currentMillis = millis();
    }

    shoulderLeftPitch.setPosition(k, intervallTimeElbow);

    revMillis = millis();
    currentMillis = millis();
    while (currentMillis - revMillis <= intervallTimeElbow)
    {
      currentMillis = millis();
    }
    }

  //Vänster arm ShoulderRollPerp
    revMillis = 0;
    currentMillis = millis();
    intervallTime = 10;

    intervallTimeElbow = 10;

    initPosShoulderRoll = 800;
    stopPosShoulderRoll = 500;

    for (int k = initPosShoulderRoll; k >= stopPosShoulderRoll; k -= 5)
    {

    shoulderLeftRoll.setPosition(k, intervallTimeElbow);

    revMillis = millis();
    currentMillis = millis();
    while (currentMillis - revMillis <= intervallTimeElbow)
    {
      currentMillis = millis();
    }
    }

  //Vänster arm dabPart2, kanske samtidigt som Nacken
    
    initPosNeckYaw = 500;
    stopPosNeckYaw = 350;
    initPosNeckPitch = 500;
    stopPosNeckPitch = 600;
    posNeckPitchDiff = stopPosNeckPitch - initPosNeckPitch;

    intervallTimeElbow = 10;
    initPosArm = 0;
    stopPosArm = 400;

    initPosShoulderPitch = 500;
    stopPosShoulderPitch = 700;
    revMillis = 0;
    currentMillis = millis();
    intervallTime = 10;


    //Nacke pitch och vänster dab part 2 merge
    for (int pos = stopPosArm, k = stopPosShoulderPitch, i = initPosNeckPitch, j = initPosNeckPitch; pos >= initPosArm, k >= initPosShoulderPitch, i <= stopPosNeckPitch, j >= initPosNeckPitch - posNeckPitchDiff; pos -= 4, k -= 2, i += 2, j -= 2) 
    {
>>>>>>> parent of f6b50c2... update
    elbowLeft.setPosition(pos, intervallTimeElbow);
    revCurMillis();

    revMillis = millis();
    currentMillis = millis();
    while (currentMillis - revMillis <= intervallTimeElbow)
    {
      currentMillis = millis();
    }

<<<<<<< HEAD
=======
    shoulderLeftPitch.setPosition(k, intervallTimeElbow);

    revMillis = millis();
    currentMillis = millis();
    while (currentMillis - revMillis <= intervallTimeElbow)
    {
      currentMillis = millis();
    }
    servoNeck.moveJoint(neckPitchRight, i);
      revMillis = millis();
      currentMillis = millis();
      while (currentMillis - revMillis <= intervallTime)
      {
        currentMillis = millis();
      }

      servoNeck.moveJoint(neckPitchLeft, j);

      revMillis = millis();
      currentMillis = millis();
      while (currentMillis - revMillis <= intervallTime)
      {
        currentMillis = millis();
      }
    }


  //Nack röresler gamla exemplet
     /*
      revMillis = 0;
      currentMillis = millis();
      intervallTime = 10;
      servoNeck.LED(neckPitchRight, &rgb[2]);
      servoNeck.LED(neckPitchLeft, &rgb[2]);
      servoNeck.LED(neckYaw, &rgb[2]);

      for (int i = initPosNeckPitch, j = initPosNeckPitch; i <= stopPosNeckPitch, j >= initPosNeckPitch - posNeckPitchDiff; i += 1, j -= 1)
      {

      servoNeck.moveJoint(neckPitchRight, i);
      revMillis = millis();
      currentMillis = millis();
      while (currentMillis - revMillis <= intervallTime)
      {
        currentMillis = millis();
      }

      servoNeck.moveJoint(neckPitchLeft, j);

      revMillis = millis();
      currentMillis = millis();
      while (currentMillis - revMillis <= intervallTime)
      {
        currentMillis = millis();
      }
      }
    */
    for (int i = initPosNeckYaw; i >= stopPosNeckYaw; i -= 2)
    {
>>>>>>> parent of f6b50c2... update
    servoNeck.moveJoint(neckYaw, i);

    revMillis = millis();
    currentMillis = millis();
    while (currentMillis - revMillis <= intervallTime)
    {
      currentMillis = millis();
    }
<<<<<<< HEAD
  }
=======
    }

>>>>>>> parent of f6b50c2... update

}

//-------------------------------------Skriv Multi parts funktioner över------------------------------------------------//

MultiPartClass multiPart = MultiPartClass();