#include <Wire.h>

void setup(){
	Wire.begin(0x08);
  	Wire.onReceive(receiveEvent);
  	pinMode(13,OUTPUT);
}

void loop(){};

void receiveEvent(int howMany){
	
  if(Wire.available()){
  
    char aux = Wire.read();
    
    if(aux == 'a')
      digitalWrite(13,HIGH);
    
  }
  
  delay(400);
  digitalWrite(13,LOW);

}