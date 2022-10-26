#include "Unit.h"
Unit::Unit()
{
	mUnitAnimation = NULL;
	mUnitCurrentPosition = Vector2D(0.0f, 0.0f);
}
Unit::Unit(Animation* unitAnimation, Vector2D startingPosition)
{
	mUnitAnimation = unitAnimation;
	mUnitAnimationVector.push_back(unitAnimation);
	mUnitCurrentPosition = startingPosition;
}
Unit::~Unit()
{
	mUnitAnimation = nullptr;
	mUnitAnimationVector.clear();
	mCurrentAnimation = 0;
}
void Unit::updateUnit(double deltaTime)
{
	mUnitAnimation->updateAnimation(deltaTime);
}
void Unit::updateUnit(Vector2D newPosition, double deltaTime) //Call mAnimation().updateAnimation() and change Unit.currentPosition to mouse-cursor
{
	mUnitCurrentPosition = newPosition;
	mUnitAnimation->updateAnimation(deltaTime);
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
	return mUnitAnimation->getCurrentSprite();
}
void Unit::setAnimation(Animation* newAnimation) //Swap between animations
{
	mUnitAnimation = newAnimation;
}
void Unit::changeAnimationSet()
{
	int endOfVector = mUnitAnimationVector.size() - 1;
	if (mCurrentAnimation < endOfVector)
	{
		mCurrentAnimation++;
		mUnitAnimation = mUnitAnimationVector.at(mCurrentAnimation);
	}
	else
	{
		mCurrentAnimation = 0;
		mUnitAnimation = mUnitAnimationVector.at(mCurrentAnimation);
	}
}
void Unit::addAnimation(Animation* newAnimation)
{
	mUnitAnimationVector.push_back(newAnimation);
}