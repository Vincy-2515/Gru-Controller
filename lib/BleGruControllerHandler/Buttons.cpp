#include <Buttons.h>
#include <componentHandler.h>

static Action __current_action = ACTION_NONE;
static Rotation __current_rotation = ROTATION_DEFAULT;
static Gear __current_gear = GEAR_DEFAULT;
static int __currently_active_motor_id = -1;
static bool __is_macro4_pressed = false;

static void __handleButtonArrowUp(int btn_status);
static void __handleButtonArrowRight(int btn_status);
static void __handleButtonArrowDown(int btn_status);
static void __handleButtonArrowLeft(int btn_status);
static void __handleButtonMacro1(int btn_status);
static void __handleButtonMacro2(int btn_status);
static void __handleButtonMacro3(int btn_status);
static void __handleButtonMacro4(int btn_status);
static void __checkButtonStatusAndUpdateActionAndRotation(int btn_status, MotorId motor_id, Action action, Rotation rotation, Gear gear);
static void __updateActionAndRotation(MotorId motor_id, Action action, Rotation rotation, Gear gear);
static void __updateGear(int btn_status, Gear gear);

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

/*============
    HANDLERS
  ============*/

/*-----------------
    Arrow buttons
  -----------------*/

static void __handleButtonArrowUp(int btn_status) {
	if (__is_macro4_pressed) {
		__checkButtonStatusAndUpdateActionAndRotation(btn_status, MOTOR_COIL, ACTION_ROTATE_COIL, ROTATION_DEFAULT, __current_gear);
	} else {
		__checkButtonStatusAndUpdateActionAndRotation(btn_status, MOTOR_TROLLEY, ACTION_MOVE_TROLLEY, ROTATION_DEFAULT, __current_gear);
	}
}

static void __handleButtonArrowRight(int btn_status) {
	__checkButtonStatusAndUpdateActionAndRotation(btn_status, MOTOR_ARM, ACTION_ROTATE_ARM, ROTATION_DEFAULT, __current_gear);
}

static void __handleButtonArrowDown(int btn_status) {
	if (__is_macro4_pressed) {
		__checkButtonStatusAndUpdateActionAndRotation(btn_status, MOTOR_COIL, ACTION_ROTATE_COIL, ROTATION_INVERSE, __current_gear);
	} else {
		__checkButtonStatusAndUpdateActionAndRotation(btn_status, MOTOR_TROLLEY, ACTION_MOVE_TROLLEY, ROTATION_INVERSE, __current_gear);
	}
}

static void __handleButtonArrowLeft(int btn_status) {
	__checkButtonStatusAndUpdateActionAndRotation(btn_status, MOTOR_ARM, ACTION_ROTATE_ARM, ROTATION_INVERSE, __current_gear);
}

/*-----------------
    Macro buttons
  -----------------*/

static void __handleButtonMacro1(int btn_status) {
	__updateGear(btn_status, GEAR_FIRST);
}

static void __handleButtonMacro2(int btn_status) {
	__updateGear(btn_status, GEAR_SECOND);
}

static void __handleButtonMacro3(int btn_status) {
	__updateGear(btn_status, GEAR_THIRD);
}

static void __handleButtonMacro4(int btn_status) {
	if ((btn_status == BUTTON_PRESSED) && __is_macro4_pressed) {
		__is_macro4_pressed = false;
	} else if ((btn_status == BUTTON_PRESSED) && !__is_macro4_pressed) {
		__is_macro4_pressed = true;
	}
}

/*===================
    OTHER FUNCTIONS
  ===================*/

static void __checkButtonStatusAndUpdateActionAndRotation(int btn_status, MotorId motor_id, Action action, Rotation rotation, Gear gear) {
	if (btn_status == BUTTON_PRESSED) {
		__updateActionAndRotation(motor_id, action, rotation, gear);
	} else {
		__updateActionAndRotation(motor_id, ACTION_NONE, ROTATION_DEFAULT, GEAR_DEFAULT);
	}
}

static void __updateActionAndRotation(MotorId motor_id, Action action, Rotation rotation, Gear gear) {
	if ((action != ACTION_NONE) && (__current_action != ACTION_NONE)) {
		return;
	} else if ((__currently_active_motor_id != -1) && (__currently_active_motor_id != motor_id) && (action != ACTION_NONE)) {
		return;
	}

	printInfoMessage("motor_state: {current: [ACTION: %d, ROTATION: %d, GEAR: %d], new: [ACTION: %d, ROTATION: %d, GEAR: %d], MACRO_4: %d}", __current_action, __current_rotation, __current_gear, action, rotation, gear, __is_macro4_pressed);

	updateMotorState(motor_id, action, rotation, gear);

	__current_action = action;
	__current_rotation = rotation;
	__currently_active_motor_id = (action == ACTION_NONE) ? -1 : motor_id;
}

static void __updateGear(int btn_status, Gear gear) {
	if (btn_status == BUTTON_RELEASED) {
		__current_gear = GEAR_DEFAULT;
		return;
	} else if ((__current_gear != GEAR_DEFAULT) && (btn_status != BUTTON_RELEASED)) {
		return;
	}

	__current_gear = gear;
}