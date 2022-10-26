#include "CollisionEvent.h"
CollisionEvent::CollisionEvent(CollisionType type):GameEvents(EventType::COLLISION_EVENT)
{
	mCollisionType = type;
}
CollisionEvent::~CollisionEvent()
{

}

CollisionType CollisionEvent::getCollisionType()
{
	return mCollisionType;
}