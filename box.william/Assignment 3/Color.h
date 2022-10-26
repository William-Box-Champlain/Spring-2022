#include <allegro5/allegro.h>
#include <Trackable.h>
#pragma once
class Color : public Trackable
{
public:
	Color();
	Color(int red, int green, int blue);
	Color(int red, int green, int blue, int opacity);
private:
	ALLEGRO_COLOR getColor();
	ALLEGRO_COLOR mColor;

	friend class GraphicsSystem;
	friend class GraphicsBuffer;
};