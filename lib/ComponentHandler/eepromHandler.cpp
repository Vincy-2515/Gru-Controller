#include <eepromHandler.h>

void writeBoolValueToEeprom(Preferences& preferences, const char* namespace_name, const char* key_name, bool value) {
	if (!preferences.begin(namespace_name, EEPROM_MODE_READ_WRITE)) {
		printErrorMessage("No value was written, couldn't access the namespace \"%s\"", namespace_name);
		return;
	}

	if (!preferences.isKey(key_name)) {
		printErrorMessage("No value was written, inexistent key \"%s\"", key_name);
		return;
	}

	if (preferences.putBool(key_name, value) == 0) {
		printErrorMessage("No value was written, some error had occurred");
	} else {
		printInfoMessage("Wrote value \"%d\" to key \"%s\"", value, key_name);
	}

	preferences.end();
}

bool readBoolValueFromEeprom(Preferences& preferences, const char* namespace_name, const char* key_name) {
	if (!preferences.begin(namespace_name, EEPROM_MODE_READ)) {
		printErrorMessage("No value was read, couldn't access the namespace \"%s\"", namespace_name);
		return false;
	}

	if (!preferences.isKey(key_name)) {
		printErrorMessage("No value was read, inexistent key \"%s\"", key_name);
		return false;
	}

	bool value = preferences.getBool(key_name);

	preferences.end();

	return value;
}

void writeByteValueToEeprom(Preferences& preferences, const char* namespace_name, const char* key_name, byte value) {
	if (!preferences.begin(namespace_name, EEPROM_MODE_READ_WRITE)) {
		printErrorMessage("No value was written, couldn't access the namespace \"%s\"", namespace_name);
		return;
	}

	if (!preferences.isKey(key_name)) {
		printErrorMessage("No value was written, inexistent key \"%s\"", key_name);
		return;
	}

	if (preferences.putUChar(key_name, value) == 0) {
		printErrorMessage("No value was written, some error had occurred");
	} else {
		printInfoMessage("Wrote value \"%d\" to key \"%s\"", value, key_name);
	}

	preferences.end();
}

byte readByteValueFromEeprom(Preferences& preferences, const char* namespace_name, const char* key_name) {
	if (!preferences.begin(namespace_name, EEPROM_MODE_READ)) {
		printErrorMessage("No value was read, couldn't access the namespace \"%s\"", namespace_name);
		return 0;
	}

	if (!preferences.isKey(key_name)) {
		printErrorMessage("No value was read, inexistent key \"%s\"", key_name);
		return 0;
	}

	byte value = preferences.getUChar(key_name);

	preferences.end();

	return value;
}
