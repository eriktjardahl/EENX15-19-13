#include <dxl_pro.h>
#include <XL320.h>
#include <XYZrobotServo.h>
#include <SoftwareSerial.h>

//#include <Servo.h>

#define SERVO_COUNT 6

#define rxPin0 0
#define txPin1 1

#define rxPin3 3
#define txPin4 4

#define rxPin6 6
#define txPin7 7

#define rxPin8 8
#define txPin9 9

#define rxPin10 10
#define txPin11 11




SoftwareSerial A116servoSerial=SoftwareSerial(rxPin0, txPin1);

SoftwareSerial A116servo2Serial=SoftwareSerial(rxPin10, txPin11);

SoftwareSerial XL320servoSerial=SoftwareSerial(rxPin3, txPin4);

SoftwareSerial XL320servo2Serial=SoftwareSerial(rxPin6, txPin7);

SoftwareSerial XL320servo3Serial=SoftwareSerial(rxPin8, txPin9);


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
 * ID 6-10 Vänster hand. 6=Lillfinger, 7=Ringfinger,8=Långfinger, 9=Pekfinger, 10=tumme
 */

XL320 servoNeck;
/*
 * Id 11-14 Nack rotationer. 
 */

//Servo Elbow;




XYZrobotServo * servos[SERVO_COUNT] = {
  &servo1, &servo2, &servo7, &servo4, &servo5, &servo6};


void setup(){ 

  pinMode(rxPin0,INPUT);
  pinMode(txPin1,OUTPUT);

  pinMode(rxPin3,INPUT);
  pinMode(txPin4,OUTPUT);

  pinMode(rxPin6,INPUT);
  pinMode(txPin7,OUTPUT);
  
  pinMode(rxPin8,INPUT);
  pinMode(txPin9,OUTPUT);


  pinMode(rxPin10,INPUT);
  pinMode(txPin11,OUTPUT);
  


   A116servoSerial.begin(115200);
   A116servo2Serial.begin(115200);
   XL320servoSerial.begin(115200);
   XL320servo2Serial.begin(115200);
   XL320servo3Serial.begin(115200);
   servoLeft.begin(XL320servoSerial);
   servoRight.begin(XL320servo2Serial);
   servoNeck.begin(XL320servo3Serial);
   
   //Elbow.attach(txPin12);


}

void loop() {
 // put your main code here, to run repeatedly:
int i;


  for(i=1;i<=1000;i++){

    
    servo1.setPosition(i,10);
    servo2.setPosition(i,10);
    servo4.setPosition(i,10);
    
    servo5.setPosition(i,10);
    servo6.setPosition(i,10);
    servo7.setPosition(i,10);


    servoLeft.moveJoint(1,i);
    servoLeft.moveJoint(2,i);
    servoLeft.moveJoint(3,i);
    servoLeft.moveJoint(4,i);
    servoLeft.moveJoint(5,i);

    
    servoRight.moveJoint(6,i);
    servoRight.moveJoint(7,i);
    servoRight.moveJoint(8,i);
    servoRight.moveJoint(9,i);
    servoRight.moveJoint(10,i);

    servoNeck.moveJoint(11,i);
    servoNeck.moveJoint(12,i);
    servoNeck.moveJoint(13,i);
    servoNeck.moveJoint(14,i);
    

    //Elbow.write(j);    
     
    
  }

  
  servo1.setPosition(0,10);
  servo2.setPosition(0,10);
  servo4.setPosition(0,10);
  servo5.setPosition(0,10);
  servo6.setPosition(0,10);
  servo7.setPosition(0,10);
  
  servoLeft.moveJoint(1,0);
  servoLeft.moveJoint(2,0);
  servoLeft.moveJoint(3,0);
  servoLeft.moveJoint(4,0);
  servoLeft.moveJoint(5,0);
  
  servoRight.moveJoint(6,0);
  servoRight.moveJoint(7,0);
  servoRight.moveJoint(8,0);
  servoRight.moveJoint(9,0);
  servoRight.moveJoint(10,0);

    servoNeck.moveJoint(11,0);
    servoNeck.moveJoint(12,0);
    servoNeck.moveJoint(13,0);
    servoNeck.moveJoint(14,0);
  
  //Elbow.writeMicroseconds(1500);


  
}
