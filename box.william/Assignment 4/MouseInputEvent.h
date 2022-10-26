#pragma once
#include "InputEvent.h"
#include <Vector2D.h>

enum class MouseCode;

class MouseInputEvent:public InputEvent
{
public:

	MouseInputEvent(Vector2D& mousePosition, const MouseCode& code);
	~MouseInputEvent();

	Vector2D getPositon();
	MouseCode getCode();

private:

	Vector2D mPosition;
	MouseCode mCode;
};