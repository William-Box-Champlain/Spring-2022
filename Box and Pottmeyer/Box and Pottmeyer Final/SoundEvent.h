#pragma once
#include "GameEvents.h"

enum class SoundEffect
{
	CLICK,
	EAT_DOT,
	EAT_POWER_UP,
	DEATH,
};

class SoundEvent:public GameEvents
{
public:
	SoundEvent(SoundEffect sound);
	~SoundEvent();

	SoundEffect getSoundEffect();

private:
	SoundEffect mSoundEffect;
};