class Hand_motion_right{

  private:


  char input_signal;
  XL320 robot;

  //lillfinger .   ID:6
  //ringfinger     ID:7
  //långfinger    ID:8
  //pekfinger     ID:9
  //tummer        ID:10
 

  public: 

  Hand_motion_right(char input_signal){
    
    switch (input_signal) {
    case 'a':    // sten
      Serial.println("Sten");
     for(int j = 0 ; j < 1023; j+=5){
      for(int i = 6 ; i < 11; i++){
        robot.moveJoint(i, j);
        
      }
     }
      break;
    case 'b':    // sax
      Serial.println("Sax");
         for(int j = 0 ; j < 1023; j+=5){
      for(int i = 6 ; i < 11; i++){
       if( i == 6 ||  i == 7 ||  i == 10)
        robot.moveJoint(i, j);
      }}
      break;
    case 'c':    // påse
      Serial.println("Påse");
      break;
          case 'd':    // reset
      Serial.println("reset");
       for(int j = 1023 ; j = 0; j--){
      for(int i = 6 ; i < 11; i++){
        robot.moveJoint(i, j);
      
      break;
 
 
  }     
  }

}
