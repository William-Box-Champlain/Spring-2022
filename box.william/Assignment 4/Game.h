#include <Trackable.h>
#include <PerformanceTracker.h>
#include "GraphicsSystem.h"
#include "InputSystem.h"
#include "Animation.h"
#include "Unit.h"
#include "AllegroInitializer.h"
#include "GraphicsBufferManager.h"
#include "UnitManager.h"
#include "Snake.h"
#include "GameListener.h"
#include <EventSystem.h>
#include "LevelLoader.h"
#include "PickUpManager.h"
#include "HeadsUpDisplay.h"

#pragma once

//Initialization settings

const int DISP_WIDTH = 800;
const int DISP_HEIGHT = 600;
const int FRAME_RATE = 60;

const Vector2D COLUMNS_AND_ROWS = Vector2D(4, 4);
const int NUMBER_OF_FRAMES = 16;
const bool DOES_ANIMATION_LOOP = true;

const Vector2D NO_COLUMNS_OR_ROWS = Vector2D(1, 1);
const int ONE_FRAME = 1;
const bool NO_LOOP = false;

//Asset path and file names

const std::string ASSET_PATH = "..\\..\\common\\assets\\";

const std::string CUSTOM_ASSET_PATH = "..\\..\\box.william\\Assignment 4\\Assets\\";

//Credit goes to Gerrit Pottmeyer for providing the assets for both Food and Power Ups. (Food2.png and Pwr2.png)

const std::string SNAKE_HEAD_FILE_NAME = "SnakeHead.png";
const std::string SNAKE_TAIL_FILE_NAME = "SnakeTail.png";
const std::string FOOD_FILE_NAME = "Food2.png";
const std::string WALL_FILE_NAME = "Wall.png";
const std::string POWER_UP_FILE_NAME = "Pwr2.png";
const std::string BLACK_SCREEN = "BlackScreen.png";
const std::string GREY_BACKGROUND = "BackGround.png";

const std::string WOODS_FILE_NAME = "Woods.png";
const std::string SMURF_FILE_NAME = "smurf_sprites.png";
const std::string DEAN_FILE_NAME = "dean_sprites.png";

const std::string FONT_FILE_NAME = "cour.ttf";

const Vector2D ORIGIN = Vector2D(0.0f, 0.0f);

class Game:public Trackable
{
public:
	~Game();
	static void createGame();
	static void createGame(int xResolution, int yResolution, int frameRate);
	void gameSystemsInitializer();
	void gameCleanUp();
	void gameLoop();
	static Game* getGame();
	Snake* getSnake();
	LevelLoader* getLevelLoader();

	void stopGame();
	void startGame();
	void endGame();
	void restartGame();

private:
	static Game* mspGame;

	bool mKeepPlaying;
	bool mStartGame;
	bool mEndGame;

	Game();
	Game(int xResolution, int yResolution, int frameRate);

	void initializeGameLoop();
	void input();
	void update(float deltaTime, bool& keepPlaying, bool& startGame);
	void draw(bool& startGame, float deltaTime);
	void drawStartScreen();
	void drawEndScreen();

	int mFrameRate;
	int mWidth;
	int mHeight;
	AllegroInitializer* mpInitializer;
	GraphicsSystem* mpGraphicsSystem;
	InputSystem* mpInputSystem;
	

	//gameLoop variables
	GameListener* mpGameListener;
	//EventSystem* mpEventSystem;

	GraphicsBufferManager* mpGraphicsBufferManager;
	UnitManager* mpUnitManager;

	Snake* mpSnake;

	LevelLoader* mpLevelLoader;
	PickUpManager* mpPickUpManager;
	HeadsUpDisplay* mpHUD;

	Font* mpFont;
};