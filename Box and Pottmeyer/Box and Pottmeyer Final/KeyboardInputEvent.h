#pragma once
#include "InputEvent.h"
#include "InputSystem.h"

class KeyboardInputEvent:public InputEvent
{
public:
	KeyboardInputEvent(KeyCodes key);
	~KeyboardInputEvent();

	KeyCodes getKey();
private:
	KeyCodes mKey;
};