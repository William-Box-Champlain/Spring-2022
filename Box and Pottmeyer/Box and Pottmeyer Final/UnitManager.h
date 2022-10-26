#pragma once
#include <Trackable.h>
#include <vector>
#include "GraphicsSystem.h"
#include "Unit.h"
#include "EventSystem.h"

class UnitManager:public Trackable
{
public:
	UnitManager();
	~UnitManager();
	void addUnit(Unit* unitToAdd);
	void createUnit(Animation* unitAnimation, Vector2D startingPosition);
	void createUnit(GraphicsBuffer* unitAnimationSpriteSheet, Vector2D columnsAndRows, int numberOfFrames, int frameRate, bool shouldLoop, Vector2D startingPosition);
	void addAnimation(Animation* newUnitAnimation);
	void deleteUnit(Vector2D mousePosition);
	void deleteUnit(int i);
	void destroyUnit(Unit* unitToDestroy);
	Unit* getUnit(int i);
	void clearUnits();
	void UpdateUnitPosition(Vector2D newPosition); //updates position of unit at end of mUnitVector
	void UpdateAllUnits(double deltaTime); //update all units with deltaTime
	void drawAllUnits(GraphicsSystem* graphicsSystemToDrawWith); //draw all units with given GraphicsSystem
	void drawAllUnits(GraphicsSystem* graphicsSystemToDrawWith, float scale);
	void checkCollision(Unit* probablySnake);
	bool noEventCollisionCheck(Unit* unitToCheck);
	Unit* getUnitAtPosition(Vector2D position);
	bool isUnitAtPosition(Vector2D position);
	void clearAllUnits();
	void disableOrEnableAnimations();
	void flipAnimation();
	std::vector<Unit*> getUnitVector();

protected:
	std::vector<Unit*> mUnitVector;
	bool mAnimationsOn;
};