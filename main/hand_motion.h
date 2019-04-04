#ifndef HAND_MOTION_H
#define HAND_MOTION_H
#endif

#include <cmd_def.h>
#include <SoftwareSerial.h>




void handCtrl(char READ_VAR)
{
  
    switch (READ_VAR)
    {
    case 'd':
        int servoPosition += 1;                             //than position of servo motor increases by 1 ( anti clockwise)
        hand.moveJoint(RIGHT_FINGER_1, servoPosition); // the servo will move according to position
        break;
    case 'a':
        int servoPosition -= 1;                             //than position of servo motor decreases by 1 (clockwise)
        hand.moveJoint(RIGHT_FINGER_1, servoPosition); // the servo will move according to position
        break;
    default:
        break;
    }
}
