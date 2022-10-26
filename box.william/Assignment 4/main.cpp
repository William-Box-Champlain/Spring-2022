#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>

#include <iostream>
#include <cassert>
#include <string>

#include <PerformanceTracker.h>
#include <MemoryTracker.h>
#include <Vector2D.h>
#include <Timer.h>

#include "AllegroInitializer.h"
#include "GraphicsBuffer.h"
#include "GraphicsSystem.h"
#include "Color.h"
#include "Font.h"
#include "Sprite.h"
#include "Unit.h"
#include "Animation.h"
#include "Game.h"
#include "InputSystem.h"

using namespace std;

int main()
{
	PerformanceTracker* pPerformanceTracker = new PerformanceTracker;

	Game::createGame();
	Game* pGame = Game::getGame();

	pGame->gameSystemsInitializer();
	pGame->gameLoop();

	//pGame->gameCleanUp();
	delete pGame;

	delete pPerformanceTracker;
	MemoryTracker::getInstance()->reportAllocations(cout);

	system("pause");
	return 0;
}