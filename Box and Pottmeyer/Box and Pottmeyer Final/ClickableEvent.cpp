#include "ClickableEvent.h"
ClickableEvent::ClickableEvent(Clickables type):GameEvents(EventType::CLICKABLE_EVENT)
{
	mClickableType = type;
}

ClickableEvent::~ClickableEvent()
{

}

Clickables ClickableEvent::getType()
{
	return mClickableType;
}
