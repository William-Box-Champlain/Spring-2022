#include "AnimationManager.h"

AnimationManager::AnimationManager()
{
	//doesn't do anything
}

AnimationManager::~AnimationManager()
{
	clearManager();
}

void AnimationManager::addAnimation(Animation* animationToAdd, MapKey animationName)
{
	if (mpAnimationMap.find(animationName) == mpAnimationMap.end())
	{
		mpAnimationMap[animationName] = animationToAdd;
	}
}

void AnimationManager::addAnimation(OrderedSprites* sprites, int frameRate, bool shouldLoop, MapKey animationName)
{
	if (mpAnimationMap.find(animationName) == mpAnimationMap.end())
	{
		mpAnimationMap[animationName] = new Animation(sprites,frameRate,shouldLoop);
	}
}

void AnimationManager::removeAnimation(MapKey animationName)
{
	auto animationToDelete = mpAnimationMap.find(animationName);
	if (animationToDelete != mpAnimationMap.end())
	{
		delete animationToDelete->second;
		mpAnimationMap.erase(animationName);
	}
}

Animation* AnimationManager::getAnimation(MapKey animationName)
{
	if (mpAnimationMap.find(animationName) != mpAnimationMap.end())
	{
		return mpAnimationMap.at(animationName);
	}
	else
	{
		return NULL;
	}
}

void AnimationManager::clearManager()
{
	for (auto animationsToDelete : mpAnimationMap)
	{
		if (animationsToDelete.second != NULL || animationsToDelete.second != nullptr)
		{
			delete animationsToDelete.second;
		}
	}
	mpAnimationMap.clear();
}