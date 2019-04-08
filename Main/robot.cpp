#include "Arduino.h"
#include "robot.h"

//-------------------------------------Initiera alla motorer------------------------------------------------//


SoftwareSerial A116servoSerial=SoftwareSerial(rxPin0, txPin1); //Vänster arm

SoftwareSerial A116servo2Serial=SoftwareSerial(rxPin10, txPin11); //Höger arm

SoftwareSerial XL320servoSerial=SoftwareSerial(rxPin3, txPin4); //Vänster hand

SoftwareSerial XL320servo2Serial=SoftwareSerial(rxPin6, txPin7);  //Höger hand

SoftwareSerial XL320servo3Serial=SoftwareSerial(rxPin8, txPin9);  //Nacke



XYZrobotServo servo1(A116servoSerial,1);

XYZrobotServo servo2(A116servoSerial,2);

//XYZrobotServo servo3(A116servoSerial,3);

XYZrobotServo servo4(A116servoSerial,4);

XYZrobotServo servo5(A116servo2Serial,5);

XYZrobotServo servo6(A116servo2Serial,6);

XYZrobotServo servo7(A116servo2Serial,7);



XL320 servoLeft;
/*
 * ID 1-5 Vänster hand. 1=Lillfinger, 2=Ringfinger, 3=Långfinger, 4=Pekfinger, 5=tumme
 */

XL320 servoRight;
/*
 * ID 6-10 Höger hand. 6=Lillfinger, 7=Ringfinger,8=Långfinger, 9=Pekfinger, 10=tumme
 */

XL320 servoNeck;
/*
 * Id 11-14 Nack rotationer. 
 */

//---------------------------------Arm--------------------------------------------------//

JointArmClass::JointArmClass(){
}

void JointArmClass::SETUP(){
  pinMode(rxPin0,INPUT);
  pinMode(txPin1,OUTPUT);

  pinMode(rxPin3,INPUT);
  pinMode(txPin4,OUTPUT);

  pinMode(rxPin6,INPUT);
  pinMode(txPin7,OUTPUT);

  pinMode(rxPin10,INPUT);
  pinMode(txPin11,OUTPUT);

  A116servoSerial.begin(115200);
  A116servo2Serial.begin(115200);
  XL320servoSerial.begin(115200);
  XL320servo2Serial.begin(115200);
  
  servoLeft.begin(XL320servoSerial);
  servoRight.begin(XL320servo2Serial);  
  
  }

void 

//-------------------------------------Skriv armfunktioner över------------------------------------------------//

JointArmClass jointArm = JointArmClass();

//-------------------------------------Neck------------------------------------------------//

JointNeckClass::JointNeckClass(){
}

void JointNeckClass::SETUP(){
  pinMode(rxPin8,INPUT);
  pinMode(txPin9,OUTPUT);

  XL320servo3Serial.begin(115200);

  servoNeck.begin(XL320servo3Serial);
}

//-------------------------------------Skriv nackfunktioner över------------------------------------------------//

JointNeckClass jointNeck = JointNeckClass();  
