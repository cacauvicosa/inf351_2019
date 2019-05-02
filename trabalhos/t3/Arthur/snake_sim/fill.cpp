#include "fx.cpp"


#define LED_PIN 1
#define ROWS 12
#define COLS 12
#define LED_COUNT 144

int map_px ( int l, int c ) {
	return l *  COLS + ((l % 2)?COLS-c-1:c);
}

Adafruit_NeoPixel strip(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);


void setup () {
	
	set_num_cols(COLS); // Apenas no simulador, comentar para Arduino

	strip.begin();

	strip.setPixelColor(map_px(6,7), 0x00FF0000); // line 6, column 7, RED
	
	strip.show ();
	
}

void loop () {
  for (int i=0; i<12;i++) {
    for (int j=0; j< 12; j++) {
	strip.setPixelColor(map_px(i,j), 0x00FF0000); // line 6, column 7, RED
	strip.show();
	delay(500);
    }
  }

}
