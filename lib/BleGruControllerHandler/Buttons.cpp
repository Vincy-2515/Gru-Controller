#include <Buttons.h>

/**
 * AZIONI:
 * - ArrowUp, ArrowDown: [CARRELLO] Scorrimento avanti e indietro del carrello
 * - ArrowRight, ArrowLeft: [BRACCIO] Rotazione oraria e antioraria del braccio
 * - Macro4 + (ArrowUp, ArrowDown): [BOBINA] Arrotolamento e rilascio del cavo
 * - Macro1, Macro2, Macro3 + (Controlli per [CARRELLO], [BRACCIO], [BOBINA]):
 * 		Velocità di rotazione:
 * 			> Macro1: bassa velocità
 * 			> Macro2: media velocità
 * 			> Macro3: alta velocità
 */

static void __btnArrowUpHandler(int btn_status);
static void __btnArrowRightHandler(int btn_status);
static void __btnArrowDownHandler(int btn_status);
static void __btnArrowLeftHandler(int btn_status);
static void __btnMacro1Handler(int btn_status);
static void __btnMacro2Handler(int btn_status);
static void __btnMacro3Handler(int btn_status);
static void __btnMacro4Handler(int btn_status);

static Button __btnArrowUp("btnArrowUp", "!B516", "!B507", __btnArrowUpHandler);
static Button __btnArrowRight("btnArrowRight", "!B813", "!B804", __btnArrowRightHandler);
static Button __btnArrowDown("btnArrowDown", "!B615", "!B606", __btnArrowDownHandler);
static Button __btnArrowLeft("btnArrowLeft", "!B714", "!B705", __btnArrowLeftHandler);
static Button __btnMacro1("btnMacro1", "!B11:", "!B10;", __btnMacro1Handler);
static Button __btnMacro2("btnMacro2", "!B219", "!B20:", __btnMacro2Handler);
static Button __btnMacro3("btnMacro3", "!B318", "!B309", __btnMacro3Handler);
static Button __btnMacro4("btnMacro4", "!B417", "!B408", __btnMacro4Handler);

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

static void __btnArrowUpHandler(int btn_status) {
}

static void __btnArrowRightHandler(int btn_status) {
}

static void __btnArrowDownHandler(int btn_status) {
}

static void __btnArrowLeftHandler(int btn_status) {
}

static void __btnMacro1Handler(int btn_status) {
}

static void __btnMacro2Handler(int btn_status) {
}

static void __btnMacro3Handler(int btn_status) {
}

static void __btnMacro4Handler(int btn_status) {
}
