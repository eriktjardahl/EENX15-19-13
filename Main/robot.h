#include <dxl_pro.h>
#include <XL320.h>
#include <XYZrobotServo.h>
#include <SoftwareSerial.h>

#ifndef rxPin0 0
#define rxPin0 0
#endif
#ifndef txPin1 1
#define txPin1 1
#endif


#ifndef rxPin3 3
#define rxPin3 3
#endif
#ifndef txPin4 4
#define txPin4 4
#endif

#ifndef rxPin6 6
#define rxPin6 6
#endif
#ifndef txPin7 7
#define txPin7 7
#endif

#ifndef rxPin8 8
#define rxPin8 8
#endif
#ifndef txPin9 9
#define txPin9 9
#endif

#ifndef rxPin10 10
#define rxPin10 10
#endif
#ifndef txPin11 11
#define txPin11 11
#endif

#ifndef SERVO_COUNT
#define SERVO_COUNT 6
#endif


//---------------------------------Arm--------------------------------------------------//

 
#ifndef JOINTARMCLASS
#define JOINTARMCLASS

class JointArmClass {
  public:
    JointArmClass();
    void SETUP();
    void SSP();    

};

extern JointArmClass jointArm;

#endif


//-------------------------------------Neck------------------------------------------------//

#ifndef JOINTNECKCLASS
#define JOINTNECKCLASS

class JointNeckClass{
  public:
  JointNeckClass();
  void SETUP();
  void NICK();
};

extern JointNeckClass jointNeck;

#endif
