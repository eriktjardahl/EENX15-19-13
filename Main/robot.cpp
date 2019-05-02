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
XYZrobotServo elbowLeft(A116servo2Serial, 5);
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
char lastCase;
//char LastCase = 'a';

char rgb[] = "rgbypcwo";

unsigned long revMillis;
unsigned long currentMillis;
int intervallTime;
int intervallTimeElbow;
int intervallTimeShoulder;

//---------------------------------Communication--------------------------------------------------//
Communication::Communication()
{
}
char Communication::readSerial()
{
  int a = 0;
  char dataString[50] = {0};

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

      revMillis = millis();
      currentMillis = millis();
      while (currentMillis - revMillis <= intervallTimeElbow)
      {
        currentMillis = millis();
      }
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

      revMillis = millis();
      currentMillis = millis();
      while (currentMillis - revMillis <= intervallTime)
      {
        currentMillis = millis();
      }
    }

    for (int i = stopPosHand; i >= initPosHand; i -= 100) //reset av handen
    {

      servoRight.moveJoint(thumbRight, i);
      servoRight.LED(thumbRight, &rgb[5]);

      revMillis = millis();
      currentMillis = millis();
      while (currentMillis - revMillis <= intervallTime)
      {
        currentMillis = millis();
      }

      servoRight.moveJoint(littleFingerRight, i);
      servoRight.LED(littleFingerRight, &rgb[5]);

      revMillis = millis();
      currentMillis = millis();
      while (currentMillis - revMillis <= intervallTime)
      {
        currentMillis = millis();
      }
      servoRight.moveJoint(ringFingerRight, i);
      servoRight.LED(ringFingerRight, &rgb[5]);

      revMillis = millis();
      currentMillis = millis();
      while (currentMillis - revMillis <= intervallTime)
      {
        currentMillis = millis();
      }
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

      revMillis = millis();
      currentMillis = millis();
      while (currentMillis - revMillis <= intervallTimeElbow)
      {
        currentMillis = millis();
      }
    }

    for (int i = stopPosHand; i >= initPosHand; i -= 100) //reset av handen
    {

      servoRight.moveJoint(middleFingerRight, i);
      servoRight.LED(middleFingerRight, &rgb[5]);

      revMillis = millis();
      currentMillis = millis();
      while (currentMillis - revMillis <= intervallTime)
      {
        currentMillis = millis();
      }
      servoRight.moveJoint(ringFingerRight, i);
      servoRight.LED(ringFingerRight, &rgb[5]);

      revMillis = millis();
      currentMillis = millis();
      while (currentMillis - revMillis <= intervallTime)
      {
        currentMillis = millis();
      }
      servoRight.moveJoint(littleFingerRight, i);
      servoRight.LED(littleFingerRight, &rgb[5]);

      revMillis = millis();
      currentMillis = millis();
      while (currentMillis - revMillis <= intervallTime)
      {
        currentMillis = millis();
      }
      servoRight.moveJoint(thumbRight, i);
      servoRight.LED(thumbRight, &rgb[5]);

      revMillis = millis();
      currentMillis = millis();
      while (currentMillis - revMillis <= intervallTime)
      {
        currentMillis = millis();
      }

      servoRight.moveJoint(indexFingerRight, i);
      servoRight.LED(indexFingerRight, &rgb[5]);

      revMillis = millis();
      currentMillis = millis();
      while (currentMillis - revMillis <= intervallTime)
      {
        currentMillis = millis();
      }
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

      revMillis = millis();
      currentMillis = millis();
      while (currentMillis - revMillis <= intervallTime)
      {
        currentMillis = millis();
      }
    }

    ran = true;
    //}
    break;
  case 'e': // dab, skriven behövs provas
    revMillis = 0;
    currentMillis = millis();
    intervallTime = 10;

    intervallTimeElbow = 10;
    stopPosArm = 300;
    initPosArm = 0;

    initPosShoulderRoll = 800;
    stopPosShoulderRoll = 500;

    initPosShoulderPitch = 500;
    stopPosShoulderPitch = 650;

    for (int pos = stopPosArm; pos >= initPosArm; pos -= 4)
    {
      elbowRight.setPosition(pos, intervallTimeElbow);

      revMillis = millis();
      currentMillis = millis();
      while (currentMillis - revMillis <= intervallTimeElbow)
      {
        currentMillis = millis();
      }
    }
    for (int k = stopPosShoulderRoll; k <= initPosShoulderRoll; k += 4)
    {
      shoulderRightRoll.setPosition(k, intervallTimeElbow);

      revMillis = millis();
      currentMillis = millis();
      while (currentMillis - revMillis <= intervallTimeElbow)
      {
        currentMillis = millis();
      }
    }
    for (int i = stopPosShoulderPitch; i >= initPosShoulderPitch; i -= 4)
    {
      shoulderRightPitch.setPosition(i, intervallTimeElbow);

      revMillis = millis();
      currentMillis = millis();
      while (currentMillis - revMillis <= intervallTimeElbow)
      {
        currentMillis = millis();
      }
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

      revMillis = millis();
      currentMillis = millis();
      while (currentMillis - revMillis <= intervallTime)
      {
        currentMillis = millis();
      }
      servoRight.moveJoint(indexFingerRight, i);
      servoRight.LED(indexFingerRight, &rgb[5]);

      revMillis = millis();
      currentMillis = millis();
      while (currentMillis - revMillis <= intervallTime)
      {
        currentMillis = millis();
      }
      servoRight.moveJoint(ringFingerRight, i);
      servoRight.LED(ringFingerRight, &rgb[5]);

      revMillis = millis();
      currentMillis = millis();
      while (currentMillis - revMillis <= intervallTime)
      {
        currentMillis = millis();
      }
      servoRight.moveJoint(littleFingerRight, i);
      servoRight.LED(littleFingerRight, &rgb[5]);

      revMillis = millis();
      currentMillis = millis();
      while (currentMillis - revMillis <= intervallTime)
      {
        currentMillis = millis();
      }
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

    revMillis = millis();
    currentMillis = millis();
    while (currentMillis - revMillis <= intervallTimeElbow)
    {
      currentMillis = millis();
    }
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

        revMillis = millis();
        currentMillis = millis();
        while (currentMillis - revMillis <= intervallTimeElbow)
        {
          currentMillis = millis();
        }
      }
    }

    if (j == 1 || j == 3 || j == 5)
    {

      for (int pos = initPosSSP; pos <= stopPosArm; pos += 4)
      {

        elbowRight.setPosition(pos, intervallTimeElbow);

        revMillis = millis();
        currentMillis = millis();
        while (currentMillis - revMillis <= intervallTimeElbow)
        {
          currentMillis = millis();
        }
      }
    }

    if (j == 2 || j == 4)
    {

      for (int pos = stopPosArm; pos >= initPosSSP; pos -= 4)
      {

        elbowRight.setPosition(pos, intervallTimeElbow);

        revMillis = millis();
        currentMillis = millis();
        while (currentMillis - revMillis <= intervallTimeElbow)
        {
          currentMillis = millis();
        }
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
  stopPosArm = 300;
 
  initPosShoulderPitch = 500;
  stopPosShoulderPitch = 650;

  for (int pos = initPosArm, k = initPosShoulderPitch; pos <= stopPosArm, k <= stopPosShoulderPitch; pos += 2, k += 1) //Gå ner så det bara är 8 varv kvar till initPosSSP
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
  
}

void JointArmClassRight::maxElbow() //skriven, ej testad
{
  initPosArm = 0;
  stopPosArm = 500;

  revMillis = 0;
  currentMillis = millis();
  intervallTimeElbow = 10;

  for (int pos = initPosArm; pos <= stopPosArm; pos += 4)
  {

    elbowRight.setPosition(pos, intervallTimeElbow);

    revMillis = millis();
    currentMillis = millis();
    while (currentMillis - revMillis <= intervallTimeElbow)
    {
      currentMillis = millis();
    }
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

    revMillis = millis();
    currentMillis = millis();
    while (currentMillis - revMillis <= intervallTimeElbow)
    {
      currentMillis = millis();
    }
  }
}

void JointArmClassRight::ShoulderPitchPerp()
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

    revMillis = millis();
    currentMillis = millis();
    while (currentMillis - revMillis <= intervallTimeElbow)
    {
      currentMillis = millis();
    }
  }
}

