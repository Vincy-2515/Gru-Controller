#ifndef BUTTONS_H
#define BUTTONS_H

#pragma once

#include <Arduino.h>
#include <Button.h>

#define NUMBER_OF_BUTTONS (8)

typedef enum {
	BTN_PRESSED,
	BTN_RELEASED
};

extern Button buttons[NUMBER_OF_BUTTONS];

#endif