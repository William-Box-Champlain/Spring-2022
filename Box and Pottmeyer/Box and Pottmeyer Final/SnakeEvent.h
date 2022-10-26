#pragma once
#include "GameEvents.h"

enum class SnakeEventType 
{
	GROW,
	SHRINK,
	DIE
};

class SnakeEvent:public GameEvents
{
public:
	SnakeEvent(SnakeEventType snakeEventType);
	~SnakeEvent();

	SnakeEventType getSnakeEvent();

private:
	SnakeEventType mSnakeEvent;
};