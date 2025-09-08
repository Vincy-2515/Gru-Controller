#include <ArduinoBLE.h>
#include <componentHandler.h>
#include <logHandler.h>

#define SERIAL_BAUD 115200

#define DEVICE_NAME "ESP32-DEVKIT-C"
#define LOCAL_NAME "GRU"

#define DELAY_BETWEEN_PRINT_CHARACTERISTICS_STATUS 1000

#define UUID_SERVICE_UART "6E400001-B5A3-F393-E0A9-E50E24DCCA9E"
#define UUID_CHARACTERISTIC_RX "6E400002-B5A3-F393-E0A9-E50E24DCCA9E"
#define UUID_CHARACTERISTIC_TX "6E400003-B5A3-F393-E0A9-E50E24DCCA9E"

#define RX_VALUE_SIZE 128
#define TX_VALUE_SIZE 128

// KEY-CODES:
#define KEY_DOWN_ARROW_UP "!B516"
#define KEY_UP_ARROW_UP "!B507"
#define KEY_DOWN_ARROW_RIGHT "!B813"
#define KEY_UP_ARROW_RIGHT "!B804"
#define KEY_DOWN_ARROW_DOWN "!B615"
#define KEY_UP_ARROW_DOWN "!B606"
#define KEY_DOWN_ARROW_LEFT "!B714"
#define KEY_UP_ARROW_LEFT "!B705"
#define KEY_DOWN_MACRO_NUMBER_1 "!B11:"
#define KEY_UP_MACRO_NUMBER_1 "!B10;"
#define KEY_DOWN_MACRO_NUMBER_2 "!B219"
#define KEY_UP_MACRO_NUMBER_2 "!B20:"
#define KEY_DOWN_MACRO_NUMBER_3 "!B318"
#define KEY_UP_MACRO_NUMBER_3 "!B309"
#define KEY_DOWN_MACRO_NUMBER_4 "!B417"
#define KEY_UP_MACRO_NUMBER_4 "!B408"

BLEService serviceUart(UUID_SERVICE_UART);

BLEStringCharacteristic characteristicRx(UUID_CHARACTERISTIC_RX,
    BLEWrite, RX_VALUE_SIZE);
BLEStringCharacteristic characteristicTx(UUID_CHARACTERISTIC_TX,
    BLENotify, TX_VALUE_SIZE);

void printCharacteristicsStatus();
void handleDeviceConnection(BLEDevice central);
void handleDeviceDisconnection(BLEDevice central);
void handleCharacteristicRxWritten(BLEDevice device, BLECharacteristic characteristic);

unsigned long millis_previous_print_of_characteristics_status = 0;

void setup() {
	Serial.begin(SERIAL_BAUD);
	pinSetup();
	while (!Serial)
		blinkLedBuiltin(1);

	printInfoMessage("Starting setup procedure...");

	if (!BLE.begin()) {
		printErrorMessage("Bluetooth Low Energy module failed starting, press the reset button to recover");
		while (true)
			blinkLedBuiltin(1);
	}

	printInfoMessage("Bluetooth Low Energy module started successfully");
	digitalWrite(LED_BUILTIN, HIGH);

	BLE.setDeviceName(DEVICE_NAME);
	BLE.setLocalName(LOCAL_NAME);

	BLE.setEventHandler(BLEConnected, handleDeviceConnection);
	BLE.setEventHandler(BLEDisconnected, handleDeviceDisconnection);

	serviceUart.addCharacteristic(characteristicRx);
	characteristicRx.writeValue("");
	characteristicRx.setEventHandler(BLEWritten, handleCharacteristicRxWritten);

	serviceUart.addCharacteristic(characteristicTx);
	characteristicTx.writeValue("");

	BLE.addService(serviceUart);
	BLE.setAdvertisedService(serviceUart);

	if (!BLE.advertise()) {
		printErrorMessage("Advertising failed starting, press the reset button to recover");
		while (true)
			blinkLedBuiltin(1);
	}
	printInfoMessage("Advertising started successfully");

	printInfoMessage("Setup completed");
}

void loop() {
	BLE.poll();

	while (millis() > millis_previous_print_of_characteristics_status + DELAY_BETWEEN_PRINT_CHARACTERISTICS_STATUS) {
		printCharacteristicsStatus();
		millis_previous_print_of_characteristics_status = millis();
	}
}

void printCharacteristicsStatus() {
	/* ... */
}

void handleDeviceConnection(BLEDevice central) {
	printInfoMessage("[%s] Central connected",
	    central.address().c_str());

	blinkLedBuiltin(3);
}

void handleDeviceDisconnection(BLEDevice central) {
	printInfoMessage("[%s] Central disconnected",
	    central.address().c_str());

	blinkLedBuiltin(2);
}

