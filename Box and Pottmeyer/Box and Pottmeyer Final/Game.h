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
#include "GhostManager.h"
#include "GameListener.h"
#include <EventSystem.h>
#include "LevelLoader.h"
#include "PickUpManager.h"
#include "HeadsUpDisplay.h"
#include "ClickableButton.h"
#include "Audio.h"
#include "OrderedSpritesManager.h"
#include "AnimationManager.h"

#pragma once

enum GameState
{
	PRE_GAME,
	RUNNING,
	PAUSED,
	POST_GAME,
	GAME_END
};

enum GameDifficulty
{
	EASY = 250,
	MEDIUM = 200,
	HARD = 150
};

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

//Credit goes to Gerrit Pottmeyer for providing the assets for both Food and Power Ups. (Food2.png and Pwr2.png)
struct FileData
{
	std::string SNAKE_HEAD_FILE_NAME = "";
	std::string SNAKE_TAIL_FILE_NAME = "";
	std::string FOOD_FILE_NAME = "";
	std::string WALL_FILE_NAME = "";
	std::string POWER_UP_FILE_NAME = "";
	std::string POWER_DOWN_FILE_NAME = "";
	std::string BLACK_SCREEN = "";
	std::string GREY_BACKGROUND = "";
	std::string START_BUTTON = "";
	std::string EXIT_BUTTON = "";
	std::string SAVE_BUTTON = "";
	std::string LOAD_BUTTON = "";
	std::string LANGUAGE_BUTTON = "";
	std::string GHOST_FILENAME = "";

	std::string AUDIO_BUTTON_FILE = "";
	std::string AUDIO_FOOD_FILE = "";
	std::string AUDIO_EXPLOSION_FILE = "";
	std::string AUDIO_POWERUP_FILE = "";

	std::string WOODS_FILE_NAME = "";
	std::string SMURF_FILE_NAME = "";
	std::string DEAN_FILE_NAME = "";

	std::string FONT_FILE_NAME = "";
	std::string CUSTOM_FONT_FILE_NAME = "";
};

//Asset path
const std::string ASSET_PATH = "..\\..\\common\\assets\\";
const std::string CUSTOM_ASSET_PATH = "..\\..\\Box and Pottmeyer\\Box and Pottmeyer Final\\Assets\\";
const std::string ASSET_DATA_PATH = "..\\..\\Box and Pottmeyer\\Box and Pottmeyer Final\\Data\\";

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
	UnitManager* getUnitManager();
	UnitManager* getClickableManager();
	LevelLoader* getLevelLoader();
	Audio* getAudioManager();
	FileData* getFileData();

	void setGameState(GameState newState);
	void stopGame();
	void startGame();
	void pauseGame();
	void endGame();
	void restartGame();
	void swapLanguage();
	void incrementDifficulty();

private:
	static Game* mspGame;

	bool mIsAurebesh;

	Game();
	Game(int xResolution, int yResolution, int frameRate);

	void initializeGameLoop();
	void input();
	void update(float deltaTime);
	void draw(float deltaTime);
	void drawStartScreen();
	void drawEndScreen();
	void drawPauseScreen();

	void difficultyCheck();

	void loadAssets(std::string fileName);

	int mFrameRate;
	int mWidth;
	int mHeight;
	int mActiveLanguage = 1;
	GameDifficulty mDifficulty = EASY;

	FileData* mpFileData;

	GameState mGameState;
	AllegroInitializer* mpInitializer;
	GraphicsSystem* mpGraphicsSystem;
	InputSystem* mpInputSystem;
	

	//gameLoop variables
	GameListener* mpGameListener;
	//EventSystem* mpEventSystem;

	GraphicsBufferManager* mpGraphicsBufferManager;
	OrderedSpritesManager* mpOrderedSpritesManager;
	AnimationManager* mpAnimationManager;

	UnitManager* mpWallManager;
	Snake* mpSnake;
	GhostManager* mpGhostManager;
	PickUpManager* mpPickUpManager;
	UnitManager* mpClickableButtonManager;

	LevelLoader* mpLevelLoader;
	HeadsUpDisplay* mpHUD;

	Font* mpCourFont;
	Font* mpAureFont;
	Audio* mpAudio;
};