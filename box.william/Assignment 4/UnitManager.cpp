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
	//for (int i = 0; i < (int)mUnitVector.size()-1; i++)
	//{
	//	//delete mUnitVector.at(i);
	//	mUnitVector.erase(mUnitVector.begin() + i);
	//}
	for (auto p : mUnitVector)
	{
		delete p;
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

	for (int i = 0; i < (int)mUnitVector.size() - 1; i++)
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
	for (int i = 0; i < (int)mUnitVector.size()-1; i++)
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
	for (int i = 0; i < (int)mUnitVector.size()-1; i++)
	{
		deleteUnit(i);
	}
}
void UnitManager::UpdateAllUnits(double deltaTime)
{
	if (mAnimationsOn)
	{
		for (int i = 0; i < (int)mUnitVector.size()-1; i++)
		{
			if (mUnitVector.at(i)->getIsAnimated())
			{
				mUnitVector.at(i)->updateUnit(deltaTime);
			}
		}
	}
}
void UnitManager::drawAllUnits(GraphicsSystem* graphicsSystemToDrawWith)
{
	for (int i = 0; i < (int)mUnitVector.size()-1; i++)
	{
		graphicsSystemToDrawWith->draw(mUnitVector.at(i)->getUnitPosition(),mUnitVector.at(i)->drawUnit());
	}
}
void UnitManager::drawAllUnits(GraphicsSystem* graphicsSystemToDrawWith, float scale)
{
	for (int i = 0; i < (int)mUnitVector.size() - 1; i++)
	{
		graphicsSystemToDrawWith->draw(mUnitVector.at(i)->getUnitPosition(), mUnitVector.at(i)->drawUnit(),scale,scale);
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
void UnitManager::checkCollision(Unit* collidingUnit)
{
	if (!mUnitVector.empty()) 
	{
		Vector2D collidingUnitPosition = collidingUnit->getUnitPosition();
		for (size_t i = 0; i < mUnitVector.size() - 1; i++)
		{
			if (collidingUnit != mUnitVector.at(i))
			{
				float distance = collidingUnitPosition.getDistanceBetween(collidingUnitPosition, mUnitVector.at(i)->getUnitPosition());
				if (distance < collidingUnit->getCurrentSprite()->getSpriteWidth())
				{
					mUnitVector.at(i)->createCollisionEvent();
					if (mUnitVector.at(i)->getUnitType() == UnitType::FOOD || mUnitVector.at(i)->getUnitType() == UnitType::POWER_UP || mUnitVector.at(i)->getUnitType() == UnitType::POWER_DOWN)
					{
						delete mUnitVector.at(i);
						mUnitVector.erase(mUnitVector.begin() + i);
					}
					//std::cout << "Collision Event" << std::endl;
				}
			}
		}
	}
}
bool UnitManager::noEventCollisionCheck(Unit* unitToCheck)
{
	if (!mUnitVector.empty())
	{
		Vector2D collidingUnitPosition = unitToCheck->getUnitPosition();
		for (size_t i = 0; i < mUnitVector.size() - 1; i++)
		{
			if (unitToCheck != mUnitVector.at(i))
			{
				float distance = collidingUnitPosition.getDistanceBetween(collidingUnitPosition, mUnitVector.at(i)->getUnitPosition());
				if (distance < unitToCheck->getCurrentSprite()->getSpriteWidth())
				{
					return true;
					//std::cout << "Collision Event" << std::endl;
				}
			}
		}
	}
	return false;
}