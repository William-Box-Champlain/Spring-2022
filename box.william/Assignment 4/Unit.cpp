#include "Unit.h"
Unit::Unit()
{
	mUnitCurrentPosition = Vector2D(0.0f, 0.0f);
	mUnitType = UnitType::DEFAULT;
}
Unit::Unit(Animation* unitAnimation, Vector2D startingPosition)
{
	mUnitAnimationVector.push_back(unitAnimation);
	mUnitCurrentPosition = startingPosition;
}
Unit::Unit(GraphicsBuffer* unitAnimationSpriteSheet, Vector2D columnsAndRows, int numberOfFrames, int frameRate, bool shouldLoop, Vector2D startingPosition)
{
	mUnitAnimationVector.push_back(new Animation(unitAnimationSpriteSheet,columnsAndRows,numberOfFrames,frameRate,shouldLoop));
	mUnitCurrentPosition = startingPosition;
}
Unit::~Unit()
{
	for (int i = 0; i < (int)mUnitAnimationVector.size()-1; i++)
	{
		delete mUnitAnimationVector.at(i);
		mUnitAnimationVector.erase(mUnitAnimationVector.begin() + i);
	}
	mUnitAnimationVector.clear();
	mCurrentAnimation = 0;
}
void Unit::updateUnit(double deltaTime)
{
	//mUnitAnimation->updateAnimation(deltaTime);
	mUnitAnimationVector.at(mCurrentAnimation)->updateAnimation(deltaTime);
}
void Unit::updateUnit(Vector2D newPosition, double deltaTime) //Call mAnimation().updateAnimation() and change Unit.currentPosition to mouse-cursor
{
	mUnitCurrentPosition = newPosition;
	//mUnitAnimation->updateAnimation(deltaTime);
	mUnitAnimationVector.at(mCurrentAnimation)->updateAnimation(deltaTime);
}
void Unit::updateUnitPosition(Vector2D newPosition)
{
	mUnitCurrentPosition = newPosition;
}
Vector2D Unit::getUnitPosition()
{
	return mUnitCurrentPosition;
}
Sprite* Unit::drawUnit() //Draw Unit to GraphicsBuffer object
{
	//return mUnitAnimation->getCurrentSprite();
	return mUnitAnimationVector.at(mCurrentAnimation)->getCurrentSprite();
}
Sprite* Unit::getCurrentSprite()
{
	return mUnitAnimationVector.at(mCurrentAnimation)->getCurrentSprite();
}
void Unit::setAnimation(Animation* newAnimation) //Swap between animations
{
	mUnitAnimationVector.push_back(newAnimation);
	mCurrentAnimation = mUnitAnimationVector.size()-1;
}
void Unit::changeAnimationSet()
{
	int endOfVector = mUnitAnimationVector.size() - 1;
	if (mCurrentAnimation < endOfVector)
	{
		mCurrentAnimation++;
		//mUnitAnimation = mUnitAnimationVector.at(mCurrentAnimation);
	}
	else
	{
		mCurrentAnimation = 0;
		//mUnitAnimation = mUnitAnimationVector.at(mCurrentAnimation);
	}
}
void Unit::addAnimation(Animation* newAnimation)
{
	mUnitAnimationVector.push_back(newAnimation);
}
void Unit::addAnimation(GraphicsBuffer* newUnitAnimationSpriteSheet, Vector2D columnsAndRows, int numberOfFrames, int frameRate, bool shouldLoop)
{
	mUnitAnimationVector.push_back(new Animation(newUnitAnimationSpriteSheet, columnsAndRows, numberOfFrames, frameRate, shouldLoop));
}
void Unit::createCollisionEvent()
{

}
bool Unit::getIsAnimated()
{
	return mIsAnimated;
}
UnitType Unit::getUnitType()
{
	return mUnitType;
}