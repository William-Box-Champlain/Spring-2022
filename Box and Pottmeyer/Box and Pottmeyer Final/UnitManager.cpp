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
	for (std::vector<Unit*>::iterator iter = mUnitVector.begin(); iter != mUnitVector.end(); ++iter)
	{
		Unit* pUnit = *iter;
		if (unitToDestroy == pUnit)
		{
			delete pUnit;
			mUnitVector.erase(iter);
		}
	}
}
Unit* UnitManager::getUnit(int i)
{
	return mUnitVector.at(i);
}
void UnitManager::clearUnits()
{
	for (std::vector<Unit*>::iterator iter = mUnitVector.begin(); iter != mUnitVector.end(); ++iter)
	{
		int index = std::distance(mUnitVector.begin(), iter);
		deleteUnit(index);
	}
}
void UnitManager::UpdateAllUnits(double deltaTime)
{
	if (mAnimationsOn)
	{
		for (auto unit:mUnitVector)
		{
			auto unitBeingFuckedWith = unit;
			if (unit->getIsAnimated())
			{
				unit->updateUnit(deltaTime);
			}

		}
	}
}
void UnitManager::drawAllUnits(GraphicsSystem* graphicsSystemToDrawWith)
{
	for (auto unit : mUnitVector)
	{
		graphicsSystemToDrawWith->draw(unit->getUnitPosition(), unit->drawUnit());
	}
}
void UnitManager::drawAllUnits(GraphicsSystem* graphicsSystemToDrawWith, float scale)
{
	for (auto unit : mUnitVector)
	{
		auto unitBeingFuckedWith = unit;
		graphicsSystemToDrawWith->draw(unit->getUnitPosition(), unit->drawUnit(), scale, scale);
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
std::vector<Unit*> UnitManager::getUnitVector()
{
	return mUnitVector;
}
void UnitManager::checkCollision(Unit* collidingUnit)
{
	if (!mUnitVector.empty()) 
	{
		Vector2D collidingUnitPosition = collidingUnit->getUnitPosition();
		for (auto unit : mUnitVector)
		{
			if (collidingUnit != unit)
			{
				float distance = collidingUnitPosition.getDistanceBetween(collidingUnitPosition, unit->getUnitPosition());
				if (distance < collidingUnit->getCurrentSprite()->getSpriteWidth())
				{
					unit->createCollisionEvent();
					if (unit->getUnitType() == UnitType::FOOD || unit->getUnitType() == UnitType::POWER_UP || unit->getUnitType() == UnitType::POWER_DOWN)
					{
						delete unit;
						auto iter = std::find(mUnitVector.begin(), mUnitVector.end(), unit);
						mUnitVector.erase(iter);
						break;
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
Unit* UnitManager::getUnitAtPosition(Vector2D position)
{
	//iterate through mUnitVector, and check if position is within the area of the unit at i, if true, return the unit at i.
	if (!mUnitVector.empty())
	{
		Vector2D topLeftCorner;
		Vector2D bottomRightCorner;
		for (auto p : mUnitVector)
		{
			topLeftCorner = p->getUnitPosition();
			bottomRightCorner = topLeftCorner + p->getCurrentSprite()->getSpriteDimensions();
			if (topLeftCorner.getX() <= position.getX() && position.getX() <= bottomRightCorner.getX() && topLeftCorner.getY() <= position.getY() && position.getY() <= bottomRightCorner.getY())
			{
				return p;
			}
		}
		return NULL;
	}
}

bool UnitManager::isUnitAtPosition(Vector2D position)
{
	if (!mUnitVector.empty())
	{
		Vector2D topLeftCorner;
		Vector2D bottomRightCorner;
		for (auto p : mUnitVector)
		{
			topLeftCorner = p->getUnitPosition();
			bottomRightCorner = topLeftCorner + p->getCurrentSprite()->getSpriteDimensions();
			if (topLeftCorner.getX() <= position.getX() && position.getX() <= bottomRightCorner.getX() && topLeftCorner.getY() <= position.getY() && position.getY() <= bottomRightCorner.getY())
			{
				return true;
			}
		}
		return false;
	}
}
