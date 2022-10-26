#include "GameListener.h"
#include <EventSystem.h>
#include "GameEvents.h"
#include "MouseInputEvent.h"
#include "KeyboardInputEvent.h"
#include "MoveEvent.h"
#include "LevelEvents.h"
#include "SnakeEvent.h"
#include "Game.h"
#include "SoundEvent.h"
#include "ClickableEvent.h"

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
	pEventSystem->addListener((EventType)SOUND_EVENT, this);
	pEventSystem->addListener((EventType)CLICKABLE_EVENT, this);
}

GameListener::~GameListener()
{
}

void GameListener::handleEvent(const Event& gameEvent)
{
	if (gameEvent.getType() == INPUT_EVENT)
	{
		InputEvent tempInputEvent = (const InputEvent&)gameEvent;
		if (tempInputEvent.getType() == InputType::MOUSE)
		{
			MouseInputEvent tempMouseEvent = (const MouseInputEvent&)gameEvent;
			if (tempMouseEvent.getCode() == MouseOutputs::LEFT_MOUSE)
			{
				int xPos = (int)tempMouseEvent.getPositon().getX();
				int yPos = (int)tempMouseEvent.getPositon().getY();
				std::cout << "X pos:" << tempMouseEvent.getPositon().getX() << " Y pos:" << tempMouseEvent.getPositon().getY() << std::endl;
				std::cout << "Mouse Output:" << (int)tempMouseEvent.getCode() << std::endl;
				std::cout << Game::getGame()->getClickableManager()->getUnitAtPosition(tempMouseEvent.getPositon()) << std::endl;
				ClickableButton* tempButton = dynamic_cast<ClickableButton*>(Game::getGame()->getClickableManager()->getUnitAtPosition(tempMouseEvent.getPositon()));
				if (tempButton != NULL)
				{
					tempButton->clickButton();
				}
			}
		}
		else if (tempInputEvent.getType() == InputType::KEYBOARD)
		{

		}
		else if (tempInputEvent.getType() == InputType::DEFAULT)
		{

		}
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
			Game::getGame()->restartGame();
			Game::getGame()->getLevelLoader()->restartGame();
		}
		if (tempGameEvent.getLevelEvent() == LevelEventType::RESTART_GAME)
		{
			Game::getGame()->restartGame();
			Game::getGame()->getLevelLoader()->restartGame();
		}
		if (tempGameEvent.getLevelEvent() == LevelEventType::PAUSE_GAME)
		{
			Game::getGame()->pauseGame();
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
			Game::getGame()->getAudioManager()->playSound(2);
			Game::getGame()->restartGame();
			Game::getGame()->getLevelLoader()->restartGame();
		}
	}
	else if (gameEvent.getType() == MOVE_EVENT)
	{
		MoveEvent moveEvent = (const MoveEvent&)gameEvent;
		std::cout << "X direction: " << moveEvent.getDirection().getX() << std::endl;
		std::cout << "Y direction: " << moveEvent.getDirection().getY() << std::endl;
		Snake* tempSnake = Game::getGame()->getSnake();
		tempSnake->changeHeading(moveEvent.getDirection());
	}
	else if (gameEvent.getType() == COLLISION_EVENT)
	{
		CollisionEvent collisionEvent = (const CollisionEvent&)gameEvent;
		if (collisionEvent.getCollisionType() == CollisionType::FOOD)
		{
			auto tempSpeed = Game::getGame()->getSnake()->getSnakeSpeed();
			tempSpeed -= 50;
			Game::getGame()->getSnake()->setSnakeSpeed(tempSpeed);
			std::cout << "Food Collision" << std::endl;
			Game::getGame()->getLevelLoader()->incrementScore();
			std::cout << "Current Score: " << Game::getGame()->getLevelLoader()->getScore() << std::endl;
			Game::getGame()->getAudioManager()->playSound(1);
		}
		else if (collisionEvent.getCollisionType() == CollisionType::POWER_UP)
		{
			auto tempSpeed = Game::getGame()->getSnake()->getSnakeSpeed();
			tempSpeed += 50;
			Game::getGame()->getSnake()->setSnakeSpeed(tempSpeed);
			Game::getGame()->getAudioManager()->playSound(3);
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
	else if (gameEvent.getType() == SOUND_EVENT)
	{
		SoundEvent soundEvent = (const SoundEvent&)gameEvent;
		if (soundEvent.getSoundEffect() == SoundEffect::EAT_POWER_UP)
		{
			Game::getGame()->getAudioManager()->playSound(3);
		}
		else if (soundEvent.getSoundEffect() == SoundEffect::EAT_DOT)
		{
			Game::getGame()->getAudioManager()->playSound(1);
		}
		else if (soundEvent.getSoundEffect() == SoundEffect::DEATH)
		{
			Game::getGame()->getAudioManager()->playSound(2);
		}
		else if (soundEvent.getSoundEffect() == SoundEffect::CLICK)
		{
			Game::getGame()->getAudioManager()->playSound(0);
		}
	}
	else if(gameEvent.getType() == CLICKABLE_EVENT)
	{
		ClickableEvent clickableEvent = (const ClickableEvent&)gameEvent;
		if (clickableEvent.getType() == Clickables::START)
		{
			Game::getGame()->getAudioManager()->playSound(0);
			Game::getGame()->startGame();
		}
		else if (clickableEvent.getType() == Clickables::DIFFICULTY)
		{
			Game::getGame()->getAudioManager()->playSound(0);
			Game::getGame()->incrementDifficulty();
		}
		else if (clickableEvent.getType() == Clickables::SAVE)
		{
			//save game
			Game::getGame()->getAudioManager()->playSound(0);
			Game::getGame()->getLevelLoader()->saveGame();
		}
		else if (clickableEvent.getType() == Clickables::RESTART)
		{
			//restart level
			Game::getGame()->getAudioManager()->playSound(0);
			Game::getGame()->getLevelLoader()->loadLevel(Game::getGame()->getLevelLoader()->getCurrentLevel());
		}
		else if (clickableEvent.getType() == Clickables::QUIT)
		{
			Game::getGame()->getAudioManager()->playSound(0);
			Game::getGame()->endGame();
		}
		else if (clickableEvent.getType() == Clickables::LOAD)
		{
			//load save state
			Game::getGame()->getAudioManager()->playSound(0);
			Game::getGame()->getLevelLoader()->loadGame();
		}
		else if (clickableEvent.getType() == Clickables::LANGUAGE)
		{
			//change language
			Game::getGame()->getAudioManager()->playSound(0);
			Game::getGame()->swapLanguage();
		}
	}
}