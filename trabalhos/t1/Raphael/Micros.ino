#define LED_OUTPUT (LED_BUILTIN)

int theta = 0;
bool increment = true;

unsigned long last_time = 0;
unsigned long curr_time = 0;

unsigned long accumulator = 0;

bool active = false;

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
  last_time = curr_time;
  curr_time = micros();

  accumulator += curr_time - last_time;

  if (active == false && accumulator >= 1000 - theta) {
    active = !active;
    accumulator = 0;

    digitalWrite(LED_OUTPUT, HIGH); // sets the pin on
  } else if (active == true && accumulator >= 1000 + theta) {
    active = !active;
    accumulator = 0;

    digitalWrite(LED_OUTPUT, LOW);
    cycle(1, 0, 1000);
  }
}
