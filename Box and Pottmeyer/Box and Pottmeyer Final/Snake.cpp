#include "Snake.h"
Snake::Snake():UnitManager()
{
	mBodyAnimation = NULL;
	mHead = NULL;
	mMovementDelay = 0;
	mMovementDelayRemaining = mMovementDelay;
}
Snake::Snake(GraphicsBuffer* snakeHeadAnimationSpriteSheet, Vector2D headColumnsAndRows, int headNumberOfFrames,int headFrameRate, bool headShouldLoop, GraphicsBuffer* snakeBodyAnimationSpriteSheet, Vector2D columnsAndRows, int numberOfFrames, int frameRate, bool shouldLoop, Vector2D startingPosition, direction startingHeading)
{
	mHeadingVector = directionToVector(startingHeading);
	//mHead = new Unit(snakeHeadAnimationSpriteSheet, headColumnsAndRows, headNumberOfFrames, headFrameRate, headShouldLoop, startingPosition);
	mHead = new SnakeSegment(snakeHeadAnimationSpriteSheet, headColumnsAndRows, headNumberOfFrames, headFrameRate, headShouldLoop, startingPosition);
	mUnitVector.push_back(mHead);
	mBodyAnimation = new Animation(snakeBodyAnimationSpriteSheet, columnsAndRows, numberOfFrames, frameRate, shouldLoop);
}
Snake::Snake(Animation* snakeHeadAnimation, Animation* snakeBodyAnimation, Vector2D startingPosition, direction startingHeading)
{
	mHeadingVector = directionToVector(startingHeading);
	mHead = new SnakeSegment(snakeHeadAnimation, startingPosition);
	mUnitVector.push_back(mHead);
	mBodyAnimation = snakeBodyAnimation;
	mMovementDelay = 500.0f;
	mMovementDelayRemaining = 500.0f * mMovementScalar;
}
void Snake::addSegments(int numberOfNewSegments)
{
	for (int i = 0; i < (int)numberOfNewSegments; i++)
	{
		addSegment();
	}
}
void Snake::addSegment()
{
	Unit* temp = new SnakeSegment(mBodyAnimation, mGhostTailPosition);
	addUnit(temp);
}
void Snake::removeSegment()
{
	//delete mUnitVector.back();
	mUnitVector.erase(mUnitVector.end()-1);
}
void Snake::removeSegments(int segmentsToRemove)
{
	for (size_t i = 0; i < (unsigned int)segmentsToRemove; i++)
	{
		removeSegment();
	}
}
void Snake::changeHeading(direction newHeading)
{
	mHeadingVector = directionToVector(newHeading);
}
void Snake::changeHeading(Vector2D newHeading)
{
	if (newHeading == mHeadingVector * -1)
	{
		return;
	}
	mHeadingVector = newHeading;
}
Vector2D Snake::directionToVector(direction heading)
{
	Vector2D temp;
	switch (heading)
	{
	case direction::up:
		temp = Vector2D(0, -1);
		break;
	case direction::down:
		temp = Vector2D(0, 1);
		break;
	case direction::left:
		temp = Vector2D(-1, 0);
		break;
	case direction::right:
		temp = Vector2D(1, 0);
		break;
	case direction::nothing:
		temp = Vector2D(0, 0);
		break;
	}
	return temp;
}
void Snake::updateSnake(float deltaTime) 
{
	UpdateAllUnits(deltaTime);
	mMovementDelayRemaining -= deltaTime;
	if (mMovementDelayRemaining <= 0)
	{
		mGhostTailPosition = mUnitVector.back()->getUnitPosition();
		Vector2D temp;
		for (size_t i = mUnitVector.size() - 1; i > 0; i--)
		{
			temp = mUnitVector.at(i - 1)->getUnitPosition();
			mUnitVector.at(i)->updateUnitPosition(temp);
		}
		float headPositionScalar = mHead->getCurrentSprite()->getSpriteDimensions().getX();
		Vector2D headPositionDelta = mHeadingVector * headPositionScalar;
		Vector2D newHeadPosition = headPositionDelta + mHead->getUnitPosition();
		mHead->updateUnitPosition(newHeadPosition);
		mMovementDelayRemaining = mMovementDelay * mMovementScalar;
	}
}
Snake::~Snake()
{
	cleanUp();
}
void Snake::cleanUp()
{
	delete mBodyAnimation;
	mBodyAnimation = nullptr;
}
void Snake::modifySnakeSpeed(double movementDelta)
{
	mMovementDelay += movementDelta;
}
void Snake::setSnakeSpeed(double movementDelta)
{
	mMovementDelay = movementDelta;
}
double Snake::getSnakeSpeed()
{
	return mMovementDelay;
}
Unit* Snake::getSnakeHead()
{
	return mUnitVector.at(0);
}
void Snake::changeMovementScalar(double newMoveScalar)
{
	mMovementScalar = newMoveScalar;
	mMovementDelay = mMovementDelay * mMovementScalar;
}
int Snake::getSnakeLength()
{
	return mUnitVector.size();
}
void Snake::setHeadPosition(Vector2D newHeadPosition)
{
	mHead->updateUnitPosition(newHeadPosition);
}