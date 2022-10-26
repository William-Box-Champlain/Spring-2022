#include "OrderedSpritesManager.h"

OrderedSpritesManager::OrderedSpritesManager()
{
	//doesn't do shit bruv
}

OrderedSpritesManager::~OrderedSpritesManager()
{
	for (auto orderedSpritesToDelete : mpOrderedSpritesMap)
	{
		delete orderedSpritesToDelete.second;
	}
	mpOrderedSpritesMap.clear();
}

void OrderedSpritesManager::addMultipleSprites(GraphicsBuffer* spriteSheet, Vector2D rowsAndColumns, int numberOfFrames, MapKey orderedSpritesName)
{
	if (mpOrderedSpritesMap.find(orderedSpritesName) == mpOrderedSpritesMap.end())
	{
		mpOrderedSpritesMap[orderedSpritesName] = new OrderedSprites(spriteSheet, rowsAndColumns, numberOfFrames);
	}
}

void OrderedSpritesManager::addMultipleSprites(OrderedSprites* newOrderedSprites, MapKey orderedSpritesName)
{
	if (mpOrderedSpritesMap.find(orderedSpritesName) == mpOrderedSpritesMap.end())
	{
		mpOrderedSpritesMap[orderedSpritesName] = newOrderedSprites;
	}
}

void OrderedSpritesManager::removeOrderedSprites(MapKey orderedSpritesName)
{
	auto orderedSpritesToDelete = mpOrderedSpritesMap.find(orderedSpritesName);
	if (orderedSpritesToDelete != mpOrderedSpritesMap.end())
	{
		delete orderedSpritesToDelete->second;
		mpOrderedSpritesMap.erase(orderedSpritesName);
	}
}

OrderedSprites* OrderedSpritesManager::getOrderedSprites(MapKey orderedSpritesName)
{
	if (mpOrderedSpritesMap.find(orderedSpritesName) != mpOrderedSpritesMap.end())
	{
		return mpOrderedSpritesMap.at(orderedSpritesName);
	}
	else
	{
		return NULL;
	}
}
