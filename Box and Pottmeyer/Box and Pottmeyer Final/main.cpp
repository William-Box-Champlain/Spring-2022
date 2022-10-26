//#include <allegro5/allegro.h>
//#include <allegro5/allegro_font.h>
//#include <allegro5/allegro_ttf.h>
//#include <allegro5/allegro_audio.h>
//#include <allegro5/allegro_acodec.h>
//#include <allegro5/allegro_image.h>
//#include <allegro5/allegro_primitives.h>
#include <SDL.h>
#undef main

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
#include "Audio.h"

using namespace std;

int main()
{
	PerformanceTracker* pPerformanceTracker = new PerformanceTracker;

	//Audio test stuff
	/*string temp = "..\\..\\Box and Pottmeyer\\Box and Pottmeyer Final\\Assets\\Explosion.wav";
	Audio* a = new Audio();
	a->addSound(temp.c_str());
	while (true)
	{
		a->playSound(0);
	}
	a->playSound(0);
	delete a;
	a = nullptr;*/
	//Audio test stuff

	//Game Loop Stuff
	Game::createGame();
	Game* pGame = Game::getGame();

	pGame->gameSystemsInitializer();
	pGame->gameLoop();

	//pGame->gameCleanUp(); //we don't need to do this, we delete pGame 1 line later.

	delete pGame;
	delete pPerformanceTracker;
	//Game Loop Stuff

	MemoryTracker::getInstance()->reportAllocations(cout);

	//TTF_Quit();
	//SDL_Quit();
	system("pause");
	return 0;
}