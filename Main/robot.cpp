#include "Arduino.h"
#include "robot.h"

//-------------------------------------Initiera alla motorer------------------------------------------------//


SoftwareSerial A116servoSerial=SoftwareSerial(rxPin0, txPin1); //Höger arm
SoftwareSerial A116servo2Serial=SoftwareSerial(rxPin10, txPin11); //Väsnter arm
SoftwareSerial XL320servoSerial=SoftwareSerial(rxPin3, txPin4); //Vänster hand
SoftwareSerial XL320servo2Serial=SoftwareSerial(rxPin6, txPin7);  //Höger hand
SoftwareSerial XL320servo3Serial=SoftwareSerial(rxPin8, txPin9);  //Nacke



XYZrobotServo elbowRight(A116servoSerial,1);
XYZrobotServo shoulderRightPitch(A116servoSerial,2);
//XYZrobotServo servo3(A116servoSerial,3);
XYZrobotServo shoulderRightYaw(A116servoSerial,4);
XYZrobotServo elbowLeft(A116servo2Serial,5);
XYZrobotServo shoulderLeftPitch(A116servo2Serial,6);
XYZrobotServo shoulderLeftYaw(A116servo2Serial,7);


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

JointArmClassRight::JointArmClassRight(){
}

void JointArmClassRight::SETUP(){


  pinMode(rxPin6,INPUT);
  pinMode(txPin7,OUTPUT);
  pinMode(rxPin0,INPUT);
  pinMode(txPin1,OUTPUT);


 
  A116servo2Serial.begin(115200);  // höger arm
  XL320servo2Serial.begin(115200); // höger hand
  
 
  servoRight.begin(XL320servo2Serial);  
  
  }

void JointArmClassRight::ArmRightMotionSSP(){
  int initPos=0;  // initsiera positioner 
  int stopPos=1023;
    for(int pos = initPos; pos <= stopPos ; pos+=10){
    elbowRight.setPosition(pos,playtime);
     delay(200); // vill vi ha delay?
    }
}
void JointArmClassRight::ArmRightReset(){
  int initPos = 0;
  elbowRight.setPosition(initPos,playtime);
  shoulderRightPitch.setPosition(initPos,playtime);
  shoulderRightYaw.setPosition(initPos,playtime);
  for(int i = littleFingerRight ; i < thumbRight + 1; i++){
  servoRight.moveJoint(i, pos);
  }
}
//---------------------------------HandRight-------------------------------------------------// 
void JointArmClassRight::HandRightStone(){

    int initPos=0;
    int stopPos=1023;
  


  for(int pos = initPos ; pos < stopPos; pos+=15){
      for(int i = littleFingerRight ; i <= thumbRight ; i++){
        servoRight.moveJoint(i, pos);

      }
  }
}
void JointArmClassRight::HandRightScissor(){

    int initPos=0;
    int stopPos=1023;
  

  for(int pos = initPos ; pos < stopPos; pos+=10){
      for(int i = littleFingerRight ; i < thumbRight + 1; i++){
         if( i == littleFingerLeft ||  i == ringFingerRight ||  i == thumbRight)
      
        servoRight.moveJoint(i, pos);

      }
  }
}

void JointArmClassRight::HandRightPaper(){

  
}


//-------------------------------------Skriv armfunktioner över------------------------------------------------//

JointArmClassRight jointArmRight = JointArmClassRight();

//---------------------------------Arm_Left--------------------------------------------------//

JointArmClassLeft::JointArmClassLeft(){
}

void JointArmClassLeft::SETUP(){
  pinMode(rxPin10,INPUT);
  pinMode(txPin11,OUTPUT);
  pinMode(rxPin3,INPUT);
  pinMode(txPin4,OUTPUT);


  A116servoSerial.begin(115200); //vänster arm 
  XL320servoSerial.begin(115200); //vänster hand 

  
  servoLeft.begin(XL320servoSerial);
  
  }

  void JointArmClassLeft::ArmLeftMotion(){
    
    
  }
 //---------------------------------HandLeft--------------------------------------------------// 

void JointArmClassLeft::HandLeftStone(){
    int initPos=0;
    int stopPos=1023;

     for(int pos = initPos ; pos < stopPos; pos+=10){
        for(int i = littleFingerLeft ; i < thumbLeft + 1; i++){
           servoLeft.moveJoint(i, pos);
        
        }
     }
}
void JointArmClassLeft::HandLeftScissor(){
      int initPos=0;
       int stopPos=1023;

      for(int pos = initPos ; pos < stopPos; pos+=10){
          for(int i = littleFingerLeft ; i < thumbLeft + 1; i++){
            if( i == littleFingerLeft ||  i == ringFingerLeft ||  i == thumbLeft)
              servoLeft.moveJoint(i, pos);
          }
      }
}

void JointArmClassLeft::HandLeftPaper(){

  
}

//-------------------------------------Skriv armfunktioner över------------------------------------------------//

JointArmClassLeft jointArmLeft = JointArmClassLeft();


//-------------------------------------Neck------------------------------------------------//

JointNeckClass::JointNeckClass(){
}

void JointNeckClass::SETUP(){
  pinMode(rxPin8,INPUT);
  pinMode(txPin9,OUTPUT);

  XL320servo3Serial.begin(115200);
  servoNeck.begin(XL320servo3Serial);
}

void JointNeckClass::nod(){

int initPos =0;
int stopPos=100;
int i;

  for(i=initPos; i<=stopPos; i++){
    servoNeck.moveJoint(neckPitch,i);
  }
}

void JointNeckClass::dab(){

  int initPos =0;
  int stopPos=1000;
  int i;
  for(i=initPos;i<=stopPos;i++){
    servoNeck.moveJoint(neckJaw,i);
    servoNeck.moveJoint(neckPitch,i);
  }  
}

void JointNeckClass::reset(){
  int initPosJaw=0;
  int initPosRoll=0;
  int initPosPitch=0;

  
  servoNeck.moveJoint(neckJaw,i);
  servoNeck.moveJoint(neckJaw,i);
  servoNeck.moveJoint(neckPitch,i);
    
}

//-------------------------------------Skriv nackfunktioner över------------------------------------------------//

JointNeckClass jointNeck = JointNeckClass();  
