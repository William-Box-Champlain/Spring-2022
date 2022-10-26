#pragma once
#include "Unit.h"
class Food:public Unit
{
public:
	Food(Animation* animation, Vector2D position);
	void createCollisionEvent();
private:

};