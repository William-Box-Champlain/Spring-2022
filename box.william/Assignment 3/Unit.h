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
	Unit(GraphicsBuffer* unitAnimationSpriteSheet, Vector2D columnsAndRows, int numberOfFrames, int frameRate, bool shouldLoop, Vector2D startingPosition);
	~Unit();
	void updateUnit(double deltaTime);
	void updateUnit(Vector2D newPosition, double deltaTime);
	void updateUnitPosition(Vector2D newPosition);
	Sprite* drawUnit();
	Sprite* getCurrentSprite();
	Vector2D getUnitPosition();
	void setAnimation(Animation* newAnimation);
	void addAnimation(Animation* newAnimation);
	void addAnimation(GraphicsBuffer* newUnitAnimationSpriteSheet, Vector2D columnsAndRows, int numberOfFrames, int frameRate, bool shouldLoop);
	void changeAnimationSet();
Protected:
	Vector2D mUnitCurrentPosition;
	std::vector<Animation*> mUnitAnimationVector;
	int mCurrentAnimation;
};