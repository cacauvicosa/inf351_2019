#include <Wire.h>
//deifinir endereco de casa slave
#define slave1 0x08
#define slave2 0x09

void setup(){
	Wire.begin();
  	Serial.begin(9600);
}

void loop(){
 	Wire.beginTransmission (slave1);
  	Wire.write('a');
  	Wire.endTransmission ();
  
  	delay(500);
  	
  	Wire.beginTransmission (slave2);
  	Wire.write('b');
  	Wire.endTransmission ();
  
}