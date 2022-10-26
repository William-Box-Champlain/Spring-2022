#include "GhostManager.h"

GhostManager::GhostManager()
{
	mMovementDelay = 500;
	mMovementDelayRemaining = mMovementDelay;
}
GhostManager::~GhostManager()
{
}
void GhostManager::updateGhost(double deltaTime)
{
	UpdateAllUnits(deltaTime);
 	mMovementDelayRemaining -= deltaTime;
	if (mMovementDelayRemaining <= 0)
	{
		for (auto ghost: mUnitVector)
		{
			if (checkMove(ghost,UP))
			{
				move(ghost,UP);
				break;
			}
			if (checkMove(ghost,RIGHT))
			{
				move(ghost,RIGHT);
				break;
			}
			if (checkMove(ghost, DOWN))
			{
				move(ghost, DOWN);
				break;
			}
			if (checkMove(ghost, LEFT))
			{
				move(ghost, LEFT);
				break;
			}
		}
		mMovementDelayRemaining = mMovementDelay * mMovementScalar;
	}
}

bool GhostManager::isPosValid(Vector2D newPos)
{
	Vector2D tempPos;
	for (size_t j = mGhostMovePos.size() - 1; j > 0; j--)
	{
		tempPos = mGhostMovePos.at(j);
		if (newPos == tempPos)
		{
			return true;
		}
	}
	return false;
}

bool GhostManager::checkMove(Unit* ghost, Direction direction) //check if next position is both valid and not the same as the last position
{
	//determine where ghost will be moving to
	Vector2D directionVector;
	float movementScalar = ghost->getCurrentSprite()->getSpriteDimensions().getX();
	Vector2D movementVector;
	Vector2D endPosition;
	switch (direction)
	{
	case UP:
		directionVector = Vector2D(0, -1);
		break;
	case DOWN:
		directionVector = Vector2D(0, 1);
		break;
	case LEFT:
		directionVector = Vector2D(-1, 0);
		break;
	case RIGHT:
		directionVector = Vector2D(1, 0);
		break;
	}
	movementVector = directionVector * movementScalar;
	endPosition = ghost->getUnitPosition() + movementVector;
	//check if end position is valid
	Ghost* tempGhost = dynamic_cast<Ghost*>(ghost);
	if (endPosition == tempGhost->getPreviousPos()) return false;
	for (auto position:mGhostMovePos)
	{
		if (position == endPosition)
		{
			tempGhost = nullptr;
			return true;
		}
	}
	return false;
}

void GhostManager::move(Unit* ghost, Direction direction)
{
	//determine where ghost will be moving to
	Vector2D directionVector;
	float movementScalar = ghost->getCurrentSprite()->getSpriteDimensions().getX();
	Vector2D movementVector;
	Vector2D endPosition;
	switch (direction)
	{
	case UP:
		directionVector = Vector2D(0, -1);
		break;
	case DOWN:
		directionVector = Vector2D(0, 1);
		break;
	case LEFT:
		directionVector = Vector2D(-1, 0);
		break;
	case RIGHT:
		directionVector = Vector2D(1, 0);
		break;
	}
	movementVector = directionVector * movementScalar;
	endPosition = ghost->getUnitPosition() + movementVector;
	//set mPreviousPosition to equal current position
	Ghost* tempGhost = dynamic_cast<Ghost*>(ghost);
	tempGhost->setPreviousPos(ghost->getUnitPosition());
	tempGhost = nullptr;
	//move to position;
	ghost->updateUnitPosition(endPosition);
}

void GhostManager::addMovePos(Vector2D newPos)
{
	mGhostMovePos.push_back(newPos);
}

void GhostManager::changeMovementScalar(double newMoveScalar)
{
	mMovementScalar = newMoveScalar;
	mMovementDelay = mMovementDelay * mMovementScalar;
}
