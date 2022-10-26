#pragma once

#include <string>
#include <trackable.h>

using namespace std;

enum EventType
{
	MOVE_EVENT,
	MESSAGE_EVENT,
	INPUT_EVENT,
	GAME_EVENT,
	LEVEL_EVENT,
	SNAKE_EVENT,
	HUD_EVENT,
	COLLISION_EVENT,
	SOUND_EVENT,
	CLICKABLE_EVENT,
	NUM_OF_GAME_EVENTS
};

class Event :public Trackable
{
public:
	Event(EventType type);
	virtual ~Event();

	EventType getType() const { return mType; };

private:
	EventType mType;

};