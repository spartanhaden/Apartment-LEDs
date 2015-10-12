#include "neopixel.h"

SYSTEM_MODE(AUTOMATIC);

#define PIXEL_TYPE WS2812B

Adafruit_NeoPixel strip1 = Adafruit_NeoPixel(45, D0, PIXEL_TYPE);
Adafruit_NeoPixel strip2 = Adafruit_NeoPixel(15, D1, PIXEL_TYPE);

uint32_t leds[60];
bool enabled = true;

void setup() {
	Particle.function("switch", switchState);
	strip1.begin();
	strip2.begin();
	strip1.show();
	strip2.show();
}

int switchState(String command){
	enabled = !enabled;
}

void loop() {
	if(enabled)
		rainbow(50);
	else {
		strip1.clear();
		strip2.clear();
		strip1.show();
		strip2.show();
		delay(100);
	}
}

void rainbow(uint8_t wait) {
	uint16_t i, j;

	for(j = 0; j < 256; j++) {
		if (!enabled)
			return;
		for (i = 0; i < 60; i++) {
			if(i < 45)
				strip1.setPixelColor(i, Wheel((i+j) & 255));
			else
				strip2.setPixelColor(i - 45, Wheel((i+j) & 255));
		}
		strip1.show();
		strip2.show();
		delay(wait);
	}
}

// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
uint32_t Wheel(byte WheelPos) {
	if (WheelPos < 85)
		return strip1.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
	else if (WheelPos < 170) {
		WheelPos -= 85;
		return strip1.Color(255 - WheelPos * 3, 0, WheelPos * 3);
	} else {
		WheelPos -= 170;
		return strip1.Color(0, WheelPos * 3, 255 - WheelPos * 3);
	}
}
