#include "PickUpManager.h"
PickUpManager::PickUpManager()
{

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
PickUpManager::PickUpManager(int foodChance, int powerUpChance, int powerDownChance)
{
	mFoodChance = foodChance;
	mPowerUpChance = powerUpChance;
	mPowerDownChance = powerDownChance;
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
void PickUpManager::spawnPickUps()
{
	if (!checkForItem(UnitType::FOOD)) 
	{
		if (doesPickUpSpawn(UnitType::FOOD))spawnItemOfType(UnitType::FOOD);
	}
	if (!checkForItem(UnitType::POWER_UP))
	{
		if (doesPickUpSpawn(UnitType::POWER_UP))spawnItemOfType(UnitType::POWER_UP);
	}
	if (!checkForItem(UnitType::POWER_DOWN))
	{
		if (doesPickUpSpawn(UnitType::POWER_DOWN))spawnItemOfType(UnitType::POWER_DOWN);
	}
}
bool PickUpManager::checkForItem(UnitType typeToCheck)
{
	for (size_t i = 0; i < mUnitVector.size(); i++)
	{
		if (mUnitVector.at(i)->getUnitType() == typeToCheck) return true;
	}
	return false;
}
void PickUpManager::spawnItemOfType(UnitType typeToSpawn)
{
	std::random_device rd;
	std::mt19937 rng(rd());
	std::uniform_int_distribution<int> randWidth(mRandomRangeMin, mRandomRangeMaxX);
	std::uniform_int_distribution<int> randHeight(mRandomRangeMin, mRandomRangeMaxY);

	auto randomX = (randWidth(rng));
	auto randomY = (randHeight(rng));
	auto xPixelPosition = randomX * 40;
	auto yPixelPosition = randomY * 40;
	Vector2D tempVect = Vector2D(xPixelPosition, yPixelPosition);
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