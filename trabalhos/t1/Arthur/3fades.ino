
int num;
int outPin = LED_BUILTIN;
int i;

char opt = 'd'; // { 'd', 'l', 'm' }
char r;

unsigned long t;

int k;
int k_inc;
int target;
int t_inc;

int d;
int d_inc;

void ICACHE_RAM_ATTR fade_control() {
  if(digitalRead(outPin) == HIGH) {
    
    digitalWrite(outPin, LOW);
    d += d_inc;
    timer1_write(50000 + d);
    if(d < -45000 || d > 5000) d_inc = -d_inc;
  
  } else {
    digitalWrite(outPin, HIGH);
    timer1_write(70000);
  }
}

bool on_millis;
bool on_timer;
bool sw;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(outPin, OUTPUT);

  d = 0;
  d_inc = 1000;
 
  k = 5;
  k_inc = 5;

  target = 1000;
  t_inc = 100;

  sw = true;
  on_millis = false;
  on_timer = false;

  timer1_attachInterrupt(fade_control);
  
}

void loop() {
  // put your main code here, to run repeatedly:

  if(Serial.available() > 0) { r = Serial.read(); if (r == 'd' || r == 'l' || r == 'm') opt = r; }

  switch(opt) {
    
    case 'd' :// Delay
    { 
      on_millis = false;
      if(!on_timer){
        on_timer = true;
        timer1_enable(TIM_DIV16, TIM_EDGE, TIM_SINGLE);
        timer1_write(600000); // 12us
      }
      /*for (int i= 10; i < 1000; i+=10) {
        for (int j=0; j< 10; j++ ) {
          digitalWrite(outPin, HIGH); // sets the pin on
          delayMicroseconds(1000-i);      // pauses for 50 microseconds
          digitalWrite(outPin, LOW);  // sets the pin off
          delayMicroseconds(1000+i);      // pauses for 50 microseconds
        }
        yield();
      } */
      break;
    }

    case 'l' : // For
    // 80MHz => 10^7 instruções ~ 0.125 segundos
    {
      if(on_timer) {

        on_timer = false;
        timer1_disable();
        
      }
      on_millis = false;
      
      if(k < -3600 || k >= 4800) { k_inc = -k_inc; }
      k += k_inc;
  
      num = 4800;
      for(i = 0; i < num + k; i++);
      digitalWrite(outPin, LOW);
      for(i = 0; i < num - k ; i++);
      digitalWrite(outPin, HIGH);
    
      break;
    }
    case 'm' :
    {

      if(on_timer) {

        on_timer = false;
        timer1_disable();
     
      }
      
      if(!on_millis){
        
        on_millis = true;
        t = micros();
        sw = true;
        digitalWrite(outPin, LOW);
        
      } else {

        unsigned long interval = micros() - t;

        if(interval > 1000) {
          if(sw) {
            if(interval > target + 1000){
              digitalWrite(outPin, LOW);
              sw = false;
              target += t_inc; 
              if(target < 0 || target > 20000) t_inc = -t_inc;
              t = micros();
            }
          } else {
              digitalWrite(outPin, HIGH);
              sw = true;
          }
        }
      }

      break;
    }
  }
}
