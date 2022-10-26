#include "SoundEvent.h"
SoundEvent::SoundEvent(SoundEffect sound):GameEvents(EventType::SOUND_EVENT)
{
	mSoundEffect = sound;
}
SoundEvent::~SoundEvent()
{

}

SoundEffect SoundEvent::getSoundEffect()
{
	return mSoundEffect;
}