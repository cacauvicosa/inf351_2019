#include <Adafruit_NeoPixel.h>
#define PIN 6
#define NUM_LEDS 144
Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUM_LEDS, PIN, NEO_GRB + NEO_KHZ800);

void setup() {
  strip.begin();
  strip.show(); // Initialize all pixels to 'off'
}


void table(int i, int j, byte red, byte green, byte blue)
{
  int x = i * 12;
  x  = (i%2)? x+11-j:x+j;
  setPixel(x, red, green, blue);
   
}

void loop() {
 for(uint16_t i=0; i<12; i++) {
   for(uint16_t j=0; j<12; j++) {
      table(i,j,20-i,0,0);
      showStrip();
      delay(10);
   }
 }
   for(uint16_t i=0; i<12; i++) {
   for(uint16_t j=0; j<12; j++) {
      table(i,j,0,10+i,0);
      showStrip();
      delay(10);
 
   }
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
