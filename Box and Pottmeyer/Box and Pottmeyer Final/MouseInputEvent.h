#pragma once
#include <Vector2D.h>
#include "InputEvent.h"
#include "InputSystem.h"

class MouseInputEvent:public InputEvent
{
public:

	MouseInputEvent(Vector2D mousePosition, MouseOutputs code);
	MouseInputEvent(Vector2D mousePosition);
	~MouseInputEvent();

	Vector2D getPositon();
	MouseOutputs getCode();

private:

	Vector2D mPosition;
	MouseOutputs mCode;
};