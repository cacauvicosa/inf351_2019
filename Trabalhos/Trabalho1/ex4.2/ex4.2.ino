
void mydelay(unsigned int t) {

int i;
for(i = 0; i < t; i++)
    __asm("nop\n" "nop\n" "nop\n" "nop\n"
          "nop\n" "nop\n" "nop\n" "nop\n"
          "nop\n" "nop\n" "nop\n");
          
} 

const int outPin = 13;
void setup() {
  // put your setup code here, to run once:
  pinMode(13,OUTPUT);
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
