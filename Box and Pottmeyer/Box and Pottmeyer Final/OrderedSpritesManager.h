#pragma once
#include <Trackable.h>
#include <unordered_map>
#include <string>
#include "OrderedSprites.h"

typedef std::string MapKey;

class OrderedSpritesManager:public Trackable
{
public:
	OrderedSpritesManager();
	~OrderedSpritesManager();

	void addMultipleSprites(GraphicsBuffer* spriteSheet, Vector2D rowsAndColumns, int numberOfFrames, MapKey orderedSpritesName);
	void addMultipleSprites(OrderedSprites* newOrderedSprites, MapKey orderedSpritesName);
	void removeOrderedSprites(MapKey orderedSpritesName);
	OrderedSprites* getOrderedSprites(MapKey orderedSpritesName);

private:
	void clearManager();
	std::unordered_map<MapKey, OrderedSprites*> mpOrderedSpritesMap;
};