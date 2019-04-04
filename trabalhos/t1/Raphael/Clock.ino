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

  int a, b, i;

  while (true) {
    // put your main code here, to run repeatedly:
    cycle(1, 0, 1000);

    // 12.5ns per instruction
    a = 1000 * (1000 - theta) / 12.5;
    b = 1000 * (1000 + theta) / 12.5;

    digitalWrite(LED_OUTPUT, LOW); // sets the pin off
    for (i = 0; i < a; i++)        // pauses for a microseconds
      ;

    digitalWrite(LED_OUTPUT, HIGH); // sets the pin on
    for (i = 0; i < b; i++)         // pauses for b microseconds
      ;
  }
}

void loop() {}
