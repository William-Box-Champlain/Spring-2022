#include "PowerDown.h"
PowerDown::PowerDown(Animation* animation, Vector2D position):Unit(animation, position)
{
	mUnitType = UnitType::POWER_DOWN;
}
void PowerDown::createCollisionEvent()
{
	Unit::createCollisionEvent();
	EventSystem* eventSystem = EventSystem::getInstance();
	eventSystem->fireEvent(CollisionEvent(CollisionType::POWER_UP));
}