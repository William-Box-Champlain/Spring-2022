#include "GameListener.h"
#include <EventSystem.h>
#include "GameEvents.h"
#include "InputEvent.h"
#include "MoveEvent.h"
#include "LevelEvents.h"
#include "SnakeEvent.h"
#include "Game.h"

GameListener::GameListener()
{
	EventSystem* pEventSystem = EventSystem::getInstance();
	//pEventSystem->initInstance();
	pEventSystem->init();
	pEventSystem->addListener((EventType)INPUT_EVENT, this);
	pEventSystem->addListener((EventType)MESSAGE_EVENT, this);
	pEventSystem->addListener((EventType)GAME_EVENT, this);
	pEventSystem->addListener((EventType)HUD_EVENT, this);
	pEventSystem->addListener((EventType)MOVE_EVENT, this);
	pEventSystem->addListener((EventType)LEVEL_EVENT, this);
	pEventSystem->addListener((EventType)SNAKE_EVENT, this);
	pEventSystem->addListener((EventType)COLLISION_EVENT, this);
}

GameListener::~GameListener()
{
}

void GameListener::handleEvent(const Event& gameEvent)
{
	if (gameEvent.getType() == INPUT_EVENT)
	{

	}
	else if (gameEvent.getType() == MESSAGE_EVENT)
	{

	}
	else if (gameEvent.getType() == LEVEL_EVENT)
	{
		
		LevelEvents tempGameEvent = (const LevelEvents&)gameEvent;
		if (tempGameEvent.getLevelEvent() == LevelEventType::CLOSE_GAME)
		{
			Game::getGame()->stopGame();
		}
		if (tempGameEvent.getLevelEvent() == LevelEventType::START_GAME)
		{
			Game::getGame()->startGame();
		}
		if (tempGameEvent.getLevelEvent() == LevelEventType::END_GAME)
		{
			Game::getGame()->endGame();
		}
		if (tempGameEvent.getLevelEvent() == LevelEventType::RESTART_GAME)
		{
			Game::getGame()->restartGame();
			Game::getGame()->getLevelLoader()->restartGame();
		}
		/*
		else if (tempGameEvent.getGameEvent() == GameEventType::CHANGE_LEVEL)
		{

		}
		else if (tempGameEvent.getGameEvent() == GameEventType::RESTART_LEVEL)
		{

		}
		*/
	}
	else if (gameEvent.getType() == SNAKE_EVENT)
	{
		SnakeEvent snakeEvent = (const SnakeEvent&)gameEvent;
		if (snakeEvent.getSnakeEvent() == SnakeEventType::GROW)
		{
			Snake* tempSnake = Game::getGame()->getSnake();
			tempSnake->addSegment();
		}
		else if (snakeEvent.getSnakeEvent() == SnakeEventType::SHRINK)
		{
			Snake* tempSnake = Game::getGame()->getSnake();
			tempSnake->removeSegment();
		}
		else if (snakeEvent.getSnakeEvent() == SnakeEventType::DIE)
		{
			Game::getGame()->restartGame();
			Game::getGame()->getLevelLoader()->restartGame();
		}
	}
	else if (gameEvent.getType() == MOVE_EVENT)
	{
		MoveEvent moveEvent = (const MoveEvent&)gameEvent;
		Snake* tempSnake = Game::getGame()->getSnake();
		Vector2D tempVector = moveEvent.getDirection();
		tempSnake->changeHeading(tempVector);
	}
	else if (gameEvent.getType() == COLLISION_EVENT)
	{
		CollisionEvent collisionEvent = (const CollisionEvent&)gameEvent;
		if (collisionEvent.getCollisionType() == CollisionType::FOOD)
		{
			Game::getGame()->getSnake()->addSegment();
			auto tempSpeed = Game::getGame()->getSnake()->getSnakeSpeed();
			tempSpeed -= 50;
			Game::getGame()->getSnake()->setSnakeSpeed(tempSpeed);
			std::cout << "Food Collision" << std::endl;
			Game::getGame()->getLevelLoader()->incrementScore();
			std::cout << "Current Score: " << Game::getGame()->getLevelLoader()->getScore() << std::endl;
		}
		else if (collisionEvent.getCollisionType() == CollisionType::POWER_UP)
		{
			auto tempSpeed = Game::getGame()->getSnake()->getSnakeSpeed();
			tempSpeed += 50;
			Game::getGame()->getSnake()->setSnakeSpeed(tempSpeed);
			std::cout << "Power Up Collision, Current Speed: " << tempSpeed << std::endl;
		}
		else if (collisionEvent.getCollisionType() == CollisionType::SNAKE)
		{
			EventSystem* eventSystem = EventSystem::getInstance();
			eventSystem->fireEvent(SnakeEvent(SnakeEventType::DIE));
			std::cout << "Snake Collision" << std::endl;
		}
		else if (collisionEvent.getCollisionType() == CollisionType::WALL)
		{
			EventSystem* eventSystem = EventSystem::getInstance();
			eventSystem->fireEvent(SnakeEvent(SnakeEventType::DIE));
			std::cout << "Wall Collision" << std::endl;
		}
	}
}