#include "Game.h"

Game* Game::mspGame = NULL;

Game::Game()
{
	mpInitializer = new AllegroInitializer();
	mpGraphicsSystem = new GraphicsSystem();
	mpInputSystem = new InputSystem();
	mpGraphicsBufferManager = new GraphicsBufferManager();
	mpUnitManager = new UnitManager();
	EventSystem::initInstance();
	mpGameListener = new GameListener();
	mpPickUpManager = new PickUpManager();
	mpLevelLoader = new LevelLoader();
	//mpFont = new Font(ASSET_PATH, FONT_FILE_NAME, 20, 0);

	//gameLoop variables

	this->mFrameRate = FRAME_RATE;
	this->mWidth = DISP_WIDTH;
	this->mHeight = DISP_HEIGHT;

	mKeepPlaying = true;
	mStartGame = false;
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
	mpGameListener = new GameListener();
	mpPickUpManager = new PickUpManager();
	mpLevelLoader = new LevelLoader();

	mKeepPlaying = true;
	mStartGame = false;
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
	//EventSystem::initInstance();
	//mpEventSystem = EventSystem::getInstance();
	//mpEventSystem->init();
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
	
	delete mpSnake;
	delete mpPickUpManager;
	delete mpLevelLoader;
	delete mpGameListener;
	
	delete mpFont;

	mpSnake = nullptr;
	mpInputSystem = nullptr;
	mpInitializer = nullptr;
	mpGraphicsSystem = nullptr;
	mpUnitManager = nullptr;
	mpGraphicsBufferManager = nullptr;

	EventSystem::cleanupInstance();
}
void Game::gameLoop() 
{
	PerformanceTracker* pPerformanceTracker = new PerformanceTracker();
	float targetTime = 1 / (double)mFrameRate; //time in seconds
	float targetTimeMS = targetTime * 1000; //time in MS
	initializeGameLoop();

	

	while (mKeepPlaying)
	{
		pPerformanceTracker->clearTracker("loop");
		pPerformanceTracker->startTracking("loop");
		//start timers
		Timer gameLoopTimer;
		gameLoopTimer.start();
		//
		input();
		update(targetTimeMS, mKeepPlaying, mStartGame);
		draw(mStartGame,targetTimeMS);
		//sleep
		gameLoopTimer.sleepUntilElapsed(targetTimeMS);
		pPerformanceTracker->stopTracking("loop");
		//std::cout << "MS for this loop: " << pPerformanceTracker->getElapsedTime("loop") << " Snake-speed for this loop " << testSnake->getSnakeSpeed() << std::endl;

	}
	delete pPerformanceTracker;
}
void Game::initializeGameLoop()
{
	//create graphicsBuffers
	mpGraphicsBufferManager->addGraphicsBuffer(ASSET_PATH, WOODS_FILE_NAME, "woods");
	mpGraphicsBufferManager->addGraphicsBuffer(CUSTOM_ASSET_PATH, SNAKE_HEAD_FILE_NAME, "snakeHead");
	mpGraphicsBufferManager->addGraphicsBuffer(CUSTOM_ASSET_PATH, SNAKE_TAIL_FILE_NAME, "snakeTail");
	mpGraphicsBufferManager->addGraphicsBuffer(CUSTOM_ASSET_PATH, WALL_FILE_NAME, "wall");
	mpGraphicsBufferManager->addGraphicsBuffer(CUSTOM_ASSET_PATH, POWER_UP_FILE_NAME, "powerUp");
	mpGraphicsBufferManager->addGraphicsBuffer(CUSTOM_ASSET_PATH, FOOD_FILE_NAME, "food");
	mpGraphicsBufferManager->addGraphicsBuffer(CUSTOM_ASSET_PATH, BLACK_SCREEN, "blackScreen");
	mpGraphicsBufferManager->addGraphicsBuffer(CUSTOM_ASSET_PATH, GREY_BACKGROUND, "backGround");

	Vector2D twoColumnsTwoRows = Vector2D(2, 2);

	mpPickUpManager->addAnimation(new Animation(mpGraphicsBufferManager->getGraphicsBuffer("food"), twoColumnsTwoRows, 4, 15, true) , UnitType::FOOD);
	mpPickUpManager->addAnimation(new Animation(mpGraphicsBufferManager->getGraphicsBuffer("powerUp"), twoColumnsTwoRows, 4, 15, true), UnitType::POWER_UP);
	mpPickUpManager->addAnimation(new Animation(mpGraphicsBufferManager->getGraphicsBuffer("powerUp"), twoColumnsTwoRows, 4, 15, true), UnitType::POWER_DOWN);

	Vector2D middle = Vector2D(400, 300);
	mpSnake = new Snake(new Animation(mpGraphicsBufferManager->getGraphicsBuffer("snakeHead"), NO_COLUMNS_OR_ROWS, ONE_FRAME, FRAME_RATE, NO_LOOP), new Animation(mpGraphicsBufferManager->getGraphicsBuffer("snakeTail"), NO_COLUMNS_OR_ROWS, ONE_FRAME, FRAME_RATE, NO_LOOP), middle, up);

	mpFont = new Font(ASSET_PATH, FONT_FILE_NAME, 20, 0);

	mpHUD = new HeadsUpDisplay(mpFont);

	mpLevelLoader->addLevel("testLevel.txt");
	mpLevelLoader->addLevel("Level1.txt");
	mpLevelLoader->addLevel("Level2.txt");
	mpLevelLoader->loadLevel(0,mpUnitManager,mpPickUpManager,mpSnake,mpGraphicsBufferManager);
}
void Game::input()
{
	//mpInputSystem->updateKeyboardAndMouseState();
	mpInputSystem->update();
}
void Game::update(float deltaTime, bool& keepPlaying, bool& startGame)
{	
	if (keepPlaying && startGame && !mEndGame)
	{
		mpPickUpManager->spawnPickUps();
		mpUnitManager->UpdateAllUnits(deltaTime);
		mpSnake->updateSnake(deltaTime);
		mpPickUpManager->UpdateAllUnits(deltaTime);
		mpSnake->checkCollision(mpSnake->getSnakeHead());
		mpUnitManager->checkCollision(mpSnake->getSnakeHead());
		mpPickUpManager->checkCollision(mpSnake->getSnakeHead());
		mpLevelLoader->incrementLevel();
		mpLevelLoader->incrementTime(deltaTime);
	}
}
void Game::draw(bool& startGame, float deltaTime)
{
	if (startGame)
	{
		mpGraphicsSystem->draw(mpGraphicsBufferManager->getGraphicsBuffer("backGround"), ORIGIN);
		mpUnitManager->drawAllUnits(mpGraphicsSystem);
		mpSnake->drawAllUnits(mpGraphicsSystem);
		float adjustScale = 1.25f;
		mpPickUpManager->drawAllUnits(mpGraphicsSystem,adjustScale);
		float targetTime = (deltaTime/1000);
		float frameRate = 1 / targetTime;
		mpHUD->drawHUD(mpGraphicsSystem,mpLevelLoader->getScore(),mpLevelLoader->getTime(),frameRate);
	}
	else if(!startGame && !mEndGame)
	{
		drawStartScreen();
	}
	else if (!startGame && mEndGame)
	{
		drawEndScreen();
	}
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
Snake* Game::getSnake()
{
	return mpSnake;
}
LevelLoader* Game::getLevelLoader()
{
	return mpLevelLoader;
}
void Game::stopGame()
{
	mKeepPlaying = false;
}
void Game::startGame()
{
	mStartGame = true;
}
void Game::endGame()
{
	mEndGame = true;
	mStartGame = false;
}
void Game::drawStartScreen()
{
	Vector2D middle = Vector2D(200, 300);
	Color white = Color(255, 255, 255, 0);
	mpGraphicsSystem->draw(mpGraphicsBufferManager->getGraphicsBuffer("blackScreen"), ORIGIN);
	mpGraphicsSystem->writeText(mpFont, middle, white, "Press SPACE to start");
}
void Game::drawEndScreen()
{
	Vector2D middle = Vector2D(200, 300);
	Color white = Color(255, 255, 255, 0);
	mpGraphicsSystem->draw(mpGraphicsBufferManager->getGraphicsBuffer("blackScreen"), ORIGIN);
	mpGraphicsSystem->writeText(mpFont, middle, white, "Press Escape to exit, Enter to restart");
}
void Game::restartGame()
{
	mEndGame = !mEndGame;
	mStartGame = !mStartGame;
}