#ifndef COMPONENTHANDLER_H
#define COMPONENTHANDLER_H

#include <Arduino.h>
#include <EEPROM.h>
#include <EepromAdresses.h>
#include <logHandler.h>

#pragma once

void componentSetup();
void blinkLedBuiltin(int ripetitions);
void updateValueToEeprom(int address, byte value);

#endif