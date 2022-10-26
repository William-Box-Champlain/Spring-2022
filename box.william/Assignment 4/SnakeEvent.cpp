#include "SnakeEvent.h"
SnakeEvent::SnakeEvent(SnakeEventType snakeEventType) :GameEvents(EventType::SNAKE_EVENT)
{
	mSnakeEvent = snakeEventType;
}
SnakeEvent::~SnakeEvent()
{

}
SnakeEventType SnakeEvent::getSnakeEvent()
{
	return mSnakeEvent;
}