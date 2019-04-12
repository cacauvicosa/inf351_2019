
#include <avr/io.h> 
int outPin = 13;               // digital pin 8


    
inline void mydelay(unsigned long  period) {
  unsigned long int time_now = 0;
  time_now = micros();
  while(micros()-time_now <= period);
}

void setup() {
  pinMode(outPin, OUTPUT);    // sets the digital pin as output
}

void loop() {
  for (int i= 0; i < 1000; i+=10) {
    for (int j=0; j< 10; j++ ) {
       
       digitalWrite(outPin, LOW); // sets the pin on
       mydelay(1000+i); //delayMicroseconds(1000-i);      // pauses for 50 microseconds
       digitalWrite(outPin, HIGH);  // sets the pin off
       mydelay(1000-i); //delayMicroseconds(1000+i);      // pauses for 50 microseconds
      
     }

  }
}
