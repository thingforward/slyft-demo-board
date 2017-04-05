#include <Arduino.h>

#include "Grove_LED_Bar/Grove_LED_Bar.h"

#include "app.h"

#define	PIN_BUTTON	D6
#define PIN_ROTARY	A0
#define PIN_LEDBAR_SCL	D2
#define PIN_LEDBAR_SDA	D1

int 	rotary_value	= 0;
bool	button_value 	= false;

Grove_LED_Bar	led_bar(PIN_LEDBAR_SCL, PIN_LEDBAR_SDA, true);

void setup_app() {
	pinMode(PIN_BUTTON, INPUT);
	pinMode(PIN_ROTARY, INPUT);
	led_bar.begin();
}

void loop_app() {
	rotary_value = analogRead(PIN_ROTARY);
	button_value = digitalRead(PIN_BUTTON);

	Serial.printf("rotary: %d, button: %i\n", rotary_value, button_value);

	float f = rotary_value / 100.0f;
	if ( f > 9) {
		f = 9;
	}

	led_bar.setLevel(f);

	if ( button_value) {
		led_bar.toggleLed(10);
	}
}

