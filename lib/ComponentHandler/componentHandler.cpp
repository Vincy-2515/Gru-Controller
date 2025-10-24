#include "componentHandler.h"
#include <Motors.h>

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
	Motor* m = motors[motor_id];

	if (action == ACTION_NONE) {
		if (m->getActiveBreaking() == true) {
			digitalWrite(m->getDirectionControllingPin1(), HIGH);
			digitalWrite(m->getDirectionControllingPin2(), HIGH);
			digitalWrite(m->getSpeedControllingPin(), HIGH);
		} else {
			digitalWrite(m->getDirectionControllingPin1(), LOW);
			digitalWrite(m->getDirectionControllingPin2(), LOW);
			digitalWrite(m->getSpeedControllingPin(), LOW);
		}
	} else {
		if (rotation == ROTATION_DEFAULT) {
			digitalWrite(m->getDirectionControllingPin1(), HIGH);
			digitalWrite(m->getDirectionControllingPin2(), LOW);
			digitalWrite(m->getSpeedControllingPin(), m->getSpeed(gear));
		} else {
			digitalWrite(m->getDirectionControllingPin1(), LOW);
			digitalWrite(m->getDirectionControllingPin2(), HIGH);
			digitalWrite(m->getSpeedControllingPin(), m->getSpeed(gear));
		}
	}

	printInfoMessage("Setted values {DIR_1: %d, DIR_2: %d, SPEED: %d} to %s pins",
	    digitalRead(motors[motor_id]->getDirectionControllingPin1()),
	    digitalRead(motors[motor_id]->getDirectionControllingPin2()),
	    digitalRead(motors[motor_id]->getSpeedControllingPin()),
	    motors[motor_id]->getMotorName());
}

void __pinsSetup() {
	printInfoMessage("Starting pins setup procedure...");

	pinMode(LED_BUILTIN, OUTPUT);
	digitalWrite(LED_BUILTIN, LOW);

	for (Motor* m : motors) {
		pinMode(m->getDirectionControllingPin1(), OUTPUT);
		pinMode(m->getDirectionControllingPin2(), OUTPUT);
		pinMode(m->getSpeedControllingPin(), OUTPUT);
	}

	printInfoMessage("Pins setup procedure ended");
}

void __updateMotorsValuesFromEeprom() {
	printInfoMessage("Starting motors' values setup procedure...");

	for (Motor* m : motors) {
		m->updateValuesFromEeprom();
	}

	printInfoMessage("Motors' values setup procedure ended");
}
