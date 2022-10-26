#include "KeyboardInputEvent.h"

KeyboardInputEvent::KeyboardInputEvent(KeyCodes key):InputEvent(InputType::KEYBOARD)
{
	mKey = key;
}

KeyboardInputEvent::~KeyboardInputEvent()
{
}

KeyCodes KeyboardInputEvent::getKey()
{
	return mKey;
}
