#include <SoftwareSerial.h>

SoftwareSerial BT(10,11);
  void setup(){
  
    pinMode(13,OUTPUT);//전전원불들엉온늕확읺항슴맡틒폰블뤁틋몯젣댈작동한늕확
    BT.begin(9600);
    BT.println("Hello My name is BAEK");
  }
  
  char a;
  void loop(){
    if(BT.available()){
      a = (BT.read());
      if(a=='1'){
        digitalWrite(13,HIGH);
        BT.println("LED on");
      }
      
      if(a=='2'){
        digitalWrite(13,LOW);
        BT.println("LED off");
      }
      if(a=='?'){
        BT.println("Send '1' or '2'");
      } 
      
    }
  }
