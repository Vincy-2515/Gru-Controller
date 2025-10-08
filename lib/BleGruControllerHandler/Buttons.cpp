#include <Buttons.h>

typedef enum {
	ACTION_NONE,
	ACTION_ROTATE_ARM,
	ACTION_MOVE_TROLLEY,
	ACTION_ROTATE_COIL
} Action;

typedef enum {
	ROTATION_DEFAULT,
	ROTATION_INVERSE
} Rotation;

typedef enum {
	GEAR_DEFAULT,
	GEAR_FIRST,
	GEAR_SECOND,
	GEAR_THIRD
} Gear;

Action __current_action = ACTION_NONE;
Rotation __current_rotation = ROTATION_DEFAULT;
Gear __current_gear = GEAR_DEFAULT;
bool __is_macro4_pressed = false;

static void __updateState(Action action, Rotation rotation, Gear gear);
static void __checkButtonStatusAndUpdateState(int btn_status, Action action, Rotation rotation, Gear gear);
static void __handleButtonArrowUp(int btn_status);
static void __handleButtonArrowRight(int btn_status);
static void __handleButtonArrowDown(int btn_status);
static void __handleButtonArrowLeft(int btn_status);
static void __handleButtonMacro1(int btn_status);
static void __handleButtonMacro2(int btn_status);
static void __handleButtonMacro3(int btn_status);
static void __handleButtonMacro4(int btn_status);

static Button __btnArrowUp("btnArrowUp", "!B516", "!B507", __handleButtonArrowUp);
static Button __btnArrowRight("btnArrowRight", "!B813", "!B804", __handleButtonArrowRight);
static Button __btnArrowDown("btnArrowDown", "!B615", "!B606", __handleButtonArrowDown);
static Button __btnArrowLeft("btnArrowLeft", "!B714", "!B705", __handleButtonArrowLeft);
static Button __btnMacro1("btnMacro1", "!B11:", "!B10;", __handleButtonMacro1);
static Button __btnMacro2("btnMacro2", "!B219", "!B20:", __handleButtonMacro2);
static Button __btnMacro3("btnMacro3", "!B318", "!B309", __handleButtonMacro3);
static Button __btnMacro4("btnMacro4", "!B417", "!B408", __handleButtonMacro4);

Button buttons[NUMBER_OF_BUTTONS] = {
	__btnArrowUp,
	__btnArrowRight,
	__btnArrowDown,
	__btnArrowLeft,
	__btnMacro1,
	__btnMacro2,
	__btnMacro3,
	__btnMacro4
};

static void __updateState(Action action, Rotation rotation, Gear gear) {
	if ((action != ACTION_NONE) && (__current_action != ACTION_NONE)) {
		return;
	}

	printInfoMessage("current: {a: %d, r: %d, g: %d}, new: {a: %d, r: %d, g: %d}, 4: %d", __current_action, __current_rotation, __current_gear, action, rotation, gear, __is_macro4_pressed);

	__current_action = action;
	__current_rotation = rotation;
	__current_gear = gear;
}

static void __checkButtonStatusAndUpdateState(int btn_status, Action action, Rotation rotation, Gear gear) {
	if (btn_status == BUTTON_PRESSED) {
		__updateState(action, rotation, gear);
	} else {
		__updateState(ACTION_NONE, ROTATION_DEFAULT, GEAR_DEFAULT);
	}
}

/*============
    HANDLERS:
  ============*/

static void __handleButtonArrowUp(int btn_status) {
	if (__is_macro4_pressed) {
		__checkButtonStatusAndUpdateState(btn_status, ACTION_MOVE_TROLLEY, ROTATION_DEFAULT, __current_gear);
	} else {
		__checkButtonStatusAndUpdateState(btn_status, ACTION_ROTATE_COIL, ROTATION_DEFAULT, __current_gear);
	}
}

static void __handleButtonArrowRight(int btn_status) {
	__checkButtonStatusAndUpdateState(btn_status, ACTION_ROTATE_ARM, ROTATION_DEFAULT, __current_gear);
}

static void __handleButtonArrowDown(int btn_status) {
	if (__is_macro4_pressed) {
		__checkButtonStatusAndUpdateState(btn_status, ACTION_MOVE_TROLLEY, ROTATION_INVERSE, __current_gear);
	} else {
		__checkButtonStatusAndUpdateState(btn_status, ACTION_ROTATE_COIL, ROTATION_INVERSE, __current_gear);
	}
}

static void __handleButtonArrowLeft(int btn_status) {
	__checkButtonStatusAndUpdateState(btn_status, ACTION_ROTATE_ARM, ROTATION_INVERSE, __current_gear);
}

static void __handleButtonMacro1(int btn_status) {
	__checkButtonStatusAndUpdateState(btn_status, ACTION_NONE, ROTATION_DEFAULT, GEAR_FIRST);
}

static void __handleButtonMacro2(int btn_status) {
	__checkButtonStatusAndUpdateState(btn_status, ACTION_NONE, ROTATION_DEFAULT, GEAR_SECOND);
}

static void __handleButtonMacro3(int btn_status) {
	__checkButtonStatusAndUpdateState(btn_status, ACTION_NONE, ROTATION_DEFAULT, GEAR_THIRD);
}

static void __handleButtonMacro4(int btn_status) {
	if ((btn_status == BUTTON_PRESSED) && __is_macro4_pressed) {
		__is_macro4_pressed = false;
	} else if ((btn_status == BUTTON_PRESSED) && !__is_macro4_pressed) {
		__is_macro4_pressed = true;
	}
}
