#pragma once
#include "InputEvent.h"

enum class KeyCode;

class KeyboardInputEvent:public InputEvent
{
public:
	KeyboardInputEvent(const KeyCode& key);
	~KeyboardInputEvent();

	KeyCode getKey();
private:

	KeyCode mKey;
};