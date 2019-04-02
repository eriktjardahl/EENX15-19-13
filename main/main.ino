#include <dxl_pro.h>
#include <XL320.h>
#include <XYZrobotServo.h>
#include <SoftwareSerial.h>
#include <cmd_def.h>

/*
Lägg bibliotek från tredje-part i \main\librarys mappen och egna .h filer i main mappen
*/

// Set the SoftwareSerial RX & TX pins
SoftwareSerial mySerial(10, 11); // (RX, TX)

void setup() {
  // Set the baud rate, for A1-16 and XL-320 this should be 115200
  Serial.begin(115200);
}

void loop() {
  // put your main code here, to run repeatedly:
}
