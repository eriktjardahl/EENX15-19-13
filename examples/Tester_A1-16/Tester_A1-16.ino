#include <dxl_pro.h>
#include <XL320.h>
#include <XYZrobotServo.h>
#include <SoftwareSerial.h>

#define SERVO_COUNT 6

SoftwareSerial servoSerial(10, 11);


XYZrobotServo servo1(servoSerial,1);

XYZrobotServo servo2(servoSerial,2);

XYZrobotServo servo3(servoSerial,3);

XYZrobotServo servo4(servoSerial,4);

XYZrobotServo servo5(servoSerial,5);

XYZrobotServo servo6(servoSerial,6);


XYZrobotServo * servos[SERVO_COUNT] = {
  &servo1, &servo2, &servo3, &servo4, &servo5, &servo6};


void setup(){ 

  Serial.begin(115200);

   servoSerial.begin(115200);


}

void loop() {

servo1.reboot();
servo2.reboot();
servo3.reboot();
servo4.reboot();
servo5.reboot();
servo6.reboot();

      int playtime =750;

 
  
  // put your main code here, to run repeatedly:

  servo1.setPosition(400,playtime);
  delay(2000);

  servo1.setPosition(0,playtime);
  delay(1000);

  servo2.setPosition(400,playtime);
  delay(2000);

  servo2.setPosition(0,playtime);
  delay(1000);

  servo3.setPosition(400,playtime);;
  delay(2000);

  servo3.setPosition(0,playtime);
  delay(1000);

  servo4.setPosition(400,playtime);
  delay(2000);

  servo4.setPosition(0,playtime);
  delay(1000);

  servo5.setPosition(400,playtime);
  delay(2000);

  servo5.setPosition(0,playtime);
  delay(1000);

  servo6.setPosition(400,playtime);
  delay(2000);

  servo6.setPosition(0,playtime);
  delay(1000);
  
}
