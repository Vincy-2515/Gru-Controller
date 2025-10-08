#ifndef COMPONENTHANDLER_H
#define COMPONENTHANDLER_H

#include <Arduino.h>
#include <EEPROM.h>
#include <EepromAddresses.h>
#include <logHandler.h>
#include <Motors.h>

void componentSetup();
void blinkLedBuiltin(int ripetitions);
void updateValueToEeprom(int address, byte value);

#endif