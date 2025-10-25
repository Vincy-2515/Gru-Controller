#include <Motor.h>

#include <eepromHandler.h>
#include <logHandler.h>

Motor::Motor(
    String motor_name,
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
    String eeprom_key_breaking_force) {

	this->__motor_name = motor_name;

	this->__direction_controlling_pin_1 = direction_controlling_pin1;
	this->__direction_controlling_pin_2 = direction_controlling_pin2;
	this->__speed_controlling_pin = speed_controlling_pin;

	this->__speed_pwm_channel_mumber = speed_pwm_channel_number;
	this->__speed_pwm_channel_frequency = speed_pwm_channel_frequency;
	this->__speed_pwm_channel_resolution = speed_pwm_channel_resolution;

	this->__first_gear_speed = 0;
	this->__second_gear_speed = 0;
	this->__third_gear_speed = 0;
	this->__default_speed = 0;
	this->__active_breaking = false;
	this->__breaking_force = 0;

	this->__EEPROM_NAMESPACE_MOTOR = eeprom_namespace_motor;
	this->__EEPROM_KEY_FIRST_GEAR_SPEED = eeprom_key_first_gear_speed;
	this->__EEPROM_KEY_SECOND_GEAR_SPEED = eeprom_key_second_gear_speed;
	this->__EEPROM_KEY_THIRD_GEAR_SPEED = eeprom_key_third_gear_speed;
	this->__EEPROM_KEY_DEFAULT_SPEED = eeprom_key_default_speed;
	this->__EEPROM_KEY_ACTIVE_BREAKING = eeprom_key_active_breaking;
	this->__EEPROM_KEY_BREAKING_FORCE = eeprom_key_breaking_force;
}

void Motor::initializeMotorSpeedsPreferences() {
	// NOTE: "Preferences.begin()" MUST NOT be executed inside Objects' constructors
	if (!this->motor_preferences.begin(this->getEepromNamespaceMotor(), EEPROM_MODE_READ)) {
		printErrorMessage("\"motor_preferences\" has not been initialized");
		return;
	}

	if (!this->__areAllKeyInitialized()) {
		printWarningMessage("All or some keys of the namespace \"%s\" are not initialized, initializing...", this->getEepromNamespaceMotor());

		this->motor_preferences.end();
		if (!this->motor_preferences.begin(this->getEepromNamespaceMotor(), EEPROM_MODE_READ_WRITE)) {
			printErrorMessage("\"motor_preferences\" has not been initialized");
			return;
		}

		this->motor_preferences.putUChar(this->getEepromKeyFirstGearSpeed(), 0);
		this->motor_preferences.putUChar(this->getEepromKeySecondGearSpeed(), 0);
		this->motor_preferences.putUChar(this->getEepromKeyThirdGearSpeed(), 0);
		this->motor_preferences.putUChar(this->getEepromKeyDefaultSpeed(), 0);
		this->motor_preferences.putBool(this->getEepromKeyActiveBreaking(), false);
		this->motor_preferences.putUChar(this->getEepromKeyBreakingForce(), 0);

		this->motor_preferences.end();
	}

	this->motor_preferences.end();
}

void Motor::updateValuesFromEeprom() {
	this->setFirstGearSpeed(readByteValueFromEeprom(this->motor_preferences, this->getEepromNamespaceMotor(), this->getEepromKeyFirstGearSpeed()));
	this->setSecondGearSpeed(readByteValueFromEeprom(this->motor_preferences, this->getEepromNamespaceMotor(), this->getEepromKeySecondGearSpeed()));
	this->setThirdGearSpeed(readByteValueFromEeprom(this->motor_preferences, this->getEepromNamespaceMotor(), this->getEepromKeyThirdGearSpeed()));
	this->setDefaultSpeed(readByteValueFromEeprom(this->motor_preferences, this->getEepromNamespaceMotor(), this->getEepromKeyDefaultSpeed()));
	this->setActiveBreaking(readBoolValueFromEeprom(this->motor_preferences, this->getEepromNamespaceMotor(), this->getEepromKeyActiveBreaking()));
	this->setBreakingForce(readByteValueFromEeprom(this->motor_preferences, this->getEepromNamespaceMotor(), this->getEepromKeyBreakingForce()));
}

void Motor::transferValuesToEeprom() {
	writeByteValueToEeprom(this->motor_preferences, this->getEepromNamespaceMotor(), this->getEepromKeyFirstGearSpeed(), this->getFirstGearSpeed());
	writeByteValueToEeprom(this->motor_preferences, this->getEepromNamespaceMotor(), this->getEepromKeySecondGearSpeed(), this->getSecondGearSpeed());
	writeByteValueToEeprom(this->motor_preferences, this->getEepromNamespaceMotor(), this->getEepromKeyThirdGearSpeed(), this->getThirdGearSpeed());
	writeByteValueToEeprom(this->motor_preferences, this->getEepromNamespaceMotor(), this->getEepromKeyDefaultSpeed(), this->getDefaultSpeed());
	writeBoolValueToEeprom(this->motor_preferences, this->getEepromNamespaceMotor(), this->getEepromKeyActiveBreaking(), this->getActiveBreaking());
	writeByteValueToEeprom(this->motor_preferences, this->getEepromNamespaceMotor(), this->getEepromKeyBreakingForce(), this->getBreakingForce());
}

void Motor::setAllSpeeds(byte first_gear_speed, byte second_gear_speed, byte third_gear_speed, byte default_speed) {
	this->setFirstGearSpeed(first_gear_speed);
	this->setSecondGearSpeed(second_gear_speed);
	this->setThirdGearSpeed(third_gear_speed);
	this->setDefaultSpeed(default_speed);
}

