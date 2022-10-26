#pragma once
#include "GameEvents.h"

enum LevelEventType 
{
	CLOSE_LEVEL,
	RESTART_GAME,
	CHANGE_LEVEL,
	CLOSE_GAME,
	START_GAME,
	END_GAME
};

class LevelEvents:public GameEvents
{
public:
	LevelEvents(LevelEventType newLevelEvent);
	~LevelEvents();
	LevelEventType getLevelEvent();
private:
	LevelEventType mLevelEvent;
};