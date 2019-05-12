#include "Arduino.h"
#include "robot.h"

unsigned long revMillis;
unsigned long currentMillis;

void internalTimer(int intervall)
{
    revMillis = millis();
    currentMillis = millis();
    while (currentMillis - revMillis <= intervall)
    {
        currentMillis = millis();
    }
}

void move_A1_16(XYZrobotServo A1_16_servo, int Start, int Stop, int Inc, int interval)
{
    if (Start < Stop)
    {
        for (int pos = Start; pos <= Stop; pos += Inc)
        {
            A1_16_servo.setPosition(pos, interval);
            internalTimer(interval);
        }
    }
    else
    {
        for (int pos = Start; pos >= Stop; pos -= Inc)
        {
            A1_16_servo.setPosition(pos, interval);
            internalTimer(interval);
        }
    }
}

void MOVE_NECK_PITCH(XL320 servo, int servo1, int servo2, int initPos1, int initPos2, int endPos1, int endPos2, int interval)
{
    for (int i = initPos1, k = initPos2; i <= endPos1, k >= endPos2; i++, k--)
    {
        servo.moveJoint(servo1, i);
        servo.moveJoint(servo2, k);
        internalTimer(interval);
    }
}

void move_XL_320(XL320 servo, int joint, int initPos, int stopPos, int Inc, int interval)
{
    if (initPos < stopPos)
    {
        for (int i = initPos; i <= stopPos; i += Inc)
        {
            servo.moveJoint(joint, i);
            internalTimer(interval);
        }
    }
    else
    {
        for (int i = initPos; i >= stopPos; i -= Inc)
        {
            servo.moveJoint(joint, i);
            internalTimer(interval);
        }
    }
}