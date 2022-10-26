#include "Food.h"
Food::Food(Animation* animation, Vector2D position):Unit(animation, position)
{
	mUnitType = UnitType::FOOD;
}
void Food::createCollisionEvent()
{
	Unit::createCollisionEvent();
	EventSystem* eventSystem = EventSystem::getInstance();
	eventSystem->fireEvent(CollisionEvent(CollisionType::FOOD));
}