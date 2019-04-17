#include <Adafruit_NeoPixel.h>
#define PIN 6
#define NUM_LEDS 144
Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUM_LEDS, PIN, NEO_GRB + NEO_KHZ800);

void setup() {
  Serial.begin(9600);
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
 for (byte r=0; r<40; r+=4) {
 for (byte g=0; g<40; g+=4) {  
 for (byte b=0; b<40; b+=4) {  
   for(int j=0; j<12; j++) {
     for(int i=0; i<12; i++) {
        table(i,j,r,g,b);
     }
   }
   showStrip();   
 }
 }
 }

 for (byte g=0; g<40; g+=4) {  
 for (byte r=0; r<40; r+=4) {
 for (byte b=0; b<40; b+=4) {  
   for(int j=0; j<12; j++) {
     for(int i=0; i<12; i++) {
        table(i,j,r,g,b);
     }
   }
   showStrip();   
 }
 }
 }

 for (byte b=0; b<40; b+=4) {  
 for (byte g=0; g<40; g+=4) {  
 for (byte r=0; r<40; r+=4) {
   for(int j=0; j<12; j++) {
     for(int i=0; i<12; i++) {
        table(i,j,r,g,b);
     }
   }
   showStrip();   
 }
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
