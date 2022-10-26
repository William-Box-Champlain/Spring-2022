#include "PickUpManager.h"
PickUpManager::PickUpManager()
{
	mFoodChance = 0;
	mPowerDownChance = 0;
	mPowerUpChance = 0;
	mpFoodAnimation = NULL;
	mpPowerDownAnimation = NULL;
	mpPowerUpAnimation = NULL;

}
void PickUpManager::addAnimation(Animation* animation, UnitType animationType)
{
	switch (animationType)
	{
	case UnitType::POWER_UP:
		mpPowerUpAnimation = animation;
		break;
	case UnitType::POWER_DOWN:
		mpPowerDownAnimation = animation;
		break;
	case UnitType::FOOD:
		mpFoodAnimation = animation;
		break;
	default:
		break;
	}
}
void PickUpManager::setInvalidSpawnPosition(Vector2D invalidSpawnPoint)
{
	mInvalidSpawnPositions.push_back(invalidSpawnPoint);
}
PickUpManager::PickUpManager(int foodChance, int powerUpChance, int powerDownChance)
{
	mFoodChance = foodChance;
	mPowerUpChance = powerUpChance;
	mPowerDownChance = powerDownChance;
	mpFoodAnimation = NULL;
	mpPowerDownAnimation = NULL;
	mpPowerUpAnimation = NULL;
}
void PickUpManager::setFoodChance(int chance)
{
	mFoodChance = chance;
}
void PickUpManager::setPowerUpChance(int chance)
{
	mPowerUpChance = chance;
}
void PickUpManager::setPowerDownChance(int chance)
{
	mPowerDownChance = chance;
}
int PickUpManager::getFoodChance()
{
	return mFoodChance;
}
int PickUpManager::getPowerUpChance()
{
	return mPowerUpChance;
}
int PickUpManager::getPowerDownChance()
{
	return mPowerDownChance;
}
Unit* PickUpManager::getItem(UnitType type)
{
	for (auto unit : mUnitVector)
	{
		if (unit->getUnitType() == type)
		{
			return unit;
		}
	}
	return NULL;
}
void PickUpManager::spawnItemAtPos(UnitType type, Vector2D pos)
{
	if (type == UnitType::FOOD)
	{
		Unit* item = new Food(mpFoodAnimation, pos);
		addUnit(item);
	}
	else if (type == UnitType::POWER_UP)
	{
		Unit* item = new PowerUp(mpPowerUpAnimation, pos);
		addUnit(item);
	}
	else if (type == UnitType::POWER_DOWN)
	{
		Unit* item = new PowerDown(mpPowerDownAnimation, pos);
		addUnit(item);
	}
}
void PickUpManager::spawnItemAtPos(Unit* unit, UnitType type, Vector2D pos)
{
	if (type == UnitType::FOOD)
	{
		unit = new Food(mpFoodAnimation, pos);
		addUnit(unit);
	}
	else if (type == UnitType::POWER_UP)
	{
		unit = new PowerUp(mpFoodAnimation, pos);
		addUnit(unit);
	}
	else if (type == UnitType::POWER_DOWN)
	{
		unit = new PowerDown(mpFoodAnimation, pos);
		addUnit(unit);
	}
}
void PickUpManager::spawnPickUps(UnitManager* wallManager)
{
	if (mUnitVector.empty()) 
	{
		spawnAllPickups(wallManager);
		return;
	} 
	if (!checkForItem(UnitType::FOOD)) 
	{
		if (doesPickUpSpawn(UnitType::FOOD))spawnItemOfType(UnitType::FOOD, wallManager);
	}
	if (!checkForItem(UnitType::POWER_UP))
	{
		if (doesPickUpSpawn(UnitType::POWER_UP))spawnItemOfType(UnitType::POWER_UP, wallManager);
	}
	if (!checkForItem(UnitType::POWER_DOWN))
	{
		if (doesPickUpSpawn(UnitType::POWER_DOWN))spawnItemOfType(UnitType::POWER_DOWN, wallManager);
	}
}
bool PickUpManager::checkForItem(UnitType typeToCheck)
{
	for (auto unit:mUnitVector)
	{
		if (unit->getUnitType() == typeToCheck) return true;
	}
	return false;
}
void PickUpManager::spawnAllPickups(UnitManager* wallManager)
{
	spawnItemOfType(UnitType::FOOD, wallManager);
	spawnItemOfType(UnitType::POWER_UP, wallManager);
	spawnItemOfType(UnitType::POWER_DOWN, wallManager);
}
Vector2D PickUpManager::generateRandomPosition()
{
	std::random_device rd;
	std::mt19937 rng(rd());
	std::uniform_int_distribution<int> randWidth(mRandomRangeMin, mRandomRangeMaxX);
	std::uniform_int_distribution<int> randHeight(mRandomRangeMin, mRandomRangeMaxY);

	auto randomX = (randWidth(rng));
	auto randomY = (randHeight(rng));
	int xPixelPosition = (int)randomX * 40;
	int yPixelPosition = (int)randomY * 40;
	return Vector2D(xPixelPosition, yPixelPosition);
}
void PickUpManager::spawnItemOfType(UnitType typeToSpawn, UnitManager* wallManager)
{
	Vector2D tempVect = generateRandomPosition();
	while (wallManager->isUnitAtPosition(tempVect))
	{
		tempVect = generateRandomPosition();
	}
	switch (typeToSpawn)
	{
	case UnitType::POWER_UP:
	{
		Unit* temp = new PowerUp(mpPowerUpAnimation, tempVect);
		
		addUnit(temp);
		break;
	}
	case UnitType::POWER_DOWN:
	{
		Unit* temp = new PowerDown(mpPowerDownAnimation, tempVect);
		addUnit(temp);
		break;
	}
	case UnitType::FOOD:
	{
		Unit* temp = new Food(mpFoodAnimation, tempVect);
		addUnit(temp);
		break;
	}
	default:
		break;
	}
}
bool PickUpManager::doesPickUpSpawn(UnitType typeToCheck)
{
	std::random_device rd;
	std::mt19937 rng(rd());
	std::uniform_int_distribution<int> uni(mRandomRangeMin, mRandomRangeMax);

	auto randomInt = uni(rng);
	switch (typeToCheck)
	{
	case UnitType::DEFAULT:
		break;
	case UnitType::POWER_UP:
		if (randomInt <= mPowerUpChance) return true;
		break;
	case UnitType::POWER_DOWN:
		if (randomInt <= mPowerDownChance) return true;
		break;
	case UnitType::FOOD:
		if (randomInt <= mFoodChance) return true;
		break;
	default:
		break;
	}
	return false;
}
