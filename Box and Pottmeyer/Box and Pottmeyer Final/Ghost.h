#pragma once
#include "Unit.h"
class Ghost :public Unit
{
public:
	Ghost();
	Ghost(GraphicsBuffer* unitAnimationSpriteSheet, Vector2D columnsAndRows, int numberOfFrames, int frameRate, bool shouldLoop, Vector2D startingPosition);
	Ghost(Animation* unitAnimation, Vector2D startingPosition);
	void createCollisionEvent();
	void setPreviousPos(Vector2D startingPos);
	Vector2D getPreviousPos();
private:
	Vector2D mPreviousPos;
};