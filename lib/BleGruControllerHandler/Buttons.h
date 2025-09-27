#ifndef BUTTONS_H
#define BUTTONS_H

#pragma once

#include <Arduino.h>
#include <Button.h>
#include <Motors.h>

#define NUMBER_OF_BUTTONS (8)

typedef enum {
	BUTTON_PRESSED,
	BUTTON_RELEASED
} ButtonStatus;

extern Button buttons[NUMBER_OF_BUTTONS];

#endif