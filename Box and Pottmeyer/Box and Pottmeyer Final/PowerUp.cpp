#include "PowerUp.h"
PowerUp::PowerUp(Animation* animation, Vector2D position):Unit(animation, position)
{
	mUnitType = UnitType::POWER_UP;
}
void PowerUp::createCollisionEvent()
{
	Unit::createCollisionEvent();
	EventSystem* eventSystem = EventSystem::getInstance();
	eventSystem->fireEvent(CollisionEvent(CollisionType::POWER_UP));
}