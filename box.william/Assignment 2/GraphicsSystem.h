#include <allegro5/allegro.h>
#include <Vector2D.h>
#include <string>
#include "Color.h"
#include "Font.h"
#include "Sprite.h"
#include "GraphicsBuffer.h"
#include <Trackable.h>
#pragma once
class GraphicsSystem : public Trackable
{
public:
	GraphicsSystem();
	~GraphicsSystem();
	void graphicsSystemInit(int width, int height);
	void graphicsSystemCleanUp();
	int getHeight();
	int getWidth();
	ALLEGRO_BITMAP* getBackBuffer();
	void flip();
	void draw(Vector2D spritePosition, Sprite* spriteToDraw, float spriteScale = 1.0f, float spriteScaleY = 1.0f);
	void draw(GraphicsBuffer* graphicsBufferToDraw, Vector2D graphicsBufferPosition, float spriteScaleX = 1.0f, float spriteScaleY = 1.0f);
	void draw(GraphicsBuffer* graphicsBufferToDrawOn, Vector2D spritePosition, Sprite* spriteToDraw, float spriteScaleX = 1.0f, float spriteScaleY = 1.0f);
	void writeText(Font* fontToWriteWith, Vector2D fontPosition, Color fontColor, std::string stringToDraw);
	void saveBuffer(GraphicsBuffer* graphicsBufferToSave, std::string fileName);
private:
	int mWidth;
	int mHeight;
	ALLEGRO_DISPLAY* mGraphicsSystemDisplay;
	ALLEGRO_BITMAP* mGraphicsSystemBackBuffer;
};