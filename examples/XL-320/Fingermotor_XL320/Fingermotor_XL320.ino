

#include <SoftwareSerial.h>

#include <XL320.h>
#include <dxl_pro.h>

XL320 robot;
SoftwareSerial mySerial(10, 11); //(RX,TX)

char rgb[] = "rgbyocwo";
int servoPosition = 0;
int ledColour = 0;
int servoID = 1;

int val; // initial value of input

void setup()
{
  Serial.begin(115200); // Serial communication begins at 115200 bps

  mySerial.begin(115200);

  robot.begin(Serial);

  robot.setJointSpeed(servoID, 1023);
}

void loop()
{
  if (Serial.available()) // if serial value is available
  {
    val = Serial.read(); // then read the serial value
    if (val == 'd')      //if value input is equals to d
    {
      servoPosition += 1;                      //than position of servo motor increases by 1 ( anti clockwise)
      robot.moveJoint(servoID, servoPosition); // the servo will move according to position
      delay(15);                               //delay for the servo to get to the position
    }
    if (val == 'a') //if value input is equals to a
    {
      servoPosition -= 1;                      //than position of servo motor decreases by 1 (clockwise)
      robot.moveJoint(servoID, servoPosition); // the servo will move according to position
      delay(15);                               //delay for the servo to get to the position
    }
  }
}
