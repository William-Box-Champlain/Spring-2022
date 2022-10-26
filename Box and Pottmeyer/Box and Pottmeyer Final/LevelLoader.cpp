#include "LevelLoader.h"
LevelLoader::LevelLoader()
{
	mMapDimensions = Vector2D(20, 15);
	mCurrentTime = 0;
}
LevelLoader::~LevelLoader()
{
	mpUnitManager = nullptr;
	mpGraphicsBufferManager = nullptr;
	mpPickUpManager = nullptr;
	mpSnake = nullptr;

}
void LevelLoader::addLevel(std::string fileName)
{
	mLevelFiles.push_back(fileName);
}
void LevelLoader::loadLevel(int level, UnitManager* gameUnitManager, PickUpManager* gamePickUpManager, Snake* gameSnake, GraphicsBufferManager* gameGraphicsBufferManager, GhostManager* gameGhostManager, AnimationManager* gameAnimationManager)
{
	mpUnitManager = gameUnitManager;
	mpPickUpManager = gamePickUpManager;
	mpSnake = gameSnake;
	mpGraphicsBufferManager = gameGraphicsBufferManager;
	mCurrentLevel = level;
	mpGhostManager = gameGhostManager;
	mpAnimationManager = gameAnimationManager;
	if ((unsigned int)level > (unsigned int)mLevelFiles.size()-1)
	{
		endGame();
		return;
	}
	std::string levelFile = mLevelFiles.at(level);
	cout << levelFile << endl;
	std::ifstream input(levelFile);
	//assert(input);
	if (input.good())
	{
		std::string key;
		while (!input.eof())
		{
			input >> key;
			if (key == "pickUps")
			{
				while (key != "endOfPickUps")
				{
					input >> key;
					if (key == "foodValue")
					{
						input >> key;
						mCurrentFoodValue = stoi(key);
					}
					if (key == "targetScore")
					{
						input >> key;
						mWinningScore = stoi(key);
					}
					if (key == "foodChance")
					{
						input >> key;
						gamePickUpManager->setFoodChance(stoi(key));
					}
					if (key == "powerUpChance")
					{
						input >> key;
						gamePickUpManager->setPowerUpChance(stoi(key));
					}
					if (key == "powerDownChance")
					{
						input >> key;
						gamePickUpManager->setPowerDownChance(stoi(key));
					}
				}
			}
			if (key == "snake")
			{
				while (key != "endOfSnake")
				{
					input >> key;
					if (key == "snakeSpeed")
					{
						input >> key;
						gameSnake->setSnakeSpeed(stoi(key));
					}
					else if (key == "snakeLength")
					{
						input >> key;
						gameSnake->addSegments(stoi(key));
					}
				}
			}
			if (key == "map")
			{
				while (key != "endOfMap")
				{
					for (int i = 0; i < mMapDimensions.getY(); i++) //15
					{
						for (int j = 0; j < mMapDimensions.getX(); j++)//20
						{
							input >> key;
							//cout << key << endl;
							if (key != "endOfMap")
							{
							/*if (key == "1")
							{*/
								int keyInt = stoi(key);
								Vector2D tempPosition = Vector2D(j * 40, i * 40);
								switch (keyInt)
								{
								case 0: //floor

									break;
								case 1: //wall
								{
									gamePickUpManager->setInvalidSpawnPosition(tempPosition);
									gameUnitManager->addUnit(new Wall(gameAnimationManager->getAnimation("wallAnimation"), tempPosition));
									//cout << "created wall" << i << "x" << j << endl;
									break;
								}
								case 2: //snake
								{
									gameSnake->setHeadPosition(tempPosition);
									break;
								}
								case 3: //ghost movement
								{
									//record position into vector
									gameGhostManager->addMovePos(tempPosition);
									break;
								}
								case 4: //ghost position
								{
									gameGhostManager->addMovePos(tempPosition);
									gameGhostManager->addUnit(new Ghost(gameAnimationManager->getAnimation("ghostAnimation"), tempPosition));
									break;
								}
								default:
									break;
								}
							/*}*/
								
							}
						}
					}
				}
			}
		}

	}
	input.close();
}
void LevelLoader::loadLevel(int level)
{
	loadLevel(level, mpUnitManager, mpPickUpManager, mpSnake, mpGraphicsBufferManager, mpGhostManager,mpAnimationManager);
}
void LevelLoader::saveGame(UnitManager* gameUnitManager, PickUpManager* gamePickUpManager, Snake* gameSnake, GhostManager* gameGhostManager)
{
	std::ofstream output("saveData.txt", ios::out);
	//assert(input);
	if (output.good())
	{
		output << "levelNum " << to_string(mCurrentLevel) << endl;

		output << "pickUps" << endl;
		output << "foodValue " << to_string(mCurrentFoodValue) << endl;
		output << "targetScore " << to_string(mWinningScore) << endl;
		output << "foodChance " << (gamePickUpManager->getFoodChance()) << endl;
		output << "powerUpChance " << to_string(gamePickUpManager->getPowerUpChance()) << endl;
		output << "powerDownChance " << to_string(gamePickUpManager->getPowerDownChance()) << endl;

		output << "foodPos " << to_string(gamePickUpManager->getItem(UnitType::FOOD)->getUnitPosition().getX()) << " " << to_string(gamePickUpManager->getItem(UnitType::FOOD)->getUnitPosition().getY()) << endl;
		output << "pwrUpPos " << to_string(gamePickUpManager->getItem(UnitType::POWER_UP)->getUnitPosition().getX()) << " " << to_string(gamePickUpManager->getItem(UnitType::POWER_UP)->getUnitPosition().getY()) << endl;
		output << "pwrDownPos " << to_string(gamePickUpManager->getItem(UnitType::POWER_DOWN)->getUnitPosition().getX()) << " " << to_string(gamePickUpManager->getItem(UnitType::POWER_DOWN)->getUnitPosition().getY()) << endl;

		output << "endOfPickUps" << endl;

		output << "files" << endl;
		output << "endOfFiles" << endl;

		output << "snake" << endl;
		output << "score " << mCurrentScore << endl;
		output << "snakeSpeed " << gameSnake->getSnakeSpeed() << endl;
		output << "snakeLength " << gameSnake->getSnakeLength() << endl;
		output << "snakePos " << to_string(gameSnake->getSnakeHead()->getUnitPosition().getX()) << " " << to_string(gameSnake->getSnakeHead()->getUnitPosition().getY()) << endl;
		output << "endOfSnake" << endl;
	}
	output.close();
}
void LevelLoader::saveGame()
{
	saveGame(mpUnitManager, mpPickUpManager, mpSnake, mpGhostManager);
}
void LevelLoader::incrementScore()
{
	mCurrentScore += mCurrentFoodValue;
}
void LevelLoader::incrementLevel()
{
	if (mCurrentScore == mWinningScore)
	{
		std::cout << "Current Level: " << mCurrentLevel << std::endl;
		cleanUpLevel();
		int nextLevel = mCurrentLevel + 1;
		loadLevel(nextLevel, mpUnitManager, mpPickUpManager, mpSnake, mpGraphicsBufferManager,mpGhostManager,mpAnimationManager);
	}
}
void LevelLoader::loadGame(UnitManager* gameUnitManager, PickUpManager* gamePickUpManager, Snake* gameSnake, GraphicsBufferManager* gameGraphicsBufferManager, GhostManager* gameGhostManager, AnimationManager* animationManager)
{
	cleanUpLevel();
	mpUnitManager = gameUnitManager;
	mpPickUpManager = gamePickUpManager;
	mpSnake = gameSnake;
	mpGraphicsBufferManager = gameGraphicsBufferManager;
	//mCurrentLevel = level;
	mpGhostManager = gameGhostManager;
	
	std::string levelFile = "saveData.txt";
	cout << levelFile << endl;
	std::ifstream input(levelFile);
	//assert(input);
	if (input.good())
	{
		std::string key;
		while (!input.eof())
		{
			input >> key;
			if (key == "levelNum")
			{
				input >> mCurrentLevel;
				loadLevel(mCurrentLevel);
			}
			if (key == "pickUps")
			{
				while (key != "endOfPickUps")
				{
					input >> key;
					if (key == "foodValue")
					{
						input >> key;
						mCurrentFoodValue = stoi(key);
					}
					if (key == "targetScore")
					{
						input >> key;
						mWinningScore = stoi(key);
					}
					if (key == "foodChance")
					{
						input >> key;
						gamePickUpManager->setFoodChance(stoi(key));
					}
					if (key == "powerUpChance")
					{
						input >> key;
						gamePickUpManager->setPowerUpChance(stoi(key));
					}
					if (key == "powerDownChance")
					{
						input >> key;
						gamePickUpManager->setPowerDownChance(stoi(key));
					}
					if (key == "foodPos")
					{
						int x, y;
						input >> key;
						x = stoi(key);
						input >> key;
						y = stoi(key);
						gamePickUpManager->spawnItemAtPos(UnitType::FOOD, Vector2D(x, y));
					}
					if (key == "pwrUpPos")
					{
						int x, y;
						input >> key;
						x = stoi(key);
						input >> key;
						y = stoi(key);
						gamePickUpManager->spawnItemAtPos(UnitType::POWER_UP, Vector2D(x, y));
					}
					if (key == "pwrDownPos")
					{
						int x, y;
						input >> key;
						x = stoi(key);
						input >> key;
						y = stoi(key);
						gamePickUpManager->spawnItemAtPos(UnitType::POWER_DOWN, Vector2D(x, y));
					}
				}
			}
			if (key == "snake")
			{
				while (key != "endOfSnake")
				{
					input >> key;
					if (key == "score")
					{
						int score;
						input >> score;
						mCurrentScore = score;
					}
					else if (key == "snakeSpeed")
					{
						input >> key;
						gameSnake->setSnakeSpeed(stoi(key));
					}
					else if (key == "snakeLength")
					{
						input >> key;
						if (stoi(key) <= 0 || stoi(key) >= 2)
						{
							gameSnake->addSegments(stoi(key));
						}
					}
					else if (key == "snakePos")
					{
						float x, y;
						input >> x >> y;
						gameSnake->setHeadPosition(Vector2D(x, y));
					}
				}
			}
		}

	}
	input.close();
}
void LevelLoader::loadGame()
{
	loadGame(mpUnitManager, mpPickUpManager, mpSnake, mpGraphicsBufferManager, mpGhostManager,mpAnimationManager);
}
int LevelLoader::getScore()
{
	return mCurrentScore;
}
int LevelLoader::getCurrentLevel()
{
	return mCurrentLevel;
}
void LevelLoader::cleanUpLevel()
{
	
	//reduce snake down to just the head
	/*std::cout << "clean up Snake" << std::endl;
	int snakeLength = mpSnake->getSnakeLength() - 2;
	mpSnake->removeSegments(snakeLength);*/
	//remove walls from level
	std::cout << "clean up walls" << std::endl;
	mpUnitManager->clearAllUnits();
	//remove pickups from level
	std::cout << "clean up pick ups" << std::endl;
	mpPickUpManager->clearAllUnits();

	std::cout << "clean up ghosts" << std::endl;
	mpGhostManager->clearAllUnits();
}
void LevelLoader::endGame()
{
	EventSystem* eventSystem = EventSystem::getInstance();
	eventSystem->fireEvent(LevelEvents(LevelEventType::END_GAME));
}
void LevelLoader::restartGame()
{
	cleanUpLevel();
	mCurrentLevel = 0;
	mCurrentScore = 0;
	loadLevel(mCurrentLevel, mpUnitManager, mpPickUpManager, mpSnake, mpGraphicsBufferManager,mpGhostManager,mpAnimationManager);
}
float LevelLoader::getTime()
{
	return mCurrentTime;
}
void LevelLoader::incrementTime(float deltaTime)
{
	mCurrentTime += deltaTime;
}