#include <Trackable.h>
#include <PerformanceTracker.h>
#include "GraphicsSystem.h"
#include "InputSystem.h"
#include "Animation.h"
#include "Unit.h"
#include "AllegroInitializer.h"
#include "GraphicsBufferManager.h"
#include "UnitManager.h"

#pragma once

//Initialization settings

const int DISP_WIDTH = 800;
const int DISP_HEIGHT = 600;
const int FRAME_RATE = 60;

const Vector2D COLUMNS_AND_ROWS = Vector2D(4, 4);
const int NUMBER_OF_FRAMES = 16;
const bool DOES_ANIMATION_LOOP = true;

//Asset path and file names

const std::string ASSET_PATH = "..\\..\\common\\assets\\";

const std::string WOODS_FILE_NAME = "Woods.png";
const std::string SMURF_FILE_NAME = "smurf_sprites.png";
const std::string DEAN_FILE_NAME = "dean_sprites.png";

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

private:
	static Game* mspGame;

	Game();
	Game(int xResolution, int yResolution, int frameRate);

	void initializeGameLoop();
	void input();
	void update(float deltaTime, bool& keepPlaying);
	void draw();
	int mFrameRate;
	int mWidth;
	int mHeight;
	AllegroInitializer* mpInitializer;
	GraphicsSystem* mpGraphicsSystem;
	InputSystem* mpInputSystem;

	//gameLoop variables
	GraphicsBufferManager* mpGraphicsBufferManager;
	UnitManager* mpUnitManager;
};