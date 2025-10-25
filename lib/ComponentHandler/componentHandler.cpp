#include "componentHandler.h"
#include <Motors.h>

void __sendValues(Motor* motor, uint8_t direction1_value, uint8_t direction2_value, uint8_t speed_value);
void __pinsSetup();
void __updateMotorsValuesFromEeprom();

void componentsSetup() {
	__pinsSetup();
	__updateMotorsValuesFromEeprom();
}

void blinkLedBuiltin(int ripetitions) {
	int i = 0;
	while (i < ripetitions) {
		digitalWrite(LED_BUILTIN, LOW);
		delay(125);
		digitalWrite(LED_BUILTIN, HIGH);
		delay(125);
		i++;
	}
}

void updateMotorState(MotorId motor_id, Action action, Rotation rotation, Gear gear) {
	Motor* motor = motors[motor_id];

	if (action == ACTION_NONE) {
		if (motor->getActiveBreaking() == true) {
			__sendValues(motor, HIGH, HIGH, motor->getBreakingForce());
		} else {
			__sendValues(motor, LOW, LOW, motor->getBreakingForce());
		}
	} else {
		if (rotation == ROTATION_DEFAULT) {
			__sendValues(motor, HIGH, LOW, motor->getSpeed(gear));
		} else {
			__sendValues(motor, LOW, HIGH, motor->getSpeed(gear));
		}
	}
}

void __sendValues(Motor* motor, uint8_t direction1_value, uint8_t direction2_value, uint8_t speed_value) {
	digitalWrite(motor->getDirectionControllingPin1(), direction1_value);
	digitalWrite(motor->getDirectionControllingPin2(), direction2_value);
	analogWrite(motor->getSpeedControllingPin(), speed_value);

	printInfoMessage("Setted values {DIR_1: %d, DIR_2: %d, SPEED: %d} to %s pins",
	    direction1_value,
	    direction2_value,
	    speed_value,
	    motor->getMotorName());
}

void __pinsSetup() {
	printInfoMessage("Starting pins setup procedure...");

	pinMode(LED_BUILTIN, OUTPUT);
	digitalWrite(LED_BUILTIN, LOW);

	for (Motor* motor : motors) {
		pinMode(motor->getDirectionControllingPin1(), OUTPUT);
		pinMode(motor->getDirectionControllingPin2(), OUTPUT);
		pinMode(motor->getSpeedControllingPin(), OUTPUT);

		ledcAttachChannel(
		    motor->getSpeedControllingPin(),
		    motor->getSpeedPwmChannelFrequency(),
		    motor->getSpeedPwmChannelResolution(),
		    motor->getSpeedPwmChannelNumber());
	}

	printInfoMessage("Pins setup procedure ended");
}

void __updateMotorsValuesFromEeprom() {
	printInfoMessage("Starting motors' values setup procedure...");

	for (Motor* motor : motors) {
		motor->updateValuesFromEeprom();
	}

	printInfoMessage("Motors' values setup procedure ended");
}
