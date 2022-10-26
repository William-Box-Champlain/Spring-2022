#pragma once
#include "Unit.h"
class Wall:public Unit
{
public:
	Wall();
	Wall(Animation* unitAnimation, Vector2D startingPosition);
	~Wall();
	void createCollisionEvent();
};