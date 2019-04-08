#include "Arduino.h"
#include "robot.h"

//-------------------------------------Initiera alla motorer------------------------------------------------//


SoftwareSerial A116servoSerial=SoftwareSerial(rxPin0, txPin1); //Höger arm

SoftwareSerial A116servo2Serial=SoftwareSerial(rxPin10, txPin11); //Väsnter arm

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
 * Vänster hand
  lillfinger .   ID:1
  ringfinger     ID:2
  långfinger    ID:3
  pekfinger     ID:4
  tummer        ID:5
 */

XL320 servoRight;
/*
 * ID 6-10 Höger hand. 6=Lillfinger, 7=Ringfinger,8=Långfinger, 9=Pekfinger, 10=tumme
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

void JointArmClassRight::MOVE(){

  int i;
  for(i=1;i<=1000;i++){
      
    servo1.setPosition(i,10);
}
    servo1.setPosition(0,10);

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
 //---------------------------------HandLeft--------------------------------------------------// 
<<<<<<< HEAD
 void JointArmClassLeft::HandLeft_Stone(){
    int initPos=0;
    int stopPos=1023;

     for(int pos = initPos ; pos < stopPos; pos+=10){
      for(int i = littleFinger_Left ; i < thumb_Left + 1; i++){
        servoLeft.moveJoint(i, pos);
        
     }
     }
     }
void JointArmClassLeft::HandLeft_Scissor(){
      int initPos=0;
       int stopPos=1023;

      for(int pos = initPos ; pos < stopPos; pos+=10){
      for(int i = littleFinger_Left ; i < thumb_Left + 1; i++){
       if( i == littleFinger_Left ||  i == ringFinger_Left ||  i == thumb_Left)
        servoLeft.moveJoint(i, pos);
      }
      }
      }
   
    
 
=======
>>>>>>> 87e87ab9c7a7a27ae5673386ef12bb836af05462



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
<<<<<<< HEAD


=======
>>>>>>> 87e87ab9c7a7a27ae5673386ef12bb836af05462
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



//-------------------------------------Skriv nackfunktioner över------------------------------------------------//

JointNeckClass jointNeck = JointNeckClass();  
