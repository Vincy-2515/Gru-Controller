#include <Motor.h>
#include <eepromHandler.h>

Motor::Motor(
    String motor_name,
    int direction_controlling_pin1,
    int direction_controlling_pin2,
    int speed_controlling_pin,
    String eeprom_namespace_motor,
    String eeprom_key_first_gear_speed,
    String eeprom_key_second_gear_speed,
    String eeprom_key_third_gear_speed,
    String eeprom_key_default_speed,
    String eeprom_key_active_breaking) {

	this->__motor_name = motor_name;

	this->__direction_controlling_pin_1 = direction_controlling_pin1;
	this->__direction_controlling_pin_2 = direction_controlling_pin2;
	this->__speed_controlling_pin = speed_controlling_pin;

	this->__EEPROM_NAMESPACE_MOTOR = eeprom_namespace_motor;
	this->__EEPROM_KEY_FIRST_GEAR_SPEED = eeprom_key_first_gear_speed;
	this->__EEPROM_KEY_SECOND_GEAR_SPEED = eeprom_key_second_gear_speed;
	this->__EEPROM_KEY_THIRD_GEAR_SPEED = eeprom_key_third_gear_speed;
	this->__EEPROM_KEY_DEFAULT_SPEED = eeprom_key_default_speed;
	this->__EEPROM_KEY_ACTIVE_BREAKING = eeprom_key_active_breaking;

	this->__initializeMotorSpeedsPreferences();
}

void Motor::updateValuesFromEeprom() {
	this->setFirstGearSpeed(readByteValueFromEeprom(this->motor_speeds_preferences, this->getEepromNamespaceMotor(), this->getEepromKeyFirstGearSpeed()));
	this->setSecondGearSpeed(readByteValueFromEeprom(this->motor_speeds_preferences, this->getEepromNamespaceMotor(), this->getEepromKeySecondGearSpeed()));
	this->setThirdGearSpeed(readByteValueFromEeprom(this->motor_speeds_preferences, this->getEepromNamespaceMotor(), this->getEepromKeyThirdGearSpeed()));
	this->setDefaultSpeed(readByteValueFromEeprom(this->motor_speeds_preferences, this->getEepromNamespaceMotor(), this->getEepromKeyDefaultSpeed()));
	this->setActiveBreaking(readBoolValueFromEeprom(this->motor_speeds_preferences, this->getEepromNamespaceMotor(), this->getEepromKeyActiveBreaking()));
}

void Motor::transferValuesToEeprom() {
	writeByteValueToEeprom(this->motor_speeds_preferences, this->getEepromNamespaceMotor(), this->getEepromKeyFirstGearSpeed(), this->getFirstGearSpeed());
	writeByteValueToEeprom(this->motor_speeds_preferences, this->getEepromNamespaceMotor(), this->getEepromKeySecondGearSpeed(), this->getSecondGearSpeed());
	writeByteValueToEeprom(this->motor_speeds_preferences, this->getEepromNamespaceMotor(), this->getEepromKeyThirdGearSpeed(), this->getThirdGearSpeed());
	writeByteValueToEeprom(this->motor_speeds_preferences, this->getEepromNamespaceMotor(), this->getEepromKeyDefaultSpeed(), this->getDefaultSpeed());
	writeByteValueToEeprom(this->motor_speeds_preferences, this->getEepromNamespaceMotor(), this->getEepromKeyActiveBreaking(), this->getActiveBreaking());
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
}

const char* Motor::getMotorName() {
	return this->__motor_name.c_str();
}

/*===========================
    GETTERS OF PINS NUMBERS
  ===========================*/

int Motor::getDirectionControllingPin1() {
	return this->__direction_controlling_pin_1;
}

int Motor::getDirectionControllingPin2() {
	return this->__direction_controlling_pin_2;
}

int Motor::getSpeedControllingPin() {
	return this->__speed_controlling_pin;
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

// clang-format off
String Motor::toString() {
	return (
		this->__motor_name + ": {" + 
		this->__direction_controlling_pin_1 + ", " + 
		this->__direction_controlling_pin_2 + ", " + 
		this->__speed_controlling_pin + ", " + 
		this->__EEPROM_NAMESPACE_MOTOR + ": [" +
		this->__EEPROM_KEY_FIRST_GEAR_SPEED + ": " +  this->__first_gear_speed + ", " +
		this->__EEPROM_KEY_SECOND_GEAR_SPEED + ": " +  this->__second_gear_speed + ", " +
		this->__EEPROM_KEY_THIRD_GEAR_SPEED + ": " +  this->__third_gear_speed + ", " +
		this->__EEPROM_KEY_DEFAULT_SPEED  + ": " +  this->__default_speed + ", " +
		this->__EEPROM_KEY_ACTIVE_BREAKING + ": " + this->__active_breaking + "]" +
		"}");
	}
// clang-format on

void Motor::__initializeMotorSpeedsPreferences() {
	this->motor_speeds_preferences.begin(this->getEepromNamespaceMotor(), EEPROM_MODE_READ);

	bool is_preferences_namespace_initialized = this->motor_speeds_preferences.isKey(EEPROM_KEY_INITIALIZATION);

	if (!is_preferences_namespace_initialized) {
		printWarningMessage("Namespace \"%s\" not initialized, initializing...", this->getEepromNamespaceMotor());

		this->motor_speeds_preferences.end();
		this->motor_speeds_preferences.begin(this->getEepromNamespaceMotor(), EEPROM_MODE_READ_WRITE);

		this->motor_speeds_preferences.putUChar(this->getEepromKeyFirstGearSpeed(), 0);
		this->motor_speeds_preferences.putUChar(this->getEepromKeySecondGearSpeed(), 0);
		this->motor_speeds_preferences.putUChar(this->getEepromKeyThirdGearSpeed(), 0);
		this->motor_speeds_preferences.putUChar(this->getEepromKeyDefaultSpeed(), 0);
		this->motor_speeds_preferences.putBool(this->getEepromKeyActiveBreaking(), false);

		this->motor_speeds_preferences.putBool(EEPROM_KEY_INITIALIZATION, true);

		this->motor_speeds_preferences.end();
	}

	this->motor_speeds_preferences.end();
}
