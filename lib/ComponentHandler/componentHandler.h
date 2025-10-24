#ifndef COMPONENTHANDLER_H
#define COMPONENTHANDLER_H

#include <Arduino.h>
#include <Preferences.h>
#include <eepromHandler.h>
#include <logHandler.h>
#include <types.h>

void componentsSetup();
void blinkLedBuiltin(int ripetitions);
void updateMotorState(MotorId motor_id, Action action, Rotation rotation, Gear gear);

#endif