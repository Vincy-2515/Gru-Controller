#include <Motors.h>
#include <bleGruControllerHandler.h>

BLEService __serviceUart(UUID_SERVICE_UART);

BLEStringCharacteristic __characteristicRx(UUID_CHARACTERISTIC_RX,
    BLEWrite, RX_VALUE_SIZE);
BLEStringCharacteristic __characteristicTx(UUID_CHARACTERISTIC_TX,
    BLENotify, TX_VALUE_SIZE);

void __handleDeviceConnection(BLEDevice central);
void __handleDeviceDisconnection(BLEDevice central);
void __handleCharacteristicRxWritten(BLEDevice device, BLECharacteristic characteristic);
bool __checkForButtonPress(const char* command, char* msg_buffer);
bool __checkForCommand(const char* command, char* msg_buffer);

void bleGruControllerSetup() {
	printInfoMessage("Starting BLE setup procedure...");

	if (!BLE.begin()) {
		printErrorMessage("Bluetooth Low Energy module failed starting, press the reset button to recover");
		while (true)
			blinkLedBuiltin(1);
	}

	printInfoMessage("Bluetooth Low Energy module started successfully");
	digitalWrite(LED_BUILTIN, HIGH);

	BLE.setDeviceName(DEVICE_NAME);
	BLE.setLocalName(LOCAL_NAME);

	BLE.setEventHandler(BLEConnected, __handleDeviceConnection);
	BLE.setEventHandler(BLEDisconnected, __handleDeviceDisconnection);

	__serviceUart.addCharacteristic(__characteristicRx);
	__characteristicRx.writeValue("");
	__characteristicRx.setEventHandler(BLEWritten, __handleCharacteristicRxWritten);

	__serviceUart.addCharacteristic(__characteristicTx);
	__characteristicTx.writeValue("");

	BLE.addService(__serviceUart);

	if (!BLE.setAdvertisedService(__serviceUart)) {
		while (true) {
			printErrorMessage("Advertising failed starting, press the reset button to recover");
			blinkLedBuiltin(1);
		}
	}

	if (!BLE.advertise()) {
		printErrorMessage("Advertising failed starting, press the reset button to recover");
		while (true)
			blinkLedBuiltin(1);
	}
	printInfoMessage("Advertising started successfully");

	printInfoMessage("BLE setup procedure ended");
}

void bleGruControllerLoop() {
	BLE.poll();
}

void __handleDeviceConnection(BLEDevice central) {
	printInfoMessage("[%s] Central connected",
	    central.address().c_str());

	blinkLedBuiltin(3);
}

void __handleDeviceDisconnection(BLEDevice central) {
	printInfoMessage("[%s] Central disconnected",
	    central.address().c_str());

	blinkLedBuiltin(2);
}

void __handleCharacteristicRxWritten(BLEDevice device, BLECharacteristic characteristic) {
	String command_string = __characteristicRx.value();
	const char* command = command_string.c_str();

	printInfoMessage("Received command: \"%s\"", command);

	bool is_command_recognized = false;
	char msg_buffer[TX_VALUE_SIZE];

	is_command_recognized = __checkForButtonPress(command, msg_buffer);
	if (!is_command_recognized) {
		is_command_recognized = __checkForCommand(command, msg_buffer);
	}

	if (!is_command_recognized) {
		printErrorMessage("Command unrecognized: %s", command);
		__characteristicTx.writeValue("Command unrecognized, type \"help\" for help\n"+ String("\n"));
	}
}

bool __checkForButtonPress(const char* command, char* msg_buffer) {
	for (Button& b : buttons) {
		if (strcmp(command, b.getButtonPressedKeyCode()) == 0) {
			snprintf(msg_buffer,
			    TX_VALUE_SIZE,
			    "Command recognized: Pressed \"%s\"",
			    b.getButtonName());

			b.callHandler(BUTTON_PRESSED);

			printInfoMessage(msg_buffer);
			__characteristicTx.writeValue(msg_buffer + String("\n"));

			return true;
		} else if (strcmp(command, b.getButtonReleasedKeyCode()) == 0) {
			snprintf(msg_buffer,
			    TX_VALUE_SIZE,
			    "Command recognized: Released \"%s\"",
			    b.getButtonName());

			b.callHandler(BUTTON_RELEASED);

			printInfoMessage(msg_buffer);
			__characteristicTx.writeValue(msg_buffer+ String("\n"));

			return true;
		} else {
			continue;
		}
	}

	return false;
}

