
#include "Arduino.h"
#include "robot.h"

<<<<<<< HEAD
char input = 'b';
//char lastCase ='a';
=======
char input = 'f';
//char LastCase;
>>>>>>> e3ecda4350358b11c49de0e28e62623cec7d9630

void setup()
{
  // put your setup code here, to run once:
  jointArmLeft.SETUP();
  jointArmRight.SETUP();
  jointNeck.SETUP();
  Serial.begin(115200);

  switch (input)
  {
  case 'a': //Påse
    jointArmRight.close();
    jointArmRight.armMotionSSP();
    jointArmRight.paper();
    //lastCase = input;
    break;

<<<<<<< HEAD
  case 'b': //Reset
    jointArmLeft.RESET();
    break;
=======
  case 'b': //sax
    jointArmRight.close();
    jointArmRight.armMotionSSP();
    jointArmRight.scissor();
>>>>>>> e3ecda4350358b11c49de0e28e62623cec7d9630

    break;

<<<<<<< HEAD
  case 'd': // sten
    
    jointArmLeft.scissor();
=======
  case 'c': // sten
    jointArmRight.close();
    jointArmRight.armMotionSSP();
    jointArmRight.rock();
>>>>>>> e3ecda4350358b11c49de0e28e62623cec7d9630
    break;

  case 'd': //ok
    jointArmRight.ok();
    break;

  case 'e': // DAB
    jointNeck.dab();
    jointArmLeft.dab();
    jointArmRight.dab();
    break;

  case 'f': // fuck
    jointArmRight.fack();
    break;

  case 'o':
    jointArmRight.open();
    break;

  case 'p':
    jointArmRight.close();
    break;

  case 'r': //reset högerarm
    jointArmRight.RESET(/*lastCase*/);
    break;

  case 's': //reset nacke
    jointNeck.RESET();
    break;
  }
  
}

void loop()
{
}
