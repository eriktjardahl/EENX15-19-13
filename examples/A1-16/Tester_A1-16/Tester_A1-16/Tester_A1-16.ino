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

#define rxPin10 10
#define txPin11 11

#define txPin12 12



SoftwareSerial A116servoSerial=SoftwareSerial(rxPin0, txPin1);


SoftwareSerial A116servo2Serial=SoftwareSerial(rxPin10, txPin11);

SoftwareSerial XL320servoSerial=SoftwareSerial(rxPin3, txPin4);

SoftwareSerial XL320servo2Serial=SoftwareSerial(rxPin6, txPin7);


XYZrobotServo servo1(A116servoSerial,1);

XYZrobotServo servo2(A116servoSerial,2);

//XYZrobotServo servo3(A116servoSerial,3);

XYZrobotServo servo4(A116servoSerial,4);

XYZrobotServo servo5(A116servo2Serial,5);

XYZrobotServo servo6(A116servo2Serial,6);

XYZrobotServo servo7(A116servo2Serial,7);

XL320 servoVanster;

XL320 servoHoger;

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


  pinMode(rxPin10,INPUT);
  pinMode(txPin11,OUTPUT);

  pinMode(txPin12,OUTPUT);


   A116servoSerial.begin(115200);
   A116servo2Serial.begin(115200);
   XL320servoSerial.begin(115200);
   XL320servo2Serial.begin(115200);
   servoVanster.begin(XL320servoSerial);
   servoHoger.begin(XL320servo2Serial);
   //Elbow.attach(txPin12);


}

void loop() {
 // put your main code here, to run repeatedly:
 
      int playtime =75;
      int distance = 10000;

int i;


  for(i=1;i<=1000;i++){

    
    servo1.setPosition(i,10);
    servo2.setPosition(i,10);
    servo4.setPosition(i,10);
    
    servo5.setPosition(i,10);
    servo6.setPosition(i,10);
    servo7.setPosition(i,10);

    servoVanster.moveJoint(5,i);
    servoHoger.moveJoint(2,i);

    //Elbow.write(j);
     
    
  }

  
  servo1.setPosition(0,10);
  servo2.setPosition(0,10);
  servo4.setPosition(0,10);
  servo5.setPosition(0,10);
  servo6.setPosition(0,10);
  servo7.setPosition(0,10);
  servoVanster.moveJoint(5,0);
  servoHoger.moveJoint(2,0);
  //Elbow.writeMicroseconds(1500);


  
}
