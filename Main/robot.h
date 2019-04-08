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


#ifndef neckJaw 11
#define neckJaw 11
#endif

#ifndef neckPich 12
#define neckPitch 12
#endif

#ifndef neckRoll 13
#define neckRoll 13
#endif



#ifndef littleFinger_Left
#define littleFinger_Left 1
#endif

#ifndef ringFinger_Left
#define ringFinger_Left 2
#endif

#ifndef middleFinger_Left
#define middleFinger_Left 3
#endif

#ifndef indexFinger_Left
#define indexFinger_Left 4
#endif

#ifndef thumb_Left
#define thumb_Left 5
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
    void HandLeft_Stone(); 
    void HandLeft_Scissor();  

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
  void nod();
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
