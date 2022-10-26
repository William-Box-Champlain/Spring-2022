#include "SnakeSegment.h"
SnakeSegment::SnakeSegment():Unit() {};
SnakeSegment::SnakeSegment(GraphicsBuffer* unitAnimationSpriteSheet, Vector2D columnsAndRows, int numberOfFrames, int frameRate, bool shouldLoop, Vector2D startingPosition):Unit(unitAnimationSpriteSheet, columnsAndRows, numberOfFrames, frameRate, shouldLoop, startingPosition) {};
SnakeSegment::SnakeSegment(Animation* unitAnimation, Vector2D startingPosition) :Unit(unitAnimation,startingPosition) {};
void SnakeSegment::createCollisionEvent()
{
	Unit::createCollisionEvent();
	EventSystem* eventSystem = EventSystem::getInstance();
	eventSystem->fireEvent(CollisionEvent(CollisionType::SNAKE));
}