#include <Motor.h>

Motor::Motor(String motor_name,
    int direction_controlling_pin1,
    int direction_controlling_pin2,
    int speed_controlling_pin,
    int first_gear_speed_eeprom_address,
    int second_gear_speed_eeprom_address,
    int third_gear_speed_eeprom_address,
    int default_speed_eeprom_address) {
	this->__motor_name = motor_name;
	this->__direction_controlling_pin_1 = direction_controlling_pin1;
	this->__direction_controlling_pin_2 = direction_controlling_pin2;
	this->__speed_controlling_pin = speed_controlling_pin;
	this->__eeprom_address_first_gear_speed = first_gear_speed_eeprom_address;
	this->__eeprom_address_second_gear_speed = second_gear_speed_eeprom_address;
	this->__eeprom_address_third_gear_speed = third_gear_speed_eeprom_address;
	this->__eeprom_address_default_speed = default_speed_eeprom_address;
}

void Motor::updateValuesFromEeprom() {
	this->__first_gear_speed = EEPROM.read(this->__eeprom_address_first_gear_speed);
	this->__second_gear_speed = EEPROM.read(this->__eeprom_address_second_gear_speed);
	this->__third_gear_speed = EEPROM.read(this->__eeprom_address_third_gear_speed);
	this->__default_speed = EEPROM.read(this->__eeprom_address_default_speed);
}

void Motor::transferValuesToEeprom() {
	updateValueToEeprom(this->__eeprom_address_first_gear_speed, this->__first_gear_speed);
	updateValueToEeprom(this->__eeprom_address_second_gear_speed, this->__second_gear_speed);
	updateValueToEeprom(this->__eeprom_address_third_gear_speed, this->__third_gear_speed);
	updateValueToEeprom(this->__eeprom_address_default_speed, this->__default_speed);
}

void Motor::setFirstGearSpeed(byte first_gear_speed) {
	this->__first_gear_speed = first_gear_speed;
}

byte Motor::getFirstGearSpeed() {
	return this->__first_gear_speed;
}

void Motor::setSecondGearSpeed(byte second_gear_speed) {
	this->__second_gear_speed = second_gear_speed;
}

byte Motor::getSecondGearSpeed() {
	return this->__second_gear_speed;
}

void Motor::setThirdGearSpeed(byte third_gear_speed) {
	this->__third_gear_speed = third_gear_speed;
}

byte Motor::getThirdGearSpeed() {
	return this->__third_gear_speed;
}

void Motor::setDefaultSpeed(byte default_speed) {
	this->__default_speed = default_speed;
}

byte Motor::getDefaultSpeed() {
	return this->__default_speed;
}