void JointArmClassRight::ShoulderRollPerp()
{
  revMillis = 0;
  currentMillis = millis();
  intervallTime = 10;

  intervallTimeElbow = 10;

  initPosShoulderRoll = 800;
  stopPosShoulderRoll = 500;

  for (int k = initPosShoulderRoll; k >= stopPosShoulderRoll; k -= 1) //Gå ner så det bara är 8 varv kvar till initPosSSP
  {
        
    shoulderRightRoll.setPosition(k, intervallTimeElbow);

    revMillis = millis();
    currentMillis = millis();
    while (currentMillis - revMillis <= intervallTimeElbow)
    {
      currentMillis = millis();
    }
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

    revMillis = millis();
    currentMillis = millis();
    while (currentMillis - revMillis <= intervallTimeElbow)
    {
      currentMillis = millis();
    }
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

    revMillis = millis();
    currentMillis = millis();
    while (currentMillis - revMillis <= intervallTimeElbow)
    {
      currentMillis = millis();
    }
  }

  for (int k = stopPosHand, pos = initPosSSP + 32; k >= initPosHand, pos >= initPosSSP; k -= 100, pos -= 4) //När det är 8 varv kvar så börjar handen röra på sig
  {

    elbowRight.setPosition(pos, intervallTimeElbow);

    revMillis = millis();
    currentMillis = millis();
    while (currentMillis - revMillis <= intervallTimeElbow)
    {
      currentMillis = millis();
    }

    servoRight.moveJoint(indexFingerRight, k);
    servoRight.LED(indexFingerRight, &rgb[1]);

    revMillis = millis();
    currentMillis = millis();
    while (currentMillis - revMillis <= intervallTime)
    {
      currentMillis = millis();
    }

    servoRight.moveJoint(middleFingerRight, k);
    servoRight.LED(middleFingerRight, &rgb[1]);

    revMillis = millis();
    currentMillis = millis();
    while (currentMillis - revMillis <= intervallTime)
    {
      currentMillis = millis();
    }
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

    revMillis = millis();
    currentMillis = millis();
    while (currentMillis - revMillis <= intervallTimeElbow)
    {
      currentMillis = millis();
    }
  }
  for (int i = stopPosHand, pos = initPosSSP + 32; i >= initPosHand, pos >= initPosSSP; i -= 100, pos -= 4) //när det bara är 8 loopar kvar börjar handen röra på sig
  {
    elbowRight.setPosition(pos, intervallTimeElbow);

    revMillis = millis();
    currentMillis = millis();
    while (currentMillis - revMillis <= intervallTimeElbow)
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
  case 'e': //skriven, ej testad
    revMillis = 0;
    currentMillis = millis();
    intervallTime = 10;

    intervallTimeShoulder = 10;

    initPosShoulderRoll = 0;
    stopPosShoulderRoll = 180;

    for (int k = stopPosShoulderRoll; k >= initPosShoulderRoll; k -= 4)
    {

      shoulderLeftRoll.setPosition(k, intervallTimeShoulder);

      revMillis = millis();
      currentMillis = millis();
      while (currentMillis - revMillis <= intervallTimeShoulder)
      {
        currentMillis = millis();
      }
    }
    break;
  case 'p': // skriven, ej testad
    stopPosHand = 800;
    revMillis = 0;
    currentMillis = millis();
    intervallTime = 10;
    intervallTimeElbow = 10;
    initPosHand = 0;
    initPosArm = 0;
    for (int i = stopPosHand; i >= initPosHand; i -= 100) //reset av handen
    {

      servoLeft.moveJoint(middleFingerLeft, i);
      servoLeft.LED(middleFingerLeft, &rgb[5]);

      revMillis = millis();
      currentMillis = millis();
      while (currentMillis - revMillis <= intervallTime)
      {
        currentMillis = millis();
      }
      servoLeft.moveJoint(ringFingerLeft, i);
      servoLeft.LED(ringFingerLeft, &rgb[5]);

      revMillis = millis();
      currentMillis = millis();
      while (currentMillis - revMillis <= intervallTime)
      {
        currentMillis = millis();
      }
      servoLeft.moveJoint(littleFingerLeft, i);
      servoLeft.LED(littleFingerLeft, &rgb[5]);

      revMillis = millis();
      currentMillis = millis();
      while (currentMillis - revMillis <= intervallTime)
      {
        currentMillis = millis();
      }
      servoLeft.moveJoint(thumbLeft, i);
      servoLeft.LED(thumbLeft, &rgb[5]);

      revMillis = millis();
      currentMillis = millis();
      while (currentMillis - revMillis <= intervallTime)
      {
        currentMillis = millis();
      }

      servoRight.moveJoint(indexFingerRight, i);
      servoRight.LED(indexFingerRight, &rgb[5]);

      revMillis = millis();
      currentMillis = millis();
      while (currentMillis - revMillis <= intervallTime)
      {
        currentMillis = millis();
      }
    }
    break;
  }
}