bool __checkForCommand(const char* command, char* msg_buffer) {
	if (strstr(command, "set_motors_speed") != NULL) {
		byte motor_arm_first_gear_speed;
		byte motor_arm_second_gear_speed;
		byte motor_arm_third_gear_speed;
		byte motor_arm_default_speed;

		byte motor_trolley_first_gear_speed;
		byte motor_trolley_second_gear_speed;
		byte motor_trolley_third_gear_speed;
		byte motor_trolley_default_speed;

		byte motor_coil_first_gear_speed;
		byte motor_coil_second_gear_speed;
		byte motor_coil_third_gear_speed;
		byte motor_coil_default_speed;

		if (sscanf(
		        command,
		        "set_motors_speed %d,%d,%d,%d; %d,%d,%d,%d; %d,%d,%d,%d;",
		        &motor_arm_first_gear_speed, &motor_arm_second_gear_speed, &motor_arm_third_gear_speed, &motor_arm_default_speed,
		        &motor_trolley_first_gear_speed, &motor_trolley_second_gear_speed, &motor_trolley_third_gear_speed, &motor_trolley_default_speed,
		        &motor_coil_first_gear_speed, &motor_coil_second_gear_speed, &motor_coil_third_gear_speed, &motor_coil_default_speed)
		    != EOF) {

			if ((motor_arm_first_gear_speed < 0 || motor_arm_first_gear_speed > 255)
			    || (motor_arm_second_gear_speed < 0 || motor_arm_second_gear_speed > 255)
			    || (motor_arm_third_gear_speed < 0 || motor_arm_third_gear_speed > 255)
			    || (motor_arm_default_speed < 0 || motor_arm_default_speed > 255)

			    || (motor_trolley_first_gear_speed < 0 || motor_trolley_first_gear_speed > 255)
			    || (motor_trolley_second_gear_speed < 0 || motor_trolley_second_gear_speed > 255)
			    || (motor_trolley_third_gear_speed < 0 || motor_trolley_third_gear_speed > 255)
			    || (motor_trolley_default_speed < 0 || motor_trolley_default_speed > 255)

			    || (motor_coil_first_gear_speed < 0 || motor_coil_first_gear_speed > 255)
			    || (motor_coil_second_gear_speed < 0 || motor_coil_second_gear_speed > 255)
			    || (motor_coil_third_gear_speed < 0 || motor_coil_third_gear_speed > 255)
			    || (motor_coil_default_speed < 0 || motor_coil_default_speed > 255)) {

				__characteristicTx.writeValue("Only values between the range 0-255 are accepted, value not updated");
				printErrorMessage("Only values between the range 0-255 are accepted, value not updated");

				return false;
			}

			printInfoMessage("Setting motors speeds...");

			motors[MOTOR_ARM]->setAllSpeeds(
			    motor_arm_first_gear_speed,
			    motor_arm_second_gear_speed,
			    motor_arm_third_gear_speed,
			    motor_arm_default_speed);

			motors[MOTOR_TROLLEY]->setAllSpeeds(
			    motor_trolley_first_gear_speed,
			    motor_trolley_second_gear_speed,
			    motor_trolley_third_gear_speed,
			    motor_trolley_default_speed);

			motors[MOTOR_COIL]->setAllSpeeds(
			    motor_coil_first_gear_speed,
			    motor_coil_second_gear_speed,
			    motor_coil_third_gear_speed,
			    motor_coil_default_speed);

			return true;
		}

		return false;
	} else if (strstr(command, "get_motors_info") != NULL) {
		printInfoMessage("Printing motors informations...");

		__characteristicTx.writeValue(motors[MOTOR_ARM]->toString());
		printInfoMessage(motors[MOTOR_ARM]->toString().c_str());

		__characteristicTx.writeValue(motors[MOTOR_TROLLEY]->toString());
		printInfoMessage(motors[MOTOR_TROLLEY]->toString().c_str());

		__characteristicTx.writeValue(motors[MOTOR_COIL]->toString());
		printInfoMessage(motors[MOTOR_COIL]->toString().c_str());

		return true;
	} else if (strstr(command, "write_motor_preferences_to_eeprom") != NULL) {
		printInfoMessage("Writing values to EEPROM memory...");

		motors[MOTOR_ARM]->transferValuesToEeprom();
		motors[MOTOR_TROLLEY]->transferValuesToEeprom();
		motors[MOTOR_COIL]->transferValuesToEeprom();

		return true;
	} else if (strstr(command, "active_breaking") != NULL) {
		printInfoMessage("Changing active breaking preference...");

		byte motor_arm_active_breaking;
		byte motor_trolley_active_breaking;
		byte motor_coil_active_breaking;

		byte motor_arm_breaking_force;
		byte motor_trolley_breaking_force;
		byte motor_coil_breaking_force;

		if (sscanf(command, "active_breaking %d,%d,%d; %d,%d,%d;",
		        &motor_arm_active_breaking, &motor_trolley_active_breaking, &motor_coil_active_breaking,
		        &motor_arm_breaking_force, &motor_trolley_breaking_force, &motor_coil_breaking_force)
		    != EOF) {

			if ((motor_arm_active_breaking < 0 || motor_arm_active_breaking > 1)
			    || (motor_trolley_active_breaking < 0 || motor_trolley_active_breaking > 1)
			    || (motor_coil_active_breaking < 0 || motor_coil_active_breaking > 1)) {

				__characteristicTx.writeValue("Only values between the range 0-1 are accepted, value not updated");
				printErrorMessage("Only values between the range 0-1 are accepted, value not updated");

				return false;
			}
			if ((motor_arm_breaking_force < 0 || motor_arm_breaking_force > 254)
			    || (motor_trolley_breaking_force < 0 || motor_trolley_breaking_force > 254)
			    || (motor_coil_breaking_force < 0 || motor_coil_breaking_force > 254)) { //254 because 255 outputs 0 for some reason

				__characteristicTx.writeValue("Only values between the range 0-254 are accepted for breaking force, value not updated");
				printErrorMessage("Only values between the range 0-254 are accepted for breaking force, value not updated");

				return false;
			}

			bool motor_arm_active_breaking_value = motor_arm_active_breaking == 1 ? true : false;
			bool motor_trolley_active_breaking_value = motor_trolley_active_breaking == 1 ? true : false;
			bool motor_coil_active_breaking_value = motor_coil_active_breaking == 1 ? true : false;

			motors[MOTOR_ARM]->setActiveBreaking(motor_arm_active_breaking_value);
			motors[MOTOR_TROLLEY]->setActiveBreaking(motor_trolley_active_breaking_value);
			motors[MOTOR_COIL]->setActiveBreaking(motor_coil_active_breaking_value);

			motors[MOTOR_ARM]->setBreakingForce(motor_arm_breaking_force);
			motors[MOTOR_TROLLEY]->setBreakingForce(motor_trolley_breaking_force);
			motors[MOTOR_COIL]->setBreakingForce(motor_coil_breaking_force);

			return true;
		}

		return false;
	} else if (strstr(command, "help") != NULL) {
		printInfoMessage("Printing help informations...");

		__characteristicTx.writeValue("\n-=={ HELP MENU }==-\n\nAvailable commands:");
		__characteristicTx.writeValue("> set_motors_speed a,b,c,d; e,f,g,h; i,k,l,m;");
		__characteristicTx.writeValue("> get_motors_info");
		__characteristicTx.writeValue("> write_motor_preferences_to_eeprom");
		__characteristicTx.writeValue("> active_breaking a,b,c; d,e,f;");
		__characteristicTx.writeValue("> help");
		__characteristicTx.writeValue("> info");

		return true;
	} else if (strstr(command, "info") != NULL) {
		printInfoMessage("Printing infos...");

		// clang-format off
		String string = String("") +
		"\n-=={ INFORMATIONS }==-" +
		"\n" +
		"\n Version: v1.0.0" +
		"\n Developer: Vincenzo Scarso" +
		"\n Github: https://github.com/Vincy-2515";
		// clang-format on

		__characteristicTx.writeValue(string);

		return true;
	}

	return false;
}
