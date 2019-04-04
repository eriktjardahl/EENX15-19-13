#include <dxl_pro.h>
#include <XL320.h>
#include <XYZrobotServo.h>
#include <SoftwareSerial.h>

#define SERVO_COUNT 6

#define rxPin0 0
#define txPin1 1

#define rxPin10 10
#define txPin11 11

SoftwareSerial servoSerial=SoftwareSerial(rxPin0, txPin1);


SoftwareSerial servo2Serial=SoftwareSerial(rxPin10, txPin11);


XYZrobotServo servo1(servoSerial,1);

XYZrobotServo servo2(servoSerial,2);

//XYZrobotServo servo3(servoSerial,3);

XYZrobotServo servo4(servo2Serial,4);

XYZrobotServo servo5(servo2Serial,5);

XYZrobotServo servo6(servoSerial,6);

XYZrobotServo servo7(servoSerial,7);


XYZrobotServo * servos[SERVO_COUNT] = {
  &servo1, &servo2, &servo7, &servo4, &servo5, &servo6};


void setup(){ 

  pinMode(rxPin0,INPUT);
  pinMode(txPin1,OUTPUT);

  pinMode(rxPin10,INPUT);
  pinMode(txPin11,OUTPUT);


   servoSerial.begin(115200);
   servo2Serial.begin(115200);


}

void loop() {

      int playtime =75;
      int distance = 10000;
 
  
  // put your main code here, to run repeatedly:
/*
  servo1.setPosition(distance,playtime);
  delay(2000);

  servo1.setPosition(0,playtime);
  delay(1000);
*/
int i;

  for(i=1;i<=1000;i++){

    
    servo1.setPosition(i,10);
    servo2.setPosition(i,10);

    servo4.setPosition(i,10);
    servo5.setPosition(i,10);
    
  }
  servo1.setPosition(0,10);
  servo2.setPosition(0,10);
  servo4.setPosition(0,10);
  servo5.setPosition(0,10);

/*
  servo2.setPosition(distance,playtime);
  delay(2000);

  servo2.setPosition(0,playtime);
  delay(1000);

  servo4.setPosition(distance,playtime);
  delay(2000);

  servo4.setPosition(0,playtime);
  delay(1000);

  servo5.setPosition(distance,playtime);
  delay(2000);

  servo5.setPosition(0,playtime);
  delay(1000);

  servo6.setPosition(distance,playtime);
  delay(2000);

  servo6.setPosition(0,playtime);
  delay(1000);

  servo7.setPosition(distance,playtime);
  delay(2000);

  servo7.setPosition(0,playtime);
  delay(1000);
*/
  
}
