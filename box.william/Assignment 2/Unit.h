#include <Trackable.h>
#include <Vector2D.h>
#include "Animation.h"
#include "GraphicsSystem.h"
#pragma once
class Unit:public Trackable
{
public:
	Unit();
	Unit(Animation* unitAnimation, Vector2D startingPosition);
	~Unit();
	void updateUnit(double deltaTime);
	void updateUnit(Vector2D newPosition, double deltaTime);
	void updateUnitPosition(Vector2D newPosition);
	Sprite* drawUnit();
	Vector2D getUnitPosition();
	void setAnimation(Animation* newAnimation);
	void addAnimation(Animation* newAnimation);
	void changeAnimationSet();
private:
	Vector2D mUnitCurrentPosition;
	Animation* mUnitAnimation;
	std::vector<Animation*> mUnitAnimationVector;
	int mCurrentAnimation;
};