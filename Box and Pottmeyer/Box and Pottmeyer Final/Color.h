#include <SDL.h>
//#include <SDL_image.h>
#include <Trackable.h>
#pragma once
class Color : public Trackable
{
public:
	Color();
	Color(int red, int green, int blue);
	Color(int red, int green, int blue, int opacity);
private:
	SDL_Color getColor();
	SDL_Color mColor;

	friend class GraphicsSystem;
	friend class GraphicsBuffer;
};