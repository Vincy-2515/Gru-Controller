#ifndef BUTTON_H
#define BUTTON_H

#include <Arduino.h>

class Button {
private:
	String __button_name;
	String __button_pressed_key_code;
	String __button_released_key_code;
	void (*__handler)(String button_name, int button_status) = nullptr;

public:
	Button(const char* button_name,
	    const char* button_pressed_key_code,
	    const char* button_released_key_code,
	    void (*handler)(String button_name, int button_status));
	const char* getButtonName();
	const char* getButtonPressedKeyCode();
	const char* getButtonReleasedKeyCode();
	bool callHandler(String button_name, int button_status);
};

#endif /* BUTTON_H */