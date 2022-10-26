#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <iostream>
#include <Trackable.h>

#pragma once
class AllegroInitializer : public Trackable
{
public:
	AllegroInitializer();
	void Initialize();
private:

};