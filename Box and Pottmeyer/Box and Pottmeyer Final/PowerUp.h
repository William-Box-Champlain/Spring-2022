#pragma once
#include "Unit.h"
class PowerUp:public Unit
{
public:
    PowerUp(Animation* animation, Vector2D position);
    void createCollisionEvent();
private:

};