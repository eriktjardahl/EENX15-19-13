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


//---------------------------------Arm_RIGHT--------------------------------------------------//

 
#ifndef JOINTARMCLASS_RIGHT
#define JOINTARMCLASS_RIGHT

class JointArmClassRight {
  public:
    JointArmClassRight();
    void SETUP();
    void SSP();
    void MOVE();    

};

extern JointArmClassRight jointArmRight;

#endif
//---------------------------------Arm_LEFT--------------------------------------------------//

#ifndef JOINTARMCLASS_LEFT
#define JOINTARMCLASS_LEFT

class JointArmClassLeft {
  public:
    JointArmClassLeft();
    void SETUP();
    void SSP();    

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
  void NICK();
};

extern JointNeckClass jointNeck;

#endif
/*
//---------------------------------Hand_LEFT--------------------------------------------------//

#ifndef JOINTHANDCLASS_LEFT
#define JOINTHANDCLASS_LEFT

class JointHandClassLeft {
  public:
    JointHandClassLeft();
    void SETUP();
    void SSP();    

};

extern JointHandClassLeft jointHandLeft;

#endif

//---------------------------------Hand_RIGHT--------------------------------------------------//

#ifndef JOINTHANDCLASS_RIGHT
#define JOINTHANDCLASS_RIGHT

class JointHandClassRight {
  public:
    JointHandClassRight();
    void SETUP();
    void SSP();    

};

extern JointHandClassRight jointHandRight;

#endif
 */
