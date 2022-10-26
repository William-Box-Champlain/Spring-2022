#pragma once
#include "UnitManager.h"
#include "SnakeSegment.h"
enum direction {
	up,
	down,
	left,
	right
};
class Snake :public UnitManager
{
public:
	Snake();
	Snake(GraphicsBuffer* snakeHeadAnimationSpriteSheet, Vector2D headColumnsAndRows, int headNumberOfFrames, int headFrameRate, bool headShouldLoop, GraphicsBuffer* snakeBodyAnimationSpriteSheet, Vector2D columnsAndRows, int numberOfFrames, int frameRate, bool shouldLoop, Vector2D startingPosition, direction startingHeading);
	Snake(Animation* snakeHeadAnimation, Animation* snakeBodyAnimation, Vector2D startingPosition, direction startingHeading);
	~Snake();
	void addSegments(int numberOfNewSegments);
	void addSegment();
	void removeSegment();
	void removeSegments(int segmentsToRemove);
	void changeHeading(direction newHeading);
	void changeHeading(Vector2D newHeading);
	void updateSnake(double deltaTime);
	void modifySnakeSpeed(double movementDelta);
	void setSnakeSpeed(double movementDelta);
	void setHeadPosition(Vector2D headPosition);
	double getSnakeSpeed();
	int getSnakeLength();
	Unit* getSnakeHead();
protected:
	void cleanUp();
	Vector2D directionToVector(direction heading);
	Vector2D mHeadingVector;
	Vector2D mGhostTailPosition;
	double mMovementDelay;
	double mMovementDelayRemaining;
	Unit* mHead;
	Animation* mBodyAnimation;
};