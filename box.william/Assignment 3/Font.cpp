#include "Font.h"
Font::Font(std::string filePath, std::string fontName, int fontSize, int fontFlags) 
{
	this->mFontSize = fontSize;
	this->mFont = al_load_ttf_font((filePath + fontName).c_str(), fontSize, fontFlags);
}
Font::~Font() 
{
	al_destroy_font(mFont);
}
int Font::getSize() 
{
	return mFontSize;
}
ALLEGRO_FONT* Font::getFont() 
{
	return mFont;
}