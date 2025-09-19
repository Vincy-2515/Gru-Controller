#include <Arduino.h>
#include <ArduinoBLE.h>
#include <bleGruControllerHandler.h>
#include <componentHandler.h>
#include <logHandler.h>

#define SERIAL_BAUD 115200

void setup() {
	Serial.begin(SERIAL_BAUD);
	printInfoMessage("Starting setup procedure...");

	componentSetup();
	bleGruControllerSetup();
	
	printInfoMessage("Setup completed");
}

void loop() {
	bleGruControllerLoop();
}