void handleCharacteristicRxWritten(BLEDevice device, BLECharacteristic characteristic) {
	String command_string = characteristicRx.value();
	const char* command = command_string.c_str();

	if (strcmp(command, "BLINK") == 0) {
		blinkLedBuiltin(1);
		char buffer[RX_VALUE_SIZE];
		snprintf(buffer, sizeof(buffer), "CMMD ACCEPTED: %s", command);
		characteristicTx.writeValue(buffer);
	} else if (strcmp(command, KEY_DOWN_ARROW_UP) == 0) {
		/* ... */
		char buffer[RX_VALUE_SIZE];
		snprintf(buffer, sizeof(buffer), "CMMD ACCEPTED: %s", command);
		characteristicTx.writeValue(buffer);
	} else if (strcmp(command, KEY_UP_ARROW_UP) == 0) {
		/* ... */
		char buffer[RX_VALUE_SIZE];
		snprintf(buffer, sizeof(buffer), "CMMD ACCEPTED: %s", command);
		characteristicTx.writeValue(buffer);
	} else if (strcmp(command, KEY_DOWN_ARROW_RIGHT) == 0) {
		/* ... */
		char buffer[RX_VALUE_SIZE];
		snprintf(buffer, sizeof(buffer), "CMMD ACCEPTED: %s", command);
		characteristicTx.writeValue(buffer);
	} else if (strcmp(command, KEY_UP_ARROW_RIGHT) == 0) {
		/* ... */
		char buffer[RX_VALUE_SIZE];
		snprintf(buffer, sizeof(buffer), "CMMD ACCEPTED: %s", command);
		characteristicTx.writeValue(buffer);
	} else if (strcmp(command, KEY_DOWN_ARROW_DOWN) == 0) {
		/* ... */
		char buffer[RX_VALUE_SIZE];
		snprintf(buffer, sizeof(buffer), "CMMD ACCEPTED: %s", command);
		characteristicTx.writeValue(buffer);
	} else if (strcmp(command, KEY_UP_ARROW_DOWN) == 0) {
		/* ... */
		char buffer[RX_VALUE_SIZE];
		snprintf(buffer, sizeof(buffer), "CMMD ACCEPTED: %s", command);
		characteristicTx.writeValue(buffer);
	} else if (strcmp(command, KEY_DOWN_ARROW_LEFT) == 0) {
		/* ... */
		char buffer[RX_VALUE_SIZE];
		snprintf(buffer, sizeof(buffer), "CMMD ACCEPTED: %s", command);
		characteristicTx.writeValue(buffer);
	} else if (strcmp(command, KEY_UP_ARROW_LEFT) == 0) {
		/* ... */
		char buffer[RX_VALUE_SIZE];
		snprintf(buffer, sizeof(buffer), "CMMD ACCEPTED: %s", command);
		characteristicTx.writeValue(buffer);
	} else if (strcmp(command, KEY_DOWN_MACRO_NUMBER_1) == 0) {
		/* ... */
		char buffer[RX_VALUE_SIZE];
		snprintf(buffer, sizeof(buffer), "CMMD ACCEPTED: %s", command);
		characteristicTx.writeValue(buffer);
	} else if (strcmp(command, KEY_UP_MACRO_NUMBER_1) == 0) {
		/* ... */
		char buffer[RX_VALUE_SIZE];
		snprintf(buffer, sizeof(buffer), "CMMD ACCEPTED: %s", command);
		characteristicTx.writeValue(buffer);
	} else if (strcmp(command, KEY_DOWN_MACRO_NUMBER_2) == 0) {
		/* ... */
		char buffer[RX_VALUE_SIZE];
		snprintf(buffer, sizeof(buffer), "CMMD ACCEPTED: %s", command);
		characteristicTx.writeValue(buffer);
	} else if (strcmp(command, KEY_UP_MACRO_NUMBER_2) == 0) {
		/* ... */
		char buffer[RX_VALUE_SIZE];
		snprintf(buffer, sizeof(buffer), "CMMD ACCEPTED: %s", command);
		characteristicTx.writeValue(buffer);
	} else if (strcmp(command, KEY_DOWN_MACRO_NUMBER_3) == 0) {
		/* ... */
		char buffer[RX_VALUE_SIZE];
		snprintf(buffer, sizeof(buffer), "CMMD ACCEPTED: %s", command);
		characteristicTx.writeValue(buffer);
	} else if (strcmp(command, KEY_UP_MACRO_NUMBER_3) == 0) {
		/* ... */
		char buffer[RX_VALUE_SIZE];
		snprintf(buffer, sizeof(buffer), "CMMD ACCEPTED: %s", command);
		characteristicTx.writeValue(buffer);
	} else if (strcmp(command, KEY_DOWN_MACRO_NUMBER_4) == 0) {
		/* ... */
		char buffer[RX_VALUE_SIZE];
		snprintf(buffer, sizeof(buffer), "CMMD ACCEPTED: %s", command);
		characteristicTx.writeValue(buffer);
	} else if (strcmp(command, KEY_UP_MACRO_NUMBER_4) == 0) {
		/* ... */
		char buffer[RX_VALUE_SIZE];
		snprintf(buffer, sizeof(buffer), "CMMD ACCEPTED: %s", command);
		characteristicTx.writeValue(buffer);
	} else {
		char buffer[RX_VALUE_SIZE];
		snprintf(buffer, sizeof(buffer), "ERROR: %s", command);
		printErrorMessage(buffer);
		characteristicTx.writeValue(buffer);
	}
}
