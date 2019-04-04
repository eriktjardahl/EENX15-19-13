
  int servoID;
  char input_signal;
  XL320 robot;

  //lillfinger .   ID:1
  //ringfinger     ID:2
  //långfinger    ID:3
  //pekfinger     ID:4
  //tummer        ID:5
 

  public: 

  Hand_motion_left(char input_signal){
    
    switch (input_signal) {
    case 'a':    // sten
      Serial.println("Sten");
     for(int j = 0 ; j < 1023; j+=10){
      for(int i = 1 ; i < 6; i++){
        robot.moveJoint(i, j);
        
      }
     }
      break;
    case 'b':    // sax
      Serial.println("Sax");
         for(int j = 0 ; j < 1023; j+=10){
      for(int i = 1 ; i < 6; i++){
       if( i == 1 ||  i == 2 ||  i == 5)
        robot.moveJoint(i, j);
      }}
      break;
    case 'c':    // påse
      Serial.println("Påse");

      
      break;
 
  }

    



     
  }

  

  

    


  
}
