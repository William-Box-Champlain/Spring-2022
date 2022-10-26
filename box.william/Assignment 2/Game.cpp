#include "Game.h"

Game* gpGame = new Game();

Game::Game()
{
	mpInitializer = new AllegroInitializer();
	mpGraphicsSystem = new GraphicsSystem();
	mpInputSystem = new InputSystem();

	//gameLoop variables
	mpWoodsGraphicsBuffer = nullptr;
	mpSmurfGraphicsBuffer = nullptr;
	mpDeanGraphicsBuffer = nullptr;

	mpDeanSpriteAnimation = nullptr;
	mpSmurfSpriteAnimation = nullptr;

	mpAnimatedUnit = nullptr;

	this->mFrameRate = FRAME_RATE;
	this->mWidth = DISP_WIDTH;
	this->mHeight = DISP_HEIGHT;
}
Game::Game(int xResolution, int yResolution, int frameRate)
{
	this->mFrameRate = frameRate;
	this->mWidth = xResolution;
	this->mHeight = yResolution;
	mpGraphicsSystem = new GraphicsSystem();
	mpGraphicsSystem->graphicsSystemInit(mWidth, mHeight);
	mpInputSystem = new InputSystem();
	mpAnimatedUnit = NULL;
	mpWoodsGraphicsBuffer = NULL;
	mpDeanGraphicsBuffer = NULL;
	mpDeanSpriteAnimation = NULL;
	mpSmurfGraphicsBuffer = NULL;
	mpSmurfSpriteAnimation = NULL;
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
	mpGraphicsSystem->graphicsSystemCleanUp();
	//clean up graphics buffers
	delete mpWoodsGraphicsBuffer;
	delete mpDeanGraphicsBuffer;
	delete mpSmurfGraphicsBuffer;
	//clean up sprites
	delete mpDeanSpriteAnimation;
	delete mpSmurfSpriteAnimation;
	//clean up units
	delete mpAnimatedUnit;
	//clean up graphics and input system
	delete mpGraphicsSystem;

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
		update(gameLoopTimer.getElapsedTime(), keepPlaying);
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
	mpWoodsGraphicsBuffer = new GraphicsBuffer(ASSET_PATH, WOODS_FILE_NAME);
	mpSmurfGraphicsBuffer = new GraphicsBuffer(ASSET_PATH, SMURF_FILE_NAME);
	mpDeanGraphicsBuffer = new GraphicsBuffer(ASSET_PATH, DEAN_FILE_NAME);

	//Create animations (which will also create sprites)
	Vector2D columnsAndRows = Vector2D(4, 4);
	int numberOfFrames = 16;
	int frameRate = 60;
	bool doesAnimationLoop = true;

	mpSmurfSpriteAnimation = new Animation(mpSmurfGraphicsBuffer, columnsAndRows, numberOfFrames, frameRate, doesAnimationLoop);
	mpDeanSpriteAnimation = new Animation(mpDeanGraphicsBuffer, columnsAndRows, numberOfFrames, frameRate, doesAnimationLoop);

	Vector2D unitStartingPosition = Vector2D(400, 300);
	mpAnimatedUnit = new Unit(mpSmurfSpriteAnimation, unitStartingPosition);
	mpAnimatedUnit->addAnimation(mpDeanSpriteAnimation);
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
		mpAnimatedUnit->updateUnitPosition(mpInputSystem->getMousePosition());
	}	
	if (mpInputSystem->isKeyDown(ALLEGRO_KEY_ENTER)) //enter key function
	{
		mpAnimatedUnit->changeAnimationSet();
	}
	if (mpInputSystem->isKeyDown(ALLEGRO_KEY_F)) //speed up animation
	{
		if (!animationChanged)
		{
			mpSmurfSpriteAnimation->speedUpAnimation(1);
		}
		else
		{
			mpDeanSpriteAnimation->speedUpAnimation(1);
		}
	}
	if (mpInputSystem->isKeyDown(ALLEGRO_KEY_S)) //slow down animation
	{
		if (!animationChanged)
		{
			mpSmurfSpriteAnimation->slowDownAnimation(1);
		}
		else
		{
			mpDeanSpriteAnimation->slowDownAnimation(1);
		}
	}
	if (mpInputSystem->isKeyDown(ALLEGRO_KEY_ESCAPE)) // break loop
	{
		keepPlaying = false;
	}
	mpAnimatedUnit->updateUnit(deltaTime);
}
void Game::draw()
{
	mpGraphicsSystem->draw(mpWoodsGraphicsBuffer, ORIGIN);
	mpGraphicsSystem->draw(mpAnimatedUnit->getUnitPosition(), mpAnimatedUnit->drawUnit());
	mpGraphicsSystem->flip();
}