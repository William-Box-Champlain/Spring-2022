#include "Color.h"
Color::Color() 
{
	this->mColor = al_map_rgb(0, 0, 0);
}
Color::Color(int red, int green, int blue)
{
	this->mColor = al_map_rgb(red, green, blue);
}
Color::Color(int red, int green, int blue, int opacity) 
{
	this->mColor = al_map_rgba(red, green, blue, opacity);
}
ALLEGRO_COLOR Color::getColor() 
{
	return mColor;
}