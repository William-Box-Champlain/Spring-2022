#include "Ghost.h"
Ghost::Ghost() :Unit() {};
Ghost::Ghost(GraphicsBuffer* unitAnimationSpriteSheet, Vector2D columnsAndRows, int numberOfFrames, int frameRate, bool shouldLoop, Vector2D startingPosition) :Unit(unitAnimationSpriteSheet, columnsAndRows, numberOfFrames, frameRate, shouldLoop, startingPosition) {};
Ghost::Ghost(Animation* unitAnimation, Vector2D startingPosition) :Unit(unitAnimation, startingPosition) {};
void Ghost::createCollisionEvent()
{
	Unit::createCollisionEvent();
	EventSystem* eventSystem = EventSystem::getInstance();
	eventSystem->fireEvent(CollisionEvent(CollisionType::WALL));
}

void Ghost::setPreviousPos(Vector2D startingPos)
{
	mPreviousPos = startingPos;
}

Vector2D Ghost::getPreviousPos()
{
	return mPreviousPos;
}
