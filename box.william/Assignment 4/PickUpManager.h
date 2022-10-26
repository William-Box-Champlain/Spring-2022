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
	void spawnPickUps(); //Spawn food and pickups
	void addAnimation(Animation* animation, UnitType animationType);
private:
	int mFoodChance;
	int mPowerUpChance;
	int mPowerDownChance;

	bool checkForItem(UnitType typeToCheck);

	bool doesPickUpSpawn(UnitType typeToCheck);

	void spawnItemOfType(UnitType typeToSpawn);

	int mScreenWidth = 800;
	int mScreenHeight = 600;

	int mRandomRangeMin = 1;
	int mRandomRangeMax = 20;
	int mRandomRangeMaxX = 18;
	int mRandomRangeMaxY = 13;

	Animation* mpFoodAnimation;
	Animation* mpPowerUpAnimation;
	Animation* mpPowerDownAnimation;
};