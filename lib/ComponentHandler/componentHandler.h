#ifndef COMPONENTHANDLER_H
#define COMPONENTHANDLER_H

#include <Arduino.h>
#include <EepromNamespacesAndKeys.h>
#include <Motors.h>
#include <Preferences.h>
#include <logHandler.h>

#define EEPROM_MODE_READ_WRITE false
#define EEPROM_MODE_READ true

void componentsSetup();
void blinkLedBuiltin(int ripetitions);
void writeValueToEeprom(Preferences& preferences, const char* namespace_name, const char* key_name, byte value);
byte readValueFromEeprom(Preferences& preferences, const char* namespace_name, const char* key_name);

#endif