#pragma once
#include "GameEvents.h"

enum class CollisionType
{
    FOOD,
    POWER_UP,
    WALL,
    SNAKE
};

class CollisionEvent:public GameEvents
{
public:
    CollisionEvent(CollisionType type);
    ~CollisionEvent();

    CollisionType getCollisionType();
private:
    CollisionType mCollisionType;
};