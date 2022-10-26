#include "Font.h"
Font::Font(std::string filePath, std::string fontName, int fontSize) 
{
	this->mFontSize = fontSize;
	this->mFont = TTF_OpenFont((filePath + fontName).c_str(), fontSize);
}
Font::~Font() 
{
	TTF_CloseFont(mFont);
}
int Font::getSize() 
{
	return mFontSize;
}
TTF_Font* Font::getFont()
{
	return mFont;
}