#include <Trackable.h>
#include <PerformanceTracker.h>
#include "GraphicsSystem.h"
#include "InputSystem.h"
#include "Animation.h"
#include "Unit.h"
#include "AllegroInitializer.h"

#pragma once

//Initialization settings

const int DISP_WIDTH = 800;
const int DISP_HEIGHT = 600;
const int FRAME_RATE = 60;

//Asset path and file names

const std::string ASSET_PATH = "..\\..\\common\\assets\\";

const std::string WOODS_FILE_NAME = "Woods.png";
const std::string SMURF_FILE_NAME = "smurf_sprites.png";
const std::string DEAN_FILE_NAME = "dean_sprites.png";

const Vector2D ORIGIN = Vector2D(0.0f, 0.0f);

class Game:public Trackable
{
public:
	Game();
	Game(int xResolution, int yResolution, int frameRate);
	~Game();
	void gameSystemsInitializer();
	void gameCleanUp();
	void gameLoop();

private:
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
	GraphicsBuffer* mpWoodsGraphicsBuffer;
	GraphicsBuffer* mpSmurfGraphicsBuffer;
	GraphicsBuffer* mpDeanGraphicsBuffer;

	Animation* mpDeanSpriteAnimation;
	Animation* mpSmurfSpriteAnimation;

	Unit* mpAnimatedUnit;
};
extern Game* gpGame;