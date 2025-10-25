#ifndef COMPONENTHANDLER_H
#define COMPONENTHANDLER_H

#include <Arduino.h>
#include <Preferences.h>
#include <eepromHandler.h>
#include <logHandler.h>
#include <types.h>

#define ANALOG_HIGH (255)
#define ANALOG_LOW (0)

void componentsSetup();
void blinkLedBuiltin(int ripetitions);
void updateMotorState(MotorId motor_id, Action action, Rotation rotation, Gear gear);

#endif