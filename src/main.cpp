#include <Arduino.h>
#include <ArduinoBLE.h>
#include <bleGruControllerHandler.h>
#include <componentHandler.h>
#include <eepromHandler.h>
#include <logHandler.h>

#define SERIAL_BAUD (115200)

void setup() {
	Serial.begin(SERIAL_BAUD);

	printInfoMessage("Starting setup procedure...");

	eepromSetup();
	componentsSetup();
	bleGruControllerSetup();

	printInfoMessage("Setup completed");
}

void loop() {
	bleGruControllerLoop();
}
