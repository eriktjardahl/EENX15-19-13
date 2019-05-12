#include <XYZrobotServo.h>
#include <SoftwareSerial.h>
#include <dxl_pro.h>
#include <XL320.h>

//================== Function definitions ==================//
void internalTimer(int intervall);
void move_A1_16(XYZrobotServo A1_16_servo, int Start, int Stop, int Inc, int interval);
void move_XL_320(XL320 servo, int joint, int initPos, int stopPos, int Inc, int interval);
void MOVE_NECK_PITCH(XL320 servo, int servo1, int servo2, int initPos1, int initPos2, int endPos1, int endPos2, int interval);