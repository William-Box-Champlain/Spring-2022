#include "Game.h"

Game* Game::mspGame = NULL;

Game::Game()
{
	mpInitializer = new AllegroInitializer();
	mpGraphicsSystem = new GraphicsSystem();
	mpInputSystem = new InputSystem();
	mpGraphicsBufferManager = new GraphicsBufferManager();
	mpUnitManager = new UnitManager();

	//gameLoop variables

	this->mFrameRate = FRAME_RATE;
	this->mWidth = DISP_WIDTH;
	this->mHeight = DISP_HEIGHT;
}
Game::Game(int xResolution, int yResolution, int frameRate)
{
	this->mFrameRate = frameRate;
	this->mWidth = xResolution;
	this->mHeight = yResolution;
	mpInitializer = new AllegroInitializer();
	mpGraphicsSystem = new GraphicsSystem();
	mpInputSystem = new InputSystem();
	mpGraphicsBufferManager = new GraphicsBufferManager();
	mpUnitManager = new UnitManager();
}
Game::~Game()
{
	gameCleanUp();
}
void Game::gameSystemsInitializer()
{
	mpInitializer->Initialize();
	mpGraphicsSystem->graphicsSystemInit(mWidth, mHeight);
	mpInputSystem->inputSystemInitializer();
}
void Game::gameCleanUp()
{
	//mpGraphicsSystem->graphicsSystemCleanUp();
	//clean up graphics buffers
	//clean up sprites
	//clean up units
	//clean up graphics and input system
	delete mpInputSystem;
	delete mpInitializer;
	//delete functionality on the below classes are not working properly
	delete mpGraphicsSystem;
	delete mpUnitManager;
	delete mpGraphicsBufferManager;

	mpInputSystem = nullptr;
	mpInitializer = nullptr;
	mpGraphicsSystem = nullptr;
	mpUnitManager = nullptr;
	mpGraphicsBufferManager = nullptr;
}
void Game::gameLoop() 
{
	PerformanceTracker* pPerformanceTracker = new PerformanceTracker();
	bool keepPlaying = true;
	float targetTime = 1 / (double)mFrameRate; //time in seconds
	float targetTimeMS = targetTime * 1000; //time in MS
	initializeGameLoop();

	while (keepPlaying)
	{
		pPerformanceTracker->clearTracker("loop");
		pPerformanceTracker->startTracking("loop");
		//start timers
		Timer gameLoopTimer;
		gameLoopTimer.start();
		//input();
		update(targetTimeMS, keepPlaying);
		draw();
		//sleep
		gameLoopTimer.sleepUntilElapsed(targetTimeMS);
		pPerformanceTracker->stopTracking("loop");
		std::cout << "MS for this loop: " << pPerformanceTracker->getElapsedTime("loop") << std::endl;

	}
}
void Game::initializeGameLoop()
{
	//create graphicsBuffers
	mpGraphicsBufferManager->addGraphicsBuffer(ASSET_PATH, WOODS_FILE_NAME, "woods");
	mpGraphicsBufferManager->addGraphicsBuffer(ASSET_PATH, SMURF_FILE_NAME, "smurf");
	mpGraphicsBufferManager->addGraphicsBuffer(ASSET_PATH, DEAN_FILE_NAME, "deanSmurf");
}
void Game::input()
{
	mpInputSystem->updateKeyboardAndMouseState();
}
void Game::update(float deltaTime, bool& keepPlaying)
{
	bool animationChanged = false;
	if (mpInputSystem->isMouseDown(1)) //left click function
	{
		mpUnitManager->createUnit(mpGraphicsBufferManager->getGraphicsBuffer("smurf"), COLUMNS_AND_ROWS, NUMBER_OF_FRAMES, FRAME_RATE, DOES_ANIMATION_LOOP, mpInputSystem->getMousePosition());
		mpUnitManager->addAnimation(new Animation(mpGraphicsBufferManager->getGraphicsBuffer("deanSmurf"), COLUMNS_AND_ROWS, NUMBER_OF_FRAMES, FRAME_RATE, DOES_ANIMATION_LOOP));
	}
	if (mpInputSystem->isMouseDown(2)) //right click function
	{
		mpUnitManager->deleteUnit(mpInputSystem->getMousePosition());
	}
	if (mpInputSystem->isKeyDown(ALLEGRO_KEY_ENTER)) //enter key function
	{

	}
	if (mpInputSystem->isKeyDown(ALLEGRO_KEY_F)) //speed up animation
	{
		if (!animationChanged)
		{
			
		}
		else
		{
			
		}
	}
	if (mpInputSystem->isKeyDown(ALLEGRO_KEY_S)) //slow down animation
	{
		if (!animationChanged)
		{
			
		}
		else
		{
			
		}
	}
	if (mpInputSystem->isKeyDown(ALLEGRO_KEY_ESCAPE)) // break loop
	{
		keepPlaying = false;
	}
	if (mpInputSystem->isKeyDown(ALLEGRO_KEY_SPACE))
	{
		mpUnitManager->disableOrEnableAnimations();
	}
	if (mpInputSystem->isKeyDown(ALLEGRO_KEY_ENTER))
	{
		mpUnitManager->flipAnimation();
	}
	mpUnitManager->UpdateAllUnits(deltaTime);
}
void Game::draw()
{
	mpGraphicsSystem->draw(mpGraphicsBufferManager->getGraphicsBuffer("woods"), ORIGIN);
	//mpGraphicsSystem->draw(mpAnimatedUnit->getUnitPosition(), mpAnimatedUnit->drawUnit());
	mpUnitManager->drawAllUnits(mpGraphicsSystem);
	mpGraphicsSystem->flip();
}
Game* Game::getGame()
{
	if (mspGame == NULL)
	{
		createGame(DISP_WIDTH, DISP_HEIGHT, FRAME_RATE);
	}
	return mspGame;
}
void Game::createGame()
{
	if (!mspGame)
	{
		mspGame = new Game();
	}
}
void Game::createGame(int xResolution, int yResolution, int frameRate)
{
	if (!mspGame)
	{
		mspGame = new Game(xResolution, yResolution, frameRate);
	}
}