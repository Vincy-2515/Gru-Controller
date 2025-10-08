#include "componentHandler.h"

void componentSetup() {
	pinMode(LED_BUILTIN, OUTPUT);
	digitalWrite(LED_BUILTIN, LOW);

	if (!EEPROM.begin(EEPROM_ADDRESS_COUNT)) {
		printErrorMessage("EEPROM class failed to initialize, press the reset button to retry");
		while (true)
			blinkLedBuiltin(1);
	}

	for (Motor& m : motors) {
		m.updateValuesFromEeprom();
	}
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

void updateValueToEeprom(int address, byte value) {
	if (EEPROM.read(address) != value) {
		EEPROM.write(address, value);
		EEPROM.commit();
	}
}
