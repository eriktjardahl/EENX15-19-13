// This sketch shows how to move a servo back and forth between
// two different position.
//
// Positions are represented as numbers between 0 and 1023.  When
// you set a position, you can also specify the playtime, which
// is how long you want the movement to take, in units of 10 ms.
//
// This sketch only writes data to the servos; it does not
// receive anything.

#include <XYZrobotServo.h>

// On boards with a hardware serial port available for use, use
// that port. For other boards, create a SoftwareSerial object
// using pin 10 to receive (RX) and pin 11 to transmit (TX).
#ifdef SERIAL_PORT_HARDWARE_OPEN
#define servoSerial SERIAL_PORT_HARDWARE_OPEN
#else
#include <SoftwareSerial.h>
SoftwareSerial servoSerial(10, 11);
#endif

// Set up a servo object, specifying what serial port to use and
// what ID number to use.
//
// WARNING: Only change the ID number below to a servo that can
// rotate freely without damaging anything.
//#define SERVO_COUNT 3
XYZrobotServo servo1(servoSerial, 1);




//XYZrobotServo * servos[SERVO_COUNT] = {
  //&servo, &servo2, &servo3};
const uint8_t playtime = 75;

void setup()
{
  // Turn on the serial port and set its baud rate.
  servoSerial.begin(115200);
}

void loop()
{
  servo1.reboot();
  delay(2500);
  servo1.setPosition(0, playtime);
  delay(2500);
  servo1.setPosition(1023, playtime);

  
}
