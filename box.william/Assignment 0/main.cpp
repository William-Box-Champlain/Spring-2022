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

using namespace std;

int main()
{
	PerformanceTracker* pPerformanceTracker = new PerformanceTracker;

	const string INIT_TRACKER_NAME = "init";
	const string DRAW_TRACKER_NAME = "draw";
	const string WAIT_TRACKER_NAME = "wait";


	if (!al_init())
	{
		cout << "error initting Allegro\n";
		system("pause");
		return 1;
	}
	if (!al_init_image_addon())
	{
		cout << "error - Image Add-on not initted\n";
		system("pause");
		return 1;
	}
	if (!al_init_font_addon())
	{
		cout << "error - Font Add-on not initted\n";
		system("pause");
		return 1;
	}
	if (!al_init_ttf_addon())
	{
		cout << "error - TTF Add-on not initted\n";
		system("pause");
		return 1;
	}
	if (!al_init_primitives_addon())
	{
		cout << "error - primitives Add-on not initted\n";
		system("pause");
		return 1;
	}
	if (!al_install_audio())
	{
		cout << "error - Audio Add-on not initted\n";
		system("pause");
		//return 1;
	}
	if (!al_init_acodec_addon())
	{
		cout << "error - Audio Codec Add-on not initted\n";
		system("pause");
		//return 1;
	}
	if (!al_reserve_samples(1))
	{
		cout << "error - samples not reserved\n";
		system("pause");
		//return 1;
	}


	const int DISP_WIDTH = 800;
	const int DISP_HEIGHT = 600;

	const string ASSET_PATH = "..\\..\\common\\assets\\";
	const string BACKGROUND_FILENAME = "axamer-lizum.png";
	const string QUIMBY_FILENAME = "mayor_quimby.png";
	const string FONT_FILENAME = "cour.ttf";
	const int FONT_SIZE = 24;
	const string SAMPLE_FILENAME = "clapping.wav";
	const double SLEEP_TIME = 5.0;

	ALLEGRO_DISPLAY* display = al_create_display(DISP_WIDTH, DISP_HEIGHT);
	assert(display);

	ALLEGRO_BITMAP* bitmap = al_load_bitmap((ASSET_PATH + BACKGROUND_FILENAME).c_str());
	assert(bitmap);
	ALLEGRO_BITMAP* quimby = al_load_bitmap((ASSET_PATH + QUIMBY_FILENAME).c_str());
	assert(quimby);
	ALLEGRO_BITMAP* memMap = al_create_bitmap(400,300);
	assert(memMap);


	ALLEGRO_FONT *cour_font = al_load_ttf_font((ASSET_PATH + FONT_FILENAME).c_str(), FONT_SIZE, 0);
	assert(cour_font);

	const ALLEGRO_COLOR WHITE = al_map_rgb(255, 255, 255);
	const ALLEGRO_COLOR BLACK = al_map_rgb(0, 0, 0);
	const ALLEGRO_COLOR BLACK_TRANSPARENT = al_map_rgba(0, 0, 0, 200);
	const ALLEGRO_COLOR PURPLE = al_map_rgb(128, 64, 212);

	//make memMap a color
	//ALLEGRO_BITMAP* oldBitmap = al_get_target_bitmap();
	//al_set_target_bitmap(memMap);
	//al_clear_to_color(PURPLE);
	//al_set_target_bitmap(al_get_backbuffer(display));
	//al_draw_filled_triangle(50, 50, 150, 50, 50, 300, WHITE);
	//al_set_target_bitmap(oldBitmap);


	ALLEGRO_SAMPLE* sample = al_load_sample((ASSET_PATH + SAMPLE_FILENAME).c_str());
	assert(sample);

	al_play_sample(sample, 1.0f, ALLEGRO_AUDIO_PAN_NONE, 1.0f, ALLEGRO_PLAYMODE_LOOP, nullptr);

	const int CIRCLE_RADIUS = 150;
	const int LOC1_X = 400;
	const int LOC1_Y = 300;
	const int LOC2_X = 200;
	const int LOC2_Y = 500;
	const int LOC3_X = 500;
	const int LOC3_Y = 400;
	int sourceWidth = al_get_bitmap_width(quimby);
	int sourceHeight = al_get_bitmap_height(quimby);
	const float SCALE_FACTOR = 0.75f;

	bool keepRunning = true;
	Timer timer;

	//draw stuff
	al_clear_to_color(PURPLE);

	al_draw_bitmap(bitmap, 0, 0, 0);


	al_draw_filled_circle(LOC1_X, LOC1_Y, CIRCLE_RADIUS, BLACK);
	al_draw_text(cour_font, WHITE, LOC1_X, LOC1_Y, ALLEGRO_ALIGN_CENTER, "Welcome to Allegro!");

	al_draw_filled_circle(LOC2_X, LOC2_Y, CIRCLE_RADIUS, BLACK_TRANSPARENT);
	al_draw_text(cour_font, PURPLE, LOC2_X, LOC2_Y, ALLEGRO_ALIGN_CENTER, "Welcome to Allegro!");

	al_draw_scaled_bitmap(quimby, 0, 0, sourceWidth, sourceHeight, LOC3_X, LOC3_Y, sourceWidth*SCALE_FACTOR, sourceHeight*SCALE_FACTOR, 0);

	//al_draw_bitmap(memMap, 200, 150, 0);

	//show what you have drawn
	al_flip_display();



	timer.sleep(5000.0);

	pPerformanceTracker->stopTracking("loop");
	//cout << "Frame Took:" << pPerformanceTracker->getElapsedTime("loop") << " ms" << endl;

	pPerformanceTracker->clearTracker("loop");

	al_destroy_sample(sample);
	al_destroy_font(cour_font);
	al_destroy_bitmap(bitmap);
	al_destroy_bitmap(quimby);
	al_destroy_bitmap(memMap);
	al_destroy_display(display);

	delete pPerformanceTracker;
	MemoryTracker::getInstance()->reportAllocations(cout);

	system("pause");
	return 0;
}