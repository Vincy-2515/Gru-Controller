#include <Button.h>

Button::Button(const char* button_name,
    const char* button_pressed_key_code,
    const char* button_released_key_code,
    void (*handler)(int btn_status)) {
	this->__button_name = String(
	    button_name ? button_name : "");
	this->__button_pressed_key_code = String(
	    button_pressed_key_code ? button_pressed_key_code : "");
	this->__button_released_key_code = String(
	    button_released_key_code ? button_released_key_code : "");
	this->__handler = handler;
}

const char* Button::getButtonName() {
	return this->__button_name.c_str();
}

const char* Button::getButtonPressedKeyCode() {
	return this->__button_pressed_key_code.c_str();
}

const char* Button::getButtonReleasedKeyCode() {
	return this->__button_released_key_code.c_str();
}

bool Button::callHandler(int btn_status) {
	if (__handler) {
		__handler(btn_status);
		return true;
	}

	return false;
}
