#include "InputEvent.h"

InputEvent::InputEvent():GameEvents(EventType::INPUT_EVENT)
{
	mInputType = DEFAULT;
}

InputEvent::InputEvent(InputType input):GameEvents(EventType::INPUT_EVENT)
{
	mInputType = input;
}

InputEvent::~InputEvent()
{

}

InputType InputEvent::getType()
{
	return mInputType;
}
