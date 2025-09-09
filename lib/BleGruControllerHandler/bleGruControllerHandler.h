#ifndef BLEGRUCONTROLLERHANDLER_H
#define BLEGRUCONTROLLERHANDLER_H

#pragma once

#include <Arduino.h>
#include <ArduinoBLE.h>
#include <Buttons.h>
#include <componentHandler.h>
#include <logHandler.h>

#define DEVICE_NAME "ESP32-DEVKIT-C"
#define LOCAL_NAME "GRU"

#define UUID_SERVICE_UART "6E400001-B5A3-F393-E0A9-E50E24DCCA9E"
#define UUID_CHARACTERISTIC_RX "6E400002-B5A3-F393-E0A9-E50E24DCCA9E"
#define UUID_CHARACTERISTIC_TX "6E400003-B5A3-F393-E0A9-E50E24DCCA9E"

#define RX_VALUE_SIZE 128
#define TX_VALUE_SIZE 128

void bleGruControllerSetup();
void bleGruControllerLoop();

#endif /* BLEGRUCONTROLLERHANDLER_H */