byte Motor::getSpeed(Gear gear) {
	switch (gear) {
	case GEAR_DEFAULT:
		return this->getDefaultSpeed();
	case GEAR_FIRST:
		return this->getFirstGearSpeed();
	case GEAR_SECOND:
		return this->getSecondGearSpeed();
	case GEAR_THIRD:
		return this->getThirdGearSpeed();
	default:
		break;
	}

	return this->getDefaultSpeed();
}

const char* Motor::getMotorName() {
	return this->__motor_name.c_str();
}

/*============================
    GETTERS OF PINS' NUMBERS
  ============================*/

int Motor::getDirectionControllingPin1() {
	return this->__direction_controlling_pin_1;
}

int Motor::getDirectionControllingPin2() {
	return this->__direction_controlling_pin_2;
}

int Motor::getSpeedControllingPin() {
	return this->__speed_controlling_pin;
}

/*===========================
    GETTERS OF PWM SETTINGS
  ===========================*/

int Motor::getSpeedPwmChannelNumber() {
	return this->__speed_pwm_channel_mumber;
}

int Motor::getSpeedPwmChannelFrequency() {
	return this->__speed_pwm_channel_frequency;
}

int Motor::getSpeedPwmChannelResolution() {
	return this->__speed_pwm_channel_resolution;
}

/*===================================================
    GETTER AND SETTER OF ACTIVE-BREAKING PREFERENCE
  ===================================================*/

bool Motor::getActiveBreaking() {
	return this->__active_breaking;
}

void Motor::setActiveBreaking(bool active_breaking) {
	this->__active_breaking = active_breaking;
}

byte Motor::getBreakingForce() {
	return this->__breaking_force;
}

void Motor::setBreakingForce(byte breaking_force) {
	this->__breaking_force = breaking_force;
}

/*===========================
    GETTERS OF GEARS SPEEDS
  ===========================*/

byte Motor::getFirstGearSpeed() {
	return this->__first_gear_speed;
}

byte Motor::getSecondGearSpeed() {
	return this->__second_gear_speed;
}

byte Motor::getThirdGearSpeed() {
	return this->__third_gear_speed;
}

byte Motor::getDefaultSpeed() {
	return this->__default_speed;
}

/*===========================
    SETTERS OF GEARS SPEEDS
  ===========================*/

void Motor::setFirstGearSpeed(byte first_gear_speed) {
	this->__first_gear_speed = first_gear_speed;
}

void Motor::setSecondGearSpeed(byte second_gear_speed) {
	this->__second_gear_speed = second_gear_speed;
}

void Motor::setThirdGearSpeed(byte third_gear_speed) {
	this->__third_gear_speed = third_gear_speed;
}

void Motor::setDefaultSpeed(byte default_speed) {
	this->__default_speed = default_speed;
}

/*========================================
    GETTERS OF EEPROM NAMESPACE AND KEYS
  ========================================*/

const char* Motor::getEepromNamespaceMotor() {
	return this->__EEPROM_NAMESPACE_MOTOR.c_str();
}

const char* Motor::getEepromKeyFirstGearSpeed() {
	return this->__EEPROM_KEY_FIRST_GEAR_SPEED.c_str();
}

const char* Motor::getEepromKeySecondGearSpeed() {
	return this->__EEPROM_KEY_SECOND_GEAR_SPEED.c_str();
}

const char* Motor::getEepromKeyThirdGearSpeed() {
	return this->__EEPROM_KEY_THIRD_GEAR_SPEED.c_str();
}

const char* Motor::getEepromKeyDefaultSpeed() {
	return this->__EEPROM_KEY_DEFAULT_SPEED.c_str();
}

const char* Motor::getEepromKeyActiveBreaking() {
	return this->__EEPROM_KEY_ACTIVE_BREAKING.c_str();
}

const char* Motor::getEepromKeyBreakingForce() {
	return this->__EEPROM_KEY_BREAKING_FORCE.c_str();
}

// clang-format off
String Motor::toString() {
	return (
		this->__motor_name + ": {" + 
		"DIR_PIN_1: " + this->__direction_controlling_pin_1 + ", " + 
		"DIR_PIN_2: " + this->__direction_controlling_pin_2 + ", " + 
		"SPEED_PIN: " + this->__speed_controlling_pin + ", " + 
		this->__EEPROM_NAMESPACE_MOTOR + ": [" +
		this->__EEPROM_KEY_FIRST_GEAR_SPEED + ": " +  this->__first_gear_speed + ", " +
		this->__EEPROM_KEY_SECOND_GEAR_SPEED + ": " +  this->__second_gear_speed + ", " +
		this->__EEPROM_KEY_THIRD_GEAR_SPEED + ": " +  this->__third_gear_speed + ", " +
		this->__EEPROM_KEY_DEFAULT_SPEED  + ": " +  this->__default_speed + ", " +
		this->__EEPROM_KEY_ACTIVE_BREAKING + ": " + this->__active_breaking + ", " +
		this->__EEPROM_KEY_BREAKING_FORCE + ": " + this->__breaking_force + "]" +
		"}");
	}
// clang-format on

bool Motor::__areAllKeyInitialized() {
	return (
	    this->motor_preferences.isKey(getEepromKeyFirstGearSpeed())
	    && this->motor_preferences.isKey(getEepromKeySecondGearSpeed())
	    && this->motor_preferences.isKey(getEepromKeyThirdGearSpeed())
	    && this->motor_preferences.isKey(getEepromKeyDefaultSpeed())
	    && this->motor_preferences.isKey(getEepromKeyActiveBreaking())
		&& this->motor_preferences.isKey(getEepromKeyBreakingForce()));
}