#include "componentHandler.h"

#define __EEPROM_KEY_INITIALIZATION "isInitialized"

void __pinsSetup();
void __eepromSetup();
void __motorsSetup();

void componentsSetup() {
	__pinsSetup();
	__eepromSetup();
	__motorsSetup();
}

void __pinsSetup() {
	printInfoMessage("Starting pins setup procedure...");

	pinMode(LED_BUILTIN, OUTPUT);
	digitalWrite(LED_BUILTIN, LOW);

	printInfoMessage("Pins setup procedure ended");
}

void __eepromSetup() {
	printInfoMessage("Starting EEPROM setup procedure...");

	for (Motor* m : motors) {
		m->motor_speeds.begin(m->getEepromNamespaceMotor(), EEPROM_MODE_READ);

		bool is_preferences_namespace_initialized = m->motor_speeds.isKey(__EEPROM_KEY_INITIALIZATION);

		if (!is_preferences_namespace_initialized) {
			printWarningMessage("Namespace: \"%s\" not initialized, initializing...", m->getEepromNamespaceMotor());

			m->motor_speeds.end();
			m->motor_speeds.begin(m->getEepromNamespaceMotor(), EEPROM_MODE_READ_WRITE);

			m->motor_speeds.putUChar(m->getEepromKeyFirstGearSpeed(), 0);
			m->motor_speeds.putUChar(m->getEepromKeySecondGearSpeed(), 0);
			m->motor_speeds.putUChar(m->getEepromKeyThirdGearSpeed(), 0);
			m->motor_speeds.putUChar(m->getEepromKeyDefaultSpeed(), 0);

			m->motor_speeds.putBool(__EEPROM_KEY_INITIALIZATION, true);

			m->motor_speeds.end();
		}

		m->motor_speeds.end();
	}

	printInfoMessage("EEPROM setup procedure ended");
}

void __motorsSetup() {
	printInfoMessage("Starting motors setup procedure...");

	for (Motor* m : motors) {
		m->updateValuesFromEeprom();
	}

	printInfoMessage("Motors setup procedure ended");
}

void blinkLedBuiltin(int ripetitions) {
	int i = 0;
	while (i < ripetitions) {
		digitalWrite(LED_BUILTIN, LOW);
		delay(125);
		digitalWrite(LED_BUILTIN, HIGH);
		delay(125);
		i++;
	}
}

void writeValueToEeprom(Preferences& preferences, const char* namespace_name, const char* key_name, byte value) {
	if (!preferences.begin(namespace_name, EEPROM_MODE_READ_WRITE)) {
		printErrorMessage("No value was written, couldn't access the namespace");
		return;
	}

	if (!preferences.isKey(key_name)) {
		printErrorMessage("No value was written, inexistent key: \"%s\"", key_name);
		return;
	}

	if (preferences.putUChar(key_name, value) == 0) {
		printErrorMessage("No value was written, some error had occurred");
	} else {
		printInfoMessage("Wrote value: \"%d\" to key: \"%s\"", value, key_name);
	}

	preferences.end();
}

byte readValueFromEeprom(Preferences& preferences, const char* namespace_name, const char* key_name) {
	if (!preferences.begin(namespace_name, EEPROM_MODE_READ)) {
		printErrorMessage("No value was read, couldn't access the namespace");
		return 0;
	}

	if (!preferences.isKey(key_name)) {
		printErrorMessage("No value was read, inexistent key: \"%s\"", key_name);
		return 0;
	}

	byte value = preferences.getUChar(key_name);

	preferences.end();

	return value;
}
