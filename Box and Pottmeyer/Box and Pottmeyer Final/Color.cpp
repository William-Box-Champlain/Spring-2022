#include "Color.h"
Color::Color() 
{
	this->mColor.r = 0;
	this->mColor.r = 0;
	this->mColor.r = 0;
}
Color::Color(int red, int green, int blue)
{
	this->mColor.r = red;
	this->mColor.r = green;
	this->mColor.r = blue;
}
Color::Color(int red, int green, int blue, int opacity) 
{
	this->mColor.r = red;
	this->mColor.r = green;
	this->mColor.r = blue;
	this->mColor.a = opacity;
}
SDL_Color Color::getColor()
{
	return mColor;
}