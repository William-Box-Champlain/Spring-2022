#include <allegro5/allegro.h>
#include <string>
#include "Color.h"
#include <Trackable.h>
#pragma once
class GraphicsBuffer : public Trackable
{
public:
	GraphicsBuffer(std::string filePath, std::string fileName);
	GraphicsBuffer(int width, int height);
	~GraphicsBuffer();
	int getHeight();
	int getWidth();
	void setGraphicsBufferToColor(Color newColor);

private:
	ALLEGRO_BITMAP* getGraphicsBufferBitMap();
	ALLEGRO_BITMAP* mGraphicsBufferBitMap;
	
	friend class GraphicsSystem;
};