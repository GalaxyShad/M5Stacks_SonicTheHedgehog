#include "include\Keyboard.h"

bool Keyboard::isKeyPressedRight() {
    #ifdef CORE
    return KEY_RIGHT.isPressed();
    #endif

	#ifdef PC
	return sf::Keyboard::isKeyPressed(KEY_RIGHT);
	#endif
}

bool Keyboard::isKeyPressedLeft() {
    #ifdef CORE
    return KEY_LEFT.isPressed();
    #endif

	#ifdef PC
	return sf::Keyboard::isKeyPressed(KEY_LEFT);
	#endif
}

bool Keyboard::isKeyPressedAction() {
    #ifdef CORE
    return KEY_ACTION.isPressed();
    #endif

	#ifdef PC
	return sf::Keyboard::isKeyPressed(KEY_ACTION);
	#endif
}  

bool Keyboard::isKeyPressedSpindash() {
	#ifdef CORE
	if (KEY_LEFT.isPressed() && KEY_RIGHT.isPressed())
		return true;
	#endif

	#ifdef PC
	return sf::Keyboard::isKeyPressed(KEY_SPINDASH_PC);
	#endif
}
