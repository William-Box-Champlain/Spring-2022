#pragma once
#include "Ghost.h"
#include "UnitManager.h"

#include <vector>
#include <Vector2D.h>

enum Direction {
	UP,
	DOWN,
	LEFT,
	RIGHT
};

class GhostManager :public UnitManager
{
public:
	GhostManager();
	~GhostManager();

	void updateGhost(double deltaTime);
	bool isPosValid(Vector2D newPos);
	void addMovePos(Vector2D newPos);
	void changeMovementScalar(double newMoveScalar);

private:

	bool checkMove(Unit* ghost, Direction direction);
	void move(Unit* ghost, Direction direction);

	double mMovementDelay;
	double mMovementDelayRemaining;
	double mMovementScalar = 1;
	Vector2D mPreviousPosition;
	std::vector<Vector2D>mGhostMovePos;
};