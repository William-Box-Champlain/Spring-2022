#pragma once
#include "GameEvents.h"
#include <Vector2D.h>
class MoveEvent:public GameEvents
{
public:
	MoveEvent(Vector2D direction);
	~MoveEvent();

	Vector2D getDirection();
private:
	Vector2D mDirection;
};