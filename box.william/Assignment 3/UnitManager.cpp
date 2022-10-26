#include "UnitManager.h"
UnitManager::UnitManager()
{
	mAnimationsOn = true;
}
UnitManager::~UnitManager()
{
	clearAllUnits();
}
void UnitManager::clearAllUnits()
{
	for (int i = 0; i < mUnitVector.size(); i++)
	{
		delete mUnitVector.at(i);
	}
	mUnitVector.clear();
}
void UnitManager::addUnit(Unit* unitToAdd)
{
	mUnitVector.push_back(unitToAdd);
}
void UnitManager::createUnit(Animation* unitAnimation, Vector2D startingPosition)
{
	addUnit(new Unit(unitAnimation, startingPosition));
}
void UnitManager::createUnit(GraphicsBuffer* unitAnimationSpriteSheet, Vector2D columnsAndRows, int numberOfFrames, int frameRate, bool shouldLoop, Vector2D startingPosition)
{
	addUnit(new Unit(unitAnimationSpriteSheet, columnsAndRows, numberOfFrames, frameRate, shouldLoop, startingPosition));
}
void UnitManager::addAnimation(Animation* newUnitAnimation)
{
	mUnitVector.back()->addAnimation(newUnitAnimation);
}
void UnitManager::deleteUnit(Vector2D mousePosition)
{
	Vector2D temp;
	float distanceFromMouse;

	for (int i = 0; i < mUnitVector.size() - 1; i++)
	{
		Unit* pTempUnit = mUnitVector.at(i);
		distanceFromMouse = temp.getDistanceBetween(Vector2D(pTempUnit->getUnitPosition().getX() - (pTempUnit->getCurrentSprite()->getSpriteWidth() / 2), pTempUnit->getUnitPosition().getY() - (pTempUnit->getCurrentSprite()->getSpriteHeight())), mousePosition);
		if (distanceFromMouse <= (pTempUnit->getCurrentSprite()->getSpriteWidth() / 2 ))
		{
			destroyUnit(pTempUnit);
		}
	}
}
void UnitManager::deleteUnit(int i)
{
	delete mUnitVector.at(i);
	mUnitVector.erase(mUnitVector.begin()+i);
}
void UnitManager::destroyUnit(Unit* unitToDestroy)
{
	for (int i = 0; i < mUnitVector.size(); i++)
	{
		if (unitToDestroy == mUnitVector.at(i))
		{
			delete mUnitVector.at(i);
			mUnitVector.erase(mUnitVector.begin() + i);
			break;
		}
	}
}
Unit* UnitManager::getUnit(int i)
{
	return mUnitVector.at(i);
}
void UnitManager::clearUnits()
{
	for (int i = 0; i < mUnitVector.size(); i++)
	{
		deleteUnit(i);
	}
}
void UnitManager::UpdateAllUnits(double deltaTime)
{
	if (mAnimationsOn)
	{
		for (int i = 0; i < mUnitVector.size(); i++)
		{
			mUnitVector.at(i)->updateUnit(deltaTime);
		}
	}
}
void UnitManager::drawAllUnits(GraphicsSystem* graphicsSystemToDrawWith)
{
	for (int i = 0; i < mUnitVector.size(); i++)
	{
		graphicsSystemToDrawWith->draw(mUnitVector.at(i)->getUnitPosition(),mUnitVector.at(i)->drawUnit());
	}
}
void UnitManager::UpdateUnitPosition(Vector2D newPosition)
{
	mUnitVector.back()->updateUnitPosition(newPosition);
}
void UnitManager::disableOrEnableAnimations()
{
	mAnimationsOn = !mAnimationsOn;
}
void UnitManager::flipAnimation()
{
	mUnitVector.back()->changeAnimationSet();
}