#include "fx.cpp"

#define LED_PIN 6
#define LED_COUNT 144


Adafruit_NeoPixel strip(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);

void setup()
{
	strip.begin();
	strip.show();
}

void loop()
{
	strip.clear();
	for(int i = 0; i < LED_COUNT; i++)
	{
		strip.setPixelColor(i, 255, 0, 0);
		strip.show();
		delay(100);
	}
}
