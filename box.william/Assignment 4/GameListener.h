#include <EventListener.h>

#pragma once
class GameListener:public EventListener
{
public:
	GameListener();
	~GameListener();

	void handleEvent(const Event& gameEvent);

private:
};