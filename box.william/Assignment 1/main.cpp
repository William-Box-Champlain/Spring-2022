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

using namespace std;

int main()
{
	srand(time(NULL));

	PerformanceTracker* pPerformanceTracker = new PerformanceTracker;

	const string INIT_TRACKER_NAME = "init";
	const string DRAW_TRACKER_NAME = "draw";
	const string WAIT_TRACKER_NAME = "wait";


	AllegroInitializer mainInit = AllegroInitializer();

	mainInit.Initialize();

	const int DISP_WIDTH = 800;
	const int DISP_HEIGHT = 600;

	const string ASSET_PATH = "..\\..\\common\\assets\\";
	const string BACKGROUND_FILENAME = "steps.png";
	const string QUIMBY_FILENAME = "mayor_quimby.png";
	const string SMURF_FILENAME = "smurf_sprites.png";
	const string FONT_FILENAME = "cour.ttf";
	const int FONT_SIZE = 24;
	const string SAMPLE_FILENAME = "clapping.wav";
	const double SLEEP_TIME = 5.0;

	GraphicsSystem* display = new GraphicsSystem();
	display->graphicsSystemInit(DISP_WIDTH, DISP_HEIGHT);
	assert(display);

	GraphicsBuffer* steps = new GraphicsBuffer(ASSET_PATH, BACKGROUND_FILENAME);
	assert(steps);
	GraphicsBuffer* quimby = new GraphicsBuffer(ASSET_PATH, QUIMBY_FILENAME);
	assert(quimby);
	GraphicsBuffer* smurf = new GraphicsBuffer(ASSET_PATH, SMURF_FILENAME);
	GraphicsBuffer* memMap = new GraphicsBuffer(400, 300);
	assert(memMap);
	GraphicsBuffer* redMap = new GraphicsBuffer(400, 300);

	Vector2D quimbyOrigin = Vector2D(0, 0);
	Vector2D quimbyColumnsAndRows = Vector2D(1,1);
	Sprite* quimbySprite = new Sprite(quimby, quimbyOrigin, quimbyColumnsAndRows);

	Vector2D smurfOrigin = Vector2D(0, 0);
	Vector2D smurfColumnsAndRows = Vector2D(4, 4);
	Sprite* smurfSprite = new Sprite(smurf, smurfOrigin, smurfColumnsAndRows);

	Font* courFont = new Font(ASSET_PATH, FONT_FILENAME, FONT_SIZE, 0);

	const Color WHITE(255, 255, 255);
	const Color BLACK(0, 0, 0);
	const Color BLACK_TRANSPARENT(0, 0, 0, 200);
	const Color PURPLE(128,64,212);

	redMap->setGraphicsBufferToColor(PURPLE);

	//make memMap a color
	//ALLEGRO_BITMAP* oldBitmap = al_get_target_bitmap();
	//al_set_target_bitmap(memMap);
	//al_clear_to_color(PURPLE);
	//al_set_target_bitmap(al_get_backbuffer(display));
	//al_draw_filled_triangle(50, 50, 150, 50, 50, 300, WHITE);
	//al_set_target_bitmap(oldBitmap);

	//ALLEGRO_SAMPLE* sample = al_load_sample((ASSET_PATH + SAMPLE_FILENAME).c_str());
	//assert(sample);

	//al_play_sample(sample, 1.0f, ALLEGRO_AUDIO_PAN_NONE, 1.0f, ALLEGRO_PLAYMODE_LOOP, nullptr);

	const int CIRCLE_RADIUS = 150;
	const int LOC1_X = 400;
	const int LOC1_Y = 300;
	const int LOC2_X = 200;
	const int LOC2_Y = 500;
	const int LOC3_X = 500;
	const int LOC3_Y = 400;
	int sourceWidth = quimby->getWidth();
	int sourceHeight = quimby->getHeight();
	const float SCALE_FACTOR = 0.75f;

	bool keepRunning = true;
	Timer timer;

	//draw stuff
	//al_clear_to_color(PURPLE);

	//al_draw_bitmap(bitmap, 0, 0, 0);

	Vector2D origin = Vector2D(0, 0);
	display->draw(steps, origin);
	//display->draw(redMap, origin, quimbySprite);
	display->draw(redMap, origin);

	//Draw quimby at location 3.
	Vector2D quimbyPosition = Vector2D(LOC3_X, LOC3_Y);
	display->draw(quimbyPosition, quimbySprite);

	//Draw smurfs at random locations.
	int numberOfSmurfs = 16;
	for (int i = 0; i < 16; i++)
	{
		int randomPositionX = rand() % display->getWidth();
		int randomPositionY = rand() % display->getHeight();
		Vector2D smurfPosition = Vector2D(randomPositionX, randomPositionY);
		display->draw(smurfPosition, smurfSprite);
	}

	//al_draw_filled_circle(LOC1_X, LOC1_Y, CIRCLE_RADIUS, BLACK);
	//al_draw_text(cour_font, WHITE, LOC1_X, LOC1_Y, ALLEGRO_ALIGN_CENTER, "Welcome to Allegro!");

	//draw "Welcome to Allegro!" at location 1
	Vector2D textPosition1 = Vector2D(LOC1_X, LOC1_Y);
	display->writeText(courFont, textPosition1, WHITE, "Welcome to Allegro!");

	//al_draw_filled_circle(LOC2_X, LOC2_Y, CIRCLE_RADIUS, BLACK_TRANSPARENT);
	//al_draw_text(cour_font, PURPLE, LOC2_X, LOC2_Y, ALLEGRO_ALIGN_CENTER, "Welcome to Allegro!");
	
	//draw "Welcome to Allegro!" at location 2
	Vector2D textPosition2 = Vector2D(LOC2_X, LOC2_Y);
	display->writeText(courFont, textPosition2, PURPLE, "Welcome to Allegro!");

	//al_draw_scaled_bitmap(quimby, 0, 0, sourceWidth, sourceHeight, LOC3_X, LOC3_Y, sourceWidth*SCALE_FACTOR, sourceHeight*SCALE_FACTOR, 0);
		
	//display->Draw(memMap, origin);
	//al_draw_bitmap(memMap, 200, 150, 0);

	//show what you have drawn
	//al_flip_display();

	display->flip();

	timer.sleep(5000.0);

	pPerformanceTracker->stopTracking("loop");
	//cout << "Frame Took:" << pPerformanceTracker->getElapsedTime("loop") << " ms" << endl;

	pPerformanceTracker->clearTracker("loop");

	//al_destroy_sample(sample);
	//al_destroy_font(cour_font);
	//al_destroy_bitmap(bitmap);
	//al_destroy_bitmap(quimby);
	//al_destroy_bitmap(memMap);
	//al_destroy_display(display);

	delete pPerformanceTracker;
	MemoryTracker::getInstance()->reportAllocations(cout);

	system("pause");
	return 0;
}