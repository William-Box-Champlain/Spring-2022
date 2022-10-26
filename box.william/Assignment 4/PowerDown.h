#pragma once
#include "Unit.h"
class PowerDown :
    public Unit
{
public:
    PowerDown(Animation* animation, Vector2D position);
    void createCollisionEvent();
private:

};