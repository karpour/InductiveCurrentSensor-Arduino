#include <Arduino.h>
#include <HardwareSerial.h>
#include "InductiveCurrentSensor.h"

void setup() {
	Serial.begin(57600);
	pinMode(13, OUTPUT); // LED
	analogReference(EXTERNAL); // connected to 3.3V supply
}

void loop() {
	Serial.print(measure_amplitude());
	Serial.print("\n");

	/*
	float avg = 0.0;
	for(int i=0;i<10;i++) avg+=measure_amplitude();
	Serial.print("; ");
	Serial.print(avg/10.0);
	*/

	delay(1000);
}