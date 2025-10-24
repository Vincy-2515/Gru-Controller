#ifndef COMPONENT_TYPES_H
#define COMPONENT_TYPES_H

#include <Arduino.h>

typedef enum MotorId {
	MOTOR_ARM,
	MOTOR_TROLLEY,
	MOTOR_COIL
} MotorId;

typedef enum Action {
	ACTION_NONE,
	ACTION_ROTATE_ARM,
	ACTION_MOVE_TROLLEY,
	ACTION_ROTATE_COIL
} Action;

typedef enum Rotation {
	ROTATION_DEFAULT,
	ROTATION_INVERSE
} Rotation;

typedef enum Gear {
	GEAR_DEFAULT,
	GEAR_FIRST,
	GEAR_SECOND,
	GEAR_THIRD
} Gear;

typedef enum ButtonStatus {
	BUTTON_PRESSED,
	BUTTON_RELEASED
} ButtonStatus;

#endif /* COMPONENT_TYPES_H */
