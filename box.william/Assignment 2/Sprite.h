#include <allegro5/allegro.h>
#include "GraphicsBuffer.h"
#include <Vector2D.h>
#include <Trackable.h>
#pragma once
class Sprite : public Trackable
{
public:
	Sprite(GraphicsBuffer* SpriteGraphicsBuffer, Vector2D SpriteSourceLocation, Vector2D SpriteWidthAndHeight);
	~Sprite();
	Vector2D getSpriteSourceLocation();
	int getSpriteWidth();
	int getSpriteHeight();
	GraphicsBuffer* getSpriteGraphicsBuffer();
private: 
	GraphicsBuffer* mSpriteGraphicsBuffer;
	Vector2D mSpriteSourceLocation;
	Vector2D mSpriteWidthAndHeight;
};