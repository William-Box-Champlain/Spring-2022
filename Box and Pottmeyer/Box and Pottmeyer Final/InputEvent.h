#pragma once
#include "GameEvents.h"
#include "InputSystem.h"

enum InputType
{
	DEFAULT,
	MOUSE,
	KEYBOARD
};

class InputEvent :public GameEvents
{
public:
	InputEvent();
	InputEvent(InputType input);
	InputType getType();
	~InputEvent();
private:
	InputType mInputType;
};