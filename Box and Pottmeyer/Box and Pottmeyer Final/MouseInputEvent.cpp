#include "MouseInputEvent.h"

MouseInputEvent::MouseInputEvent(Vector2D mousePosition, MouseOutputs code):InputEvent(InputType::MOUSE)
{
	mPosition = mousePosition;
	mCode = code;
}

MouseInputEvent::MouseInputEvent(Vector2D mousePosition):InputEvent(InputType::MOUSE)
{
	mPosition = mousePosition;
}

MouseInputEvent::~MouseInputEvent()
{

}

Vector2D MouseInputEvent::getPositon()
{
	return mPosition;
}

MouseOutputs MouseInputEvent::getCode()
{
	return mCode;
}
