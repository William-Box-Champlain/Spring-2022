#include "Wall.h"
Wall::Wall()
{
	Unit::Unit();
}
Wall::Wall(Animation* unitAnimation, Vector2D startingPosition):Unit(unitAnimation,startingPosition)
{
	mIsAnimated = false;
}
void Wall::createCollisionEvent()
{
	Unit::createCollisionEvent();
	EventSystem* eventSystem = EventSystem::getInstance();
	eventSystem->fireEvent(CollisionEvent(CollisionType::WALL));
}