void JointArmClassLeft::dab() //skriven ,ej testad
{
  lastCase = 'e';
  revMillis = 0;
  currentMillis = millis();
  intervallTime = 10;

  intervallTimeShoulder = 10;

  initPosShoulderRoll = 0;
  stopPosShoulderRoll = 180;

  for (int k = initPosShoulderRoll; k <= stopPosShoulderRoll; k += 4)
  {

    shoulderLeftRoll.setPosition(k, intervallTimeShoulder);

    revMillis = millis();
    currentMillis = millis();
    while (currentMillis - revMillis <= intervallTimeShoulder)
    {
      currentMillis = millis();
    }
  }
}
//---------------------------------HandLeft--------------------------------------------------//

void JointArmClassLeft::rock()
{
}
void JointArmClassLeft::scissor()
{
}

void JointArmClassLeft::paper()
{
}

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

    for (int i = stopPosHand; i >= initPosHand; i -= 100)
    {

      servoLeft.moveJoint(middleFingerLeft, i);
      servoLeft.LED(middleFingerLeft, &rgb[1]);

      revMillis = millis();
      currentMillis = millis();
      while (currentMillis - revMillis <= intervallTime)
      {
        currentMillis = millis();
      }
      servoLeft.moveJoint(ringFingerLeft, i);
      servoLeft.LED(ringFingerRight, &rgb[1]);

      revMillis = millis();
      currentMillis = millis();
      while (currentMillis - revMillis <= intervallTime)
      {
        currentMillis = millis();
      }
      servoLeft.moveJoint(littleFingerLeft, i);
      servoLeft.LED(littleFingerLeft, &rgb[1]);

      revMillis = millis();
      currentMillis = millis();
      while (currentMillis - revMillis <= intervallTime)
      {
        currentMillis = millis();
      }
      servoLeft.moveJoint(thumbLeft, i);
      servoLeft.LED(thumbLeft, &rgb[1]);

      revMillis = millis();
      currentMillis = millis();
      while (currentMillis - revMillis <= intervallTime)
      {
        currentMillis = millis();
      }

      servoLeft.moveJoint(indexFingerLeft, i);
      servoLeft.LED(indexFingerLeft, &rgb[1]);

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

    revMillis = millis();
    currentMillis = millis();
    while (currentMillis - revMillis <= intervallTime)
    {
      currentMillis = millis();
    }
    servoLeft.moveJoint(ringFingerLeft, i);
    servoLeft.LED(ringFingerLeft, &rgb[1]);

    revMillis = millis();
    currentMillis = millis();
    while (currentMillis - revMillis <= intervallTime)
    {
      currentMillis = millis();
    }
    servoLeft.moveJoint(littleFingerLeft, i);
    servoLeft.LED(littleFingerLeft, &rgb[1]);

    revMillis = millis();
    currentMillis = millis();
    while (currentMillis - revMillis <= intervallTime)
    {
      currentMillis = millis();
    }
    servoLeft.moveJoint(thumbLeft, i);
    servoLeft.LED(thumbLeft, &rgb[1]);

    revMillis = millis();
    currentMillis = millis();
    while (currentMillis - revMillis <= intervallTime)
    {
      currentMillis = millis();
    }

    servoLeft.moveJoint(indexFingerRight, i);
    servoLeft.LED(indexFingerRight, &rgb[1]);

    revMillis = millis();
    currentMillis = millis();
    while (currentMillis - revMillis <= intervallTime)
    {
      currentMillis = millis();
    }
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
  case 'Nod': //skriven, behövs testas
    initPosNeckPitch = 500;
    stopPosNeckPitch = 0;
    revMillis = 0;
    currentMillis = millis();
    intervallTime = 10;
    for (int k = stopPosNeckPitch; k <= initPosNeckPitch; k++)
    {
      servoNeck.moveJoint(neckPitch, k);
      servoNeck.LED(neckPitch, &rgb[5]);

      revMillis = millis();
      currentMillis = millis();
      while (currentMillis - revMillis <= intervallTime)
      {
        currentMillis = millis();
      }
    }
    break;
  case 'e': //skriven, beöhvs testas
    initPosNeckYaw = 0;
    stopPosNeckYaw = 500;
    initPosNeckPitch = 500;
    stopPosNeckPitch = 300;
    revMillis = 0;
    currentMillis = millis();
    intervallTime = 10;

    for (int i = stopPosNeckYaw; i >= initPosNeckYaw; i--)
    {
      servoNeck.moveJoint(neckYaw, i);
      servoNeck.LED(neckYaw, &rgb[5]);

      revMillis = millis();
      currentMillis = millis();
      while (currentMillis - revMillis <= intervallTime)
      {
        currentMillis = millis();
      }
    }

    for (int k = stopPosNeckPitch; k <= initPosNeckPitch; k++)
    {
      servoNeck.moveJoint(neckPitch, k);
      servoNeck.LED(neckPitch, &rgb[5]);

      revMillis = millis();
      currentMillis = millis();
      while (currentMillis - revMillis <= intervallTime)
      {
        currentMillis = millis();
      }
    }

    break;
  }
}

