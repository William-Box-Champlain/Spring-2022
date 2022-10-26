#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <string>
#include <Trackable.h>
#pragma once
class Font : public Trackable
{
public:
	Font(std::string filePath, std::string fontName, int fontSize, int fontFlags);
	~Font();
	int getSize();
private:
	ALLEGRO_FONT* getFont();
	ALLEGRO_FONT* mFont;
	int mFontSize;

	friend class GraphicsSystem;
};