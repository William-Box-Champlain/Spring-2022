#include "Event.h"
#pragma once

class GameEvents :   public Event
{
public:
	GameEvents(EventType eventType);
	virtual ~GameEvents();
private:

};