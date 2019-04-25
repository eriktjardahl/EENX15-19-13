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
int initPosSSP;

// Declaration of stop position variables

int stopPosArm;
int stopPosHand;

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
char LastCase = 'f';

char rgb[] = "rgbypcwo";

unsigned long revMillis;
unsigned long currentMillis;
int intervallTime;
int intervallTimeElbow;

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

void JointArmClassRight::armMotionSSP() //färdig, används ej direkt.
{

  initPosArm = 0;
  stopPosArm = 330;
  initPosSSP = 160;

  revMillis = 0;
  currentMillis = millis();
  intervallTime = 10;

  if (!ran)
  {
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
  }
}

void JointArmClassRight::RESET(/*char LastCase*/)
{
  Serial.println(LastCase);
  //shoulderRightPitch.setPosition(initPosArm, playtime);
  //shoulderRightYaw.setPosition(initPosArm, playtime);

  if (!ran)
  {
    switch (LastCase)
    {
    case 'a': //påse färdig

      revMillis = 0;
      currentMillis = millis();

      intervallTimeElbow = 10;

      initPosSSP = 160;
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
      initPosSSP = 160;
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
        servoRight.LED(thumbRight, &rgb[1]);

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
        servoRight.moveJoint(ringFingerRight, i);
        servoRight.LED(ringFingerRight, &rgb[1]);

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
      initPosSSP = 160;
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
      break;

    case 'd': //ok färdig
      if (!ran)
      {
        stopPosHand = 800;
        initPosHand = 0;
        revMillis = 0;
        currentMillis = millis();
        intervallTime = 10;

        for (int i = stopPosHand; i >= initPosHand; i -= 100) //knytnäven
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
      break;
    case 'f'://fack färdig
      stopPosHand = 800;
      initPosHand = 0;
      revMillis = 0;
      currentMillis = millis();
      intervallTime = 10;

      for (int i = stopPosHand; i >= initPosHand; i -= 100) //knytnäven
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
      break;
    }
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
void JointArmClassRight::rock() // lastCase = c färdig
{
  lastCase = 'c';
  if (!ran)
  {

    stopPosHand = 0;
    initPosHand = 800;
    revMillis = 0;
    currentMillis = millis();
    intervallTime = 10;

    intervallTimeElbow = 10;
    stopPosArm = 330;
    initPosSSP = 160;

    for (int i = stopPosHand; i < initPosHand; i += 100) //knytnäven
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
  }
}
void JointArmClassRight::scissor() //lastCase = b färdig
{
  lastCase = 'b';
  if (!ran)
  {

    stopPosHand = 800;
    initPosHand = 0;
    revMillis = 0;
    currentMillis = millis();
    intervallTime = 10;

    intervallTimeElbow = 10;
    stopPosArm = 330;
    initPosSSP = 160;

    for (int i = initPosHand; i <= stopPosHand; i += 100) //knytnäven
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
  }
}

void JointArmClassRight::paper() // lastCase = a färdig
{
  lastCase = 'a';
  if (!ran)
  {
    stopPosHand = 800;
    initPosHand = 0;
    revMillis = 0;
    currentMillis = millis();
    intervallTime = 10;

    intervallTimeElbow = 10;
    stopPosArm = 330;
    initPosSSP = 160;

    for (int i = initPosHand; i <= stopPosHand; i += 100) //knytnäven
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
  }
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

  if (!ran)
  {
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
}

void JointArmClassLeft::RESET()
{
}

void JointArmClassLeft::dab()
{
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

//-------------------------------------Skriv armfunktioner över------------------------------------------------//

JointArmClassLeft jointArmLeft = JointArmClassLeft();

//-------------------------------------Neck------------------------------------------------//

JointNeckClass::JointNeckClass()
{
}

void JointNeckClass::RESET()
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
}

void JointNeckClass::dab()
{
}

//-------------------------------------Skriv nackfunktioner över------------------------------------------------//

JointNeckClass jointNeck = JointNeckClass();
