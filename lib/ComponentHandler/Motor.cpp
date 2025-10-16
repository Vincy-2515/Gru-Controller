#include <Motor.h>

Motor::Motor(
    String motor_name,
    int direction_controlling_pin1,
    int direction_controlling_pin2,
    int speed_controlling_pin,
    String eeprom_namespace_motor,
    String eeprom_key_first_gear_speed,
    String eeprom_key_second_gear_speed,
    String eeprom_key_third_gear_speed,
    String eeprom_key_default_speed) {

	this->__motor_name = motor_name;

	this->__direction_controlling_pin_1 = direction_controlling_pin1;
	this->__direction_controlling_pin_2 = direction_controlling_pin2;
	this->__speed_controlling_pin = speed_controlling_pin;

	this->__EEPROM_NAMESPACE_MOTOR = eeprom_namespace_motor;
	this->__EEPROM_KEY_FIRST_GEAR_SPEED = eeprom_key_first_gear_speed;
	this->__EEPROM_KEY_SECOND_GEAR_SPEED = eeprom_key_second_gear_speed;
	this->__EEPROM_KEY_THIRD_GEAR_SPEED = eeprom_key_third_gear_speed;
	this->__EEPROM_KEY_DEFAULT_SPEED = eeprom_key_default_speed;
}

void Motor::updateValuesFromEeprom() {
	this->setFirstGearSpeed(readValueFromEeprom(this->motor_speeds, this->getEepromNamespaceMotor(), this->getEepromKeyFirstGearSpeed()));
	this->setSecondGearSpeed(readValueFromEeprom(this->motor_speeds, this->getEepromNamespaceMotor(), this->getEepromKeySecondGearSpeed()));
	this->setThirdGearSpeed(readValueFromEeprom(this->motor_speeds, this->getEepromNamespaceMotor(), this->getEepromKeyThirdGearSpeed()));
	this->setDefaultSpeed(readValueFromEeprom(this->motor_speeds, this->getEepromNamespaceMotor(), this->getEepromKeyDefaultSpeed()));
}

void Motor::transferValuesToEeprom() {
	writeValueToEeprom(this->motor_speeds, this->getEepromNamespaceMotor(), this->getEepromKeyFirstGearSpeed(), this->getFirstGearSpeed());
	writeValueToEeprom(this->motor_speeds, this->getEepromNamespaceMotor(), this->getEepromKeySecondGearSpeed(), this->getSecondGearSpeed());
	writeValueToEeprom(this->motor_speeds, this->getEepromNamespaceMotor(), this->getEepromKeyThirdGearSpeed(), this->getThirdGearSpeed());
	writeValueToEeprom(this->motor_speeds, this->getEepromNamespaceMotor(), this->getEepromKeyDefaultSpeed(), this->getDefaultSpeed());
}

void Motor::setAllSpeeds(byte first_gear_speed, byte second_gear_speed, byte third_gear_speed, byte default_speed) {
	this->setFirstGearSpeed(first_gear_speed);
	this->setSecondGearSpeed(second_gear_speed);
	this->setThirdGearSpeed(third_gear_speed);
	this->setDefaultSpeed(default_speed);
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

// clang-format off
String Motor::toString() {
	return (
		this->__motor_name + ": {" + 
		this->__direction_controlling_pin_1 + ", " + 
		this->__direction_controlling_pin_2 + ", " + 
		this->__speed_controlling_pin + ", " + 
		this->__first_gear_speed + ", " + 
		this->__second_gear_speed + ", " + 
		this->__third_gear_speed + ", " + 
		this->__default_speed + ", " +
		this->__EEPROM_NAMESPACE_MOTOR + ", " +
		this->__EEPROM_KEY_FIRST_GEAR_SPEED + ", " + 
		this->__EEPROM_KEY_SECOND_GEAR_SPEED + ", " + 
		this->__EEPROM_KEY_THIRD_GEAR_SPEED + ", " + 
		this->__EEPROM_KEY_DEFAULT_SPEED +
		"}");
	}
// clang-format on
