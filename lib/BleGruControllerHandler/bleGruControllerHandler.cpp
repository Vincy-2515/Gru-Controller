#include <bleGruControllerHandler.h>

BLEService __serviceUart(UUID_SERVICE_UART);

BLEStringCharacteristic __characteristicRx(UUID_CHARACTERISTIC_RX,
    BLEWrite, RX_VALUE_SIZE);
BLEStringCharacteristic __characteristicTx(UUID_CHARACTERISTIC_TX,
    BLENotify, TX_VALUE_SIZE);

void __handleDeviceConnection(BLEDevice central);
void __handleDeviceDisconnection(BLEDevice central);
void __handleCharacteristicRxWritten(BLEDevice device, BLECharacteristic characteristic);

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
	BLE.setAdvertisedService(__serviceUart);

	if (!BLE.advertise()) {
		printErrorMessage("Advertising failed starting, press the reset button to recover");
		while (true)
			blinkLedBuiltin(1);
	}
	printInfoMessage("Advertising started successfully");

	printInfoMessage("BLE setup completed");
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

	bool is_command_recognized = false;
	char msg_buffer[TX_VALUE_SIZE];

	for (Button& b : buttons) {
		if (strcmp(command, b.getButtonPressedKeyCode()) == 0) {
			snprintf(msg_buffer,
			    TX_VALUE_SIZE,
			    "Command recognized: Pressed \"%s\"",
			    b.getButtonName());

			b.callHandler(BTN_PRESSED);

			printInfoMessage(msg_buffer);
			__characteristicTx.writeValue(msg_buffer);

			is_command_recognized = true;
			break;
		} else if (strcmp(command, b.getButtonReleasedKeyCode()) == 0) {
			snprintf(msg_buffer,
			    TX_VALUE_SIZE,
			    "Command recognized: Released \"%s\"",
			    b.getButtonName());

			b.callHandler(BTN_RELEASED);

			printInfoMessage(msg_buffer);
			__characteristicTx.writeValue(msg_buffer);

			is_command_recognized = true;
			break;
		} else {
			continue;
		}
	}

	if (!is_command_recognized) {
		snprintf(msg_buffer,
		    TX_VALUE_SIZE,
		    "Command unrecognized: %s",
		    command);

		printErrorMessage(msg_buffer);
		__characteristicTx.writeValue(msg_buffer);
	}
}
