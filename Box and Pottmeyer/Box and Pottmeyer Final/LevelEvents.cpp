#include "LevelEvents.h"
LevelEvents::LevelEvents(LevelEventType newLevelEvent):GameEvents(EventType::LEVEL_EVENT)
{
	mLevelEvent = newLevelEvent;
}
LevelEvents::~LevelEvents()
{

}
LevelEventType LevelEvents::getLevelEvent()
{
	return mLevelEvent;
}