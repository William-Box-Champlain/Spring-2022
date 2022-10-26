#pragma once
#include <vector>
#include <string>
#include <fstream>

#include "GraphicsBuffer.h"
#include "GraphicsBufferManager.h"
#include "UnitManager.h"
#include "PickUpManager.h"
#include "Snake.h"
#include "Wall.h"

#include "LevelEvents.h"
class LevelLoader
{
public:
	LevelLoader();
	~LevelLoader();
	void addLevel(std::string levelFileName);
	void loadLevel(int level, UnitManager* gameUnitManager, PickUpManager* gamePickUpManager, Snake* gameSnake, GraphicsBufferManager* gameGraphicsBufferManager);
	int getScore();
	void incrementScore();
	void incrementLevel();
	void incrementTime(double deltaTime);
	float getTime();
	void restartGame();

private:
	void cleanUpLevel();
	void endGame();
	std::vector<std::string> mLevelFiles;
	Vector2D mMapDimensions;
	int mWinningScore;
	int mCurrentScore;
	int mCurrentLevel;
	int mCurrentFoodValue = 1;
	double mCurrentTime;
	UnitManager* mpUnitManager;
	PickUpManager* mpPickUpManager;
	Snake* mpSnake;
	GraphicsBufferManager* mpGraphicsBufferManager;
};