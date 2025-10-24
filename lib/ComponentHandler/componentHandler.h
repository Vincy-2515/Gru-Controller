#ifndef COMPONENTHANDLER_H
#define COMPONENTHANDLER_H

#include <Arduino.h>
#include <types.h>
#include <Preferences.h>
#include <eepromHandler.h>
#include <logHandler.h>

void componentsSetup();
void blinkLedBuiltin(int ripetitions);
void updateMotorState(MotorId motor_id, Action action, Rotation rotation, Gear gear);

#endif