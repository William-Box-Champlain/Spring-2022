/*
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
*/
#include <SDL.h>
#include <SDL_ttf.h>
#include <string>
#include <Trackable.h>
#pragma once
class Font : public Trackable
{
public:
	Font(std::string filePath, std::string fontName, int fontSize);
	~Font();
	int getSize();
private:
	TTF_Font* getFont();
	TTF_Font* mFont;
	int mFontSize;

	friend class GraphicsSystem;
};