void JointNeckClass::nod() //behövs testas. är skriven
{
  initPosNeckPitch = 500;
  stopPosNeckPitch = 0;
  revMillis = 0;
  currentMillis = millis();
  intervallTime = 10;

  for (int i = 0; i <= 2; i++)
  {
    if (i == 0 || i == 2)
    {
      for (int k = initPosNeckPitch; k >= stopPosNeckPitch; k--)
      {
        servoNeck.moveJoint(neckPitch, k);
        servoNeck.LED(neckPitch, &rgb[1]);

        revMillis = millis();
        currentMillis = millis();
        while (currentMillis - revMillis <= intervallTime)
        {
          currentMillis = millis();
        }
      }
    }
    else if (i == 1)
    {
      for (int k = stopPosNeckPitch; k <= initPosNeckPitch; k++)
      {
        servoNeck.moveJoint(neckPitch, k);
        servoNeck.LED(neckPitch, &rgb[1]);

        revMillis = millis();
        currentMillis = millis();
        while (currentMillis - revMillis <= intervallTime)
        {
          currentMillis = millis();
        }
      }
    }
  }
}

void JointNeckClass::dab() //behövs testas. är skriven
{
  initPosNeckYaw = 0;
  stopPosNeckYaw = 500;
  initPosNeckPitch = 500;
  stopPosNeckPitch = 300;
  revMillis = 0;
  currentMillis = millis();
  intervallTime = 10;
  servoNeck.LED(16, &rgb[2]);
  /*

  for (int i = initPosNeckYaw; i <= stopPosNeckYaw; i++)
  {
    servoNeck.moveJoint(neckYaw, i);
    servoNeck.LED(neckYaw, &rgb[1]);

    revMillis = millis();
    currentMillis = millis();
    while (currentMillis - revMillis <= intervallTime)
    {
      currentMillis = millis();
    }
  }
/*
  for (int k = initPosNeckPitch; k >= stopPosNeckPitch; k--)
  {
    servoNeck.moveJoint(neckPitch, k);
    servoNeck.LED(neckPitch, &rgb[1]);

    revMillis = millis();
    currentMillis = millis();
    while (currentMillis - revMillis <= intervallTime)
    {
      currentMillis = millis();
    }
  }
  */
}

//-------------------------------------Skriv nackfunktioner över------------------------------------------------//

JointNeckClass jointNeck = JointNeckClass();
