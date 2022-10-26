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
void LevelLoader::loadLevel(int level, UnitManager* gameUnitManager, PickUpManager* gamePickUpManager, Snake* gameSnake, GraphicsBufferManager* gameGraphicsBufferManager)
{
	mpUnitManager = gameUnitManager;
	mpPickUpManager = gamePickUpManager;
	mpSnake = gameSnake;
	mpGraphicsBufferManager = gameGraphicsBufferManager;
	mCurrentLevel = level;
	if (level > mLevelFiles.size()-1)
	{
		endGame();
		return;
	}
	std::string levelFile = mLevelFiles.at(level);
	cout << levelFile << endl;
	std::ifstream input(levelFile);
	assert(input);
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
									gameUnitManager->addUnit(new Wall(new Animation(gameGraphicsBufferManager->getGraphicsBuffer("wall"), Vector2D(1, 1), 1, 1, false),tempPosition));
									//cout << "created wall" << i << "x" << j << endl;
									break;
								}
								case 2: //snake
								{
									gameSnake->setHeadPosition(tempPosition);
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
		loadLevel(nextLevel, mpUnitManager, mpPickUpManager, mpSnake, mpGraphicsBufferManager);
	}
}
int LevelLoader::getScore()
{
	return mCurrentScore;
}
void LevelLoader::cleanUpLevel()
{
	
	//reduce snake down to just the head
	std::cout << "clean up Snake" << std::endl;
	int snakeLength = mpSnake->getSnakeLength() - 2;
	mpSnake->removeSegments(snakeLength);
	//remove walls from level
	std::cout << "clean up walls" << std::endl;
	mpUnitManager->clearAllUnits();
	//remove pickups from level
	std::cout << "clean up pick ups" << std::endl;
	mpPickUpManager->clearAllUnits();
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
	loadLevel(mCurrentLevel, mpUnitManager, mpPickUpManager, mpSnake, mpGraphicsBufferManager);
}
float LevelLoader::getTime()
{
	return mCurrentTime;
}
void LevelLoader::incrementTime(double deltaTime)
{
	mCurrentTime += deltaTime;
}