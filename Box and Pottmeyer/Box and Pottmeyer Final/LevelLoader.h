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
#include "GhostManager.h"
#include "AnimationManager.h"

#include "LevelEvents.h"
class LevelLoader
{
public:
	LevelLoader();
	~LevelLoader();
	void addLevel(std::string levelFileName);
	void loadLevel(int level, UnitManager* gameUnitManager, PickUpManager* gamePickUpManager, Snake* gameSnake, GraphicsBufferManager* gameGraphicsBufferManager, GhostManager* gameGhostManager, AnimationManager* animationManager);
	void loadLevel(int level);
	void saveGame(UnitManager* gameUnitManager, PickUpManager* gamePickUpManager, Snake* gameSnake, GhostManager* gameGhostManager);
	void saveGame();
	void loadGame(UnitManager* gameUnitManager, PickUpManager* gamePickUpManager, Snake* gameSnake, GraphicsBufferManager* gameGraphicsBufferManager, GhostManager* gameGhostManager, AnimationManager* gameAnimationManager);
	void loadGame();
	int getScore();
	int getCurrentLevel();
	void incrementScore();
	void incrementLevel();
	void incrementTime(float deltaTime);
	float getTime();
	void restartGame();

private:
	void cleanUpLevel();
	void endGame();
	std::vector<std::string> mLevelFiles;
	//std::vector<Vector2D> mGhostMovePos;
	Vector2D mMapDimensions;
	int mWinningScore;
	int mCurrentScore;
	int mCurrentLevel;
	int mCurrentFoodValue = 1;
	float mCurrentTime;
	UnitManager* mpUnitManager;
	PickUpManager* mpPickUpManager;
	Snake* mpSnake;
	GhostManager* mpGhostManager;
	GraphicsBufferManager* mpGraphicsBufferManager;
	AnimationManager* mpAnimationManager;
};