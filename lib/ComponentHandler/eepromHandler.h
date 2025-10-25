#ifndef EEPROM_ADDRESSES_H
#define EEPROM_ADDRESSES_H

#include <Arduino.h>

/*********************************************************
    EVERY NAMESPACE AND KEY MUST BE UNDER 15 CHARACTERS
 *********************************************************/

#define EEPROM_MODE_READ_WRITE false
#define EEPROM_MODE_READ true

#define EEPROM_NAMESPACE_MOTOR_ARM "E_N_M_A"
#define EEPROM_KEY_MOTOR_ARM_FIRST_GEAR_SPEED "E_K_M_A_F_G_S"
#define EEPROM_KEY_MOTOR_ARM_SECOND_GEAR_SPEED "E_K_M_A_S_G_S"
#define EEPROM_KEY_MOTOR_ARM_THIRD_GEAR_SPEED "E_K_M_A_T_G_S"
#define EEPROM_KEY_MOTOR_ARM_DEFAULT_SPEED "E_K_M_A_D_S"
#define EEPROM_KEY_MOTOR_ARM_ACTIVE_BREAKING "E_K_M_A_A_B"
#define EEPROM_KEY_MOTOR_ARM_BREAKING_FORCE "E_K_M_A_B_F"

#define EEPROM_NAMESPACE_MOTOR_TROLLEY "E_N_M_T"
#define EEPROM_KEY_MOTOR_TROLLEY_FIRST_GEAR_SPEED "E_K_M_T_F_G_S"
#define EEPROM_KEY_MOTOR_TROLLEY_SECOND_GEAR_SPEED "E_K_M_T_S_G_S"
#define EEPROM_KEY_MOTOR_TROLLEY_THIRD_GEAR_SPEED "E_K_M_T_T_G_S"
#define EEPROM_KEY_MOTOR_TROLLEY_DEFAULT_SPEED "E_K_M_T_D_S"
#define EEPROM_KEY_MOTOR_TROLLEY_ACTIVE_BREAKING "E_K_M_T_A_B"
#define EEPROM_KEY_MOTOR_TROLLEY_BREAKING_FORCE "E_K_M_T_B_F"

#define EEPROM_NAMESPACE_MOTOR_COIL "E_N_M_C"
#define EEPROM_KEY_MOTOR_COIL_FIRST_GEAR_SPEED "E_K_M_C_F_G_S"
#define EEPROM_KEY_MOTOR_COIL_SECOND_GEAR_SPEED "E_K_M_C_S_G_S"
#define EEPROM_KEY_MOTOR_COIL_THIRD_GEAR_SPEED "E_K_M_C_T_G_S"
#define EEPROM_KEY_MOTOR_COIL_DEFAULT_SPEED "E_K_M_C_D_S"
#define EEPROM_KEY_MOTOR_COIL_ACTIVE_BREAKING "E_K_M_C_A_B"
#define EEPROM_KEY_MOTOR_COIL_BREAKING_FORCE "E_K_M_C_B_F"

class Preferences;

void eepromSetup();
void writeBoolValueToEeprom(Preferences& preferences, const char* namespace_name, const char* key_name, bool value);
bool readBoolValueFromEeprom(Preferences& preferences, const char* namespace_name, const char* key_name);
void writeByteValueToEeprom(Preferences& preferences, const char* namespace_name, const char* key_name, byte value);
byte readByteValueFromEeprom(Preferences& preferences, const char* namespace_name, const char* key_name);

#endif /* EEPROM_ADDRESSES_H */