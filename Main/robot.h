#include <dxl_pro.h>
#include <XL320.h>
#include <XYZrobotServo.h>
#include <SoftwareSerial.h>

#ifndef rxPin1 
#define rxPin1 1
#endif
#ifndef txPin2 
#define txPin2 2
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

#ifndef rxPin10 
#define rxPin10 10
#endif
#ifndef txPin11 
#define txPin11 11
#endif


#ifndef neckJaw 
#define neckJaw 11
#endif

#ifndef neckPich 
#define neckPitch 12
#endif

#ifndef neckRoll 
#define neckRoll 13
#endif

#ifndef littleFingerLeft
#define littleFingerLeft 1
#endif

#ifndef ringFingerLeft
#define ringFingerLeft 2
#endif

#ifndef middleFingerLeft
#define middleFingerLeft 3
#endif

#ifndef indexFingerLeft
#define indexFingerLeft 4
#endif


#ifndef thumbLeft
#define thumbLeft 5
#endif

#ifndef littleFingerRight
#define littleFingerRight 8
#endif

#ifndef ringFingerRight
#define ringFingerRight 9
#endif

#ifndef middleFingerRight
#define middleFingerRight 10
#endif

#ifndef indexFingerRight
#define indexFingerRight 6
#endif

#ifndef thumbRight
#define thumbRight 7
#endif

#ifndef playtime
#define playtime 30
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
    void RESET();
    void scissor();
    void rock();   
    void paper(); 
    void armMotionSSP();
    void dab();
    void ok();
    void open();
    void fack();
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
    void RESET();
    void rock(); 
    void scissor(); 
    void paper();  
    void armMotionSSP();
    void dab();
    void test();
    void open();
    

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
  void RESET();
  void nod();
  void dab();
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
