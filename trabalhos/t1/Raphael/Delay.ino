#define LED_OUTPUT (LED_BUILTIN)

int theta = 0;
bool increment = true;

int cycle(unsigned int step_, unsigned int lower, unsigned int upper) {
  if (theta <= lower)
    increment = true;
  else if (theta >= upper)
    increment = false;

  if (increment)
    theta += step_;
  else
    theta -= step_;
}

void setup() {
  // put your setup code here, to run once:
  pinMode(LED_OUTPUT, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  cycle(1, 0, 1000);

  digitalWrite(LED_OUTPUT, LOW);   // sets the pin off
  delayMicroseconds(1000 - theta); // pauses for theta microseconds

  digitalWrite(LED_OUTPUT, HIGH);  // sets the pin on
  delayMicroseconds(1000 + theta); // pauses for theta microseconds
}
