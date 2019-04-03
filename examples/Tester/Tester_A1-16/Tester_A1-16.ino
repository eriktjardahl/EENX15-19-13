#include <dxl_pro.h>
#include <XL320.h>
#include <XYZrobotServo.h>
#include <SoftwareSerial.h>

#define SERVO_COUNT 3

SoftwareSerial servoSerial(10, 11);


XYZrobotServo servo1(servoSerial,1);

XYZrobotServo servo2(servoSerial, 2);

XYZrobotServo servo3(servoSerial, 3);

XYZrobotServo * servos[SERVO_COUNT] = {
  &servo1, &servo2, &servo3};


void setup(){ 

  Serial.begin(115200);

   servoSerial.begin(115200);


}

void loop() {

servo1.reboot();
servo2.reboot();

      int playtime =750;

 
  
  // put your main code here, to run repeatedly:

  servo1.setSpeed(400);
  delay(2000);

  servo1.setSpeed(0);
  delay(1000);

servo2.setSpeed(400);
  delay(2000);

 servo2.setSpeed(0);
  delay(1000);
  
}
