#ifndef MOTOR_H
#define MOTOR_H

#pragma once

#include <Arduino.h>
#include <EEPROM.h>
#include <componentHandler.h>
#include <eepromAdresses.h>

class Motor {
private:
	String __motor_name;

	int __direction_controlling_pin_1; // IN1 or IN2 or IN3 or IN4 of the L298N
	int __direction_controlling_pin_2; // IN1 or IN2 or IN3 or IN4 of the L298N
	int __speed_controlling_pin; // ENA or ENB of the L298N

	byte __first_gear_speed;
	byte __second_gear_speed;
	byte __third_gear_speed;
	byte __default_speed;

	int __eeprom_address_first_gear_speed;
	int __eeprom_address_second_gear_speed;
	int __eeprom_address_third_gear_speed;
	int __eeprom_address_default_speed;

public:
	Motor(String motor_name,
	    int direction_controlling_pin1,
	    int direction_controlling_pin2,
	    int speed_controlling_pin,
	    int first_gear_speed_eeprom_address,
	    int second_gear_speed_eeprom_address,
	    int third_gear_speed_eeprom_address,
	    int default_speed_eeprom_address);
	void updateValuesFromEeprom();
	void transferValuesToEeprom();
	void setAllSpeeds(byte first_gear_speed, byte second_gear_speed, byte third_gear_speed, byte default_speed);
	void setFirstGearSpeed(byte first_gear_speed);
	byte getFirstGearSpeed();
	void setSecondGearSpeed(byte second_gear_speed);
	byte getSecondGearSpeed();
	void setThirdGearSpeed(byte third_gear_speed);
	byte getThirdGearSpeed();
	void setDefaultSpeed(byte default_speed);
	byte getDefaultSpeed();
	String toString();
};

#endif /* MOTOR_H */