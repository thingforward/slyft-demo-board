#include <Arduino.h>

#include "tfwifi.h"
#include "app.h"

void setup() {
	Serial.begin(9600);
	//Serial.setDebugOutput(true);

	setup_app();
	//setup_wifi();
}

void loop() {
	delay(1000);
	loop_app();
}

