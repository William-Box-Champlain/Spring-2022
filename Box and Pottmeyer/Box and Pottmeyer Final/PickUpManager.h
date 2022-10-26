#pragma once
#include "UnitManager.h"
#include "Food.h"
#include "PowerUp.h"
#include "PowerDown.h"
#include <random>
class PickUpManager:public UnitManager
{
public:
	PickUpManager();
	PickUpManager(int foodChance, int powerUpChance, int powerDownChance);
	void setFoodChance(int chance); //same as the two below
	void setPowerUpChance(int chance); //PowerUpChance is on a scale of 1 to 20
	void setPowerDownChance(int chance); //PowerDownChance is again on a scale of 1 to 20
	int getFoodChance();
	int getPowerUpChance();
	int getPowerDownChance();

	Unit* getItem(UnitType type);
	void spawnItemAtPos(UnitType type, Vector2D pos);
	void spawnItemAtPos(Unit* unit, UnitType type, Vector2D pos);

	void spawnPickUps(UnitManager* wallManager); //Spawn food and pickups
	void addAnimation(Animation* animation, UnitType animationType);
	void setInvalidSpawnPosition(Vector2D invalidSpawnPoint);
private:
	int mFoodChance;
	int mPowerUpChance;
	int mPowerDownChance;

	bool checkForItem(UnitType typeToCheck);

	bool doesPickUpSpawn(UnitType typeToCheck);

	void spawnItemOfType(UnitType typeToSpawn, UnitManager* wallManager);
	
	void spawnAllPickups(UnitManager* wallManager);

	Vector2D generateRandomPosition();

	int mScreenWidth = 800;
	int mScreenHeight = 600;

	int mRandomRangeMin = 1;
	int mRandomRangeMax = 20;
	int mRandomRangeMaxX = 18;
	int mRandomRangeMaxY = 13;

	Animation* mpFoodAnimation;
	Animation* mpPowerUpAnimation;
	Animation* mpPowerDownAnimation;

	std::vector<Vector2D> mInvalidSpawnPositions;
};