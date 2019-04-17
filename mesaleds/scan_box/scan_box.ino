#include <Adafruit_NeoPixel.h>
#define PIN 6
#define NUM_LEDS 144
Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUM_LEDS, PIN, NEO_GRB + NEO_KHZ800);

void setup() {
  Serial.begin(9600);
  strip.begin();
  strip.show(); // Initialize all pixels to 'off'
}

void draw_box(int a, int b) {
   for(int i=0; i<3; i++) {
     for(int j=0; j<3; j++) {
        table(a+i,b+j,20,0,0);
     }
   }
   showStrip();       
}


void erase_box(int a, int b) {
   for(int i=0; i<3; i++) {
     for(int j=0; j<3; j++) {
        table(a+i,b+j,0,0,0);
     }
   }
   showStrip();       
}


void table(int i, int j, byte red, byte green, byte blue)
{
  if ( i > 11 | i < 0  ) return;
  if ( j > 11 | j<  0  ) return;
  
  int x = i * 12;
  x  = (i%2)? x+11-j:x+j;
  setPixel(x, red, green, blue);
   
}

void loop() {
 for (int i=0; i < 12; i++) {
    draw_box(i,i);
    delay(500);
    erase_box(i,i);
 
 }
}




void showStrip() {
 #ifdef ADAFRUIT_NEOPIXEL_H 
   // NeoPixel
   strip.show();
 #endif
 #ifndef ADAFRUIT_NEOPIXEL_H
   // FastLED
   FastLED.show();
 #endif
}

void setPixel(int Pixel, byte red, byte green, byte blue) {
 #ifdef ADAFRUIT_NEOPIXEL_H 
   // NeoPixel
   strip.setPixelColor(Pixel, strip.Color(red, green, blue));
 #endif
 #ifndef ADAFRUIT_NEOPIXEL_H 
   // FastLED
   leds[Pixel].r = red;
   leds[Pixel].g = green;
   leds[Pixel].b = blue;
 #endif
}

void setAll(byte red, byte green, byte blue) {
  for(int i = 0; i < NUM_LEDS; i++ ) {
    setPixel(i, red, green, blue); 
  }
  showStrip();
}
