#include <Buttons.h>
#include <componentHandler.h>

#define __NO_ARROW_BUTTON_PRESSED ""

static Action __current_action = ACTION_NONE;
static Rotation __current_rotation = ROTATION_DEFAULT;
static Gear __current_gear = GEAR_DEFAULT;
static String __currently_pressed_arrow_button_name = __NO_ARROW_BUTTON_PRESSED;
static bool __is_macro4_pressed = false;

static void __handleButtonArrowUp(String button_name, int button_status);
static void __handleButtonArrowRight(String button_name, int button_status);
static void __handleButtonArrowDown(String button_name, int button_status);
static void __handleButtonArrowLeft(String button_name, int button_status);
static void __handleButtonMacro1(String button_name, int button_status);
static void __handleButtonMacro2(String button_name, int button_status);
static void __handleButtonMacro3(String button_name, int button_status);
static void __handleButtonMacro4(String button_name, int button_status);
static void __checkArrowButtonStatusAndUpdateActionAndRotation(String button_name, int button_status, MotorId motor_id, Action action, Rotation rotation, Gear gear);
static void __updateActionAndRotation(String button_name, MotorId motor_id, Action action, Rotation rotation, Gear gear);
static void __updateGear(int button_status, Gear gear);

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

static void __checkArrowButtonStatusAndUpdateActionAndRotation(
    String button_name,
    int button_status,
    MotorId motor_id,
    Action action,
    Rotation rotation,
    Gear gear) {

	if ((button_status == BUTTON_PRESSED)
	    && ((__currently_pressed_arrow_button_name == button_name)
	        || (__currently_pressed_arrow_button_name == __NO_ARROW_BUTTON_PRESSED))) {

		__updateActionAndRotation(button_name, motor_id, action, rotation, gear);

	} else if ((button_status == BUTTON_RELEASED)
	    && ((__currently_pressed_arrow_button_name == button_name)
	        || (__currently_pressed_arrow_button_name == __NO_ARROW_BUTTON_PRESSED))) {

		__updateActionAndRotation(button_name, motor_id, ACTION_NONE, ROTATION_DEFAULT, GEAR_DEFAULT);
		__currently_pressed_arrow_button_name = __NO_ARROW_BUTTON_PRESSED;

	} else {
		printWarningMessage("Button-press ignored, another \"arrow-button\" is already pressed");
	}
}

static void __updateActionAndRotation(String button_name, MotorId motor_id, Action action, Rotation rotation, Gear gear) {
	if ((action != ACTION_NONE) && (__current_action != ACTION_NONE)) {
		return;
	}

	printInfoMessage("motor_state: {current: [ACTION: %d, ROTATION: %d, GEAR: %d], new: [ACTION: %d, ROTATION: %d, GEAR: %d], MACRO_4: %d}", __current_action, __current_rotation, __current_gear, action, rotation, gear, __is_macro4_pressed);

	updateMotorState(motor_id, action, rotation, gear);

	__current_action = action;
	__current_rotation = rotation;
	__currently_pressed_arrow_button_name = button_name;
}

static void __updateGear(int button_status, Gear gear) {
	if (button_status == BUTTON_RELEASED) {
		__current_gear = GEAR_DEFAULT;
		return;
	} else if ((__current_gear != GEAR_DEFAULT) && (button_status != BUTTON_RELEASED)) {
		return;
	}

	__current_gear = gear;
}

/*============
    HANDLERS
  ============*/

/*-----------------
    Arrow buttons
  -----------------*/

static void __handleButtonArrowUp(String button_name, int button_status) {
	if (__is_macro4_pressed) {
		__checkArrowButtonStatusAndUpdateActionAndRotation(button_name, button_status, MOTOR_COIL, ACTION_ROTATE_COIL, ROTATION_DEFAULT, __current_gear);
	} else {
		__checkArrowButtonStatusAndUpdateActionAndRotation(button_name, button_status, MOTOR_TROLLEY, ACTION_MOVE_TROLLEY, ROTATION_DEFAULT, __current_gear);
	}
}

static void __handleButtonArrowRight(String button_name, int button_status) {
	__checkArrowButtonStatusAndUpdateActionAndRotation(button_name, button_status, MOTOR_ARM, ACTION_ROTATE_ARM, ROTATION_DEFAULT, __current_gear);
}

static void __handleButtonArrowDown(String button_name, int button_status) {
	if (__is_macro4_pressed) {
		__checkArrowButtonStatusAndUpdateActionAndRotation(button_name, button_status, MOTOR_COIL, ACTION_ROTATE_COIL, ROTATION_INVERSE, __current_gear);
	} else {
		__checkArrowButtonStatusAndUpdateActionAndRotation(button_name, button_status, MOTOR_TROLLEY, ACTION_MOVE_TROLLEY, ROTATION_INVERSE, __current_gear);
	}
}

static void __handleButtonArrowLeft(String button_name, int button_status) {
	__checkArrowButtonStatusAndUpdateActionAndRotation(button_name, button_status, MOTOR_ARM, ACTION_ROTATE_ARM, ROTATION_INVERSE, __current_gear);
}

/*-----------------
    Macro buttons
  -----------------*/

static void __handleButtonMacro1(String button_name, int button_status) {
	__updateGear(button_status, GEAR_FIRST);
}

static void __handleButtonMacro2(String button_name, int button_status) {
	__updateGear(button_status, GEAR_SECOND);
}

static void __handleButtonMacro3(String button_name, int button_status) {
	__updateGear(button_status, GEAR_THIRD);
}

static void __handleButtonMacro4(String button_name, int button_status) {
	if ((button_status == BUTTON_PRESSED)
	    && __is_macro4_pressed
	    && (__currently_pressed_arrow_button_name == __NO_ARROW_BUTTON_PRESSED)) {

		__is_macro4_pressed = false;

	} else if ((button_status == BUTTON_PRESSED)
	    && !__is_macro4_pressed
	    && (__currently_pressed_arrow_button_name == __NO_ARROW_BUTTON_PRESSED)) {

		__is_macro4_pressed = true;

	} else if (__currently_pressed_arrow_button_name != __NO_ARROW_BUTTON_PRESSED) {

		printWarningMessage("Button-press ignored, an \"arrow-button\" is still pressed");
	}
}
