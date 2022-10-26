//#include <allegro5/allegro.h>
#include <SDL.h>
//#include <SDL_image.h>
#include <string>
#include "Color.h"
#include <Trackable.h>
#pragma once
class GraphicsBuffer : public Trackable
{
public:
	GraphicsBuffer(std::string filePath, std::string fileName);
	GraphicsBuffer(std::string completeFilePath);
	GraphicsBuffer(int width, int height);
	~GraphicsBuffer();
	int getHeight();
	int getWidth();
	void setGraphicsBufferToColor(Color newColor);

private:
	SDL_Surface* getGraphicsBufferBitMap();
	SDL_Surface* mGraphicsBufferBitMap;
	
	bool mOwnsGraphicsBuffer;

	friend class GraphicsSystem;
};