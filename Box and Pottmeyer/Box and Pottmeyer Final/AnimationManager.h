#include <Trackable.h>
#include <string>
#include <unordered_map>
#include "Animation.h"
#pragma once

typedef std::string MapKey;

class AnimationManager:public Trackable
{
public:
	AnimationManager();
	~AnimationManager();

	void addAnimation(Animation* animationToAdd, MapKey animationName);
	void addAnimation(OrderedSprites* sprites, int frameRate, bool shouldLoop, MapKey animationName);
	void removeAnimation(MapKey animationName);

	Animation* getAnimation(MapKey animationName);

private:
	void clearManager();
	std::unordered_map<MapKey, Animation*> mpAnimationMap;
};