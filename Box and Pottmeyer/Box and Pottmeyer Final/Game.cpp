#include "Game.h"



//SDL now can be included

Game* Game::mspGame = NULL;

Game::Game()
{
	mpInitializer = new AllegroInitializer();
	mpGraphicsSystem = new GraphicsSystem();
	mpInputSystem = new InputSystem();
	mpGraphicsBufferManager = new GraphicsBufferManager();
	mpWallManager = new UnitManager();
	EventSystem::initInstance();
	mpGameListener = new GameListener();
	mpPickUpManager = new PickUpManager();
	mpLevelLoader = new LevelLoader();
	mpCourFont = nullptr;
	mpAureFont = nullptr;
	mpGhostManager = new GhostManager();
	mpClickableButtonManager = new UnitManager();
	mpAudio = new Audio();
	mpOrderedSpritesManager = new OrderedSpritesManager();
	mpAnimationManager = new AnimationManager();
	mpHUD = NULL;
	mpFileData = new FileData;

	//gameLoop variables

	this->mFrameRate = FRAME_RATE;
	this->mWidth = DISP_WIDTH;
	this->mHeight = DISP_HEIGHT;

	mGameState = GameState::PRE_GAME;

	mIsAurebesh = false;
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
	mpWallManager = new UnitManager();
	mpGameListener = new GameListener();
	mpPickUpManager = new PickUpManager();
	mpLevelLoader = new LevelLoader();
	mpGhostManager = new GhostManager();
	mpClickableButtonManager = new UnitManager();
	mpAudio = new Audio();
	mpOrderedSpritesManager = new OrderedSpritesManager();
	mpAnimationManager = new AnimationManager();
	mpHUD = NULL;
	mpFileData = new FileData;

	mGameState = GameState::PRE_GAME;
	mIsAurebesh = false;
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
	delete mpWallManager;
	delete mpGraphicsBufferManager;
	delete mpGhostManager;
	delete mpClickableButtonManager;
	delete mpHUD;
	delete mpAudio;

	delete mpSnake;
	delete mpPickUpManager;
	delete mpLevelLoader;
	delete mpGameListener;

	//delete mpAnimationManager; some weird bug is happening here, no idea what.
	delete mpOrderedSpritesManager; 
	
	delete mpCourFont;
	delete mpAureFont;

	delete mpFileData;

	
	mpInputSystem = nullptr;
	mpInitializer = nullptr;
	mpGraphicsSystem = nullptr;
	mpWallManager = nullptr;
	mpGraphicsBufferManager = nullptr;
	mpGhostManager = nullptr;
	mpClickableButtonManager = nullptr;
	mpHUD = nullptr;
	mpAudio = nullptr;

	mpOrderedSpritesManager = nullptr;
	//mpAnimationManager = nullptr;

	mpSnake = nullptr;
	mpPickUpManager = nullptr;
	mpLevelLoader = nullptr;
	mpGameListener = nullptr;

	mpCourFont = nullptr;
	mpAureFont = nullptr;

	mpFileData = nullptr;

	EventSystem::cleanupInstance();
}
void Game::gameLoop() 
{
	PerformanceTracker* pPerformanceTracker = new PerformanceTracker();
	float targetTime = 1 / (float)mFrameRate; //time in seconds
	float targetTimeMS = targetTime * 1000; //time in MS
	initializeGameLoop();
	mGameState = PAUSED;
	while (mGameState != GameState::GAME_END)
	{
		pPerformanceTracker->clearTracker("loop");
		pPerformanceTracker->startTracking("loop");
		//start timers
		Timer gameLoopTimer;
		gameLoopTimer.start();
		//
 		input();
		update(targetTimeMS);
		draw(targetTimeMS);
		//sleep
		gameLoopTimer.sleepUntilElapsed(targetTimeMS);
		pPerformanceTracker->stopTracking("loop");
		//std::cout << "MS for this loop: " << pPerformanceTracker->getElapsedTime("loop") << " Snake-speed for this loop " << testSnake->getSnakeSpeed() << std::endl;

	}
	delete pPerformanceTracker;
}
void Game::initializeGameLoop()
{
	loadAssets("Assets.txt");

	//create graphicsBuffers
	mpGraphicsBufferManager->addGraphicsBuffer(ASSET_PATH, mpFileData->WOODS_FILE_NAME, "woods");
	mpGraphicsBufferManager->addGraphicsBuffer(CUSTOM_ASSET_PATH, mpFileData->SNAKE_HEAD_FILE_NAME, "snakeHead");
	mpGraphicsBufferManager->addGraphicsBuffer(CUSTOM_ASSET_PATH, mpFileData->SNAKE_TAIL_FILE_NAME, "snakeTail");
	mpGraphicsBufferManager->addGraphicsBuffer(CUSTOM_ASSET_PATH, mpFileData->WALL_FILE_NAME, "wall");
	mpGraphicsBufferManager->addGraphicsBuffer(CUSTOM_ASSET_PATH, mpFileData->POWER_UP_FILE_NAME, "powerUp");
	mpGraphicsBufferManager->addGraphicsBuffer(CUSTOM_ASSET_PATH, mpFileData->FOOD_FILE_NAME, "food");
	mpGraphicsBufferManager->addGraphicsBuffer(CUSTOM_ASSET_PATH, mpFileData->BLACK_SCREEN, "blackScreen");
	mpGraphicsBufferManager->addGraphicsBuffer(CUSTOM_ASSET_PATH, mpFileData->GREY_BACKGROUND, "backGround");
	mpGraphicsBufferManager->addGraphicsBuffer(CUSTOM_ASSET_PATH, mpFileData->GHOST_FILENAME, "ghost");
	mpGraphicsBufferManager->addGraphicsBuffer(CUSTOM_ASSET_PATH, mpFileData->START_BUTTON, "startButton");
	mpGraphicsBufferManager->addGraphicsBuffer(CUSTOM_ASSET_PATH, mpFileData->EXIT_BUTTON, "exitButton");
	mpGraphicsBufferManager->addGraphicsBuffer(CUSTOM_ASSET_PATH, mpFileData->SAVE_BUTTON, "saveButton");
	mpGraphicsBufferManager->addGraphicsBuffer(CUSTOM_ASSET_PATH, mpFileData->LOAD_BUTTON, "loadButton");
	mpGraphicsBufferManager->addGraphicsBuffer(CUSTOM_ASSET_PATH, mpFileData->LANGUAGE_BUTTON, "languageButton");

	Vector2D twoColumnsTwoRows = Vector2D(2, 2);

	//create orderedSprites
	mpOrderedSpritesManager->addMultipleSprites(mpGraphicsBufferManager->getGraphicsBuffer("food"), twoColumnsTwoRows, 4, "foodOrderedSprites");
	mpOrderedSpritesManager->addMultipleSprites(mpGraphicsBufferManager->getGraphicsBuffer("powerUp"), twoColumnsTwoRows, 4, "powerUpOrderedSprites");
	mpOrderedSpritesManager->addMultipleSprites(mpGraphicsBufferManager->getGraphicsBuffer("powerUp"), twoColumnsTwoRows, 4, "powerDownOrderedSprites");
	mpOrderedSpritesManager->addMultipleSprites(mpGraphicsBufferManager->getGraphicsBuffer("snakeTail"), NO_COLUMNS_OR_ROWS, ONE_FRAME, "snakeTailOrderedSprites");
	mpOrderedSpritesManager->addMultipleSprites(mpGraphicsBufferManager->getGraphicsBuffer("snakeHead"), twoColumnsTwoRows, 4, "snakeHeadOrderedSprites");
	mpOrderedSpritesManager->addMultipleSprites(mpGraphicsBufferManager->getGraphicsBuffer("wall"), NO_COLUMNS_OR_ROWS, ONE_FRAME, "wallOrderedSprites");
	mpOrderedSpritesManager->addMultipleSprites(mpGraphicsBufferManager->getGraphicsBuffer("ghost"), NO_COLUMNS_OR_ROWS, ONE_FRAME, "ghostOrderedSprites");

	//create animations from those orderedSprites
	mpAnimationManager->addAnimation(mpOrderedSpritesManager->getOrderedSprites("snakeTailOrderedSprites"), FRAME_RATE, NO_LOOP, "snakeTailAnimation");
	mpAnimationManager->addAnimation(mpOrderedSpritesManager->getOrderedSprites("foodOrderedSprites"), 15, true, "foodSpriteAnimation");
	mpAnimationManager->addAnimation(mpOrderedSpritesManager->getOrderedSprites("powerDownOrderedSprites"), 15, true,"powerDownAnimation");
	mpAnimationManager->addAnimation(mpOrderedSpritesManager->getOrderedSprites("snakeHeadOrderedSprites"), 2, true,"snakeHeadAnimation");
	mpAnimationManager->addAnimation(mpOrderedSpritesManager->getOrderedSprites("powerUpOrderedSprites"), 15, true, "powerUpAnimation");
	mpAnimationManager->addAnimation(mpOrderedSpritesManager->getOrderedSprites("wallOrderedSprites"), FRAME_RATE, NO_LOOP, "wallAnimation");
	mpAnimationManager->addAnimation(mpOrderedSpritesManager->getOrderedSprites("ghostOrderedSprites"), FRAME_RATE, NO_LOOP, "ghostAnimation");

	//create the buttons
	mpClickableButtonManager->addUnit(new ClickableButton(mpAnimationManager->getAnimation("snakeTailAnimation"), Vector2D(80, 80), Clickables::START));
	mpClickableButtonManager->addUnit(new ClickableButton(mpAnimationManager->getAnimation("snakeTailAnimation"), Vector2D(80, 160), Clickables::DIFFICULTY));
	mpClickableButtonManager->addUnit(new ClickableButton(mpAnimationManager->getAnimation("snakeTailAnimation"), Vector2D(80, 240), Clickables::SAVE));
	mpClickableButtonManager->addUnit(new ClickableButton(mpAnimationManager->getAnimation("snakeTailAnimation"), Vector2D(80, 320), Clickables::LOAD));
	mpClickableButtonManager->addUnit(new ClickableButton(mpAnimationManager->getAnimation("snakeTailAnimation"), Vector2D(80, 400), Clickables::LANGUAGE));
	mpClickableButtonManager->addUnit(new ClickableButton(mpAnimationManager->getAnimation("snakeTailAnimation"), Vector2D(80, 480), Clickables::QUIT));

	//load up the animations into the pickupManager
	mpPickUpManager->addAnimation(mpAnimationManager->getAnimation("foodSpriteAnimation"), UnitType::FOOD);
	mpPickUpManager->addAnimation(mpAnimationManager->getAnimation("powerUpAnimation"), UnitType::POWER_UP);
	mpPickUpManager->addAnimation(mpAnimationManager->getAnimation("powerDownAnimation"), UnitType::POWER_DOWN);

	Vector2D middle = Vector2D(400, 300);
	mpSnake = new Snake(mpAnimationManager->getAnimation("snakeHeadAnimation"), mpAnimationManager->getAnimation("snakeTailAnimation"), middle, up);

	mpCourFont = new Font(ASSET_PATH, mpFileData->FONT_FILE_NAME, 20);
	mpAureFont = new Font((CUSTOM_ASSET_PATH + "Aurebesh\\"), mpFileData->CUSTOM_FONT_FILE_NAME, 20);

	mpHUD = new HeadsUpDisplay(mpCourFont);

	mpAudio->addSound((CUSTOM_ASSET_PATH + mpFileData->AUDIO_BUTTON_FILE).c_str());
	mpAudio->addSound((CUSTOM_ASSET_PATH + mpFileData->AUDIO_FOOD_FILE).c_str());
	mpAudio->addSound((CUSTOM_ASSET_PATH + mpFileData->AUDIO_EXPLOSION_FILE).c_str());
	mpAudio->addSound((CUSTOM_ASSET_PATH + mpFileData->AUDIO_POWERUP_FILE).c_str());

	mpLevelLoader->addLevel("testLevel.txt");
	mpLevelLoader->addLevel("Level1.txt");
	mpLevelLoader->addLevel("Level2.txt");
	mpLevelLoader->loadLevel(0,mpWallManager,mpPickUpManager,mpSnake,mpGraphicsBufferManager,mpGhostManager,mpAnimationManager);

	swapLanguage();
}
void Game::input()
{
	//mpInputSystem->updateKeyboardAndMouseState();
	mpInputSystem->update();
}
void Game::swapLanguage()
{
	if (mActiveLanguage <= 0 || mActiveLanguage >= 4)
	{
		mActiveLanguage = 1;
	}
	switch (mActiveLanguage)
	{
		case 1:
		{
			mpHUD->loadLanguage("English.txt");
			mpHUD->setFont(mpCourFont);
			mIsAurebesh = false;
			break;
		}
		case 2:
		{
			mpHUD->loadLanguage("Spanish.txt");
			mpHUD->setFont(mpCourFont);
			mIsAurebesh = false;
			break;
		}
		case 3:
		{
			mpHUD->loadLanguage("French.txt");
			mpHUD->setFont(mpCourFont);
			mIsAurebesh = false;
			break;
		}
	}
	mActiveLanguage++;
}
void Game::incrementDifficulty()
{
	switch (mDifficulty)
	{
	case EASY:
		mDifficulty = GameDifficulty::MEDIUM;
		break;
	case MEDIUM:
		mDifficulty = GameDifficulty::HARD;
		break;
	case HARD:
		mDifficulty = GameDifficulty::EASY;
		break;
	default:
		break;
	}
}
void Game::update(float deltaTime)
{	
	if (mGameState == GameState::RUNNING)
	{
		//difficultyCheck();
		mpPickUpManager->spawnPickUps(mpWallManager);
		mpWallManager->UpdateAllUnits(deltaTime);
		mpSnake->updateSnake(deltaTime);
		mpPickUpManager->UpdateAllUnits(deltaTime);
		mpGhostManager->updateGhost(deltaTime);
		mpSnake->checkCollision(mpSnake->getSnakeHead());
		mpWallManager->checkCollision(mpSnake->getSnakeHead());
		mpPickUpManager->checkCollision(mpSnake->getSnakeHead());
		mpGhostManager->checkCollision(mpSnake->getSnakeHead());
		mpLevelLoader->incrementLevel();
		mpLevelLoader->incrementTime(deltaTime);
	}
	if (mGameState == GameState::PAUSED)
	{
		mpClickableButtonManager->UpdateAllUnits(deltaTime);
	}
}
void Game::draw(float deltaTime)
{
	mpGraphicsSystem->clearFrame();
	if (mGameState == GameState::RUNNING)
	{
		float adjustScale = 1.25f;
		float targetTime = (deltaTime / 1000);
		float frameRate = 1 / targetTime;

		mpWallManager->drawAllUnits(mpGraphicsSystem);
		mpSnake->drawAllUnits(mpGraphicsSystem);
		mpGhostManager->drawAllUnits(mpGraphicsSystem);
		mpPickUpManager->drawAllUnits(mpGraphicsSystem,adjustScale);
		mpHUD->drawHUD(mpGraphicsSystem, mpLevelLoader->getScore(), mpLevelLoader->getTime(), frameRate);
	}
	else if(mGameState == GameState::PRE_GAME)
	{
		drawStartScreen();
	}
	else if (mGameState == GameState::POST_GAME)
	{
		drawEndScreen();
	}
	else if (mGameState == GameState::PAUSED)
	{
		drawPauseScreen();
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
UnitManager* Game::getUnitManager()
{
	return mpWallManager;
}
UnitManager* Game::getClickableManager()
{
	return mpClickableButtonManager;
}
LevelLoader* Game::getLevelLoader()
{
	return mpLevelLoader;
}
Audio* Game::getAudioManager()
{
	return mpAudio;
}
FileData* Game::getFileData()
{
	return mpFileData;
}
void Game::setGameState(GameState newState)
{
	mGameState = newState;
}
void Game::stopGame()
{
	setGameState(GameState::GAME_END);
}
void Game::startGame()
{
	setGameState(GameState::RUNNING);
}
void Game::pauseGame()
{
	if (mGameState != GameState::PAUSED)
	{
		setGameState(GameState::PAUSED);
	}
	else if (mGameState == GameState::PAUSED)
	{
		setGameState(GameState::RUNNING);
	}
}
void Game::endGame()
{
	setGameState(GameState::GAME_END);
}
void Game::drawStartScreen()
{
	HudText data;
	Vector2D middle = Vector2D(400, 300);
	Color white = Color(255, 255, 255, 0);
	//mpGraphicsSystem->draw(mpGraphicsBufferManager->getGraphicsBuffer("blackScreen"), ORIGIN);
	if (mIsAurebesh)
	{
		mpGraphicsSystem->writeText(mpAureFont, middle, white, mpHUD->getText()->mPause);
	}
	else
	{
		mpGraphicsSystem->writeText(mpCourFont, middle, white, mpHUD->getText()->mPause);
	}
}
void Game::drawEndScreen()
{
	HudText data;
	Vector2D middle = Vector2D(400, 300);
	Color white = Color(255, 255, 255, 0);
	//mpGraphicsSystem->draw(mpGraphicsBufferManager->getGraphicsBuffer("blackScreen"), ORIGIN);
	if (mIsAurebesh)
	{
		mpGraphicsSystem->writeText(mpAureFont, middle, white, mpHUD->getText()->mDeath);
	}
	else 
	{
		mpGraphicsSystem->writeText(mpCourFont, middle, white, mpHUD->getText()->mDeath);
	}
}
void Game::drawPauseScreen()
{
	Color white = Color(255, 255, 255, 0);
	mpClickableButtonManager->drawAllUnits(mpGraphicsSystem);
	for (auto i:mpClickableButtonManager->getUnitVector())
	{
		ClickableButton* tempButton = dynamic_cast<ClickableButton*>(i);
		Clickables type = tempButton->getButtonType();
		Vector2D tempPos = i->getUnitPosition();
		switch (int(type))
		{
			case START:
			{
				tempPos += Vector2D(+110, +20);
				mpGraphicsSystem->writeText(mpCourFont, tempPos, white, mpHUD->getText()->mStart);
				break;
			}
			case SAVE:
			{
				tempPos += Vector2D(+110, +20);
				mpGraphicsSystem->writeText(mpCourFont, tempPos, white, mpHUD->getText()->mSave);
				break;
			}
			case LOAD:
			{
				tempPos += Vector2D(+110, +20);
				mpGraphicsSystem->writeText(mpCourFont, tempPos, white, mpHUD->getText()->mLoad);
				break;
			}
			case LANGUAGE:
			{
				if (mActiveLanguage <= 0 || mActiveLanguage >= 4)
				{
					mActiveLanguage = 1;
				}
				else
				{
					switch (mActiveLanguage)
					{
						case 1:
						{
							tempPos += Vector2D(+190, +20);
							mpGraphicsSystem->writeText(mpCourFont, tempPos, white, mpHUD->getText()->mEng);
							break;
						}
						case 2:
						{
							tempPos += Vector2D(+160, +20);
							mpGraphicsSystem->writeText(mpCourFont, tempPos, white, mpHUD->getText()->mSpa);
							break;
						}
						case 3:
						{
							tempPos += Vector2D(+160, +20);
							mpGraphicsSystem->writeText(mpCourFont, tempPos, white, mpHUD->getText()->mFre);
							break;
						}
					}
				}
				break;
			}
			case DIFFICULTY:
			{
				switch (mDifficulty)
				{
				case EASY:
					{
						tempPos += Vector2D(+110, +20);
						mpGraphicsSystem->writeText(mpCourFont, tempPos, white, mpHUD->getText()->mEasy);
						break;
					}
					case MEDIUM:
					{
						tempPos += Vector2D(+110, +20);
						mpGraphicsSystem->writeText(mpCourFont, tempPos, white, mpHUD->getText()->mMedium);
						break;
					}
					case HARD:
					{
						tempPos += Vector2D(+110, +20);
						mpGraphicsSystem->writeText(mpCourFont, tempPos, white, mpHUD->getText()->mHard);
						break;
					}
				}
				break;
			}
			case QUIT:
			{
				tempPos += Vector2D(+110, +20);
				mpGraphicsSystem->writeText(mpCourFont, tempPos, white, mpHUD->getText()->mQuit);
				break;
			}
		}
	}
}
void Game::restartGame()
{
	setGameState(GameState::PRE_GAME);
}
void Game::difficultyCheck()
{
	switch (mDifficulty)
	{
	case EASY:
		mpGhostManager->changeMovementScalar(1.25);
		mpSnake->changeMovementScalar(1.0);
		break;
	case MEDIUM:
		mpGhostManager->changeMovementScalar(1.0);
		mpSnake->changeMovementScalar(1.0);
		break;
	case HARD:
		mpGhostManager->changeMovementScalar(.25);
		mpSnake->changeMovementScalar(.75);
		break;
	default:
		break;
	}
}

void Game::loadAssets(std::string fileName)
{
	ifstream input;
	input.open(ASSET_DATA_PATH + fileName);
	while (!input.eof())
	{

		string a;
		input >> a;
		if (a == "files")
		{
			while (a != "endOfFiles")
			{
				input >> a;
				if (a == "player")
				{
					string temp;
					input >> temp;
					mpFileData->SNAKE_HEAD_FILE_NAME = temp;
				}
				if (a == "snakeEnd")
				{
					string temp;
					input >> temp;
					mpFileData->SNAKE_TAIL_FILE_NAME = temp;
				}
				if (a == "food")
				{
					string temp;
					input >> temp;
					mpFileData->FOOD_FILE_NAME = temp;
				}
				if (a == "wall")
				{
					string temp;
					input >> temp;
					mpFileData->WALL_FILE_NAME = temp;
				}
				if (a == "pwr")
				{
					string temp;
					input >> temp;
					mpFileData->POWER_UP_FILE_NAME = temp;
				}
				if (a == "test")
				{
					string temp;
					input >> temp;
					mpFileData->POWER_DOWN_FILE_NAME = temp;
				}
				if (a == "black")
				{
					string temp;
					input >> temp;
					mpFileData->BLACK_SCREEN = temp;
				}
				if (a == "background")
				{
					string temp;
					input >> temp;
					mpFileData->GREY_BACKGROUND = temp;
				}
				if (a == "start")
				{
					string temp;
					input >> temp;
					mpFileData->START_BUTTON = temp;
				}
				if (a == "exit")
				{
					string temp;
					input >> temp;
					mpFileData->EXIT_BUTTON = temp;
				}
				if (a == "save")
				{
					string temp;
					input >> temp;
					mpFileData->SAVE_BUTTON = temp;
				}
				if (a == "load")
				{
					string temp;
					input >> temp;
					mpFileData->LOAD_BUTTON = temp;
				}
				if (a == "language")
				{
					string temp;
					input >> temp;
					mpFileData->LANGUAGE_BUTTON = temp;
				}
				if (a == "ghost")
				{
					string temp;
					input >> temp;
					mpFileData->GHOST_FILENAME = temp;
				}
			}
		}
		if (a == "sounds")
		{
			while (a != "endOfSounds")
			{
				input >> a;
				if (a == "button")
				{
					string temp;
					input >> temp;
					mpFileData->AUDIO_BUTTON_FILE = temp;
				}
				if (a == "food")
				{
					string temp;
					input >> temp;
					mpFileData->AUDIO_FOOD_FILE = temp;
				}
				if (a == "death")
				{
					string temp;
					input >> temp;
					mpFileData->AUDIO_EXPLOSION_FILE = temp;
				}
				if (a == "pwr")
				{
					string temp;
					input >> temp;
					mpFileData->AUDIO_POWERUP_FILE = temp;
				}
			}
		}
		if (a == "deanFiles")
		{
			while (a != "endOfDeanFiles")
			{
				input >> a;
				if (a == "woods")
				{
					string temp;
					input >> temp;
					mpFileData->WOODS_FILE_NAME = temp;
				}
				if (a == "smurf")
				{
					string temp;
					input >> temp;
					mpFileData->SMURF_FILE_NAME = temp;
				}
				if (a == "dean")
				{
					string temp;
					input >> temp;
					mpFileData->DEAN_FILE_NAME = temp;
				}
			}
		}
		if (a == "fonts")
		{
			while (a != "endOfFonts")
			{
				input >> a;
				if (a == "cour")
				{
					string temp;
					input >> temp;
					mpFileData->FONT_FILE_NAME = temp;
				}
				if (a == "aure")
				{
					string temp;
					input >> temp;
					mpFileData->CUSTOM_FONT_FILE_NAME = temp;
				}
			}
		}
	}
	input.close();
}
