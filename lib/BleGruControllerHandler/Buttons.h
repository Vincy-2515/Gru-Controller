#ifndef BUTTONS_H
#define BUTTONS_H

#include <Arduino.h>
#include <Button.h>
#include <types.h>

#define NUMBER_OF_BUTTONS (8)

// enums moved to ComponentHandler/types.h

extern Button buttons[NUMBER_OF_BUTTONS];

#endif