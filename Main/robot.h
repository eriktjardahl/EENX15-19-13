#include <XYZrobotServo.h>
#include <SoftwareSerial.h>
#include <dxl_pro.h>
#include <XL320.h>


#ifndef rxPin15 
#define rxPin15 15
#endif
#ifndef txPin14 
#define txPin14 14
#endif

#ifndef rxPin3 
#define rxPin3 3
#endif
#ifndef txPin4 
#define txPin4 4
#endif

#ifndef rxPin6 
#define rxPin6 6
#endif
#ifndef txPin7 
#define txPin7 7
#endif

#ifndef rxPin8 
#define rxPin8 8
#endif
#ifndef txPin9 
#define txPin9 9
#endif

#ifndef rxPin17 
#define rxPin17 17
#endif
#ifndef txPin16 
#define txPin16 16
#endif


#ifndef neckYaw 
#define neckYaw 11
#endif

#ifndef neckPichLeft 
#define neckPitchLeft 14
#endif

#ifndef neckPichRight 
#define neckPitchRight 13
#endif

#ifndef neckRoll 
#define neckRoll 15
#endif

#ifndef littleFingerLeft
#define littleFingerLeft 3
#endif

#ifndef ringFingerLeft
#define ringFingerLeft 2
#endif

#ifndef middleFingerLeft
#define middleFingerLeft 1
#endif

#ifndef indexFingerLeft
#define indexFingerLeft 4
#endif

#ifndef thumbLeft
#define thumbLeft 5
#endif

#ifndef littleFingerRight
#define littleFingerRight 10
#endif

#ifndef ringFingerRight
#define ringFingerRight 9
#endif

#ifndef middleFingerRight
#define middleFingerRight 8
#endif

#ifndef indexFingerRight
#define indexFingerRight 6
#endif

#ifndef thumbRight
#define thumbRight 7
#endif

#ifndef playtime
#define playtime 50
#endif

#ifndef SERVO_COUNT
#define SERVO_COUNT 6
#endif

void internalTimer(int intervall);
void stepFunc(XYZrobotServo A1_16_servo, int Start, int Stop, int Inc, int interval);
void stepFuncXL320(XL320 servo, int joint, int initPos, int stopPos, int Inc);

//---------------------------------Arm_RIGHT--------------------------------------------------//

 
#ifndef JOINTARMCLASS_RIGHT
#define JOINTARMCLASS_RIGHT

class JointArmClassRight 
{
  public:
    JointArmClassRight();
    void SETUP();
    void RESET(char LastCase);
    void scissor();
    void rock();   
    void paper(); 
    void armMotionSSP();
    void dab();
    void ok();
    void open();
    void fack();
    void close();
    void maxElbow();
    void perpendicular();
    void ShoulderRollPerp();
    void ShoulderPitchPerp();
    void test();
};

extern JointArmClassRight jointArmRight;

#endif
//---------------------------------Arm_LEFT--------------------------------------------------//

#ifndef JOINTARMCLASS_LEFT
#define JOINTARMCLASS_LEFT

class JointArmClassLeft 
{
  public:
    JointArmClassLeft();
    void SETUP();
    void RESET(char LastCase);
    void dabPart1();
    void dabPart2();
    void open();
    void close();
    void maxElbow();
    void perpendicular();
    void ShoulderRollPerp();
    void ShoulderPitchPerp();
    void test();
};

extern JointArmClassLeft jointArmLeft;

#endif


//-------------------------------------Neck------------------------------------------------//

#ifndef JOINTNECKCLASS
#define JOINTNECKCLASS

class JointNeckClass{
  public:
  JointNeckClass();
  void SETUP();
  void RESET(char LastCase);
  void nod();
  void dab();
  void neckYawLookLeft();
  void neckYawLookRight();
  void neckRollTiltLeft();
  void neckRollTiltRight();
  void neckPitchUp();
  void neckPitchDown();
  void shake();
  void wakeUp();
  void wakeDown();
  void test();

};

extern JointNeckClass jointNeck;

#endif

//---------------------------------Hand_LEFT--------------------------------------------------//

#ifndef MULTIPARTCLASS
#define MULTIPARTCLASS

class MultiPartClass{
  public:
  MultiPartClass();
  
  void RESET(char LastCase);
  void dab();
  
 // void dab();
};

extern MultiPartClass multiPart;

#endif
