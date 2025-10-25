#ifndef MOTOR_H
#define MOTOR_H

#include <Arduino.h>
#include <Preferences.h>
#include <types.h>

class Motor {
private:
	String __motor_name;

	int __direction_controlling_pin_1; // IN1 or IN2 or IN3 or IN4 of the L298N
	int __direction_controlling_pin_2; // IN1 or IN2 or IN3 or IN4 of the L298N
	int __speed_controlling_pin; // ENA or ENB of the L298N

	int __speed_pwm_channel_mumber; // PWM channel associated to the speed controlling pin
	int __speed_pwm_channel_frequency; // PWM channel frequency
	int __speed_pwm_channel_resolution; // PWM channel resolution (number of bits)

	byte __first_gear_speed;
	byte __second_gear_speed;
	byte __third_gear_speed;
	byte __default_speed;
	bool __active_breaking;
	byte __breaking_force;

	String __EEPROM_NAMESPACE_MOTOR;
	String __EEPROM_KEY_FIRST_GEAR_SPEED;
	String __EEPROM_KEY_SECOND_GEAR_SPEED;
	String __EEPROM_KEY_THIRD_GEAR_SPEED;
	String __EEPROM_KEY_DEFAULT_SPEED;
	String __EEPROM_KEY_ACTIVE_BREAKING;
	String __EEPROM_KEY_BREAKING_FORCE;

	bool __areAllKeyInitialized();

public:
	Preferences motor_preferences;

	Motor(String motor_name,
	    int direction_controlling_pin1,
	    int direction_controlling_pin2,
	    int speed_controlling_pin,
	    int speed_pwm_channel_number,
	    int speed_pwm_channel_frequency,
	    int speed_pwm_channel_resolution,
	    String eeprom_namespace_motor,
	    String eeprom_key_first_gear_speed,
	    String eeprom_key_second_gear_speed,
	    String eeprom_key_third_gear_speed,
	    String eeprom_key_default_speed,
	    String eeprom_key_active_breaking,
	    String eeprom_key_breaking_force);

	void initializeMotorSpeedsPreferences();

	void updateValuesFromEeprom();
	void transferValuesToEeprom();

	void setAllSpeeds(byte first_gear_speed, byte second_gear_speed, byte third_gear_speed, byte default_speed);

	byte getSpeed(Gear gear);

	const char* getMotorName();

	int getDirectionControllingPin1();
	int getDirectionControllingPin2();
	int getSpeedControllingPin();

	int getSpeedPwmChannelNumber();
	int getSpeedPwmChannelFrequency();
	int getSpeedPwmChannelResolution();

	bool getActiveBreaking();
	void setActiveBreaking(bool active_breaking);

	byte getBreakingForce();
	void setBreakingForce(byte breaking_force);

	byte getFirstGearSpeed();
	byte getSecondGearSpeed();
	byte getThirdGearSpeed();
	byte getDefaultSpeed();

	void setFirstGearSpeed(byte first_gear_speed);
	void setSecondGearSpeed(byte second_gear_speed);
	void setThirdGearSpeed(byte third_gear_speed);
	void setDefaultSpeed(byte default_speed);

	const char* getEepromNamespaceMotor();
	const char* getEepromKeyFirstGearSpeed();
	const char* getEepromKeySecondGearSpeed();
	const char* getEepromKeyThirdGearSpeed();
	const char* getEepromKeyDefaultSpeed();
	const char* getEepromKeyActiveBreaking();
	const char* getEepromKeyBreakingForce();

	String toString();
};

#endif /* MOTOR_H */