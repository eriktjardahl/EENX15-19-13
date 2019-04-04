#include <XYZrobotServo.h>
#include <dxl_pro.h>
#include <XL320.h>
#include <SoftwareSerial.h>
#include <cmd_def.h>
#include <speed.h>
#include <hand_motion.h>

/*
Lägg bibliotek från tredje-part i \main\libraries mappen och egna .h filer i main mappen
*/

// Set the SoftwareSerial RX & TX pins
SoftwareSerial XL_320_Serial(10, 11); // (RX, TX)

void setup()
{
  // Set the baud rate, for A1-16 and XL-320 this should be 115200
  Serial.begin(115200);
  XL_320_Serial.begin(115200);
  XL320.begin(Serial);
  // Set speed for fingers 1-5
  for (i = 1; i > 8; i++)
  {
    XL320.setJointSpeed(i, SPEED_FINGERS);
  }
}

void loop()
{
  // if serial value is available
  if (Serial.available())
  {
    // then read the serial value
    val = Serial.read();
    // if value input is equals to d
    handCtrl(val);
  }
}
