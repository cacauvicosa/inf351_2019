int outPin = 13;               // digital pin 8

void setup() {
  pinMode(outPin, OUTPUT);    // sets the digital pin as output
}

void loop() {
  for (int i= 10; i < 1000; i+=10) {
    for (int j=0; j< 10; j++ ) {
       digitalWrite(outPin, HIGH); // sets the pin on
       delayMicroseconds(1000-i);      // pauses for 50 microseconds
       digitalWrite(outPin, LOW);  // sets the pin off
       delayMicroseconds(1000+i);      // pauses for 50 microseconds
     }
  }
}
