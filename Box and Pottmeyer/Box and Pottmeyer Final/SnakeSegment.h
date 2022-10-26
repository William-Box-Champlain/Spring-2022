#pragma once
#include "Unit.h"
class SnakeSegment:public Unit
{
public:
	SnakeSegment();
	SnakeSegment(GraphicsBuffer* unitAnimationSpriteSheet, Vector2D columnsAndRows, int numberOfFrames, int frameRate, bool shouldLoop, Vector2D startingPosition);
	SnakeSegment(Animation* unitAnimation, Vector2D startingPosition);
	void createCollisionEvent();
private:
};