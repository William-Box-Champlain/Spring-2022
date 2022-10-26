#include "MoveEvent.h"
MoveEvent::MoveEvent(Vector2D direction) :GameEvents(EventType::MOVE_EVENT)
{
	mDirection = direction;
}
MoveEvent::~MoveEvent()
{

}
Vector2D MoveEvent::getDirection()
{
	return mDirection;
}